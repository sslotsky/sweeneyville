let start = () => {
  let app = Pixi.App.start();

  let textures =Array.concat(
    [
      [|"images/space.jpg"|],
      Predator.frame_sequence("idle", 3),
      Predator.frame_sequence("run", 6),
      Hero.frame_sequence("Idle", 16),
      Hero.frame_sequence("Run", 20)
    ]
  );

  let callback = (_, _) => {
    let (player, my_hero, animator) = Spawn.spawn((0.0, 0.0), Hero.sequence_map);
    let (predator, enemy, enemy_animator) = Spawn.spawn((100.0, 100.0), Predator.sequence_map);

    Pixi.Sprite.interact(my_hero);
    Pixi.Sprite.button(my_hero);
    Pixi.Sprite.listen(my_hero, "mouseover", (_) => {
      Pixi.Sprite.alpha(my_hero, 0.8);
    });

    Pixi.Sprite.listen(my_hero, "mouseout", (_) => {
      Pixi.Sprite.alpha(my_hero, 1.0);
    });

    Pixi.Sprite.listen(my_hero, "click", (_) => {
      animator#set_map(Predator.sequence_map);
    });

    enemy_animator#set_freq(10);

    Pixi.Sprite.rescale(my_hero, 0.2,   0.2);
    Pixi.Sprite.rescale(enemy, 0.2,   0.2);

    let r = Pixi.App.renderer(app);

    let bg = Pixi.App.tiling_sprite(Pixi.App.texture("images/space.jpg"), Pixi.App.width(r), Pixi.App.height(r));

    Pixi.App.addSprite(app, bg);
    Pixi.App.addSprite(app, my_hero);
    Pixi.App.addSprite(app, enemy);

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
    camera#follow(player);
    let (centerX, centerY) = (float_of_int(Pixi.App.width(r) / 2), float_of_int(Pixi.App.height(r) / 2));

    Pixi.App.add_ticker(app, (_) => {
      controller#tick();
      camera#tick();

      let data = player#data();
      let (cameraX, cameraY) = camera#position();
      let (x, y) = (centerX +. (data.x -. cameraX), centerY +. (data.y -. cameraY));

      let enemyData = predator#data();
      let (enemyX, enemyY) = (centerX +. (enemyData.x -. cameraX), centerY +. (enemyData.y -. cameraY));

      Pixi.Sprite.position(my_hero, x, y);
      Pixi.Sprite.position(enemy, enemyX, enemyY);

      animator#tick();
      enemy_animator#tick();
    });
  };

  Pixi.App.load_textures(textures, callback);
  app;
};
