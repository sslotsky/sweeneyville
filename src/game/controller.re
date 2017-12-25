open Core;

type motion =
  | Direction(direction)
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
      | false => player#decel(direction)
      | true => player#accel(direction)
    };
  };

  pri setMoving = m => moving := m;
};

type option =
  | Control(control)
  | None;

let controller(player) = {
  val down = control(player, Down);
  val up = control(player, Up);
  val left = control(player, Left);
  val right = control(player, Right);

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
      | Commands.Move(Down) => Control(down)
      | Commands.Move(Up) => Control(up)
      | Commands.Move(Left) => Control(left)
      | Commands.Move(Right) => Control(right)
      | _ => None
    };
  };
}
