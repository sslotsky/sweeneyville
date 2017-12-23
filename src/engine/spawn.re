let spawn = (coords, map: Animation.sequence_map) => {
  let (x, y) = coords;
  let (_, get_path) = map.idle;
  let sprite = Pixi.App.sprite(get_path(1));
  let character = Character.character(x, y);
  let animator = Animation.animator(character, sprite, map);

  (character, sprite, animator);
};
