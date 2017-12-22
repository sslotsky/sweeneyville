type focus =
  | Subject(Character.character)
  | None;

let camera = {
  val focused = ref(None);
  val position = ref((0.0, 0.0));

  pub follow = character => this#focus(Subject(character));

  pub tick = () => {
    let f = focused^;
    switch f {
      | Subject(c) => this#track(c)
      | None => ()
    };
  };

  pub position = () => position^;

  pri focus = sub => focused := sub;
  pri track = (c: Character.character) => {
    let d = c#data();
    position := (d.x, d.y);
  };
};
