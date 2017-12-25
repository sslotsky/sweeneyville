let scene(width, height, renderables) = {
  pub tick = () => {
    this#tick_children(renderables);
  };

  pub left_bound = () => 0.0 -. (float_of_int(width) /. 2.0);
  pub right_bound = () => float_of_int(width) /. 2.0;
  pub bottom_bound = () => float_of_int(height) /. 2.0;
  pub top_bound = () => 0.0 -. (float_of_int(height) /. 2.0);
  pub width = () => width;
  pub height = () => height;
  pub renderables = () => renderables;

  pri tick_children = children =>
    Array.iter(t => t#tick(this), children);
};
