let start = () => {
  let app = Pixi.App.start();

  let callback = (_, resources) => {
    let myHero = Pixi.App.loadHero(resources);
    Pixi.Sprite.rescale(myHero, 0.2,   0.2);

    let r = Pixi.App.renderer(app);

    let player = Character.character(Pixi.App.width(r) / 2, Pixi.App.height(r) / 2);

    Pixi.Sprite.position(myHero, player#data().x, player#data().y);
    Pixi.App.addSprite(app, myHero);

    let controller = Controller.controller(player);

    Dom.listen("keydown", event => {
      let d = Dom.keyMap(event);

      controller#move(d);

      switch d {
        | (Character.Left) => Pixi.Sprite.rescale(myHero, -0.2, 0.2)
        | (Character.Right) => Pixi.Sprite.rescale(myHero, 0.2, 0.2)
        | _ => ()
      };
    });

    Dom.listen("keyup", event => {
      let d = Dom.keyMap(event);
      controller#stop(d);
    });

    Pixi.App.addTicker(app, (_) => {
      controller#tick();
      Pixi.Sprite.position(myHero, player#data().x, player#data().y);
    });
  };

  Pixi.App.loadTexture("hero", "images/hero/Idle (1).png", callback);
  app;
};
