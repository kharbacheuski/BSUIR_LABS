const {sequelize} = require("../db/connect")
const { DataTypes } = require("sequelize");

const User = sequelize.define('users', {
    id: {
        type: DataTypes.INTEGER,
        autoIncrement: true,
        primaryKey: true
    },
    username: DataTypes.STRING,
    age: DataTypes.INTEGER,
}, {timestamps: false});

module.exports = { User }