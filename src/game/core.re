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

let inside_x = (a, b) => {
  a.x +. a.width > b.x && a.x < b.x +. b.width;
};

let inside_y = (a, b) => {
  a.y +. a.height > b.y && a.y < b.y +. b.height;
};

let above = (data_a, collider) => {
  let data_b = collider#data();
  data_a.y < data_b.y && inside_x(data_a, data_b);
};

let below = (data_a, collider) => {
  let data_b = collider#data();
  data_a.y +. data_a.height > data_b.y +. data_b.height && inside_x(data_a, data_b);
};

let left_of = (data_a, collider) => {
  let data_b = collider#data();
  data_a.x < data_b.x && inside_y(data_a, data_b);
};

let right_of = (data_a, collider) => {
  let data_b = collider#data();
  data_a.x > data_b.x && inside_y(data_a, data_b);
};

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
