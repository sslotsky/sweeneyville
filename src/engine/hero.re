let texture_name = (sequence, frame) =>
 "images/hero/" ++ sequence ++ " (" ++ string_of_int(frame) ++ ").png";

let frame_sequence = Animation.frame_sequence_generator(texture_name);

let generator = Animation.sequence_info_generator(texture_name);

let sequence_map: Animation.sequence_map = {
  idle: generator(16, "Idle"),
  running: generator(20, "Run")
};
