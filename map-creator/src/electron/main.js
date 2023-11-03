// src/electron/main.js
const { app, BrowserWindow, Menu, ipcMain, dialog } = require('electron');
const isDev = require('electron-is-dev');
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
        ? 'http://localhost:3000'
        : `file://${__dirname}/../../build/index.html`;

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
                    label: 'Undo', click: () => {
                    }
                },
            ]
        },
        {
            label: 'Layers',
            submenu: [
                {
                    label: 'View layer', click: () => {
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

    ipcMain.on('save-dialog', (event, formattedJson) => {
        const mainWindow = BrowserWindow.getFocusedWindow() || BrowserWindow.getAllWindows()[0];
        dialog.showSaveDialog(mainWindow, {
            title: 'Sauvegarder les données',
            filters: [{ name: 'JSON', extensions: ['json'] }],
            modal: true
        }).then(file => {
            if (!file.canceled && file.filePath) {
                console.log(formattedJson);
                fs.writeFileSync(file.filePath.toString(), formattedJson);
                event.sender.send('save-success');
            }
        }).catch(err => {
            console.log(err);
            event.sender.send('save-failed');
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
