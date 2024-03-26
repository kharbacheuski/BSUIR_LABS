const { Sequelize } = require("sequelize");

const databaseOptions = {
    name: "usersdb",
    user: "root",
    password: "password",
    dialect: "mysql",
    host: "localhost",
}

const sequelize = new Sequelize(
    databaseOptions.name, 
    databaseOptions.user, 
    databaseOptions.password, 
    {
        dialect: databaseOptions.dialect,
        host: databaseOptions.host
    }
);

sequelize.authenticate().then(() => {
    console.log('Connection has been established successfully.');
}).catch((error) => {
    console.error('Unable to connect to the database: ', error);
});

module.exports = { sequelize }