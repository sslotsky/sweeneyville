// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';


function $$window$1() {
  return window;
}

function listen(name, h) {
  window.addEventListener(name, h);
  return /* () */0;
}

function key_map(e) {
  var code = e.keyCode;
  var switcher = code - 37 | 0;
  if (switcher > 3 || switcher < 0) {
    return /* None */0;
  } else {
    switch (switcher) {
      case 0 : 
          return /* Move */[/* Left */2];
      case 1 : 
          return /* Move */[/* Up */0];
      case 2 : 
          return /* Move */[/* Right */3];
      case 3 : 
          return /* Move */[/* Down */1];
      
    }
  }
}

exports.$$window = $$window$1;
exports.listen   = listen;
exports.key_map  = key_map;
/* No side effect */