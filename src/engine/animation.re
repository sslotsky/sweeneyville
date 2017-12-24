open Renderable;

type sequence =
  | Running
  | Idle;

type sequence_info = (int, int => string);

type sequence_map = {
  idle: sequence_info,
  running: sequence_info
};

type texture_name = (string, int) => string;

let sequence_info_generator = (get_name: texture_name) => {
  let path = name => frame => get_name(name, frame);
  (num_frames, seq_name) => (num_frames, path(seq_name));
};

let frame_sequence_generator = (get_name: texture_name) =>
  (name, num_frames) =>
    Array.map(n => get_name(name, n), Reasonable.range(1, num_frames));

let animator(player, sprite, map: sequence_map) = {
  val ticks = ref(0);
  val frame = ref(1);
  val seq = ref(Idle);
  val freq = ref(3);
  val current_map = ref(map);

  pub tick = () => {
    ticks := ticks^ + 1;
    if (ticks^ == freq^) {
      this#animate();
      ticks := 0;
    }
  };

  pub set_freq = f => freq := f;
  pub set_map = map => {
    frame := 1;
    current_map := map;
  };

  pri animate = () => {
    let (d: render_data) = player#data();
    let moving = d.vx != 0.0 || d.vy != 0.0;
    let nextSeq = moving ? Running : Idle;

    if (nextSeq != seq^) {
      frame := 1;
      seq := nextSeq;
    } else {
      frame := frame^ == this#max_frames() ? 1 : frame^ + 1;
    };

    this#update_texture();
  };

  pri current_info = () => {
    let map = current_map^;
    switch seq^ {
      | Idle => map.idle
      | Running => map.running
    };
  };

  pri max_frames = () => {
    let (frame, _) = this#current_info();
    frame;
  };

  pri update_texture = () => {
    let (_, get_path) = this#current_info();

    Pixi.Sprite.setTexture(sprite, Pixi.App.texture(get_path(frame^)));
  };
};
