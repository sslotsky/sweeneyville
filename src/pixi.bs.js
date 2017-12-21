// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var PixiJs = require("pixi.js");

function rescale(sprite, x, y) {
  var s = sprite.scale;
  s.x = x;
  s.y = y;
  return /* () */0;
}

function position(sprite, x, y) {
  sprite.anchor.x = 0.5;
  sprite.x = x;
  sprite.y = y;
  return /* () */0;
}

function setTexture(prim, prim$1) {
  prim.texture = prim$1;
  return /* () */0;
}

var Sprite = /* module */[
  /* rescale */rescale,
  /* position */position,
  /* setTexture */setTexture
];

function start() {
  return new PixiJs.Application();
}

var loader = PixiJs.loader;

function getTexture(prim) {
  return prim.texture;
}

function resource(name) {
  return loader.resources[name];
}

function texture(name) {
  return loader.resources[name].texture;
}

function load_textures(paths, callback) {
  loader.add(paths).load(callback);
  return /* () */0;
}

function fetch_sprite(resources, path) {
  return new PixiJs.Sprite(resources[path].texture);
}

function add_ticker(app, tick) {
  app.ticker.add(tick);
  return /* () */0;
}

function renderer(prim) {
  return prim.renderer;
}

function width(prim) {
  return prim.width;
}

function height(prim) {
  return prim.height;
}

function addSprite(app, sprite) {
  app.stage.addChild(sprite);
  return /* () */0;
}

var App = /* module */[
  /* start */start,
  /* loader */loader,
  /* getTexture */getTexture,
  /* resource */resource,
  /* texture */texture,
  /* load_textures */load_textures,
  /* fetch_sprite */fetch_sprite,
  /* add_ticker */add_ticker,
  /* renderer */renderer,
  /* width */width,
  /* height */height,
  /* addSprite */addSprite
];

exports.Sprite = Sprite;
exports.App    = App;
/* loader Not a pure module */
