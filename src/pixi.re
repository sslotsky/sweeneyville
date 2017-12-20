type scale;
type sprite;
[@bs.set] external setX : (sprite, int) => unit = "x";
[@bs.set] external setY : (sprite, int) => unit = "y";
[@bs.get] external getScale : (sprite) => scale = "scale";
[@bs.set] external scaleX : (scale, float) => unit = "x";
[@bs.set] external scaleY : (scale, float) => unit = "y";

module Sprite = {
  let rescale = (sprite: sprite, x: float, y: float) => {
    let s = getScale(sprite);
    scaleX(s, x);
    scaleY(s, y);
  };

  let position = (sprite: sprite, x: int, y: int) => {
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
[@bs.send] external addTexture : (textureLoader, string, string) => textureLoader = "add";
[@bs.send] external loadTexture : (textureLoader, (textureLoader, resources) => unit) => unit = "load";
[@bs.get] external heroSprite : (resources) => resource = "hero";
[@bs.get] external heroTexture : (resource) => texture = "texture";

[@bs.module "pixi.js"] external loader : textureLoader = "loader";

module App = {
  let start = pixify;

  let loadTexture = (name, path, callback) => {
    loadTexture(addTexture(loader, name, path), callback);
  };

  let loadHero = (resources) => {
    createSprite(heroTexture(heroSprite(resources)));
  };

  let addTicker = (app, tick) => addTicker(ticker(app), tick);
  let renderer = getRenderer;
  let width = width;
  let height = height;
  let addSprite = (app, sprite) => {
    addSprite(getStage(app), sprite);
  };
};
