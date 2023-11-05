// pixi/pixiManager.js
import * as PIXI from 'pixi.js';

export const app = new PIXI.Application({
    width: 800,
    height: 600,
    backgroundColor: 0x1099bb,
});

document.body.appendChild(app.view);
