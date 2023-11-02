/*
 * ATTENTION: The "eval" devtool has been used (maybe by default in mode: "development").
 * This devtool is neither made for production nor for readable output files.
 * It uses "eval()" calls to create a separate source file in the browser devtools.
 * If you are trying to read the output file, select a different devtool (https://webpack.js.org/configuration/devtool/)
 * or disable the default devtool with "devtool: false".
 * If you are looking for production-ready output files, see mode: "production" (https://webpack.js.org/configuration/mode/).
 */
/******/ (() => { // webpackBootstrap
/******/ 	var __webpack_modules__ = ({

/***/ "./src/electron/main.js":
/*!******************************!*\
  !*** ./src/electron/main.js ***!
  \******************************/
/***/ ((__unused_webpack_module, __unused_webpack_exports, __webpack_require__) => {

eval("/* provided dependency */ var process = __webpack_require__(/*! ./node_modules/process/browser.js */ \"./node_modules/process/browser.js\");\n/* provided dependency */ var console = __webpack_require__(/*! ./node_modules/console-browserify/index.js */ \"./node_modules/console-browserify/index.js\");\n// src/electron/main.js\nvar _require = __webpack_require__(/*! electron */ \"electron\"),\n  app = _require.app,\n  BrowserWindow = _require.BrowserWindow,\n  ipcMain = _require.ipcMain,\n  Menu = _require.Menu;\nvar remote = (__webpack_require__(/*! electron */ \"electron\").remote);\nvar fs = __webpack_require__(/*! fs */ \"fs\");\nvar path = __webpack_require__(/*! path */ \"path\");\nvar isDev = __webpack_require__(/*! electron-is-dev */ \"electron-is-dev\");\nfunction createWindow() {\n  var win = new BrowserWindow({\n    width: 800,\n    height: 600,\n    webPreferences: {\n      nodeIntegration: true,\n      contextIsolation: false,\n      nodeIntegrationInWorker: true\n    }\n  });\n  var url = isDev ? 'http://localhost:3000' : \"file://\".concat(__dirname, \"/../../build/static/index.html\");\n  win.loadURL(url);\n  var menuTemplate = [{\n    label: 'File',\n    submenu: [{\n      label: 'Open',\n      click: function click() {/* Votre logique ici */}\n    }, {\n      type: 'separator'\n    }, {\n      label: 'Save',\n      click: function click() {\n        win.webContents.send('menu-action', 'save');\n      }\n    }, {\n      label: 'New',\n      click: function click() {\n        win.webContents.send('menu-action', 'new');\n      }\n    }]\n  }, {\n    label: 'Edit',\n    submenu: [{\n      label: 'Undo',\n      click: function click() {/* Votre logique ici */\n      }\n    }]\n  }, {\n    label: 'Layers',\n    submenu: [{\n      label: 'View layer',\n      click: function click() {/* Votre logique ici */\n      }\n    }]\n  }, {\n    label: 'View',\n    submenu: [{\n      role: 'reload'\n    }, {\n      role: 'forceReload'\n    }, {\n      role: 'toggleDevTools'\n    }]\n  }];\n  var menu = Menu.buildFromTemplate(menuTemplate);\n  Menu.setApplicationMenu(menu);\n}\napp.whenReady().then(createWindow);\napp.on('window-all-closed', function () {\n  if (process.platform !== 'darwin') app.quit();\n});\napp.on('activate', function () {\n  if (BrowserWindow.getAllWindows().length === 0) createWindow();\n});\nipcMain.on('save-data', function (event, data, filepath) {\n  fs.writeFile(filepath, JSON.stringify(data), function (err) {\n    if (err) {\n      console.error('Erreur lors de l’enregistrement des données : ', err);\n      // Afficher une erreur à l'utilisateur\n    } else {\n      console.log('Données enregistrées avec succès');\n      // Afficher une confirmation à l'utilisateur\n    }\n  });\n});\n\n//# sourceURL=webpack://map-creator/./src/electron/main.js?");

/***/ }),

/***/ "./node_modules/console-browserify/index.js":
/*!**************************************************!*\
  !*** ./node_modules/console-browserify/index.js ***!
  \**************************************************/
/***/ ((module, __unused_webpack_exports, __webpack_require__) => {

eval("/*global window, global*/\nvar util = __webpack_require__(/*! util */ \"util\")\nvar assert = __webpack_require__(/*! assert */ \"assert\")\nfunction now() { return new Date().getTime() }\n\nvar slice = Array.prototype.slice\nvar console\nvar times = {}\n\nif (typeof global !== \"undefined\" && global.console) {\n    console = global.console\n} else if (typeof window !== \"undefined\" && window.console) {\n    console = window.console\n} else {\n    console = {}\n}\n\nvar functions = [\n    [log, \"log\"],\n    [info, \"info\"],\n    [warn, \"warn\"],\n    [error, \"error\"],\n    [time, \"time\"],\n    [timeEnd, \"timeEnd\"],\n    [trace, \"trace\"],\n    [dir, \"dir\"],\n    [consoleAssert, \"assert\"]\n]\n\nfor (var i = 0; i < functions.length; i++) {\n    var tuple = functions[i]\n    var f = tuple[0]\n    var name = tuple[1]\n\n    if (!console[name]) {\n        console[name] = f\n    }\n}\n\nmodule.exports = console\n\nfunction log() {}\n\nfunction info() {\n    console.log.apply(console, arguments)\n}\n\nfunction warn() {\n    console.log.apply(console, arguments)\n}\n\nfunction error() {\n    console.warn.apply(console, arguments)\n}\n\nfunction time(label) {\n    times[label] = now()\n}\n\nfunction timeEnd(label) {\n    var time = times[label]\n    if (!time) {\n        throw new Error(\"No such label: \" + label)\n    }\n\n    delete times[label]\n    var duration = now() - time\n    console.log(label + \": \" + duration + \"ms\")\n}\n\nfunction trace() {\n    var err = new Error()\n    err.name = \"Trace\"\n    err.message = util.format.apply(null, arguments)\n    console.error(err.stack)\n}\n\nfunction dir(object) {\n    console.log(util.inspect(object) + \"\\n\")\n}\n\nfunction consoleAssert(expression) {\n    if (!expression) {\n        var arr = slice.call(arguments, 1)\n        assert.ok(false, util.format.apply(null, arr))\n    }\n}\n\n\n//# sourceURL=webpack://map-creator/./node_modules/console-browserify/index.js?");

/***/ }),

/***/ "./node_modules/process/browser.js":
/*!*****************************************!*\
  !*** ./node_modules/process/browser.js ***!
  \*****************************************/
/***/ ((module) => {

eval("// shim for using process in browser\nvar process = module.exports = {};\n\n// cached from whatever global is present so that test runners that stub it\n// don't break things.  But we need to wrap it in a try catch in case it is\n// wrapped in strict mode code which doesn't define any globals.  It's inside a\n// function because try/catches deoptimize in certain engines.\n\nvar cachedSetTimeout;\nvar cachedClearTimeout;\n\nfunction defaultSetTimout() {\n    throw new Error('setTimeout has not been defined');\n}\nfunction defaultClearTimeout () {\n    throw new Error('clearTimeout has not been defined');\n}\n(function () {\n    try {\n        if (typeof setTimeout === 'function') {\n            cachedSetTimeout = setTimeout;\n        } else {\n            cachedSetTimeout = defaultSetTimout;\n        }\n    } catch (e) {\n        cachedSetTimeout = defaultSetTimout;\n    }\n    try {\n        if (typeof clearTimeout === 'function') {\n            cachedClearTimeout = clearTimeout;\n        } else {\n            cachedClearTimeout = defaultClearTimeout;\n        }\n    } catch (e) {\n        cachedClearTimeout = defaultClearTimeout;\n    }\n} ())\nfunction runTimeout(fun) {\n    if (cachedSetTimeout === setTimeout) {\n        //normal enviroments in sane situations\n        return setTimeout(fun, 0);\n    }\n    // if setTimeout wasn't available but was latter defined\n    if ((cachedSetTimeout === defaultSetTimout || !cachedSetTimeout) && setTimeout) {\n        cachedSetTimeout = setTimeout;\n        return setTimeout(fun, 0);\n    }\n    try {\n        // when when somebody has screwed with setTimeout but no I.E. maddness\n        return cachedSetTimeout(fun, 0);\n    } catch(e){\n        try {\n            // When we are in I.E. but the script has been evaled so I.E. doesn't trust the global object when called normally\n            return cachedSetTimeout.call(null, fun, 0);\n        } catch(e){\n            // same as above but when it's a version of I.E. that must have the global object for 'this', hopfully our context correct otherwise it will throw a global error\n            return cachedSetTimeout.call(this, fun, 0);\n        }\n    }\n\n\n}\nfunction runClearTimeout(marker) {\n    if (cachedClearTimeout === clearTimeout) {\n        //normal enviroments in sane situations\n        return clearTimeout(marker);\n    }\n    // if clearTimeout wasn't available but was latter defined\n    if ((cachedClearTimeout === defaultClearTimeout || !cachedClearTimeout) && clearTimeout) {\n        cachedClearTimeout = clearTimeout;\n        return clearTimeout(marker);\n    }\n    try {\n        // when when somebody has screwed with setTimeout but no I.E. maddness\n        return cachedClearTimeout(marker);\n    } catch (e){\n        try {\n            // When we are in I.E. but the script has been evaled so I.E. doesn't  trust the global object when called normally\n            return cachedClearTimeout.call(null, marker);\n        } catch (e){\n            // same as above but when it's a version of I.E. that must have the global object for 'this', hopfully our context correct otherwise it will throw a global error.\n            // Some versions of I.E. have different rules for clearTimeout vs setTimeout\n            return cachedClearTimeout.call(this, marker);\n        }\n    }\n\n\n\n}\nvar queue = [];\nvar draining = false;\nvar currentQueue;\nvar queueIndex = -1;\n\nfunction cleanUpNextTick() {\n    if (!draining || !currentQueue) {\n        return;\n    }\n    draining = false;\n    if (currentQueue.length) {\n        queue = currentQueue.concat(queue);\n    } else {\n        queueIndex = -1;\n    }\n    if (queue.length) {\n        drainQueue();\n    }\n}\n\nfunction drainQueue() {\n    if (draining) {\n        return;\n    }\n    var timeout = runTimeout(cleanUpNextTick);\n    draining = true;\n\n    var len = queue.length;\n    while(len) {\n        currentQueue = queue;\n        queue = [];\n        while (++queueIndex < len) {\n            if (currentQueue) {\n                currentQueue[queueIndex].run();\n            }\n        }\n        queueIndex = -1;\n        len = queue.length;\n    }\n    currentQueue = null;\n    draining = false;\n    runClearTimeout(timeout);\n}\n\nprocess.nextTick = function (fun) {\n    var args = new Array(arguments.length - 1);\n    if (arguments.length > 1) {\n        for (var i = 1; i < arguments.length; i++) {\n            args[i - 1] = arguments[i];\n        }\n    }\n    queue.push(new Item(fun, args));\n    if (queue.length === 1 && !draining) {\n        runTimeout(drainQueue);\n    }\n};\n\n// v8 likes predictible objects\nfunction Item(fun, array) {\n    this.fun = fun;\n    this.array = array;\n}\nItem.prototype.run = function () {\n    this.fun.apply(null, this.array);\n};\nprocess.title = 'browser';\nprocess.browser = true;\nprocess.env = {};\nprocess.argv = [];\nprocess.version = ''; // empty string to avoid regexp issues\nprocess.versions = {};\n\nfunction noop() {}\n\nprocess.on = noop;\nprocess.addListener = noop;\nprocess.once = noop;\nprocess.off = noop;\nprocess.removeListener = noop;\nprocess.removeAllListeners = noop;\nprocess.emit = noop;\nprocess.prependListener = noop;\nprocess.prependOnceListener = noop;\n\nprocess.listeners = function (name) { return [] }\n\nprocess.binding = function (name) {\n    throw new Error('process.binding is not supported');\n};\n\nprocess.cwd = function () { return '/' };\nprocess.chdir = function (dir) {\n    throw new Error('process.chdir is not supported');\n};\nprocess.umask = function() { return 0; };\n\n\n//# sourceURL=webpack://map-creator/./node_modules/process/browser.js?");

/***/ }),

/***/ "assert":
/*!*************************!*\
  !*** external "assert" ***!
  \*************************/
/***/ ((module) => {

"use strict";
module.exports = require("assert");

/***/ }),

/***/ "electron":
/*!***************************!*\
  !*** external "electron" ***!
  \***************************/
/***/ ((module) => {

"use strict";
module.exports = require("electron");

/***/ }),

/***/ "electron-is-dev":
/*!**********************************!*\
  !*** external "electron-is-dev" ***!
  \**********************************/
/***/ ((module) => {

"use strict";
module.exports = require("electron-is-dev");

/***/ }),

/***/ "util":
/*!***********************!*\
  !*** external "util" ***!
  \***********************/
/***/ ((module) => {

"use strict";
module.exports = require("util");

/***/ }),

/***/ "fs":
/*!*********************!*\
  !*** external "fs" ***!
  \*********************/
/***/ ((module) => {

"use strict";
module.exports = require("fs");

/***/ }),

/***/ "path":
/*!***********************!*\
  !*** external "path" ***!
  \***********************/
/***/ ((module) => {

"use strict";
module.exports = require("path");

/***/ })

/******/ 	});
/************************************************************************/
/******/ 	// The module cache
/******/ 	var __webpack_module_cache__ = {};
/******/ 	
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/ 		// Check if module is in cache
/******/ 		var cachedModule = __webpack_module_cache__[moduleId];
/******/ 		if (cachedModule !== undefined) {
/******/ 			return cachedModule.exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = __webpack_module_cache__[moduleId] = {
/******/ 			// no module.id needed
/******/ 			// no module.loaded needed
/******/ 			exports: {}
/******/ 		};
/******/ 	
/******/ 		// Execute the module function
/******/ 		__webpack_modules__[moduleId](module, module.exports, __webpack_require__);
/******/ 	
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/ 	
/************************************************************************/
/******/ 	
/******/ 	// startup
/******/ 	// Load entry module and return exports
/******/ 	// This entry module can't be inlined because the eval devtool is used.
/******/ 	var __webpack_exports__ = __webpack_require__("./src/electron/main.js");
/******/ 	
/******/ })()
;