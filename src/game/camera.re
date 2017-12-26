open Core;

type focus =
  | Subject(renderable)
  | None;

let camera = {
  val focused = ref(None);
  val position = ref((0.0, 0.0));
  val clamped_x = ref(false);
  val clamped_y = ref(false);

  pub follow = character => this#focus(Subject(character));

  pub tick = () => {
    let f = focused^;
    switch f {
      | Subject(c) => this#track(c)
      | None => ()
    };
  };

  pub position = () => position^;

  pub clamp_x = () => clamped_x := true;
  pub clamp_y = () => clamped_y := true;
  pub unclamp_x = () => clamped_x := false;
  pub unclamp_y = () => clamped_y := false;

  pri focus = sub => focused := sub;
  pri track = (c: renderable) => {
    let (x, y) = position^;
    let d = c#data();

    let new_x = clamped_x^ ? x : d.x;
    let new_y = clamped_y^ ? y : d.y;

    position := (new_x, new_y);
  };
};
