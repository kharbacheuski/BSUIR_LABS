const app = require("../server")
const client = require("../db/connect")

app.post('/api/insert-recordType', async (req, res) => {
    try {
        const {type, genre} = req.body;

        const row = await client.query(`
            INSERT INTO "Sound-Studio"."RecordType"(type, genre, "stereo/mono")
            VALUES ('${type}', '${genre}', ${req.body['stereo/mono']});
        `)
        res.send(true)
    }
    catch(e) {
        console.error(e)
    }
})

app.put('/api/update-recordType', async (req, res) => {
    try {
        const {id, type, genre} = req.body;

        const {rows} = await client.query(`
            UPDATE "Sound-Studio"."RecordType"
            SET type='${type}', genre='${genre}', "stereo/mono"=${req.body['stereo/mono']}
            WHERE id=${id};
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})