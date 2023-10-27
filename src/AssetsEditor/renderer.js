const { app, BrowserWindow } = require('electron');
const PIXI = require('pixi.js');

// Initialisation de PIXI
const appPIXI = new PIXI.Application({ width: 800, height: 600 });
document.getElementById('pixiCanvas').appendChild(appPIXI.view);

// Liste des assets (vous pouvez ajouter vos propres images ou noms d'assets)
const assets = ['editor/pata.gif', 'editor/bellmite.png'];

// Chargement des assets
PIXI.Loader.shared.add(assets).load(setup);

function setup() {
    const toolBar = document.getElementById('toolBar');
    assets.forEach(assetName => {
        const btn = document.createElement('button');
        btn.innerHTML = assetName;
        btn.addEventListener('click', () => {
            selectAsset(assetName);
        });
        toolBar.appendChild(btn);
    });
}

function selectAsset(assetName) {
    console.log(`Asset sélectionné: ${assetName}`);
    // Ici, vous pouvez ajouter le code pour afficher ou utiliser l'asset sélectionné avec Pixi
    const texture = PIXI.Loader.shared.resources[assetName].texture;
    const sprite = new PIXI.Sprite(texture);
    appPIXI.stage.addChild(sprite);
}

app.on('ready', () => {
    new BrowserWindow({ width: 900, height: 700, webPreferences: { nodeIntegration: true } })
        .loadFile('index.html');
});
