open Core;

module type GameObject = {
  let category: game_object;
  let next_coordinates: (scene, (float, float), (float, float)) => (float, float);
  let accel: (direction, (float, float), float) => (float, float);
  let decel: (direction, float, float) => (bool, float, float);
  let check_collisions: (renderable, array(renderable)) => unit;
};

module MakeGameObject = (ObjectType: GameObject) => {
  let spawn((start_x, start_y), (height, width)): renderable = {
    val direction = ref(Nowhere);

    val data =  {
      height,
      width,
      x: start_x,
      y: start_y,
      vx: 0.0,
      vy: 0.0
    };

    val maxSpeed = 8.0;

    pub category = ObjectType.category;

    pub turn = d => direction := d;
    pub direction = () => direction^;

    pub tick = (scene) => {
      let (x, y) = ObjectType.next_coordinates(scene, (data.x, data.y), (data.vx, data.vy));
      data.x = x;
      data.y = y;
      ObjectType.check_collisions(this, scene#renderables());
    };

    pub accel = (direction) => {
      let (vx, vy) = ObjectType.accel(direction, (data.vx, data.vy), maxSpeed);
      this#setSpeedIf(true, vx, vy);
    };

    pub decel = (direction) => {
      let (condition, vx, vy) = ObjectType.decel(direction, data.vx, data.vy);
      this#setSpeedIf(condition, vx, vy);
    };

    pub data = () => {
      let {x, y, vx, vy, height, width} = data;
      {x, y, vx, vy, height, width};
    };

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

  let new_x = (max(scene#left_bound(), min(scene#right_bound(), x +. vx)));
  let new_y = (max(scene#top_bound(), min(scene#bottom_bound(), y +. vy)));

  (new_x, new_y);
};

let accel = (direction, speed, maxSpeed) => {
  let (vx, vy) = speed;
  switch direction {
    | Right => (min(vx +. 0.2, maxSpeed), vy)
    | Left => (max(vx -. 0.2, 0.0 -. maxSpeed), vy)
    | Up => (vx, max(vy -. 0.2, 0.0 -. maxSpeed))
    | Down => (vx, min(vy +. 0.2, maxSpeed))
    | Nowhere => (vx, vy)
  };
};

let decel = (direction, vx, vy) => {
  switch direction {
    | Right => (vx > 0.0, max(vx -. 0.2, 0.0), vy)
    | Left => (vx < 0.0, min(vx +. 0.2, 0.0), vy)
    | Up => (vy < 0.0, vx, min(vy +. 0.2, 0.0))
    | Down => (vy > 0.0, vx, max(vy -. 0.2, 0.0))
    | Nowhere => (false, vx, vy)
  };
};

let check_collisions = (obj, renderables) => {
  Array.iter(r => {
    if (r !== obj && collision(r, obj)) {
      Js.log("collision");
    };
  }, renderables);
};
