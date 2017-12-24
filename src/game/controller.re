type motion =
  | Direction(Renderable.direction)
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
  val down = control(player, Renderable.Down);
  val up = control(player, Renderable.Up);
  val left = control(player, Renderable.Left);
  val right = control(player, Renderable.Right);

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
      | Commands.Move(Renderable.Down) => Control(down)
      | Commands.Move(Renderable.Up) => Control(up)
      | Commands.Move(Renderable.Left) => Control(left)
      | Commands.Move(Renderable.Right) => Control(right)
      | Commands.None => None
    };
  };
}
