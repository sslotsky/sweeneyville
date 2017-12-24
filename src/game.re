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

    let (sceneX, sceneY) = (Pixi.App.width(r) * 3, Pixi.App.height(r) * 3);
    let scene = Scene.scene(sceneX, sceneY, [|player, predator|]);

    Pixi.App.addSprite(app, bg);
    Pixi.App.addSprite(app, my_hero);
    Pixi.App.addSprite(app, enemy);

    let controller = Controller.controller(player);

    Dom.listen("keydown", event => {
      let d = Dom.key_map(event);

      controller#move(d);

      switch d {
        | Commands.Move(Renderable.Left) => Pixi.Sprite.rescale(my_hero, -0.2, 0.2)
        | Commands.Move(Renderable.Right) => Pixi.Sprite.rescale(my_hero, 0.2, 0.2)
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
      let data = player#data();

      let gap_left = data.x -. scene#left_bound();
      let gap_right = scene#right_bound() -. data.x;
      let gap_top = abs_float(scene#top_bound() -. data.y);
      let gap_bottom = abs_float(data.y -. scene#bottom_bound());
      let margin = gap => dimension => int_of_float(gap) < dimension / 2;
      let side_margin = gap => margin(gap)(Pixi.App.width(r));
      let v_margin = gap => margin(gap)(Pixi.App.height(r));

      if (side_margin(gap_left) || side_margin(gap_right)) {
        camera#clampX();
      } else {
        camera#unclampX();
      };

      if (v_margin(gap_top) || v_margin(gap_bottom)) {
        camera#clampY();
      } else {
        camera#unclampY();
      };

      controller#tick();
      scene#tick();
      camera#tick();

      let (cameraX, cameraY) = camera#position();
      let (x, y) = (centerX +. (data.x -. cameraX), centerY +. (data.y -. cameraY));

      let enemyData = predator#data();
      let (enemyX, enemyY) = (centerX +. (enemyData.x -. cameraX), centerY +. (enemyData.y -. cameraY));

      let put = (sprite, x, y) => {
        let (center_x, center_y) = Pixi.Sprite.center_offset(sprite);
        Pixi.Sprite.position(sprite, x -. center_x, y -. center_y);
      };

      put(my_hero, x, y);
      put(enemy, enemyX, enemyY);

      animator#tick();
      enemy_animator#tick();
    });
  };

  Pixi.App.load_textures(textures, callback);
  app;
};
