open Pixi;
open Spawn;
open Tiler;

let start = () => {
  let app = App.start();

  let callback = (_, _) => {
    let sprite_size = 75.0;
    let tile_size = 700.0;
    let hero = spawn((0.0, 0.0), (sprite_size, sprite_size), Hero.sequence_map);
    let enemy = spawn((100.0, 400.0), (sprite_size, sprite_size), Predator.sequence_map);
    let tile = make_tile((0.0, 100.0), (tile_size, tile_size), "images/tiles.jpeg");

    Engine.boot(
      ~app=app,
      ~hero=hero,
      ~enemies=[|enemy|],
      ~tiles=[|tile|],
      ~background="images/space.jpg"
    );
  };

  App.load_textures(Assets.textures, callback);
  app;
};
