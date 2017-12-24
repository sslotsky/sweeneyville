type scene = {
  .
  tick: unit => unit,
  left_bound: unit => float,
  right_bound: unit => float,
  bottom_bound: unit => float,
  top_bound: unit => float,
  height: unit => int,
  width: unit => int
};

let scene(width, height, characters) = {
  pub tick = () => {
    Array.iter(c => c#tick(this), characters);
  };

  pub left_bound = () => 0.0 -. (float_of_int(width) /. 2.0);
  pub right_bound = () => float_of_int(width) /. 2.0;
  pub bottom_bound = () => float_of_int(height) /. 2.0;
  pub top_bound = () => 0.0 -. (float_of_int(height) /. 2.0);
  pub width = () => width;
  pub height = () => height;
};
