const app = require("../server")
const client = require("../db/connect")

app.post('/api/insert-instr-record', async (req, res) => {
    try {
        const {instrument, record} = req.body;

        const row = await client.query(`
            INSERT INTO "Sound-Studio"."Instrument_Record"("Instruments_id", "Record_id")
            VALUES (${instrument}', ${record});
        `)
        res.send(true)
    }
    catch(e) {
        console.error(e)
    }
})

app.put('/api/update-instr-record', async (req, res) => {
    try {
        const {id, instrument, record} = req.body;

        const {rows} = await client.query(`
            UPDATE "Sound-Studio"."Artist"
            SET "Instruments_id"=${instrument}, "Record_id=${record}
            WHERE id=${id};
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})