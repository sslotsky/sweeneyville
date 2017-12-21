type direction =
  | Up
  | Down
  | Left
  | Right;

type data = {
  x: int,
  y: int,
  vx: int,
  vy: int,
  direction: direction
};

let character(startX, startY) = {
  val maxSpeed = ref(15);
  val position = ref((startX, startY));
  val speed = ref((0, 0));
  val d = ref(Right);

  pub tick = () => {
    let (x, y) = position^;
    let (vx, vy) = speed^;

    position := (x + vx, y + vy);
  };

  pub place = (newX, newY) => {
    position := (newX, newY);
  };

  pub advance = (direction) => {
    let (vx, vy) = speed^;
    switch direction {
      | Right => speed := (min(vx + 1, maxSpeed^), vy)
      | Left => speed := (max(vx - 1, -maxSpeed^), vy)
      | Up => speed := (vx, max(vy - 1, -maxSpeed^))
      | Down => speed := (vx, min(vy + 1, maxSpeed^))
    };
  };

  pub degrade = (direction) => {
    let (vx, vy) = speed^;
    switch direction {
      | Right => this#setSpeedIf(vx > 0, max(vx - 1, 0), vy)
      | Left => this#setSpeedIf(vx < 0, min(vx + 1, 0), vy)
      | Up => this#setSpeedIf(vy < 0, vx, min(vy + 1, 0))
      | Down => this#setSpeedIf(vy > 0, vx, max(vy - 1, 0))
    };
  };

  pub data = () => {
    let (x, y) = position^;
    let (vx, vy) = speed^;

    {
      x: x,
      y: y,
      vx: vx,
      vy: vy,
      direction: d^
    };
  };

  pri setSpeedIf = (going, vx, vy) => {
    if (going) {
      speed := (vx, vy);
    }
  };

  pri turn = (direction) => {
    d := direction;
  };
};
