const path = require('path');
const webpack = require('webpack');
const nodeExternals = require('webpack-node-externals');
const NodePolyfillPlugin = require('node-polyfill-webpack-plugin');

module.exports = {
    mode: 'development',
    target: 'electron-main',
    entry: './src/electron/main.js',
    output: {
        path: path.join(__dirname, 'electron'),
        filename: 'electron.bundle.js'
    },
    module: {
        rules: [
            {
                test: /\.(js|jsx)$/,
                exclude: /node_modules/,
                use: {
                    loader: 'babel-loader',
                    options: {
                        presets: ['@babel/preset-env', '@babel/preset-react']
                    }
                }
            }
        ]
    },
    externals: [nodeExternals()],
    node: {
        __dirname: false,
        __filename: false
    },
    plugins: [
        new NodePolyfillPlugin()
    ]
};
