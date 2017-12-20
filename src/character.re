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

let max = (a:int, b:int) => {
  let leftGreater = a > b;

  switch leftGreater {
    | true => a
    | false => b
  };
};

let min = (a:int, b:int) => {
  let leftGreater = a > b;

  switch leftGreater {
    | true => b
    | false => a
  };
};

let doIf = (condition, block: unit => unit) => {
  switch condition {
    | true => block()
    | false => ()
  };
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
      | Right => doIf(vx > 0, () => speed := (max(vx - 1, 0), vy))
      | Left => doIf(vx < 0, () => speed := (min(vx + 1, 0), vy))
      | Up => doIf(vy < 0, () => speed := (vx, min(vy + 1, 0)))
      | Down => doIf(vy > 0, () => speed := (vx, max(vy - 1, 0)))
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

  pri turn = (direction) => {
    d := direction;
  };
};
