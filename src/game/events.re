open Core;

type event_type =
  | Tick
  | Collided;

type collided = renderable;
type collided_with = renderable;
type previous_state = render_data;

type event_response =
  | Tock(renderable, scene)
  | Collision(collided, collided_with, previous_state);

type event_handler = event_response => unit;

type hub = {
  listen: (event_type, event_handler) => unit,
  ignore: event_type => unit,
  listening: event_type => bool,
  trigger: (event_type, event_response) => unit
};

let hub = () => {
  let events = Hashtbl.create(1);

  {
    listen: (event, handler) => Hashtbl.replace(events, event, handler),
    ignore: event => Hashtbl.remove(events, event),
    listening: event => Hashtbl.mem(events, event),
    trigger: (event, event_response) => {
      if (Hashtbl.mem(events, event)) {
        let handler = Hashtbl.find(events, event);
        handler(event_response);
      };
    }
  };
};
