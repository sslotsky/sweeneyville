let texture_name = (sequence, frame) =>
 "images/alien_predator_mask/predatormask_" ++ sequence ++ "_" ++ string_of_int(frame) ++ ".png";

let frame_sequence = Animation.frame_sequence_generator(texture_name);

let generator = Animation.sequence_info_generator(texture_name);

let sequence_map: Animation.sequence_map = {
  idle: generator(3, "idle"),
  running: generator(6, "run")
};
