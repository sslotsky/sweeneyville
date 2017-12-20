type direction =
  | Up
  | Down
  | Left
  | Right
  | None;

type data = {
  x: int,
  y: int,
  vx: int,
  vy: int,
  direction: direction
};

let character(startX, startY) = {
  val position = ref((startX, startY));
  val speed = ref((5, 5));
  val d = ref(Right);

  pub move = (direction: direction) => {
    this#turn(direction);

    let (x, y) = position^;
    let (vx, vy) = speed^;

    switch direction {
    | Right => position := (x + vx, y)
    | Left => position := (x - vx, y)
    | Up => position := (x, y - vy)
    | Down => position := (x, y + vy)
    };
  };

  pub place = (newX, newY) => {
    position := (newX, newY);
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

  pri turn = (direction) => {
    d := direction;
  };
};
