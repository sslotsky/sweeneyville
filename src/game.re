open Core;
open Pixi;
open Spawn;
open Tiler;

let start = () => {
  let app = App.start();

  let textures =Array.concat(
    [
      [|"images/space.jpg", "images/tiles.jpeg"|],
      Predator.frame_sequence("idle", 3),
      Predator.frame_sequence("run", 6),
      Hero.frame_sequence("Idle", 16),
      Hero.frame_sequence("Run", 20)
    ]
  );

  let callback = (_, _) => {
    let sprite_size = 75.0;
    let tile_size = 170.0;
    let (player, my_hero, animator) = spawn((0.0, 0.0), (sprite_size, sprite_size), Hero.sequence_map);
    let (predator, enemy, enemy_animator) = spawn((100.0, 400.0), (sprite_size, sprite_size), Predator.sequence_map);
    let (tile_sprite, tile) = make_tile((0.0, 100.0), (tile_size, 250.0), "images/tiles.jpeg");

    Sprite.interact(my_hero);
    Sprite.button(my_hero);
    Sprite.listen(my_hero, "mouseover", (_) => {
      Sprite.alpha(my_hero, 0.8);
    });

    Sprite.listen(my_hero, "mouseout", (_) => {
      Sprite.alpha(my_hero, 1.0);
    });

    Sprite.listen(my_hero, "click", (_) => {
      animator#set_map(Predator.sequence_map);
    });

    enemy_animator#set_freq(10);

    let r = App.renderer(app);

    let bg = App.tiling_sprite(App.texture("images/space.jpg"), App.width(r), App.height(r));

    let (sceneX, sceneY) = (App.width(r) * 3, App.height(r) * 3);
    let scene = Scene.scene(sceneX, sceneY, [|player, predator, tile|]);

    App.addSprite(app, bg);
    App.addSprite(app, tile_sprite);
    App.addSprite(app, enemy);
    App.addSprite(app, my_hero);

    let controller = Controller.controller(player);

    Dom.listen("keydown", event => {
      let d = Dom.key_map(event);

      controller#move(d);

      switch d {
        | Commands.Move(d) => player#turn(d)
        | _ => ()
      };
    });

    Dom.listen("keyup", event => {
      let d = Dom.key_map(event);
      controller#stop(d);
    });

    let camera = Camera.camera;
    camera#follow(player);
    let (centerX, centerY) = (float_of_int(App.width(r) / 2), float_of_int(App.height(r) / 2));

    App.add_ticker(app, (_) => {
      let data = player#data();
      let gap_left = data.x -. scene#left_bound();
      let gap_right = scene#right_bound() -. data.x;
      let gap_top = abs_float(scene#top_bound() -. data.y);
      let gap_bottom = abs_float(data.y -. scene#bottom_bound());
      let margin = gap => dimension => int_of_float(gap) < dimension / 2;
      let side_margin = gap => margin(gap)(App.width(r));
      let v_margin = gap => margin(gap)(App.height(r));

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
      animator#tick();
      enemy_animator#tick();

      let (cameraX, cameraY) = camera#position();

      let put = ((renderable, sprite)) => {
        let data = renderable#data();
        let (x, y) = (centerX +. (data.x -. cameraX), centerY +. (data.y -. cameraY));
        let (center_x, center_y) = Sprite.center_offset(sprite);
        Sprite.position(sprite, x -. center_x, y -. center_y);

        let d = renderable#direction();

        switch d {
          | Left => Sprite.flip_left(sprite)
          | Right => Sprite.flip_right(sprite)
          | _ => ()
        };
      };

      let put_tile = ((renderable, sprite)) => {
        let data = renderable#data();
        let (x, y) = (centerX +. (data.x -. cameraX), centerY +. (data.y -. cameraY));
        let (hero_x, hero_y) = Sprite.center_offset(my_hero);
        Sprite.position(sprite, x +. hero_x /. 4.0, y -. hero_y);
      };

      put_tile((tile, tile_sprite));
      put((player, my_hero));
      put((predator, enemy));
    });
  };

  App.load_textures(textures, callback);
  app;
};
