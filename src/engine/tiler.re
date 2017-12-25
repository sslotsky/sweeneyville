open Tile;
open Pixi.App;

let make_tile(coords, dimensions, path) = {
  let (x, y) = dimensions;
  let sprite = tiling_sprite(texture(path), int_of_float(x), int_of_float(y));
  let tile = spawn(coords, dimensions);

  (sprite, tile);
};
