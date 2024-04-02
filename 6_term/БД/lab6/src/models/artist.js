const {sequelize} = require("../db/connect")
const { DataTypes } = require("sequelize");

const Artist = sequelize.define('Artist', {
    id: {
        type: DataTypes.INTEGER,
        autoIncrement: true,
        primaryKey: true
    },
    name: DataTypes.STRING,
    age: DataTypes.INTEGER,
}, {timestamps: false});

module.exports = Artist