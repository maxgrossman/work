// modules are defined as an array
// [ module function, map of requires ]
//
// map of requires is short require name -> numeric require
//
// anything defined in a previous bundle is accessed via the
// orig method which is the require for previous bundles

(function(modules, cache, entry, globalName) {
  /* eslint-disable no-undef */
  var globalObject =
    typeof globalThis !== 'undefined'
      ? globalThis
      : typeof self !== 'undefined'
      ? self
      : typeof window !== 'undefined'
      ? window
      : typeof global !== 'undefined'
      ? global
      : {};
  /* eslint-enable no-undef */

  // Save the require from previous bundle to this closure if any
  var previousRequire =
    typeof globalObject.parcelRequire === 'function' &&
    globalObject.parcelRequire;
  // Do not use `require` to prevent Webpack from trying to bundle this call
  var nodeRequire =
    typeof module !== 'undefined' &&
    typeof module.require === 'function' &&
    module.require.bind(module);

  function newRequire(name, jumped) {
    if (!cache[name]) {
      if (!modules[name]) {
        // if we cannot find the module within our internal map or
        // cache jump to the current global require ie. the last bundle
        // that was added to the page.
        var currentRequire =
          typeof parcelRequire === 'function' && parcelRequire;
        if (!jumped && currentRequire) {
          return currentRequire(name, true);
        }

        // If there are other bundles on this page the require from the
        // previous one is saved to 'previousRequire'. Repeat this as
        // many times as there are bundles until the module is found or
        // we exhaust the require chain.
        if (previousRequire) {
          return previousRequire(name, true);
        }

        // Try the node require function if it exists.
        if (nodeRequire && typeof name === 'string') {
          return nodeRequire(name);
        }

        var err = new Error("Cannot find module '" + name + "'");
        err.code = 'MODULE_NOT_FOUND';
        throw err;
      }

      localRequire.resolve = resolve;
      localRequire.cache = {};

      var module = (cache[name] = new newRequire.Module(name));

      modules[name][0].call(
        module.exports,
        localRequire,
        module,
        module.exports,
        this
      );
    }

    return cache[name].exports;

    function localRequire(x) {
      return newRequire(localRequire.resolve(x));
    }

    function resolve(x) {
      return modules[name][1][x] || x;
    }
  }

  function Module(moduleName) {
    this.id = moduleName;
    this.bundle = newRequire;
    this.exports = {};
  }

  newRequire.isParcelRequire = true;
  newRequire.Module = Module;
  newRequire.modules = modules;
  newRequire.cache = cache;
  newRequire.parent = previousRequire;
  newRequire.register = function(id, exports) {
    modules[id] = [
      function(require, module) {
        module.exports = exports;
      },
      {},
    ];
  };

  globalObject.parcelRequire = newRequire;

  for (var i = 0; i < entry.length; i++) {
    newRequire(entry[i]);
  }

  if (entry.length) {
    // Expose entry point to Node, AMD or browser globals
    // Based on https://github.com/ForbesLindesay/umd/blob/master/template.js
    var mainExports = newRequire(entry[entry.length - 1]);

    // CommonJS
    if (typeof exports === 'object' && typeof module !== 'undefined') {
      module.exports = mainExports;

      // RequireJS
    } else if (typeof define === 'function' && define.amd) {
      define(function() {
        return mainExports;
      });

      // <script>
    } else if (globalName) {
      this[globalName] = mainExports;
    }
  }
})({"75eab32ba9741e29f14b7d8cdb09d849":[function(require,module,exports) {
var global = arguments[3];
var HMR_HOST = null;
var HMR_PORT = 1234;
var HMR_ENV_HASH = "d751713988987e9331980363e24189ce";
module.bundle.HMR_BUNDLE_ID = "3d0f651c9df67f9d2a44d145cfe25e02";
/* global HMR_HOST, HMR_PORT, HMR_ENV_HASH */

var OVERLAY_ID = '__parcel__error__overlay__';
var OldModule = module.bundle.Module;

function Module(moduleName) {
  OldModule.call(this, moduleName);
  this.hot = {
    data: module.bundle.hotData,
    _acceptCallbacks: [],
    _disposeCallbacks: [],
    accept: function (fn) {
      this._acceptCallbacks.push(fn || function () {});
    },
    dispose: function (fn) {
      this._disposeCallbacks.push(fn);
    }
  };
  module.bundle.hotData = null;
}

module.bundle.Module = Module;
var checkedAssets, assetsToAccept, acceptedAssets; // eslint-disable-next-line no-redeclare

var parent = module.bundle.parent;

if ((!parent || !parent.isParcelRequire) && typeof WebSocket !== 'undefined') {
  var hostname = HMR_HOST || (location.protocol.indexOf('http') === 0 ? location.hostname : 'localhost');
  var port = HMR_PORT || location.port;
  var protocol = location.protocol === 'https:' ? 'wss' : 'ws';
  var ws = new WebSocket(protocol + '://' + hostname + (port ? ':' + port : '') + '/');

  ws.onmessage = function (event) {
    checkedAssets = {};
    assetsToAccept = [];
    acceptedAssets = {};
    var data = JSON.parse(event.data);

    if (data.type === 'update') {
      // Remove error overlay if there is one
      removeErrorOverlay();
      let assets = data.assets.filter(asset => asset.envHash === HMR_ENV_HASH); // Handle HMR Update

      var handled = false;
      assets.forEach(asset => {
        var didAccept = asset.type === 'css' || hmrAcceptCheck(global.parcelRequire, asset.id);

        if (didAccept) {
          handled = true;
        }
      });

      if (handled) {
        console.clear();
        assets.forEach(function (asset) {
          hmrApply(global.parcelRequire, asset);
        });

        for (var i = 0; i < assetsToAccept.length; i++) {
          var id = assetsToAccept[i][1];

          if (!acceptedAssets[id]) {
            hmrAcceptRun(assetsToAccept[i][0], id);
          }
        }
      } else {
        window.location.reload();
      }
    }

    if (data.type === 'error') {
      // Log parcel errors to console
      for (let ansiDiagnostic of data.diagnostics.ansi) {
        let stack = ansiDiagnostic.codeframe ? ansiDiagnostic.codeframe : ansiDiagnostic.stack;
        console.error('🚨 [parcel]: ' + ansiDiagnostic.message + '\n' + stack + '\n\n' + ansiDiagnostic.hints.join('\n'));
      } // Render the fancy html overlay


      removeErrorOverlay();
      var overlay = createErrorOverlay(data.diagnostics.html);
      document.body.appendChild(overlay);
    }
  };

  ws.onerror = function (e) {
    console.error(e.message);
  };

  ws.onclose = function (e) {
    console.warn('[parcel] 🚨 Connection to the HMR server was lost');
  };
}

function removeErrorOverlay() {
  var overlay = document.getElementById(OVERLAY_ID);

  if (overlay) {
    overlay.remove();
    console.log('[parcel] ✨ Error resolved');
  }
}

function createErrorOverlay(diagnostics) {
  var overlay = document.createElement('div');
  overlay.id = OVERLAY_ID;
  let errorHTML = '<div style="background: black; opacity: 0.85; font-size: 16px; color: white; position: fixed; height: 100%; width: 100%; top: 0px; left: 0px; padding: 30px; font-family: Menlo, Consolas, monospace; z-index: 9999;">';

  for (let diagnostic of diagnostics) {
    let stack = diagnostic.codeframe ? diagnostic.codeframe : diagnostic.stack;
    errorHTML += `
      <div>
        <div style="font-size: 18px; font-weight: bold; margin-top: 20px;">
          🚨 ${diagnostic.message}
        </div>
        <pre>
          ${stack}
        </pre>
        <div>
          ${diagnostic.hints.map(hint => '<div>' + hint + '</div>').join('')}
        </div>
      </div>
    `;
  }

  errorHTML += '</div>';
  overlay.innerHTML = errorHTML;
  return overlay;
}

function getParents(bundle, id) {
  var modules = bundle.modules;

  if (!modules) {
    return [];
  }

  var parents = [];
  var k, d, dep;

  for (k in modules) {
    for (d in modules[k][1]) {
      dep = modules[k][1][d];

      if (dep === id || Array.isArray(dep) && dep[dep.length - 1] === id) {
        parents.push([bundle, k]);
      }
    }
  }

  if (bundle.parent) {
    parents = parents.concat(getParents(bundle.parent, id));
  }

  return parents;
}

function updateLink(link) {
  var newLink = link.cloneNode();

  newLink.onload = function () {
    if (link.parentNode !== null) {
      link.parentNode.removeChild(link);
    }
  };

  newLink.setAttribute('href', link.getAttribute('href').split('?')[0] + '?' + Date.now());
  link.parentNode.insertBefore(newLink, link.nextSibling);
}

var cssTimeout = null;

function reloadCSS() {
  if (cssTimeout) {
    return;
  }

  cssTimeout = setTimeout(function () {
    var links = document.querySelectorAll('link[rel="stylesheet"]');

    for (var i = 0; i < links.length; i++) {
      var absolute = /^https?:\/\//i.test(links[i].getAttribute('href'));

      if (!absolute) {
        updateLink(links[i]);
      }
    }

    cssTimeout = null;
  }, 50);
}

function hmrApply(bundle, asset) {
  var modules = bundle.modules;

  if (!modules) {
    return;
  }

  if (modules[asset.id] || !bundle.parent) {
    if (asset.type === 'css') {
      reloadCSS();
    } else {
      var fn = new Function('require', 'module', 'exports', asset.output);
      modules[asset.id] = [fn, asset.depsByBundle[bundle.HMR_BUNDLE_ID]];
    }
  } else if (bundle.parent) {
    hmrApply(bundle.parent, asset);
  }
}

function hmrAcceptCheck(bundle, id) {
  var modules = bundle.modules;

  if (!modules) {
    return;
  }

  if (!modules[id] && bundle.parent) {
    return hmrAcceptCheck(bundle.parent, id);
  }

  if (checkedAssets[id]) {
    return;
  }

  checkedAssets[id] = true;
  var cached = bundle.cache[id];
  assetsToAccept.push([bundle, id]);

  if (cached && cached.hot && cached.hot._acceptCallbacks.length) {
    return true;
  }

  return getParents(global.parcelRequire, id).some(function (v) {
    return hmrAcceptCheck(v[0], v[1]);
  });
}

function hmrAcceptRun(bundle, id) {
  var cached = bundle.cache[id];
  bundle.hotData = {};

  if (cached && cached.hot) {
    cached.hot.data = bundle.hotData;
  }

  if (cached && cached.hot && cached.hot._disposeCallbacks.length) {
    cached.hot._disposeCallbacks.forEach(function (cb) {
      cb(bundle.hotData);
    });
  }

  delete bundle.cache[id];
  bundle(id);
  cached = bundle.cache[id];

  if (cached && cached.hot && cached.hot._acceptCallbacks.length) {
    cached.hot._acceptCallbacks.forEach(function (cb) {
      var assetsToAlsoAccept = cb(function () {
        return getParents(global.parcelRequire, id);
      });

      if (assetsToAlsoAccept && assetsToAccept.length) {
        assetsToAccept.push.apply(assetsToAccept, assetsToAlsoAccept);
      }
    });
  }

  acceptedAssets[id] = true;
}
},{}],"eb397b394ebff17b5f4b9224cf897db4":[function(require,module,exports) {
"use strict";

var _quadtree = _interopRequireDefault(require("./quadtree"));

var _helpers = require("./helpers");

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

const POINT_COLORS = [255, 137, 137, 255];
let POINTS_TO_RENDER = 10000;

function debounce(func, wait) {
  let timeout;
  return function () {
    var context = this,
        args = arguments;

    var later = function () {
      timeout = null;
      func.apply(context, args);
    };

    clearTimeout(timeout);
    timeout = setTimeout(later, wait);
  };
}

window.addEventListener('DOMContentLoaded', event => {
  // document.getElementById('pointsintree').innerHTML = POINTS_TO_RENDER + ' points in quadtree';
  let Q = (0, _quadtree.default)();
  let next_points = []; // function all_query(bounds) {
  //     const points_in_bounds = [];
  //     for (let i = 0; i < next_points.length; i++) {
  //         if (query_contains_point(bounds, next_points[i])) {
  //             points_in_bounds.push(next_points[i])
  //         }
  //     }
  //     return points_in_bounds;
  // }

  for (let i = 0; i < POINTS_TO_RENDER; i++) {
    next_points.push([Number((Math.random() * (180 - -180) + -180).toFixed(3)), Number((Math.random() * (90 - -90) + -90).toFixed(3))]);
    Q.add_point(next_points[i]);
  }

  let canvas = document.getElementById("canvas");
  canvas.width = 256 * 3;
  canvas.height = 256 * 3;
  let ctx = canvas.getContext("2d");
  let canvasData = ctx.createImageData(canvas.width, canvas.height);

  function get_pixel_index(x, y) {
    return (x + y * canvas.width) * 4;
  }

  function draw_pixel(x, y, r, g, b, a) {
    const index = get_pixel_index(x, y);
    canvasData.data[index] = r;
    canvasData.data[index + 1] = g;
    canvasData.data[index + 2] = b;
    canvasData.data[index + 3] = a;
  } // on zoom change change what the width,height are.


  const is_scale_x = canvas.width < canvas.height,
        scale = is_scale_x ? canvas.width : canvas.height;
  let zoom_scale = 1,
      zoom_step = zoom_scale / 20,
      step = 1,
      Q_min_lng = Q.root_region.bounds[0],
      Q_min_lat = Q.root_region.bounds[1],
      Q_max_lng = Q.root_region.bounds[2],
      Q_max_lat = Q.root_region.bounds[3],
      Q_width = Q_max_lng - Q_min_lng,
      Q_width_step = Math.round(Q_width * zoom_step),
      Q_height = Q_max_lat - Q_min_lat,
      Q_height_step = Math.round(Q_height * zoom_step),
      radius = 20,
      radius_in_pixels = Math.round((is_scale_x ? radius / Q_width : radius / Q_height) * scale);
  let lng,
      lat,
      last_coord = null,
      removed_points = [],
      last = new Float32Array(2 * (2 * radius_in_pixels) + 2 * (4 * radius_in_pixels));

  function _draw_line(xMin, yMin, xMax, yMax, line_funcs) {
    let y = yMax,
        x = xMin;
    let i = 0;

    for (; y < yMin; ++y) {
      for (; i < line_funcs.length; ++i) {
        line_funcs[i](x, y);
      }
    }

    for (; x < xMax; ++x) {
      for (i = 0; i < line_funcs.length; ++i) {
        line_funcs[i](x, y);
      }
    }

    for (; y > yMax; --y) {
      for (i = 0; i < line_funcs.length; ++i) {
        line_funcs[i](x, y);
      }
    }

    for (; x > xMin; --x) {
      for (i = 0; i < line_funcs.length; ++i) {
        line_funcs[i](x, y);
      }
    }

    for (; y < yMin; ++y) {
      for (i = 0; i < line_funcs.length; ++i) {
        line_funcs[i](x, y);
      }
    }
  }

  function draw_line(bounds, query_bounds, line_funcs) {
    _draw_line(Math.round((bounds[0] - Q_min_lng) / Q_width * scale), Math.round((Q_height - (bounds[1] - Q_min_lat)) / Q_height * scale), Math.round((bounds[2] - Q_min_lng) / Q_width * scale), Math.round((Q_height - (bounds[3] - Q_min_lat)) / Q_height * scale), query_bounds, line_funcs);
  }

  function draw_point(point, r = 0, g = 0, b = 0, a = 255) {
    const pixel_x = Math.round((point[0] - Q_min_lng) / Q_width * scale),
          pixel_y = Math.round((Q_height - (point[1] - Q_min_lat)) / Q_height * scale); // crosshair

    draw_pixel(pixel_x - 2, pixel_y, r, g, b, a);
    draw_pixel(pixel_x - 1, pixel_y, r, g, b, a);
    draw_pixel(pixel_x, pixel_y + 1, r, g, b, a);
    draw_pixel(pixel_x, pixel_y + 2, r, g, b, a);
    draw_pixel(pixel_x, pixel_y, r, g, b, a);
    draw_pixel(pixel_x + 1, pixel_y, r, g, b, a);
    draw_pixel(pixel_x + 2, pixel_y, r, g, b, a);
    draw_pixel(pixel_x, pixel_y - 1, r, g, b, a);
    draw_pixel(pixel_x, pixel_y - 2, r, g, b, a);
  } // midpoint circle drawing algorithm
  //https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
  // function draw_circle(point_x, point_y, stroke_width, circle_radius, circle_func) {
  //     let x = circle_radius, y = 0, P = 1 - circle_radius, i = 0;
  //     if (circle_radius > 0) {
  //         for (; i < stroke_width; ++i) {
  //             circle_func((point_x + x + i), (point_y - y + i));
  //             circle_func((point_x + y + i), (point_y + x + i))
  //             circle_func((point_x - y + i), (point_y + y + i))
  //         }
  //     }
  //     while (x > y) {
  //         ++y;
  //         if (P <= 0) {
  //             P += + 2*y + 1;
  //         } else {
  //             --x;
  //             P += 2*y - 2*x + 1;
  //         }
  //         if (x < y)
  //             break;
  //         for (i = 0; i < stroke_width; ++i) {
  //             circle_func((point_x + x + i), (point_y + y + i));
  //             circle_func((point_x - x + i), (point_y + y + i));
  //             circle_func((point_x + x + i), (point_y - y + i));
  //             circle_func((point_x - x + i), (point_y - y + i));
  //         }
  //         if (x != y) {
  //             for (i = 0; i < stroke_width; ++i) {
  //                 circle_func((point_x + y + i), (point_y + x + i));
  //                 circle_func((point_x - y + i), (point_y + x + i));
  //                 circle_func((point_x + y + i), (point_y - x + i));
  //                 circle_func((point_x - y + i), (point_y - x + i));
  //             }
  //         }
  //     }
  // }


  function draw(query_bounds, point_colors) {
    Q.render(draw_point, bounds => draw_line(bounds, query_bounds, [(x, y) => draw_pixel(x, y, 0, 0, 0, 50)]), query_bounds, point_colors);
    ctx.putImageData(canvasData, 0, 0);
  }

  draw([Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS);
  document.getElementById('zoomin').addEventListener('click', function (e) {
    if (step === 10) return;
    zoom_scale -= zoom_step;
    Q_min_lng += Q_width_step;
    Q_max_lng -= Q_width_step;
    Q_min_lat += Q_height_step;
    Q_max_lat -= Q_height_step;
    Q_width = Q_max_lng - Q_min_lng;
    Q_height = Q_max_lat - Q_min_lat;
    radius_in_pixels = Math.round((is_scale_x ? radius / Q_width : radius / Q_height) * scale), last = new Float32Array(2 * (2 * radius_in_pixels) + 2 * (4 * radius_in_pixels));

    for (let i = 0; i < canvasData.data.length; ++i) canvasData.data[i] = 255;

    ctx.putImageData(canvasData, 0, 0);
    draw([Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS);
    ++step;
  });
  document.getElementById('zoomout').addEventListener('click', function (e) {
    if (step === 1) return;
    zoom_scale += zoom_step;
    Q_min_lng -= Q_width_step;
    Q_max_lng += Q_width_step;
    Q_min_lat -= Q_height_step;
    Q_max_lat += Q_height_step;
    Q_width = Q_max_lng - Q_min_lng;
    Q_height = Q_max_lat - Q_min_lat;
    radius_in_pixels = Math.round((is_scale_x ? radius / Q_width : radius / Q_height) * scale), last = new Float32Array(2 * (2 * radius_in_pixels) + 2 * (4 * radius_in_pixels));

    for (let i = 0; i < canvasData.data.length; ++i) canvasData.data[i] = 255;

    ctx.putImageData(canvasData, 0, 0);
    draw([Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS);
    --step;
  });
  document.getElementById('numpoints').addEventListener('keyup', function (e) {
    const next_length = Number(e.target.value);
    if (Number.isNaN(next_length) || next_length === POINTS_TO_RENDER) return;
    POINTS_TO_RENDER = next_length;
    Q = (0, _quadtree.default)();
    next_points = [];
    removed_points = [];
    let i = 0;

    for (; i < POINTS_TO_RENDER; i++) {
      next_points.push([Number((Math.random() * (180 - -180) + -180).toFixed(3)), Number((Math.random() * (90 - -90) + -90).toFixed(3))]);
      Q.add_point(next_points[i]);
    }

    for (i = 0; i < canvasData.data.length; ++i) canvasData.data[i] = 255;

    ctx.putImageData(canvasData, 0, 0);
    draw([Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS);
  });
  document.getElementById('searchradius').addEventListener('keyup', function (e) {
    const next_radius = Number(e.target.value);
    if (Number.isNaN(next_radius)) return; // repaint the previos boudary

    for (let i = 0; i < last.length; ++i) // fill last in with what was there
    canvasData.data[last[i]] = 0;

    radius = next_radius;
    radius_in_pixels = Math.round((is_scale_x ? radius / Q_width : radius / Q_height) * scale), last = new Float32Array(2 * (2 * radius_in_pixels) + 2 * (4 * radius_in_pixels));
  });
  let pnts_qt = [],
      i = 0;
  canvas.addEventListener('mousemove', debounce(function (pnt) {
    lng = pnt.offsetX / scale * Q_width + Q_min_lng;
    lat = -1 * (pnt.offsetY / scale * Q_height - Q_height) + Q_min_lat;

    if (lng < Q_min_lng || Q_max_lng < lng || lat < Q_min_lat || 90 < Q_max_lat) {
      document.querySelector("#mouseloc").innerHTML = "Mouse location:";
      return;
    }

    document.querySelector("#mouseloc").innerHTML = "Mouse location: lng = " + lng.toFixed(3) + ", lat = " + lat.toFixed(3);
    const q_bounds = [lng - radius * 2, lat - radius, lng + radius * 2, lat + radius];
    let start = new Date().getTime();
    pnts_qt = Q.query(q_bounds);
    document.querySelector("#qtpoints").innerHTML = "There are " + (pnts_qt.length || "no") + " quadtree points under this mouse. it took " + (new Date().getTime() - start) + ' ms';

    if (last_coord !== null) {
      i = 0;

      for (; i < last.length; ++i) {
        // fill last in with what was there
        canvasData.data[last[i]] = 0;
        canvasData.data[last[i] + 1] = 0;
        canvasData.data[last[i] + 2] = 0;
        canvasData.data[last[i] + 3] = 0;
      }

      draw([last_coord[0] - radius * 2, last_coord[1] - radius, last_coord[0] + radius * 2, last_coord[1] + radius], [Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS);
      i = 0;
      draw_line([last_coord[0] - radius * 2, last_coord[1] - radius, last_coord[0] + radius * 2, last_coord[1] + radius], [(x, y) => {
        if (x > canvas.width || y > canvas.height || x < 0 || y < 0) return;
        draw_pixel(x, y, 0, 0, 0, 255);
        ;
      }, (x, y) => {
        last[i] = get_pixel_index(x, y);
        ++i;
      }]);

      for (let idx = 0; idx < removed_points.length; ++idx) draw_point(removed_points[idx], 0, 0, 255, 255);
    }

    last_coord = [lng, lat];

    for (let i = 0; i < pnts_qt.length; ++i) draw_point(pnts_qt[i], 255, 0, 0, 255);

    ctx.putImageData(canvasData, 0, 0);
  }), 10);
  document.getElementById("removepoints").addEventListener('click', function (e) {
    e.preventDefault();
    if (next_points.length === 0) return;
    let num_points_to_remove = Number(document.getElementById('numremoves').value);
    if (Number.isNaN(num_points_to_remove)) return;
    if (num_points_to_remove > next_points.length) num_points_to_remove = next_points.length;
    let i = 0;

    while (i < num_points_to_remove && num_points_to_remove <= next_points.length) {
      const remove_index = Math.floor(Math.random() * Math.floor(next_points.length));
      const removed_point = next_points[remove_index];
      removed_points.push(removed_point);
      if (!Q.remove_point(removed_point)) return;
      (0, _helpers._remove_from_list)(next_points, remove_index); // draw([Q_min_lng, Q_min_lng, Q_min_lng + Q_width, Q_min_lat + Q_height], POINT_COLORS);

      for (let idx = 0; idx < removed_points.length; ++idx) draw_point(removed_points[idx], 0, 0, 255, 255);

      ++i;
    }

    document.getElementById('pointsintree').innerHTML = next_points.length + ' points in quadtree';
    draw([Q_min_lng, Q_min_lat, Q_max_lng, Q_max_lat], POINT_COLORS);
  });
});
},{"./quadtree":"5b415db253c9f553e42d899413b2905a","./helpers":"14258dd86469cd3471eaf7ad97b272f9"}],"5b415db253c9f553e42d899413b2905a":[function(require,module,exports) {
"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = quadtree;

var _helpers = require("./helpers");

const CAPACITY = 3;

function region(bounds, parent = null) {
  let r = {
    remove_data_point: function (i) {
      (0, _helpers._remove_from_list)(r.data, i);
    },
    parent: parent,
    bounds: bounds,
    contains: function (point) {
      return (0, _helpers.query_contains_point)(bounds, point);
    },
    add: function (point) {
      // subdivide into regions,
      let i = 0;

      if (r.data.length === CAPACITY) {
        r.subdivide(); // when I subdivide, then I want to move my points into their new regions

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
          if (r.sub_regions[i].add(point)) return true;
        }
      } else if (r.contains(point)) {
        for (i = 0; i < r.data.length; i++) {
          if (r.data[i][0] === point[0] && r.data[i][1] === point[1]) return false;
        }

        r.data.push(point);
        return true;
      }

      return false;
    },
    subdivide: function () {
      const mid_lng = (bounds[0] + bounds[2]) / 2,
            mid_lat = (bounds[1] + bounds[3]) / 2;
      r.sub_regions.push(region([bounds[0], bounds[1], mid_lng, mid_lat], r));
      r.sub_regions.push(region([bounds[0], mid_lat, mid_lng, bounds[3]], r));
      r.sub_regions.push(region([mid_lng, mid_lat, bounds[2], bounds[3]], r));
      r.sub_regions.push(region([mid_lng, bounds[1], bounds[2], mid_lat], r));
      r.have_regions = true;
    },
    data: [],
    have_regions: false,
    sub_regions: [],
    in_bounds: function (query_bounds) {
      if (query_bounds[1] > r.bounds[3] || r.bounds[1] > query_bounds[3]) return false;
      if (query_bounds[2] < r.bounds[0] || r.bounds[2] < query_bounds[0]) return false;
      return true;
    },
    query: function (query_bounds, points_in_bounds) {
      if (!r.in_bounds(query_bounds)) return;
      let i = 0;

      for (i = 0; i < r.sub_regions.length; i++) {
        r.sub_regions[i].query(query_bounds, points_in_bounds);
      }

      for (i = 0; i < r.data.length; i++) {
        if ((0, _helpers.query_contains_point)(query_bounds, r.data[i])) {
          points_in_bounds.push(r.data[i]);
        }
      }
    },
    contains_point: function (point) {
      for (let i = 0; i < r.data.length; i++) {
        if (r.data[i][0] === point[0] && r.data[i][1] === point[1]) {
          return i;
        }
      }

      return -1;
    },
    collapse: function () {
      // if any region has data, i want to leave it alone.
      // if none have data, then that means i should collpase the subregions
      for (let i = 0; i < r.sub_regions.length; i++) {
        if (r.sub_regions[i].data.length) return;
      }

      r.sub_regions = [];
      r.have_regions = false;
    }
  };
  return r;
}

;

function quadtree() {
  const root_region = region([-180, -90, 180, 90]);
  let null_bounds = true;

  function _render(root, pointRenderFunc, regionRenderFunc, query_bounds = null, point_colors = [233, 150, 122, 255]) {
    let i = 0;
    null_bounds = query_bounds === null;

    if (root.have_regions) {
      for (i = 0; i < root.sub_regions.length; ++i) _render(root.sub_regions[i], pointRenderFunc, regionRenderFunc);
    }

    if (!null_bounds && !root.in_bounds(query_bounds)) return;
    regionRenderFunc(root.bounds);
    if (root.data.length == 0) return;

    for (i = 0; i < root.data.length; i++) {
      if (null_bounds || (0, _helpers.query_contains_point)(query_bounds, root.data[i])) {
        pointRenderFunc(root.data[i], point_colors[0], point_colors[1], point_colors[2], point_colors[3]);
      }
    }
  }

  function _remove_point(root, point) {
    let index = -1;

    if ((index = root.contains_point(point)) !== -1) {
      root.remove_data_point(index);
      if (root.parent && root.parent.have_regions) root.parent.collapse();
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
    remove_point: function (point) {
      return _remove_point(root_region, point);
    },
    render: function (pointRenderFunc, regionRenderFunc, query_bounds, point_colors = null) {
      _render(root_region, pointRenderFunc, regionRenderFunc, query_bounds, point_colors);
    },
    query: function (query_bounds) {
      const points_in_bounds = [];
      root_region.query(query_bounds, points_in_bounds);
      return points_in_bounds;
    }
  };
  return q;
}

;
},{"./helpers":"14258dd86469cd3471eaf7ad97b272f9"}],"14258dd86469cd3471eaf7ad97b272f9":[function(require,module,exports) {
"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports._remove_from_list = _remove_from_list;
exports.query_contains_point = query_contains_point;

function _remove_from_list(list, index) {
  if (list.length - 1 === index) list.pop();else list[index] = list.pop();
}

function query_contains_point(bounds, point) {
  if (bounds[0] > point[0]) {
    return false;
  }

  if (bounds[1] > point[1]) {
    return false;
  }

  if (point[0] > bounds[2]) {
    return false;
  }

  if (point[1] > bounds[3]) {
    return false;
  }

  return true;
}
},{}]},{},["75eab32ba9741e29f14b7d8cdb09d849","eb397b394ebff17b5f4b9224cf897db4"], null)

//# sourceMappingURL=js.3d0f651c.js.map
