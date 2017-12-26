open Core;
open Pixi;

let boot = (~app, ~hero, ~enemies, ~tiles, ~background) => {
  let (player, my_hero, animator) = hero;

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

  let r = App.renderer(app);

  let bg = App.tiling_sprite(App.texture(background), App.width(r), App.height(r));

  let (scene_x, scene_y) = (App.width(r) * 3, App.height(r) * 3);

  let objects = Array.concat([
    Array.map(
      ((obj, _)) => obj,
      tiles
    ),
    Array.map(
      ((obj, _, _)) => obj,
      enemies
    ),
  ]);

  let sprites = Array.concat([
    Array.map(
      ((_, sprite)) => sprite,
      tiles
    ),
    Array.map(
      ((_, sprite, _)) => sprite,
      enemies
    ),
  ]);

  let scene = Scene.scene(scene_x, scene_y, Array.append([|player|], objects));

  App.addSprites(app, Array.append([|bg, my_hero|], sprites));

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
  let (app_center_x, app_center_y) = (float_of_int(App.width(r) / 2), float_of_int(App.height(r) / 2));

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
      camera#clamp_x();
    } else {
      camera#unclamp_x();
    };

    if (v_margin(gap_top) || v_margin(gap_bottom)) {
      camera#clamp_y();
    } else {
      camera#unclamp_y();
    };

    controller#tick();
    scene#tick();
    camera#tick();
    animator#tick();

    Array.iter(((_, _, animator)) => animator#tick(), enemies);

    let (camera_x, camera_y) = camera#position();

    let put = ((renderable, sprite)) => {
      let data = renderable#data();
      let (x, y) = (app_center_x +. (data.x -. camera_x), app_center_y +. (data.y -. camera_y));
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
      let (x, y) = (app_center_x +. (data.x -. camera_x), app_center_y +. (data.y -. camera_y));
      let (hero_center_x, hero_center_y) = Sprite.center_offset(my_hero);
      let (tile_center, _) = Sprite.center_offset(sprite);
      Sprite.position(sprite, (x -. hero_center_x) +. tile_center -. hero_center_x, y -. hero_center_y);
    };

    Array.iter(((tile, sprite)) => put_tile((tile, sprite)), tiles);

    put((player, my_hero));

    Array.iter(((enemy, sprite, _)) => put((enemy, sprite)), enemies);
  });
};
