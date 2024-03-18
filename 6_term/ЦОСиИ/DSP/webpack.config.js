const HtmlWebpackPlugin = require('html-webpack-plugin');
const path = require('path');
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const { CleanWebpackPlugin } = require('clean-webpack-plugin');

const pages = ['index', 'furie', 'correlation', 'convolution'];

const generateHtmlPlugins = () => {
	return pages.map((page) => {
		return new HtmlWebpackPlugin({
			template: `./views/${page}.html`,
			filename: `${page}.html`,
		});
	});
};

module.exports = {
	context: path.resolve(__dirname, './'),
	mode: 'development',
	watch: true,
	entry: {
		main: './src/main.js',
		convolution: './src/charts/convolution.js',
		correlation: './src/charts/correlation.js',
		furie: './src/charts/furie.js',
	},
	output: {
		filename: '[name].built.js',
		path: path.resolve(__dirname, 'dist'),
	},
	resolve: {
		extensions: ['.js', '.json'],
	},
	module: {
		rules: [
			{
				test: /\.js$/,
				loader: 'babel-loader',
			},
			{
				test: /\.(png|jpe?g|gif|webp|svg)(\?.*)?$/,
				loader: 'url-loader',
				options: {
					limit: 10000,
					name: 'images/[contenthash].[ext]',
					publicPath: '../',
				},
			},
			{
				test: /\.(woff2?|eot|ttf|otf)(\?.*)?$/,
				loader: 'url-loader',
				options: {
					limit: 10000,
					name: 'fonts/[name].[ext]',
				},
			},
			{
				test: /\.css$/i,
				use: [MiniCssExtractPlugin.loader, "css-loader"],
			},
		],
	},
	plugins: [
		...generateHtmlPlugins(),
		new MiniCssExtractPlugin(),
		new CleanWebpackPlugin(),
	],
	devServer: {
		open: true,
		static: {
		  	directory: path.resolve(__dirname, 'dist'),
		},
		compress: true,
		port: 9000,
	},
};
