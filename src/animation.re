type sequence =
  | Running
  | Idle;

let animator(player, sprite) = {
  val ticks = ref(0);

  pub tick = () => {
    if (ticks^ == 10) {
      ticks := 0;
    }
  };
};
