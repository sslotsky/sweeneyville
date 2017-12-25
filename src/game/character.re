open Core;

module CharacterObject = {
  include Renderable;

  let category = Character;
};

module Character = Renderable.MakeGameObject(CharacterObject);

let character = Character.spawn;
