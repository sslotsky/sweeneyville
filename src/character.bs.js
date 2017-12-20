// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Curry                   = require("bs-platform/lib/js/curry.js");
var CamlinternalOO          = require("bs-platform/lib/js/camlinternalOO.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

var class_tables = [
  0,
  0,
  0
];

function character(startX, startY) {
  if (!class_tables[0]) {
    var $$class = CamlinternalOO.create_table([
          "data",
          "place",
          "move"
        ]);
    var ids = CamlinternalOO.new_methods_variables($$class, [
          "turn",
          "place",
          "move",
          "data"
        ], [
          "position",
          "speed",
          "d"
        ]);
    var turn = ids[0];
    var place = ids[1];
    var move = ids[2];
    var data = ids[3];
    var position = ids[4];
    var speed = ids[5];
    var d = ids[6];
    CamlinternalOO.set_methods($$class, /* array */[
          move,
          (function (self$1, direction) {
              Curry._2(self$1[0][turn], self$1, direction);
              var match = self$1[position][0];
              var y = match[1];
              var x = match[0];
              var match$1 = self$1[speed][0];
              var vy = match$1[1];
              var vx = match$1[0];
              switch (direction) {
                case 0 : 
                    self$1[position][0] = /* tuple */[
                      x,
                      y - vy | 0
                    ];
                    return /* () */0;
                case 1 : 
                    self$1[position][0] = /* tuple */[
                      x,
                      y + vy | 0
                    ];
                    return /* () */0;
                case 2 : 
                    self$1[position][0] = /* tuple */[
                      x - vx | 0,
                      y
                    ];
                    return /* () */0;
                case 3 : 
                    self$1[position][0] = /* tuple */[
                      x + vx | 0,
                      y
                    ];
                    return /* () */0;
                case 4 : 
                    throw [
                          Caml_builtin_exceptions.match_failure,
                          [
                            "/Users/sam/sweenyville/src/character.re",
                            27,
                            4
                          ]
                        ];
                
              }
            }),
          place,
          (function (self$1, newX, newY) {
              self$1[position][0] = /* tuple */[
                newX,
                newY
              ];
              return /* () */0;
            }),
          data,
          (function (self$1, _) {
              var match = self$1[position][0];
              var match$1 = self$1[speed][0];
              return /* record */[
                      /* x */match[0],
                      /* y */match[1],
                      /* vx */match$1[0],
                      /* vy */match$1[1],
                      /* direction */self$1[d][0]
                    ];
            }),
          turn,
          (function (self$1, direction) {
              self$1[d][0] = direction;
              return /* () */0;
            })
        ]);
    var env_init = function (env) {
      var self = CamlinternalOO.create_object_opt(0, $$class);
      self[position] = [/* tuple */[
          env[1],
          env[2]
        ]];
      self[speed] = [/* tuple */[
          1,
          1
        ]];
      self[d] = [/* Right */3];
      return self;
    };
    CamlinternalOO.init_class($$class);
    class_tables[0] = env_init;
  }
  return Curry._1(class_tables[0], [
              0,
              startX,
              startY
            ]);
}

exports.character = character;
/* No side effect */