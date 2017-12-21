type win;
type event;
[@bs.val] external window : win = "window";
[@bs.send] external listen : (win, string, event => unit) => unit = "addEventListener";
[@bs.get] external getKeyCode : (event) => int = "keyCode";

let window = () => window;
let listen = (name, h) => listen(window(), name, h);

let key_map = (e) => {
  let code = getKeyCode(e);
  switch code {
    | 40 => Commands.Move(Character.Down)
    | 38 => Commands.Move(Character.Up)
    | 37 => Commands.Move(Character.Left)
    | 39 => Commands.Move(Character.Right)
    | _ => Commands.None
  };
};
