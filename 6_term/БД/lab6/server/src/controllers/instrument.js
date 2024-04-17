const app = require("../server")
const client = require("../db/connect")

app.post('/api/insert-instrument', async (req, res) => {
    try {
        const {name, type, rent} = req.body;

        const {rows} = await client.query(`
            INSERT INTO "Sound-Studio"."Instrument"(name, type, rent)
            VALUES ('${name}', '${type}', '${rent}');
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.put('/api/update-instrument', async (req, res) => {
    try {
        const {id, name, type, rent} = req.body;

        const {rows} = await client.query(`
            UPDATE "Sound-Studio"."Instrument"
            SET name='${name}', type='${type}', rent=${rent}
            WHERE id=${id};
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})