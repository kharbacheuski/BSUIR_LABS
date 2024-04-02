const {sequelize} = require("../db/connect")
const { DataTypes } = require("sequelize");

const Employee = sequelize.define('employee', {
    id: {
        type: DataTypes.INTEGER,
        autoIncrement: true,
        primaryKey: true
    },
    username: DataTypes.STRING,
    age: DataTypes.INTEGER,
}, {timestamps: false});

module.exports = Employee