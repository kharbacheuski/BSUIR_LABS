const app = require("../server")
const client = require("../db/connect")

app.get('/api/where', async (req, res) => {
    try {
        const {rows} = await client.query('SELECT * FROM "Sound-Studio"."Artist" WHERE "personsCount" > 4')
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/where-OrderBy', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Artist" 
            WHERE "personsCount" < 5 AND genre = 'Rock'
            ORDER BY name
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/orderBy', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Employee" 
            ORDER BY "workShift"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/select', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT name, rent FROM "Sound-Studio"."Instrument"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/select-where', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Room"
            WHERE square > 30
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/crossJoin', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Instrument" CROSS JOIN "Sound-Studio"."Room"
            WHERE square < 20 AND type = 'Ударные'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})