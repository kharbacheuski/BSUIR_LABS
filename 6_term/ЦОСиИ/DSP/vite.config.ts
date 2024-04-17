import { defineConfig } from 'vite'
import { join } from 'path'

export default defineConfig({
    base: './',
    build: {
        outDir: 'dist',
        rollupOptions: {
            input: {
                index: join(__dirname, './views/index.html'),
                correlation: join(__dirname, './views/correlation.html'),
                convolution: join(__dirname, './views/convolution.html'),
                furie: join(__dirname, './views/furie.html'),
                reject_filter: join(__dirname, './views/reject_filter.html'),
            },
        },
    },
    resolve: {
        alias: [
            {
                find: /^~(.+)/,
                replacement: join(process.cwd(), 'node_modules/$1'),
            },
            {
                find: /^src(.+)/,
                replacement: join(process.cwd(), 'src/$1'),
            },
        ],
    },
    server: {
        host: 'localhost',
        port: 9000,
        open: "./views/index.html",
    },
})