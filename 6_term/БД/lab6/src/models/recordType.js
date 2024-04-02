const {sequelize} = require("../db/connect")
const { DataTypes } = require("sequelize");

const RecordType = sequelize.define('recordType', {
    id: {
        type: DataTypes.INTEGER,
        autoIncrement: true,
        primaryKey: true
    },
    username: DataTypes.STRING,
    age: DataTypes.INTEGER,
}, {timestamps: false});

module.exports = RecordType