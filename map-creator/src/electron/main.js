// src/electron/main.js
const { app, BrowserWindow } = require('electron');
const isDev = require('electron-is-dev');  // ajoutez cette ligne

function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true,
        },
    });

    const url = isDev
        ? 'http://localhost:3000'  // en mode développement, charge localhost:3000
        : `file://${__dirname}/../../build/index.html`;  // en production, charge le fichier HTML buildé

    win.loadURL(url);
}

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit();
});

app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
});
