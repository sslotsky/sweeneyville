type scale;
type anchor;
type sprite;
type texture;
type event;
[@bs.set] external setX : (sprite, float) => unit = "x";
[@bs.set] external setY : (sprite, float) => unit = "y";
[@bs.get] external getScale : (sprite) => scale = "scale";
[@bs.get] external getScaleX : (scale) => float = "x";
[@bs.set] external scaleX : (scale, float) => unit = "x";
[@bs.set] external scaleY : (scale, float) => unit = "y";
[@bs.get] external getAnchor : (sprite) => anchor = "anchor";
[@bs.set] external anchorX : (anchor, float) => unit = "x";
[@bs.set] external setTexture: (sprite, texture) => unit = "texture";
[@bs.set] external set_interactive : (sprite, Js.boolean) => unit = "interactive";
[@bs.set] external set_button_mode : (sprite, Js.boolean) => unit = "buttonMode";
[@bs.send] external on : (sprite, string, event => unit) => unit = "on";
[@bs.set] external set_alpha : (sprite, float) => unit = "alpha";

module Sprite = {
  let rescale = (sprite: sprite, x: float, y: float) => {
    let s = getScale(sprite);
    scaleX(s, x);
    scaleY(s, y);
  };

  let position = (sprite: sprite, x: float, y: float) => {
    anchorX(getAnchor(sprite), 0.5);
    setX(sprite, x);
    setY(sprite, y);
  };

  let interact = sprite => set_interactive(sprite, Js.Boolean.to_js_boolean(true));

  let button = sprite => set_button_mode(sprite, Js.Boolean.to_js_boolean(true));

  let listen = on;

  let setTexture = setTexture;

  let alpha = set_alpha;
};

[@bs.new] [@bs.module "pixi.js"] external createSprite: texture => sprite = "Sprite";

type pixiApp;
type renderer;
type ticker;
type delta;
type extras;
type tile_constructor;
[@bs.new] [@bs.module "pixi.js"] external pixify: unit => pixiApp = "Application";
[@bs.get] external getRenderer : (pixiApp) => renderer = "renderer";
[@bs.get] external width : (renderer) => int = "width";
[@bs.get] external height : (renderer) => int = "height";
[@bs.get] external ticker : (pixiApp) => ticker = "ticker";
[@bs.send] external addTicker : (ticker, delta => unit) => unit = "add";
[@bs.get] external extras : pixiApp => extras = "extras";
[@bs.get] external tiling : extras => tile_constructor = "TilingSprite";
[@bs.module "pixi.js"][@bs.scope "extras"] [@bs.new] external tiling_sprite : (texture, int, int) => sprite = "TilingSprite";

type stage;
[@bs.get] external getStage : (pixiApp) => stage = "stage";
[@bs.send] external addSprite : (stage, sprite) => unit = "addChild";

type textureLoader;
type resources;
type resource;
[@bs.send] external addTextures : (textureLoader, array(string)) => textureLoader = "add";
[@bs.send] external loadTextures : (textureLoader, (textureLoader, resources) => unit) => unit = "load";
[@bs.get] external getTexture : (resource) => texture = "texture";
[@bs.get_index] external getResource : (resources, string) => resource = "";

[@bs.module "pixi.js"] external loader : textureLoader = "loader";
[@bs.get] external getResources : textureLoader => resources = "resources";

module App = {
  let start = pixify;

  let loader = loader;

  let getTexture = getTexture;

  let resource = name => getResource(getResources(loader), name);

  let texture = name => getTexture(resource(name));

  let sprite = name => createSprite(texture(name));

  let create_sprite = createSprite;

  let tiling_sprite = tiling_sprite;

  let load_textures = (paths, callback) => {
    loadTextures(addTextures(loader, paths), callback);
  };

  let add_texture = path => addTextures(loader, [|path|]);

  let fetch_sprite = (resources, path) => {
    createSprite(getTexture(getResource(resources, path)));
  };

  let add_ticker = (app, tick) => addTicker(ticker(app), tick);
  let renderer = getRenderer;
  let width = width;
  let height = height;
  let addSprite = (app, sprite) => {
    addSprite(getStage(app), sprite);
  };
};
