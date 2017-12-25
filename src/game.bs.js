// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var $$Array                = require("bs-platform/lib/js/array.js");
var Caml_int32             = require("bs-platform/lib/js/caml_int32.js");
var Caml_oo_curry          = require("bs-platform/lib/js/caml_oo_curry.js");
var Dom$Sweenyville        = require("./engine/dom.bs.js");
var Hero$Sweenyville       = require("./engine/hero.bs.js");
var Pixi$Sweenyville       = require("./engine/pixi.bs.js");
var Scene$Sweenyville      = require("./game/scene.bs.js");
var Spawn$Sweenyville      = require("./engine/spawn.bs.js");
var Tiler$Sweenyville      = require("./engine/tiler.bs.js");
var Camera$Sweenyville     = require("./game/camera.bs.js");
var Predator$Sweenyville   = require("./engine/predator.bs.js");
var Controller$Sweenyville = require("./game/controller.bs.js");

function start() {
  var app = Pixi$Sweenyville.App[/* start */0](/* () */0);
  var textures = $$Array.concat(/* :: */[
        /* array */[
          "images/space.jpg",
          "images/tiles.jpeg"
        ],
        /* :: */[
          Predator$Sweenyville.frame_sequence("idle", 3),
          /* :: */[
            Predator$Sweenyville.frame_sequence("run", 6),
            /* :: */[
              Hero$Sweenyville.frame_sequence("Idle", 16),
              /* :: */[
                Hero$Sweenyville.frame_sequence("Run", 20),
                /* [] */0
              ]
            ]
          ]
        ]
      ]);
  var callback = function (_, _$1) {
    var match = Spawn$Sweenyville.spawn(/* tuple */[
          0.0,
          0.0
        ], /* tuple */[
          75.0,
          75.0
        ], Hero$Sweenyville.sequence_map);
    var animator = match[2];
    var my_hero = match[1];
    var player = match[0];
    var match$1 = Spawn$Sweenyville.spawn(/* tuple */[
          100.0,
          400.0
        ], /* tuple */[
          75.0,
          75.0
        ], Predator$Sweenyville.sequence_map);
    var enemy_animator = match$1[2];
    var enemy = match$1[1];
    var predator = match$1[0];
    var match$2 = Tiler$Sweenyville.make_tile(/* tuple */[
          0.0,
          100.0
        ], /* tuple */[
          170.0,
          250.0
        ], "images/tiles.jpeg");
    var tile = match$2[1];
    var tile_sprite = match$2[0];
    Pixi$Sweenyville.Sprite[/* interact */5](my_hero);
    Pixi$Sweenyville.Sprite[/* button */6](my_hero);
    Pixi$Sweenyville.Sprite[/* listen */7](my_hero, "mouseover", (function () {
            return Pixi$Sweenyville.Sprite[/* alpha */9](my_hero, 0.8);
          }));
    Pixi$Sweenyville.Sprite[/* listen */7](my_hero, "mouseout", (function () {
            return Pixi$Sweenyville.Sprite[/* alpha */9](my_hero, 1.0);
          }));
    Pixi$Sweenyville.Sprite[/* listen */7](my_hero, "click", (function () {
            return Caml_oo_curry.js2(432628799, 1, animator, Predator$Sweenyville.sequence_map);
          }));
    Caml_oo_curry.js2(-237325899, 2, enemy_animator, 10);
    var r = Pixi$Sweenyville.App[/* renderer */12](app);
    var bg = Pixi$Sweenyville.App[/* tiling_sprite */7](Pixi$Sweenyville.App[/* texture */4]("images/space.jpg"), Pixi$Sweenyville.App[/* width */13](r), Pixi$Sweenyville.App[/* height */14](r));
    var match_000 = Caml_int32.imul(Pixi$Sweenyville.App[/* width */13](r), 3);
    var match_001 = Caml_int32.imul(Pixi$Sweenyville.App[/* height */14](r), 3);
    var scene = Scene$Sweenyville.scene(match_000, match_001, /* array */[
          player,
          predator,
          tile
        ]);
    Pixi$Sweenyville.App[/* addSprite */15](app, bg);
    Pixi$Sweenyville.App[/* addSprite */15](app, tile_sprite);
    Pixi$Sweenyville.App[/* addSprite */15](app, enemy);
    Pixi$Sweenyville.App[/* addSprite */15](app, my_hero);
    var controller = Controller$Sweenyville.controller(player);
    Dom$Sweenyville.listen("keydown", (function ($$event) {
            var d = Dom$Sweenyville.key_map($$event);
            Caml_oo_curry.js2(-933174511, 3, controller, d);
            if (d) {
              return Caml_oo_curry.js2(-855250051, 4, player, d[0]);
            } else {
              return /* () */0;
            }
          }));
    Dom$Sweenyville.listen("keyup", (function ($$event) {
            var d = Dom$Sweenyville.key_map($$event);
            return Caml_oo_curry.js2(-866390014, 5, controller, d);
          }));
    Caml_oo_curry.js2(-107572879, 6, Camera$Sweenyville.camera, player);
    var match_000$1 = Pixi$Sweenyville.App[/* width */13](r) / 2 | 0;
    var match_001$1 = Pixi$Sweenyville.App[/* height */14](r) / 2 | 0;
    var centerY = match_001$1;
    var centerX = match_000$1;
    return Pixi$Sweenyville.App[/* add_ticker */11](app, (function () {
                  var data = Caml_oo_curry.js2(-1033677270, 7, player, /* () */0);
                  var gap_left = data[/* x */0] - Caml_oo_curry.js2(761282246, 8, scene, /* () */0);
                  var gap_right = Caml_oo_curry.js2(-405516197, 9, scene, /* () */0) - data[/* x */0];
                  var gap_top = Math.abs(Caml_oo_curry.js2(-963970092, 10, scene, /* () */0) - data[/* y */1]);
                  var gap_bottom = Math.abs(data[/* y */1] - Caml_oo_curry.js2(-146710358, 11, scene, /* () */0));
                  var margin = function (gap, dimension) {
                    return +((gap | 0) < (dimension / 2 | 0));
                  };
                  var side_margin = function (gap) {
                    return margin(gap, Pixi$Sweenyville.App[/* width */13](r));
                  };
                  var v_margin = function (gap) {
                    return margin(gap, Pixi$Sweenyville.App[/* height */14](r));
                  };
                  if (side_margin(gap_left) || side_margin(gap_right)) {
                    Caml_oo_curry.js2(84683005, 12, Camera$Sweenyville.camera, /* () */0);
                  } else {
                    Caml_oo_curry.js2(122902550, 13, Camera$Sweenyville.camera, /* () */0);
                  }
                  if (v_margin(gap_top) || v_margin(gap_bottom)) {
                    Caml_oo_curry.js2(84683006, 14, Camera$Sweenyville.camera, /* () */0);
                  } else {
                    Caml_oo_curry.js2(122902551, 15, Camera$Sweenyville.camera, /* () */0);
                  }
                  Caml_oo_curry.js2(-855850147, 16, controller, /* () */0);
                  Caml_oo_curry.js2(-855850147, 17, scene, /* () */0);
                  Caml_oo_curry.js2(-855850147, 18, Camera$Sweenyville.camera, /* () */0);
                  Caml_oo_curry.js2(-855850147, 19, animator, /* () */0);
                  Caml_oo_curry.js2(-855850147, 20, enemy_animator, /* () */0);
                  var match = Caml_oo_curry.js2(-889544535, 21, Camera$Sweenyville.camera, /* () */0);
                  var cameraY = match[1];
                  var cameraX = match[0];
                  var put = function (param) {
                    var sprite = param[1];
                    var renderable = param[0];
                    var data = Caml_oo_curry.js2(-1033677270, 22, renderable, /* () */0);
                    var match_000 = centerX + (data[/* x */0] - cameraX);
                    var match_001 = centerY + (data[/* y */1] - cameraY);
                    var match = Pixi$Sweenyville.Sprite[/* center_offset */10](sprite);
                    Pixi$Sweenyville.Sprite[/* position */4](sprite, match_000 - match[0], match_001 - match[1]);
                    var d = Caml_oo_curry.js2(272654911, 23, renderable, /* () */0);
                    if (d >= 2) {
                      switch (d - 2 | 0) {
                        case 0 : 
                            return Pixi$Sweenyville.Sprite[/* flip_left */2](sprite);
                        case 1 : 
                            return Pixi$Sweenyville.Sprite[/* flip_right */1](sprite);
                        case 2 : 
                            return /* () */0;
                        
                      }
                    } else {
                      return /* () */0;
                    }
                  };
                  var put_tile = function (param) {
                    var tmp = param[0];
                    var data = Caml_oo_curry.js2(-1033677270, 24, tmp, /* () */0);
                    var match_000 = centerX + (data[/* x */0] - cameraX);
                    var match_001 = centerY + (data[/* y */1] - cameraY);
                    var match = Pixi$Sweenyville.Sprite[/* center_offset */10](my_hero);
                    return Pixi$Sweenyville.Sprite[/* position */4](param[1], match_000 + match[0] / 4.0, match_001 - match[1]);
                  };
                  put_tile(/* tuple */[
                        tile,
                        tile_sprite
                      ]);
                  put(/* tuple */[
                        player,
                        my_hero
                      ]);
                  return put(/* tuple */[
                              predator,
                              enemy
                            ]);
                }));
  };
  Pixi$Sweenyville.App[/* load_textures */8](textures, callback);
  return app;
}

exports.start = start;
/* Hero-Sweenyville Not a pure module */
