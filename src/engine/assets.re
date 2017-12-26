  let textures = Array.concat(
    [
      [|"images/space.jpg", "images/tiles.jpeg"|],
      Predator.frame_sequence("idle", 3),
      Predator.frame_sequence("run", 6),
      Hero.frame_sequence("Idle", 16),
      Hero.frame_sequence("Run", 20)
    ]
  );
