// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Renderable$Sweenyville = require("./renderable.bs.js");

var CharacterObject = /* module */[
  /* MakeGameObject */Renderable$Sweenyville.MakeGameObject,
  /* next_coordinates */Renderable$Sweenyville.next_coordinates,
  /* accel */Renderable$Sweenyville.accel,
  /* decel */Renderable$Sweenyville.decel,
  /* colliders */Renderable$Sweenyville.colliders,
  /* category : Character */0
];

var Character = Renderable$Sweenyville.MakeGameObject([
      /* Character */0,
      Renderable$Sweenyville.next_coordinates,
      Renderable$Sweenyville.accel,
      Renderable$Sweenyville.decel,
      Renderable$Sweenyville.colliders
    ]);

var character = Character[/* spawn */0];

exports.CharacterObject = CharacterObject;
exports.Character       = Character;
exports.character       = character;
/* Character Not a pure module */
