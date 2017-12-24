type direction =
  | Up
  | Down
  | Left
  | Right;

type render_data = {
  mutable x: float,
  mutable y: float,
  mutable vx: float,
  mutable vy: float
};

type renderable = {
  .
  tick: Scene.scene => unit,
  accel: direction => unit,
  decel: direction => unit,
  data: unit => render_data
};

module type GameObject = {
  let next_coordinates: (Scene.scene, (float, float), (float, float)) => (float, float);
  let accel: (direction, (float, float), float) => (float, float);
  let decel: (direction, float, float) => (bool, float, float);
};

module MakeGameObject = (ObjectType: GameObject) => {
  let spawn(start_x, start_y): renderable = {
    val data =  {
      x: start_x,
      y: start_y,
      vx: 0.0,
      vy: 0.0
    };

    val maxSpeed = 8.0;

    pub tick = (scene) => {
      let (x, y) = ObjectType.next_coordinates(scene, (data.x, data.y), (data.vx, data.vy));
      data.x = x;
      data.y = y;
    };

    pub accel = (direction) => {
      let (vx, vy) = ObjectType.accel(direction, (data.vx, data.vy), maxSpeed);
      this#setSpeedIf(true, vx, vy);
    };

    pub decel = (direction) => {
      let (condition, vx, vy) = ObjectType.decel(direction, data.vx, data.vy);
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
};

let next_coordinates = (scene, position, speed) => {
  let (x, y) = position;
  let (vx, vy) = speed;

  let newX = (max(scene#left_bound(), min(scene#right_bound(), x +. vx)));
  let newY = (max(scene#top_bound(), min(scene#bottom_bound(), y +. vy)));

  (newX, newY);
};

let accel = (direction, speed, maxSpeed) => {
  let (vx, vy) = speed;
  switch direction {
    | Right => (min(vx +. 0.2, maxSpeed), vy)
    | Left => (max(vx -. 0.2, 0.0 -. maxSpeed), vy)
    | Up => (vx, max(vy -. 0.2, 0.0 -. maxSpeed))
    | Down => (vx, min(vy +. 0.2, maxSpeed))
  };
};

let decel = (direction, vx, vy) => {
  switch direction {
    | Right => (vx > 0.0, max(vx -. 0.2, 0.0), vy)
    | Left => (vx < 0.0, min(vx +. 0.2, 0.0), vy)
    | Up => (vy < 0.0, vx, min(vy +. 0.2, 0.0))
    | Down => (vy > 0.0, vx, max(vy -. 0.2, 0.0))
  };
};
