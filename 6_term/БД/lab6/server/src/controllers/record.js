const app = require("../server")
const client = require("../db/connect")

app.post('/api/insert-record', async (req, res) => {
    try {
        const {name, genre, personsCount} = req.body;

        const row = await client.query(`
            INSERT INTO "Sound-Studio"."Record"(name, genre, "personsCount")
            VALUES ('${name}', '${genre}', ${personsCount});
        `)
        res.send(true)
    }
    catch(e) {
        console.error(e)
    }
})

app.put('/api/update-record', async (req, res) => {
    try {
        const {id, name, genre, personsCount} = req.body;

        const {rows} = await client.query(`
            UPDATE "Sound-Studio"."Record"
            SET name='${name}', genre='${genre}', "personsCount"='${personsCount}'
            WHERE id=${id};
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})