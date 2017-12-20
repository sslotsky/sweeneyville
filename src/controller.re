type motion =
  | Direction(Character.direction)
  | Idle;

type control = {
  .
  move: unit => unit,
  stop: unit => unit,
  tick: unit => unit
};

let control(player, direction) : control = {
  val moving = ref(false);

  pub move = () => this#setMoving(true);
  pub stop = () => this#setMoving(false);
  pub tick = () => {
    switch moving^ {
      | false => ()
      | true => player#move(direction)
    };
  };

  pri setMoving = m => moving := m;
};

type option =
  | Control(control)
  | None;

let controller(player) = {
  val down = control(player, Character.Down);
  val up = control(player, Character.Up);
  val left = control(player, Character.Left);
  val right = control(player, Character.Right);

  pub move = d => {
    let control = this#control(d);
    switch control {
      | Control(c) => c#move()
      | None => ()
    };
  };

  pub stop = d => {
    let control = this#control(d);
    switch control {
      | Control(c) => c#stop()
      | None => ()
    };
  };

  pub tick = () => {
    List.iter(d => d#tick(), [down, up, left, right]);
  };

  pri control = d => {
    switch d {
      | Character.Down => Control(down)
      | Character.Up => Control(up)
      | Character.Left => Control(left)
      | Character.Right => Control(right)
      | Character.None => None
    };
  };
}
