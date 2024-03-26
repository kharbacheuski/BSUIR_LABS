const { User } = require("../models/user")
const {sequelize} = require("../db/connect")

class UserService {

    createUser(input) {
        const newUser = User.create({...input})

        return newUser
    }

    getUsers() {
        const users = User.findAll();

        return users
    }

    getUserById({id}) {
        const user = User.findByPk(id);

        return user
    }

    deleteUser(id) {
        User.destroy({ where: { id: id } }); 

        return id; 
    }

    async isExist(id) {
        try {
            const user = await User.findOne({ where: {id: id} })
            return user !== null
        }
        catch(e) {
            console.error(e)
        }
    }
}


module.exports = UserService