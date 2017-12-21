type sequence =
  | Running
  | Idle;

type sequence_info = (int, int => string);

type sequence_map = {
  idle: sequence_info,
  running: sequence_info
};

let animator(player, sprite, map: sequence_map) = {
  val ticks = ref(0);
  val frame = ref(1);
  val seq = ref(Idle);

  pub tick = () => {
    ticks := ticks^ + 1;
    if (ticks^ == 3) {
      this#animate();
      ticks := 0;
    }
  };

  pri animate = () => {
    let (d: Character.data) = player#data();
    let moving = d.vx != 0.0 || d.vy != 0.0;
    let nextSeq = moving ? Running : Idle;

    if (nextSeq != seq^) {
      frame := 1;
      seq := nextSeq;
    } else {
      frame := frame^ == this#maxFrames() ? 1 : frame^ + 1;
    };

    this#updateTexture();
  };

  pri current_info = () => {
    switch seq^ {
      | Idle => map.idle
      | Running => map.running
    };
  };

  pri maxFrames = () => {
    let (frame, _) = this#current_info();
    frame;
  };

  pri updateTexture = () => {
    let info = switch seq^ {
      | Idle => map.idle
      | Running => map.running
    };

    let (_, getPath) = this#current_info();

    Pixi.Sprite.setTexture(sprite, Pixi.App.texture(getPath(frame^)));
  };
};
