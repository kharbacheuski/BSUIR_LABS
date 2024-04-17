const app = require("../server")
const client = require("../db/connect")

// Запросы из четвертой лабы

app.get('/api/where', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Artist" 
            WHERE "personsCount" > 4
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/where-orderBy', async (req, res) => {
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

app.get('/api/select-instr', async (req, res) => {
    try {
        const {table} = req.query
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

app.get('/api/crossJoin-2', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Employee" CROSS JOIN "Sound-Studio"."Artist"
            WHERE job = 'Звукорежиссер' OR genre = 'Grunge'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/innerJoin', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Instrument" INNER JOIN "Sound-Studio"."Room"
            ON "Sound-Studio"."Instrument"."rent" = "Sound-Studio"."Room"."rent"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/innerJoin-where', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."RecordType" INNER JOIN "Sound-Studio"."Instrument"
            ON "Sound-Studio"."RecordType"."type" = "Sound-Studio"."Instrument"."name"
            WHERE "Sound-Studio"."Instrument"."name" = 'Бас-гитара'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/leftOuterJoin-where', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Room" LEFT OUTER JOIN "Sound-Studio"."Instrument"
            ON "Sound-Studio"."Room"."rent" = "Sound-Studio"."Instrument"."rent"
            WHERE "Sound-Studio"."Room"."rent" < 12
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/leftOuterJoin', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Employee" LEFT OUTER JOIN "Sound-Studio"."Record"
            ON "Sound-Studio"."Employee"."id" = "Sound-Studio"."Record"."employeeId"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/rightOuterJoin', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Record" RIGHT JOIN "Sound-Studio"."RecordType" 
            ON "Sound-Studio"."RecordType"."id" = "Sound-Studio"."Record"."recordTypeId"
            WHERE "Sound-Studio"."RecordType"."type" = 'Гитара'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/rightOuterJoin-2', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Record" RIGHT JOIN "Sound-Studio"."Artist" 
            ON "Sound-Studio"."Artist"."id" = "Sound-Studio"."Record"."artistId"
            WHERE genre = 'Rock'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/fullOuterJoin', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Record" FULL OUTER JOIN "Sound-Studio"."Room" 
            ON "Room"."id" = "Record"."roomId"
            WHERE "Room"."rent" > 15
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/fullOuterJoin-2', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Record" FULL OUTER JOIN "Sound-Studio"."Employee" 
            ON "Employee"."id" = "Record"."employeeId"
            WHERE job = 'Техник'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})
