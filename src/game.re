let start = () => {
  let app = Pixi.App.start();

  let callback = (_, resources) => {
    let myHero = Pixi.App.fetchSprite(resources, "images/hero/Idle (1).png");
    Pixi.Sprite.rescale(myHero, 0.2,   0.2);

    let r = Pixi.App.renderer(app);

    let player = Character.character(Pixi.App.width(r) / 2, Pixi.App.height(r) / 2);
    let animator = Animation.animator(player, myHero);

    Pixi.Sprite.position(myHero, player#data().x, player#data().y);
    Pixi.App.addSprite(app, myHero);

    let controller = Controller.controller(player);

    Dom.listen("keydown", event => {
      let d = Dom.keyMap(event);

      controller#move(d);

      switch d {
        | Commands.Move(Character.Left) => Pixi.Sprite.rescale(myHero, -0.2, 0.2)
        | Commands.Move(Character.Right) => Pixi.Sprite.rescale(myHero, 0.2, 0.2)
        | _ => ()
      };
    });

    Dom.listen("keyup", event => {
      let d = Dom.keyMap(event);
      controller#stop(d);
    });

    Pixi.App.addTicker(app, (_) => {
      controller#tick();
      let data = player#data();
      Pixi.Sprite.position(myHero, data.x, data.y);

      animator#tick();
    });
  };

  let r = Reasonable.range(1, 16);
  Js.log(r);
  Pixi.App.loadTexture("images/hero/Idle (1).png", callback);
  app;
};
