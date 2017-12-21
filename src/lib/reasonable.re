let range = (a, b) => {
  let (x, y) = (min(a, b), max(a, b));

  let rec build = nums => {
    let last = Array.get(nums, Array.length(nums) - 1);
    let finished = (last == y);

    switch finished {
      | true => nums
      | false => build(Array.append(nums, [|last + 1|]))
    };
  };

  build([|x|]);
};
