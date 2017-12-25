module TileObject = {
  include Renderable;

  let category = Core.Tile(false);
  let next_coordinates = (_, (x, y), _) => (x, y);
};

open Renderable;

module Tile = MakeGameObject(TileObject);

let spawn = Tile.spawn;
