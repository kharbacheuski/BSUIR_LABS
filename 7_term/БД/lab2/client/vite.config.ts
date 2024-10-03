import { defineConfig, loadEnv } from 'vite'
import react from '@vitejs/plugin-react'
import tsconfigPaths from 'vite-tsconfig-paths';

export default defineConfig(({ command, mode }) => {
	const env = loadEnv(mode, process.cwd(), '');
	
	return {
		plugins: [react(), tsconfigPaths()],
		build: {
			outDir: 'public',
		},
		define: {
            'process.env.REACT_APP_BASE_API_URL': JSON.stringify(env.REACT_APP_BASE_API_URL),
        },
		server: {
			port: 3000,
		},
	}
})
