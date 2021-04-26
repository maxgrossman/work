import quadtree from './quadtree';
import { query_contains_point, _remove_from_list } from './helpers';

const POINT_COLORS = [255, 137, 137, 255];
let POINTS_TO_RENDER = 10000;

function debounce(func, wait) {
    let timeout;
    return function() {
        var context = this, args = arguments;
        var later = function() {
            timeout = null;
            func.apply(context, args);
        };
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
    }
}

window.addEventListener('DOMContentLoaded', (event) => {
    // document.getElementById('pointsintree').innerHTML = POINTS_TO_RENDER + ' points in quadtree';

    let Q = quadtree();
    let next_points = [];

    function all_query(bounds) {
        const points_in_bounds = [];
        for (let i = 0; i < next_points.length; i++) {
            if (query_contains_point(bounds, next_points[i])) {
                points_in_bounds.push(next_points[i])
            }
        }
        return points_in_bounds;
    }

    for (let i = 0; i < POINTS_TO_RENDER; i++) {
        next_points.push([
            Number((Math.random() * (180 - -180) + -180).toFixed(3)),
            Number((Math.random() * (90 - -90) + -90).toFixed(3))
        ])
        Q.add_point(next_points[i])
    }

    let canvas = document.getElementById("canvas");

    canvas.width  = 256 * 2;
    canvas.height = 256 * 2;

    let ctx = canvas.getContext("2d");
    let canvasData = ctx.createImageData(canvas.width, canvas.height);

    function get_pixel_index(x, y) {
        return (x + y * canvas.width) * 4;
    }

    function draw_pixel (x, y, r, g, b, a) {
        const index = get_pixel_index(x, y);
        canvasData.data[index] = r;
        canvasData.data[index + 1] = g;
        canvasData.data[index + 2] = b;
        canvasData.data[index + 3] = a;
    }

    // on zoom change change what the width,height are.

    const is_scale_x = canvas.width < canvas.height,
          scale = is_scale_x ? canvas.width : canvas.height;


    let zoom_scale = 1, zoom_step = zoom_scale / 20, step = 1,
        Q_min_lng = Q.root_region.bounds[0],
        Q_min_lat = Q.root_region.bounds[1],
        Q_max_lng = Q.root_region.bounds[2],
        Q_max_lat = Q.root_region.bounds[3],
        Q_width = Q_max_lng - Q_min_lng,
        Q_width_step = Math.round(Q_width * zoom_step),
        Q_height = Q_max_lat - Q_min_lat,
        Q_height_step = Math.round(Q_height * zoom_step),
        radius = 20,
        radius_in_pixels = Math.round((is_scale_x ? (radius / Q_width) : (radius / Q_height)) * scale);


    let lng, lat, last_coord = null, removed_points = [],
        last = new Float32Array(2 * (2 * radius_in_pixels) + 2 * (4 * radius_in_pixels));

    function _draw_line(xMin, yMin ,xMax ,yMax, line_funcs) {
        let y = yMax, x = xMin;

        let i = 0;
        for (; y < yMin; ++y) {
            for (; i < line_funcs.length; ++i)
                line_funcs[i](x, y);
         }

        for (; x < xMax ; ++x) {
            for (i = 0; i < line_funcs.length; ++i)
                line_funcs[i](x, y);
        }
        for (; y > yMax; --y) {
            for (i = 0; i < line_funcs.length; ++i)
                line_funcs[i](x, y);
        }
        for (; x > xMin; --x) {
            for (i = 0; i < line_funcs.length; ++i)
                line_funcs[i](x, y);
        }

        for (; y < yMin; ++y) {
            for (i = 0; i < line_funcs.length; ++i)
                line_funcs[i](x, y);
        }

    }

    function draw_line(bounds, line_funcs) {
        _draw_line(
            Math.round(((bounds[0] - Q_min_lng) / Q_width) * scale),
            Math.round(((Q_height - (bounds[1] - Q_min_lat)) / Q_height) * scale),
            Math.round(((bounds[2] - Q_min_lng) / Q_width) * scale),
            Math.round(((Q_height - (bounds[3] - Q_min_lat)) / Q_height) * scale),
            line_funcs
        );
    }

    function draw_point(point, r = 0, g = 0, b = 0, a = 255) {
        const pixel_x = Math.round(((point[0] - Q_min_lng) / Q_width) * scale),
              pixel_y = Math.round(((Q_height - (point[1] - Q_min_lat)) / Q_height) * scale);

        // crosshair
        draw_pixel(pixel_x - 1, pixel_y ,r, g, b, a);
        draw_pixel(pixel_x, pixel_y + 1,r, g, b, a);
        draw_pixel(pixel_x, pixel_y ,r, g, b, a);
        draw_pixel(pixel_x + 1, pixel_y ,r, g, b, a);
        draw_pixel(pixel_x, pixel_y - 1,r, g, b, a);
    }

    // midpoint circle drawing algorithm
    //https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
    function draw_circle(point_x, point_y, stroke_width, circle_radius, circle_func) {
        let x = circle_radius, y = 0, P = 1 - circle_radius, i = 0;

        if (circle_radius > 0) {
            for (; i < stroke_width; ++i) {
                circle_func((point_x + x + i), (point_y - y + i));
                circle_func((point_x + y + i), (point_y + x + i))
                circle_func((point_x - y + i), (point_y + y + i))
            }
        }

        while (x > y) {
            ++y;

            if (P <= 0) {
                P += + 2*y + 1;
            } else {
                --x;
                P += 2*y - 2*x + 1;
            }

            if (x < y)
                break;

            for (i = 0; i < stroke_width; ++i) {
                circle_func((point_x + x + i), (point_y + y + i));
                circle_func((point_x - x + i), (point_y + y + i));
                circle_func((point_x + x + i), (point_y - y + i));
                circle_func((point_x - x + i), (point_y - y + i));
            }

            if (x != y) {
                for (i = 0; i < stroke_width; ++i) {
                    circle_func((point_x + y + i), (point_y + x + i));
                    circle_func((point_x - y + i), (point_y + x + i));
                    circle_func((point_x + y + i), (point_y - x + i));
                    circle_func((point_x - y + i), (point_y - x + i));
                }
            }

        }
    }

    function draw(query_bounds, point_colors) {
        Q.render(
            draw_point,
            (bounds) => draw_line(bounds, [(x, y) => draw_pixel(x, y, 0,0,0, 100)]),
            query_bounds,
            point_colors
        )
        ctx.putImageData(canvasData, 0, 0);
    }

    draw();

    document.getElementById('zoomin').addEventListener('click', function(e) {
        if (step === 10)
            return;

        zoom_scale -= zoom_step;

        Q_min_lng += Q_width_step;
        Q_max_lng -= Q_width_step;
        Q_min_lat += Q_height_step;
        Q_max_lat -= Q_height_step;

        Q_width = Q_max_lng - Q_min_lng;
        Q_height = Q_max_lat - Q_min_lat;

        radius_in_pixels = Math.round((is_scale_x ? (radius / Q_width) : (radius / Q_height)) * scale),
        last = new Float32Array(2 * (2 * radius_in_pixels) + 2 * (4 * radius_in_pixels));

        for (let i = 0; i < canvasData.data.length; ++i)
            canvasData.data[i] = 255;

        ctx.putImageData(canvasData, 0, 0)

        // draw([Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS);

        draw([Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS)
        ++step;
    })

    document.getElementById('zoomout').addEventListener('click', function(e) {
        if (step === 1)
            return;

        zoom_scale += zoom_step;

        Q_min_lng -= Q_width_step;
        Q_max_lng += Q_width_step;
        Q_min_lat -= Q_height_step;
        Q_max_lat += Q_height_step;

        Q_width = Q_max_lng - Q_min_lng;
        Q_height = Q_max_lat - Q_min_lat;

        radius_in_pixels = Math.round((is_scale_x ? (radius / Q_width) : (radius / Q_height)) * scale),
        last = new Float32Array(2 * (2 * radius_in_pixels) + 2 * (4 * radius_in_pixels));

        for (let i = 0; i < canvasData.data.length; ++i)
            canvasData.data[i] = 255;

        ctx.putImageData(canvasData, 0, 0)

        draw([Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS);
        --step;
    })

    document.getElementById('numpoints').addEventListener('keyup', function(e) {
        const next_length = Number(e.target.value);
        if (Number.isNaN(next_length) || next_length === POINTS_TO_RENDER)
            return;

        POINTS_TO_RENDER = next_length;

        Q = quadtree();
        next_points = [];
        removed_points = [];

        let i = 0;
        for (; i < POINTS_TO_RENDER; i++) {
            next_points.push([
                Number((Math.random() * (180 - -180) + -180).toFixed(3)),
                Number((Math.random() * (90 - -90) + -90).toFixed(3))
            ])
            Q.add_point(next_points[i])
        }

        for (i = 0; i < canvasData.data.length; ++i)
            canvasData.data[i] = 255;

        ctx.putImageData(canvasData, 0, 0);
        draw(null, POINT_COLORS);
    })
    document.getElementById('searchradius').addEventListener('keyup', function(e) {
        const next_radius = Number(e.target.value);
        if (Number.isNaN(next_radius))
            return;

        // repaint the previos boudary
        for (let i = 0; i < last.length; ++i) // fill last in with what was there
            canvasData.data[last[i]] = 0;

        radius = next_radius;
        radius_in_pixels = Math.round((is_scale_x ? (radius / Q_width) : (radius / Q_height)) * scale),
        last = new Float32Array(2 * (2 * radius_in_pixels) + 2 * (4 * radius_in_pixels));
    })

    let pnts_qt = [], i = 0;
    canvas.addEventListener('mousemove', debounce(function(pnt) {
        let start;
        lng = ((pnt.offsetX / scale) * Q_width) + Q_min_lng;
        lat = (-1 * (((pnt.offsetY / scale) * Q_height) - Q_height)) + Q_min_lat;

        if (lng < Q_min_lng || Q_max_lng < lng || lat < Q_min_lat || 90 < Q_max_lat) {
            document.querySelector("#mouseloc").innerHTML = "Mouse location:";
            return;
        }

        document.querySelector("#mouseloc").innerHTML = "Mouse location: lng = " + lng.toFixed(3) + ", lat = " + lat.toFixed(3);

        const q_bounds = [lng - radius * 2, lat - radius, lng + radius * 2, lat + radius];

        start = new Date().getTime();
        pnts_qt = Q.query(q_bounds);
        document.querySelector("#qtpoints").innerHTML = "There are " + (pnts_qt.length || "no") + " quadtree points under this mouse. it took " + (new Date().getTime() - start) + ' ms';

        start = new Date().getTime();
        const pnts_arr = all_query(q_bounds)
        document.querySelector("#listpoints").innerHTML = "There are " + (pnts_arr.length || "no") + " quadtree points under this mouse. it took " + (new Date().getTime() - start) + ' ms';

        if (last_coord !== null) {
            i = 0;
            for (; i < last.length; ++i) { // fill last in with what was there
                canvasData.data[last[i]] = 0;
                canvasData.data[last[i] + 1] = 0;
                canvasData.data[last[i] + 2] = 0;
                canvasData.data[last[i] + 3] = 0;
            }

            draw([
                last_coord[0] - radius * 2,
                last_coord[1] - radius,
                last_coord[0] + radius * 2,
                last_coord[1] + radius
            ], POINT_COLORS)

            i = 0;
            draw_line([
                last_coord[0] - radius * 2,
                last_coord[1] - radius,
                last_coord[0] + radius * 2,
                last_coord[1] + radius
            ], [
                (x, y) => {
                    if (x > canvas.width || y > canvas.height || x < 0 || y < 0 )
                        return;
                    draw_pixel(x, y, 0, 0, 0, 255);;
                },
                (x, y) => { last[i] = get_pixel_index(x, y); ++i }
            ])

            for (let idx = 0; idx < removed_points.length; ++idx)
                draw_point(removed_points[idx], 0,0,255,255);
        }

        last_coord = [lng,lat];

        for (let i = 0; i < pnts_qt.length; ++i)
            draw_point(pnts_qt[i], 255, 0, 0, 255);

        ctx.putImageData(canvasData, 0, 0);
    }), 10)

    document.getElementById("removepoints").addEventListener('click', function(e) {
        e.preventDefault();

        if (next_points.length === 0)
            return;

        let num_points_to_remove = Number(document.getElementById('numremoves').value)

        if (Number.isNaN(num_points_to_remove))
            return;

        if (num_points_to_remove > next_points.length)
            num_points_to_remove = next_points.length

        let i = 0;
        while (i < num_points_to_remove && num_points_to_remove <= next_points.length) {
            const remove_index = Math.floor(Math.random() * Math.floor(next_points.length));
            const removed_point = next_points[remove_index];

            removed_points.push(removed_point);

            if (!Q.remove_point(removed_point))
                return;

            _remove_from_list(next_points, remove_index);

            // ctx.clearRect(0,0,canvas.width,canvas.height);

            draw([Q_min_lng, Q_min_lng, Q_min_lng + Q_width, Q_min_lat + Q_height], POINT_COLORS);

            for (let idx = 0; idx < removed_points.length; ++idx)
                draw_point(removed_points[idx], 0,0,255,255);

            ++i;
        }
        document.getElementById('pointsintree').innerHTML = next_points.length + ' points in quadtree';
        draw();
    })
});
