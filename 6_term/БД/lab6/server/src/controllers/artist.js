const app = require("../server")
const client = require("../db/connect")

app.post('/api/insert-artist', async (req, res) => {
    try {
        const {name, genre, personsCount} = req.body;

        const row = await client.query(`
            INSERT INTO "Sound-Studio"."Artist"(name, genre, "personsCount")
            VALUES ('${name}', '${genre}', ${personsCount});
        `)
        res.send(true)
    }
    catch(e) {
        console.error(e)
    }
})

app.put('/api/update-artist', async (req, res) => {
    try {
        const {id, name, genre, personsCount} = req.body;

        const {rows} = await client.query(`
            UPDATE "Sound-Studio"."Artist"
            SET name='${name}', genre='${genre}', "personsCount"=${personsCount}
            WHERE id=${id};
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})