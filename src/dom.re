type win;
type event;
[@bs.val] external window : win = "window";
[@bs.send] external listen : (win, string, event => unit) => unit = "addEventListener";
[@bs.get] external getKeycode : (event) => int = "keyCode";

let window = () => window;
let listen = (name, h) => listen(window(), name, h);
let keycode = event => getKeycode(event);

let keyMap = (e) => {
  let code = keycode(e);
  switch code {
    | 40 => Character.Down
    | 38 => Character.Up
    | 37 => Character.Left
    | 39 => Character.Right
    | _ => Character.None
  };
};
