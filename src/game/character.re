open Renderable;

let character(startX, startY): renderable = {
  val data = {
    x: startX,
    y: startY,
    vx: 0.0,
    vy: 0.0
  };

  val maxSpeed = 8.0;

  pub tick = (scene) => {
    let (x, y) = next_coordinates(scene, (data.x, data.y), (data.vx, data.vy));
    data.x = x;
    data.y = y;
  };

  pub accel = (direction) => {
    let (vx, vy) = accel(direction, (data.vx, data.vy), maxSpeed);
    this#setSpeedIf(true, vx, vy);
  };

  pub decel = (direction) => {
    let (condition, vx, vy) = decel(direction, data.vx, data.vy);
    this#setSpeedIf(condition, vx, vy);
  };

  pub data = () => data;

  pri setSpeedIf = (going, vx, vy) => {
    if (going) {
      data.vx = vx;
      data.vy = vy;
    }
  };
};
