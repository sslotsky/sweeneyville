// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var $$Array    = require("bs-platform/lib/js/array.js");
var Curry      = require("bs-platform/lib/js/curry.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function range(a, b) {
  var match_000 = Pervasives.min(a, b);
  var match_001 = Pervasives.max(a, b);
  var y = match_001;
  var _nums = /* int array */[match_000];
  while(true) {
    var nums = _nums;
    var last = Caml_array.caml_array_get(nums, nums.length - 1 | 0);
    var finished = +(last === y);
    if (finished !== 0) {
      return nums;
    } else {
      _nums = $$Array.append(nums, /* int array */[last + 1 | 0]);
      continue ;
      
    }
  };
}

function select(array, lambda) {
  return $$Array.fold_left((function ($$final, item) {
                if (Curry._1(lambda, item)) {
                  return $$Array.append($$final, /* array */[item]);
                } else {
                  return $$final;
                }
              }), /* array */[], array);
}

exports.range  = range;
exports.select = select;
/* No side effect */
