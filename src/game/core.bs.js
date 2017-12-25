// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Caml_oo_curry = require("bs-platform/lib/js/caml_oo_curry.js");

function center(r) {
  return /* tuple */[
          r[/* x */0] + r[/* width */5] / 2.0,
          r[/* y */1] + r[/* height */4] / 2.0
        ];
}

function collision(a, b) {
  var data_a = Caml_oo_curry.js2(-1033677270, 1, a, /* () */0);
  var data_b = Caml_oo_curry.js2(-1033677270, 2, b, /* () */0);
  var match_000 = data_a[/* width */5] / 2.0 + data_b[/* width */5] / 2.0;
  var match_001 = data_a[/* height */4] / 2.0 + data_b[/* height */4] / 2.0;
  var match_000$1 = center(data_a);
  var match_001$1 = center(data_b);
  var match = match_001$1;
  var match$1 = match_000$1;
  if (Math.abs(match$1[0] - match[0]) < match_000) {
    return +(Math.abs(match$1[1] - match[1]) < match_001);
  } else {
    return /* false */0;
  }
}

exports.center    = center;
exports.collision = collision;
/* No side effect */
