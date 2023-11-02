// src/electron/main.js
const { app, BrowserWindow, Menu, ipcMain, dialog } = require('electron');
const isDev = require('electron-is-dev');  // ajoutez cette ligne
const fs = require('fs');
const path = require('path');

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

    ipcMain.on('save-dialog', (event) => {
        dialog.showSaveDialog({
            title: 'Sauvegarder les données',
            // Spécifiez d'autres options ici si nécessaire
        }).then(file => {
            if (!file.canceled) {
                fs.writeFileSync(file.filePath.toString(), JSON.stringify({
                    // Vous devez envoyer les données à enregistrer depuis le processus de rendu
                }));
            }
        }).catch(err => {
            console.log(err);
        });
    });

}

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit();
});

app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
});
