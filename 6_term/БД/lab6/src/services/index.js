const models = require("../models")

class Service {
    getArtists() {
        return models.Artist.findAll();
    }
}


module.exports = Service