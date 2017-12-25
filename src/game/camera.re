open Core;

type focus =
  | Subject(renderable)
  | None;

let camera = {
  val focused = ref(None);
  val position = ref((0.0, 0.0));
  val clampedX = ref(false);
  val clampedY = ref(false);

  pub follow = character => this#focus(Subject(character));

  pub tick = () => {
    let f = focused^;
    switch f {
      | Subject(c) => this#track(c)
      | None => ()
    };
  };

  pub position = () => position^;

  pub clampX = () => clampedX := true;
  pub clampY = () => clampedY := true;
  pub unclampX = () => clampedX := false;
  pub unclampY = () => clampedY := false;

  pri focus = sub => focused := sub;
  pri track = (c: renderable) => {
    let (x, y) = position^;
    let d = c#data();

    let newX = clampedX^ ? x : d.x;
    let newY = clampedY^ ? y : d.y;

    position := (newX, newY);
  };
};
