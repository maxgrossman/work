const CAPACITY = 3

const { query_contains_point, _remove_from_list } = require('./helpers');

function region(bounds, parent = null) {
    let r = {
        remove_data_point: function(i) {
            _remove_from_list(r.data, i);
        },
        parent: parent,
        bounds: bounds,
        contains: function(point) {
            return query_contains_point(bounds, point);
        },
        add: function(point) {
            // subdivide into regions,
            let i = 0;
            if (r.data.length  === CAPACITY) {
                r.subdivide()
                // when I subdivide, then I want to move my points into their new regions
                for (i = 0; i < r.data.length; i++) {
                    for (let j = 0; j < r.sub_regions.length; j++) {
                        if (r.sub_regions[j].add(r.data[i])) {
                            r.remove_data_point(i);
                            i--;
                            break;
                        }
                    }
                }
            }

            if (r.have_regions) {
                for (i = 0; i < r.sub_regions.length; i++) {
                    if (r.sub_regions[i].add(point))
                        return true;
                }
            } else if (r.contains(point)) {
                for (i = 0; i < r.data.length; i++) {
                    if (r.data[i][0] === point[0] && r.data[i][1] === point[1])
                        return false;
                }
                r.data.push(point);
                return true;
            }
            return false;
        },
        subdivide: function() {
            const mid_lng = (bounds[0] + bounds[2]) / 2,
                  mid_lat = (bounds[1] + bounds[3]) / 2;

            r.sub_regions.push(region([bounds[0],bounds[1],mid_lng,mid_lat], r));
            r.sub_regions.push(region([bounds[0],mid_lat,mid_lng,bounds[3]], r));
            r.sub_regions.push(region([mid_lng,mid_lat,bounds[2],bounds[3]], r));
            r.sub_regions.push(region([mid_lng,bounds[1],bounds[2],mid_lat], r));
            r.have_regions = true;
        },
        data: [],
        have_regions: false,
        sub_regions: [],
        in_bounds: function(query_bounds) {
            if (query_bounds[1] > r.bounds[3] || r.bounds[1] > query_bounds[3])
                return false;

            if (query_bounds[2] < r.bounds[0] || r.bounds[2] < query_bounds[0])
                return false;

            return true;
        },
        query: function(query_bounds, points_in_bounds) {
            if (!r.in_bounds(query_bounds))
                return;

            let i = 0;
            for (i = 0; i < r.sub_regions.length; i++) {
                r.sub_regions[i].query(query_bounds, points_in_bounds);
            }
            for (i = 0; i < r.data.length; i++) {
                if (query_contains_point(query_bounds, r.data[i])) {
                    points_in_bounds.push(r.data[i]);
                }
            }
        },
        contains_point: function(point) {
            for (let i = 0; i < r.data.length; i++) {
                if (r.data[i][0] === point[0] && r.data[i][1] === point[1]) {
                    return i;
                }
            }
            return -1;
        },
        collapse: function() {
            // if any region has data, i want to leave it alone.
            // if none have data, then that means i should collpase the subregions
            for (let i = 0; i < r.sub_regions.length; i++) {
                if (r.sub_regions[i].data.length)
                    return
            }
            r.sub_regions = [];
            r.have_regions = false;
        }
    };
    return r;
};


module.exports = function() {
    const root_region = region([-180,-90,180,90]);
    let   null_bounds = true;
    function _render(root, pointRenderFunc, regionRenderFunc, query_bounds = null, point_colors = [233,150,122,255]) {
        let i = 0;

        null_bounds = query_bounds === null;

        if (root.have_regions) {
            for (i = 0; i < root.sub_regions.length; ++i)
                _render(root.sub_regions[i], pointRenderFunc, regionRenderFunc);
        }

        if (!null_bounds && !root.in_bounds(query_bounds))
            return;

        regionRenderFunc(root.bounds);

        if (root.data.length == 0)
            return;

        for (i = 0; i < root.data.length; i++) {
            if (null_bounds || query_contains_point(query_bounds, root.data[i])) {
                pointRenderFunc(root.data[i], point_colors[0], point_colors[1], point_colors[2], point_colors[3]);
            }
        }
    }

    function _remove_point(root, point) {
        let index = -1
        if ((index = root.contains_point(point)) !== -1) {
            root.remove_data_point(index);
            if (root.parent && root.parent.have_regions)
                root.parent.collapse();

            return true;
        }

        if (root.have_regions) {
            for (index = 0; index < root.sub_regions.length; ++index) {
                if (_remove_point(root.sub_regions[index], point)) {
                    return true;
                }
            }
        }
    }

    let q = {
        root_region: root_region,
        add_point: root_region.add,
        remove_point: function(point) {
            return _remove_point(root_region, point);
        },
        render: function(pointRenderFunc, regionRenderFunc, query_bounds, point_colors = null) {
            _render(root_region, pointRenderFunc, regionRenderFunc, query_bounds, point_colors);
        },
        query: function(query_bounds) {
            const points_in_bounds = [];
            root_region.query(query_bounds, points_in_bounds);
            return points_in_bounds;
        }
    };
    return q;
};

