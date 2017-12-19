//import { Application, Sprite, loader } from "pixi.js";
import { start } from "./src/game.bs";

const app = start();
document.body.appendChild(app.view);

//const app = new Application();
//
//
//loader.add("hero", "images/hero/Idle (1).png").load((loader, resources) => {
//  const hero = new Sprite(resources.hero.texture);
//
//  hero.scale.x = 0.2;
//  hero.scale.y = 0.2;
//  hero.x = app.renderer.width / 2;
//  hero.y = app.renderer.height / 2;
//
//  app.stage.addChild(hero);
//
//  function keydown(e) {
//    if (e.which === 39) {
//      hero.x += 1;
//    }
//  }
//
//  const h = getHero(2);
//  debugger;
//
//  window.addEventListener("keydown", keydown, false);
//});
