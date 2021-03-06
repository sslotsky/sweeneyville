// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Curry   = require("bs-platform/lib/js/curry.js");
var Hashtbl = require("bs-platform/lib/js/hashtbl.js");

function hub() {
  var events = Hashtbl.create(/* None */0, 1);
  return /* record */[
          /* listen */(function ($$event, handler) {
              return Hashtbl.replace(events, $$event, handler);
            }),
          /* ignore */(function ($$event) {
              return Hashtbl.remove(events, $$event);
            }),
          /* listening */(function ($$event) {
              return Hashtbl.mem(events, $$event);
            }),
          /* trigger */(function ($$event, event_response) {
              if (Hashtbl.mem(events, $$event)) {
                var handler = Hashtbl.find(events, $$event);
                return Curry._1(handler, event_response);
              } else {
                return 0;
              }
            })
        ];
}

exports.hub = hub;
/* No side effect */
