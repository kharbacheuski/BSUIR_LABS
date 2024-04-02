const {sequelize} = require("../db/connect")
const { DataTypes } = require("sequelize");

const Record = sequelize.define('record', {
    id: {
        type: DataTypes.INTEGER,
        autoIncrement: true,
        primaryKey: true
    },
    username: DataTypes.STRING,
    age: DataTypes.INTEGER,
}, {timestamps: false});

module.exports = Record