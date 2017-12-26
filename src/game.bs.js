// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Hero$Sweenyville     = require("./engine/hero.bs.js");
var Pixi$Sweenyville     = require("./engine/pixi.bs.js");
var Spawn$Sweenyville    = require("./engine/spawn.bs.js");
var Tiler$Sweenyville    = require("./engine/tiler.bs.js");
var Assets$Sweenyville   = require("./engine/assets.bs.js");
var Engine$Sweenyville   = require("./engine/engine.bs.js");
var Predator$Sweenyville = require("./engine/predator.bs.js");

function start() {
  var app = Pixi$Sweenyville.App[/* start */0](/* () */0);
  var callback = function (_, _$1) {
    var hero = Spawn$Sweenyville.spawn(/* tuple */[
          0.0,
          0.0
        ], /* tuple */[
          75.0,
          75.0
        ], Hero$Sweenyville.sequence_map);
    var enemy = Spawn$Sweenyville.spawn(/* tuple */[
          100.0,
          400.0
        ], /* tuple */[
          75.0,
          75.0
        ], Predator$Sweenyville.sequence_map);
    var tile = Tiler$Sweenyville.make_tile(/* tuple */[
          0.0,
          100.0
        ], /* tuple */[
          700.0,
          700.0
        ], "images/tiles.jpeg");
    return Engine$Sweenyville.boot(app, hero, /* array */[enemy], /* array */[tile], "images/space.jpg");
  };
  Pixi$Sweenyville.App[/* load_textures */8](Assets$Sweenyville.textures, callback);
  return app;
}

exports.start = start;
/* Hero-Sweenyville Not a pure module */
