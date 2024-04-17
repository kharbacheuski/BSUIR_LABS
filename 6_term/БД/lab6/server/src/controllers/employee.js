const app = require("../server")
const client = require("../db/connect")

app.post('/api/insert-employee', async (req, res) => {
    try {
        const {job, workShift, name} = req.body;

        const {rows} = await client.query(`
            INSERT INTO "Sound-Studio"."Employee"(job, "workShift", name)
            VALUES ('${job}', ${workShift}, '${name}');
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.put('/api/update-employee', async (req, res) => {
    try {
        const {id, job, workShift, name} = req.body;

        const {rows} = await client.query(`
            UPDATE "Sound-Studio"."Employee"
            SET job='${job}', workShift=${workShift}, name='${name}'
            WHERE id=${id};
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})