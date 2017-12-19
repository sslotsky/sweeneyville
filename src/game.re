type scale;
type sprite;
[@bs.set] external setX : (sprite, float) => unit = "x";
[@bs.set] external setY : (sprite, float) => unit = "y";
[@bs.get] external getScale : (sprite) => scale = "scale";
[@bs.set] external scaleX : (scale, float) => unit = "x";
[@bs.set] external scaleY : (scale, float) => unit = "y";

let rescale = (sprite: sprite, x: float, y: float) => {
  let s = getScale(sprite);
  scaleX(s, x);
  scaleY(s, y);
};

let position = (sprite: sprite, x: float, y: float) => {
  setX(sprite, x);
  setY(sprite, y);
};

type texture;
[@bs.new] [@bs.module "pixi.js"] external createSprite: texture => sprite = "Sprite";

type pixiApp;
type renderer;
[@bs.new] [@bs.module "pixi.js"] external pixify: unit => pixiApp = "Application";
[@bs.get] external getRenderer : (pixiApp) => renderer = "renderer";
[@bs.get] external width : (renderer) => float = "width";
[@bs.get] external height : (renderer) => float = "height";

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

let start = () => {
  Js.log("hello");
  let app = pixify();

  let callback = (_: textureLoader, resources: resources) => {
    let t = heroTexture(heroSprite(resources));
    let myHero = createSprite(t);
    rescale(myHero, 0.2, 0.2);

    let r = getRenderer(app);
    position(myHero, width(r) /. float_of_int(2), height(r) /. float_of_int(2));
    addSprite(getStage(app), myHero);
  };

  let withTexture = addTexture(loader, "hero", "images/hero/Idle (1).png");
  loadTexture(withTexture, callback);
  app;
};
