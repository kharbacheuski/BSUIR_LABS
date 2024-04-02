const {Pool} = require('pg')

const pool = new Pool({
    name: "postgres",
    user: "postgres",
    password: "Tbis3dt4k7",
    dialect: "postgres",
    host: "localhost",
    port: "5432",
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