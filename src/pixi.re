type scale;
type anchor;
type sprite;
[@bs.set] external setX : (sprite, int) => unit = "x";
[@bs.set] external setY : (sprite, int) => unit = "y";
[@bs.get] external getScale : (sprite) => scale = "scale";
[@bs.get] external getScaleX : (scale) => float = "x";
[@bs.set] external scaleX : (scale, float) => unit = "x";
[@bs.set] external scaleY : (scale, float) => unit = "y";
[@bs.get] external getAnchor : (sprite) => anchor = "anchor";
[@bs.set] external anchorX : (anchor, float) => unit = "x";

module Sprite = {
  let rescale = (sprite: sprite, x: float, y: float) => {
    let s = getScale(sprite);
    scaleX(s, x);
    scaleY(s, y);
  };

  let position = (sprite: sprite, x: int, y: int) => {
    anchorX(getAnchor(sprite), 0.5);
    setX(sprite, x);
    setY(sprite, y);
  };
};

type texture;
[@bs.new] [@bs.module "pixi.js"] external createSprite: texture => sprite = "Sprite";

type pixiApp;
type renderer;
type ticker;
type delta;
[@bs.new] [@bs.module "pixi.js"] external pixify: unit => pixiApp = "Application";
[@bs.get] external getRenderer : (pixiApp) => renderer = "renderer";
[@bs.get] external width : (renderer) => int = "width";
[@bs.get] external height : (renderer) => int = "height";
[@bs.get] external ticker : (pixiApp) => ticker = "ticker";
[@bs.send] external addTicker : (ticker, delta => unit) => unit = "add";

type stage;
[@bs.get] external getStage : (pixiApp) => stage = "stage";
[@bs.send] external addSprite : (stage, sprite) => unit = "addChild";

type textureLoader;
type resources;
type resource;
[@bs.send] external addTexture : (textureLoader, string) => textureLoader = "add";
[@bs.send] external loadTexture : (textureLoader, (textureLoader, resources) => unit) => unit = "load";
[@bs.get] external getTexture : (resource) => texture = "texture";
[@bs.get_index] external getResource : (resources, string) => resource = "";

[@bs.module "pixi.js"] external loader : textureLoader = "loader";

module App = {
  let start = pixify;

  let addTexture = addTexture;

  let getTexture = getTexture;

  let loadTexture = (path, callback) => {
    loadTexture(addTexture(loader, path), callback);
  };

  let fetchSprite = (resources, path) => {
    createSprite(getTexture(getResource(resources, path)));
  };

  let addTicker = (app, tick) => addTicker(ticker(app), tick);
  let renderer = getRenderer;
  let width = width;
  let height = height;
  let addSprite = (app, sprite) => {
    addSprite(getStage(app), sprite);
  };
};
