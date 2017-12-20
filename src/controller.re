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
      | false => player#degrade(direction)
      | true => player#advance(direction)
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
    player#tick();
  };

  pri control = d => {
    switch d {
      | Commands.Move(Character.Down) => Control(down)
      | Commands.Move(Character.Up) => Control(up)
      | Commands.Move(Character.Left) => Control(left)
      | Commands.Move(Character.Right) => Control(right)
      | Commands.None => None
    };
  };
}
