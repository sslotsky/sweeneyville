open Core;
open Reasonable;

module type GameObject = {
  let category: game_object;
  let next_coordinates: (scene, (float, float), (float, float)) => (float, float);
  let accel: (direction, (float, float), float) => (float, float);
  let decel: (direction, float, float) => (bool, float, float);
  let colliders: (renderable, array(renderable)) => array(renderable);
};

module MakeGameObject = (ObjectType: GameObject) => {
  let spawn((start_x, start_y), (width, height)): renderable = {
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

    pub turn = d => {
      switch d {
        | Right | Left => direction := d
        | _ => ()
      };
    };

    pub direction = () => direction^;

    pub tick = (scene) => {
      let (current_x, current_y) = (data.x, data.y);
      let (x, y) = ObjectType.next_coordinates(scene, (data.x, data.y), (data.vx, data.vy));
      data.x = x;
      data.y = y;

      let previous_state = {...data, x: current_x, y: current_y};

      let colliders = ObjectType.colliders(this, scene#renderables());

      Array.iter(c => {
        if (above(previous_state, c) || below(previous_state, c)) {
          data.vy = 0.0;
          data.y = current_y;
        };

        if (right_of(previous_state, c) || left_of(previous_state, c)) {
          data.vx = 0.0;
          data.x = current_x;
        };
      }, colliders);
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

let colliders = (obj, renderables) => {
  select(renderables, r => r !== obj && collision(r, obj));
};
