const app = require("../server")
const client = require("../db/connect")

// Другие эндпоинты

app.get('/api/select', async (req, res) => {
    try {
        const {table} = req.query
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."${table}"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.delete('/api/delete', async (req, res) => {
    try {
        const {table, id} = req.query;

        if(table === "Record") {
            const {rows} = await client.query(`
                DELETE FROM "Sound-Studio"."Instrument_Record" 
                WHERE "Record_id"=${id};

                DELETE FROM "Sound-Studio"."Record"
                WHERE id=${id};
            `)

            res.send(rows)
        }
        if(table === "Instrument") {
            const {rows} = await client.query(`
                DELETE FROM "Sound-Studio"."Instrument_Record" 
                WHERE "Instruments_id"=${id};

                DELETE FROM "Sound-Studio"."Instrument"
                WHERE id=${id};
            `)

            res.send(rows)
        }
        else {
            const {rows} = await client.query(`
                DELETE FROM "Sound-Studio"."Instrument_Record" 
                WHERE "Record_id" IN (SELECT id FROM "Sound-Studio"."Record" WHERE "${table.toLowerCase()}Id"=${id});

                DELETE FROM "Sound-Studio"."Record"
                WHERE id IN (SELECT id FROM "Sound-Studio"."Record" WHERE "${table.toLowerCase()}Id"=${id});

                DELETE FROM "Sound-Studio"."${table}"
                WHERE id=${id};
            `)

            res.send(rows)
        }
    }
    catch(e) {
        console.error(e)
    }
})
