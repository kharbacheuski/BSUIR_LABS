const app = require("../server")
const client = require("../db/connect")

app.post('/api/insert-room', async (req, res) => {
    try {
        const {square, rent, personsCount} = req.body;

        const {rows} = await client.query(`
            INSERT INTO "Sound-Studio"."Room"(square, rent, "personsCount")
            VALUES (${square}, ${rent}, ${personsCount});
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.put('/api/update-room', async (req, res) => {
    try {
        const {id, square, rent, personsCount} = req.body;

        const {rows} = await client.query(`
            UPDATE "Sound-Studio"."Room"
            SET square=${square}, rent=${rent}, "personsCount"=${personsCount}
            WHERE id=${id};
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})