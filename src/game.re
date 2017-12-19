type scale = {
  x: float,
  y: float
};

[@bs.deriving jsConverter]
type sprite = {
  x: int,
  y: int,
  vx: int,
  vy: int,
  scale: scale
};

type texture;
[@bs.new] [@bs.module "pixi.js"] external createSprite: texture => sprite = "Sprite";

type pixiApp;
[@bs.new] [@bs.module "pixi.js"] external pixify: unit => pixiApp = "Application";

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

  let callback = (loader: textureLoader, resources: resources) => {
    [%debugger];
    let t = heroTexture(heroSprite(resources));
    let myHero = createSprite(t);
    addSprite(getStage(app), myHero);
  };

  let withTexture = addTexture(loader, "hero", "images/hero/Idle (1).png");
  loadTexture(withTexture, callback);
  app;
};
