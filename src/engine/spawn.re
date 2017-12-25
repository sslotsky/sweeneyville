open Character;
open Pixi.App;
open Pixi.Sprite;
open Animation;

let spawn = (coords, dimensions, map: sequence_map) => {
  let (x, y) = coords;
  let (width, height) = dimensions;
  let (_, get_path) = map.idle;
  let sprite = sprite(get_path(1));
  set_height(sprite, height);
  set_width(sprite, width);
  let character = character((x, y), dimensions);
  let animator = animator(character, sprite, map);

  (character, sprite, animator);
};
