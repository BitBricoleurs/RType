// src/electron/main.js
const { app, BrowserWindow, Menu, ipcMain } = require('electron');
const isDev = require('electron-is-dev');  // ajoutez cette ligne

function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
        },
    });

    const url = isDev
        ? 'http://localhost:3000'  // en mode développement, charge localhost:3000
        : `file://${__dirname}/../../build/index.html`;  // en production, charge le fichier HTML buildé

    win.loadURL(url);

    const menuTemplate = [
        {
            label: 'File',
            submenu: [
                { label: 'Open', click: () => { /* Votre logique ici */ } },
                { type: 'separator' },
                { label: 'Save', click: () => { /* Votre logique ici */ } },
                {
                    label: 'New',
                    click: () => { win.webContents.send('menu-action', 'new'); }
                }
            ]
        },
        {
            label: 'Edit',
            submenu: [
                {
                    label: 'Undo', click: () => { /* Votre logique ici */
                    }
                },
            ]
        },
        {
            label: 'Layers',
            submenu: [
                {
                    label: 'View layer', click: () => { /* Votre logique ici */
                    }
                },
            ]
        },
        {
            label: 'View',
            submenu: [
                { role: 'reload' },
                { role: 'forceReload' },
                { role: 'toggleDevTools' },
                ]
        }
    ];

    const menu = Menu.buildFromTemplate(menuTemplate);
    Menu.setApplicationMenu(menu);

}

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit();
});

app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
});
