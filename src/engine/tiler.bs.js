// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Curry            = require("bs-platform/lib/js/curry.js");
var Pixi$Sweenyville = require("./pixi.bs.js");
var Tile$Sweenyville = require("../game/tile.bs.js");

function make_tile(coords, dimensions, path, hub) {
  var sprite = Pixi$Sweenyville.App[/* tiling_sprite */7](Pixi$Sweenyville.App[/* texture */4](path), dimensions[0] | 0, dimensions[1] | 0);
  var tile = Curry._3(Tile$Sweenyville.spawn, coords, dimensions, hub);
  return /* tuple */[
          tile,
          sprite
        ];
}

exports.make_tile = make_tile;
/* Pixi-Sweenyville Not a pure module */
