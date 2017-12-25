type walkable = bool;

type direction =
  | Up
  | Down
  | Left
  | Right
  | Nowhere;

type game_object =
  | Character
  | Tile(walkable);

type render_data = {
  mutable x: float,
  mutable y: float,
  mutable vx: float,
  mutable vy: float,
  mutable height: float,
  mutable width: float
};

type scene = {
  .
  tick: unit => unit,
  left_bound: unit => float,
  right_bound: unit => float,
  bottom_bound: unit => float,
  top_bound: unit => float,
  height: unit => int,
  width: unit => int,
  renderables: unit => array(renderable)
} and renderable = {
  .
  tick: scene => unit,
  accel: direction => unit,
  decel: direction => unit,
  data: unit => render_data,
  category: game_object,
  turn: direction => unit,
  direction: unit => direction
};

let center = r => (
  r.x +. (r.width /. 2.0),
  r.y +. (r.height /. 2.0)
);

let collision = (a: renderable, b: renderable) => {
  let data_a = a#data();
  let data_b = b#data();

  let (half_width, half_height) = (
    (data_a.width /. 2.0) +. (data_b.width /. 2.0),
    (data_a.height /. 2.0) +. (data_b.height /. 2.0)
  );

  let ((ax, ay), (bx, by)) = (
    center(data_a), center(data_b)
  );

  abs_float(ax -. bx) < half_width && abs_float(ay -. by) < half_height;
};
