type audio;
[@bs.new] external audio : string => audio = "Audio";
[@bs.send] external play_audio : (audio) => unit = "play";

let play_audio = file => play_audio(audio(file));

open Pixi;
open Spawn;
open Tiler;
open Events;

let start = () => {
  let app = App.start();

  let callback = (_, _) => {
    let sprite_size = 75.0;
    let tile_size = 700.0;

    let hub = hub();
    hub.listen(Collided, (_) => {
      Js.log("Custom collision event!");
    });

    let hero = spawn((0.0, 0.0), (sprite_size, sprite_size), Hero.sequence_map, hub);
    let enemy = spawn((100.0, 400.0), (sprite_size, sprite_size), Predator.sequence_map, Events.hub());
    let tile = make_tile((0.0, 100.0), (tile_size, tile_size), "images/tiles.jpeg", Events.hub());

    Engine.boot(
      ~app=app,
      ~hero=hero,
      ~enemies=[|enemy|],
      ~tiles=[|tile|],
      ~background="images/space.jpg"
    );

    play_audio("sounds/01-01- Traveller.mp3");
  };

  App.load_textures(Assets.textures, callback);
  app;
} ;
