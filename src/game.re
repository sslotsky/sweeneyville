let start = () => {
  let app = Pixi.App.start();

  let texture_name = (sequence, frame) =>
   "images/hero/" ++ sequence ++ " (" ++ string_of_int(frame) ++ ").png";

  let frame_sequence = (name, num_frames) =>
    Array.map(n => texture_name(name, n), Reasonable.range(1, num_frames));

  let textures = Array.append(
    frame_sequence("Idle", 16),
    frame_sequence("Run", 20)
  );


  let callback = (_, resources) => {
    let my_hero = Pixi.App.fetch_sprite(resources, "images/hero/Idle (1).png");
    Pixi.Sprite.rescale(my_hero, 0.2,   0.2);

    let r = Pixi.App.renderer(app);

    let player = Character.character(0.0, 0.0);

    let path = name => frame => texture_name(name, frame);

    let map: Animation.sequence_map = {
      idle: (16, path("Idle")),
      running: (20, path("Run"))
    };

    let animator = Animation.animator(player, my_hero, map);

    Pixi.App.addSprite(app, my_hero);

    let controller = Controller.controller(player);

    Dom.listen("keydown", event => {
      let d = Dom.key_map(event);

      controller#move(d);

      switch d {
        | Commands.Move(Character.Left) => Pixi.Sprite.rescale(my_hero, -0.2, 0.2)
        | Commands.Move(Character.Right) => Pixi.Sprite.rescale(my_hero, 0.2, 0.2)
        | _ => ()
      };
    });

    Dom.listen("keyup", event => {
      let d = Dom.key_map(event);
      controller#stop(d);
    });

    let camera = Camera.camera;

    Pixi.App.add_ticker(app, (_) => {
      let (centerX, centerY) = (float_of_int(Pixi.App.width(r) / 2), float_of_int(Pixi.App.height(r) / 2));
      controller#tick();
      camera#tick();
      let data = player#data();
      let (cameraX, cameraY) = camera#position();
      let (x, y) = (centerX +. (data.x -. cameraX), centerY +. (data.y -. cameraY));
      Pixi.Sprite.position(my_hero, x, y);

      animator#tick();
    });
  };

  Pixi.App.load_textures(textures, callback);
  app;
};
