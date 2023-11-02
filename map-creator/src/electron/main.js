// src/electron/main.js
const { app, BrowserWindow, ipcMain, Menu } = require('electron');
const remote = require('electron').remote;
const fs = require('fs');
const path = require('path');
const isDev = require('electron-is-dev');

function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
            nodeIntegrationInWorker: true,
        },
    });

    const url = isDev
        ? 'http://localhost:3000'
        : `file://${__dirname}/../../build/static/index.html`;

    win.loadURL(url);

    const menuTemplate = [
        {
            label: 'File',
            submenu: [
                { label: 'Open', click: () => { /* Votre logique ici */ } },
                { type: 'separator' },
                {
                    label: 'Save',
                    click: () => {
                        win.webContents.send('menu-action', 'save');
                    }
                },
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

ipcMain.on('save-data', (event, data, filepath) =>
{
    fs.writeFile(filepath, JSON.stringify(data), (err) => {
        if (err) {
            console.error('Erreur lors de l’enregistrement des données : ', err);
            // Afficher une erreur à l'utilisateur
        } else {
            console.log('Données enregistrées avec succès');
            // Afficher une confirmation à l'utilisateur
        }
    });

});
