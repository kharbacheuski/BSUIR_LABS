const {Pool} = require('pg')

const pool = new Pool({
    name: "postgres",
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD,
    dialect: "postgres",
    host: process.env.DB_HOST,
    port: process.env.DB_PORT,
    max: 20,
    idleTimeoutMillis: 30000,
    connectionTimeoutMillis: 2000,
})

pool.connect().then(() => {
    console.log('Connection has been established successfully.');
}).catch((error) => {
    console.error('Unable to connect to the database: ', error);
});

module.exports = pool