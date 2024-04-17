const app = require("../server")
const client = require("../db/connect")

// Запросы из пятой лабы

app.get('/api/count', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT COUNT(*) FROM "Sound-Studio"."Artist" 
            CROSS JOIN "Sound-Studio"."Room" 
            INNER JOIN "Sound-Studio"."Record" 
            ON "Artist"."id" = "Record"."artistId"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/count-distinct', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT COUNT(DISTINCT "Sound-Studio"."Room"."square") FROM "Sound-Studio"."Artist" 
            CROSS JOIN "Sound-Studio"."Room" 
            CROSS JOIN "Sound-Studio"."Record" 
            WHERE square > 35 AND genre = 'Rock'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/max', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT MAX("Sound-Studio"."Artist"."personsCount") FROM "Sound-Studio"."Artist" 
            INNER JOIN "Sound-Studio"."Record" 
            ON "Record"."artistId" = "Artist"."id"
            CROSS JOIN "Sound-Studio"."Instrument" 
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/max-2', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT MAX("Sound-Studio"."Record"."totalPrice") FROM "Sound-Studio"."Record" 
            INNER JOIN "Sound-Studio"."Employee" 
            ON "Record"."employeeId" = "Employee"."id"
            INNER JOIN "Sound-Studio"."Artist" 
            ON "Record"."artistId" = "Artist"."id"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/sum', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT SUM("Sound-Studio"."Room"."square") FROM "Sound-Studio"."Room" 
            CROSS JOIN "Sound-Studio"."Employee" 
            CROSS JOIN "Sound-Studio"."RecordType" 
            WHERE "workShift" = 2 AND "RecordType"."type" = 'Вокал'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/sum-distinct', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT SUM(DISTINCT "Sound-Studio"."Record"."totalPrice") FROM "Sound-Studio"."Record" 
            INNER JOIN "Sound-Studio"."Room" 
            ON "Room"."personsCount" < 5 AND "Record"."roomId" = "Room"."id"
            INNER JOIN "Sound-Studio"."Employee" 
            ON "Employee"."workShift" = 2 AND "Record"."employeeId" = "Employee"."id"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/groupBy', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT "Sound-Studio"."RecordType"."type", SUM("Sound-Studio"."Record"."totalPrice") FROM "Sound-Studio"."Record" 
            INNER JOIN "Sound-Studio"."Artist" 
            ON "Record"."artistId" = "Artist"."id"
            INNER JOIN "Sound-Studio"."RecordType" 
            ON "Record"."recordTypeId" = "RecordType"."id"
            GROUP BY "Sound-Studio"."RecordType"."type"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/groupBy-having', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT "Sound-Studio"."Record"."date" as Date, MIN("Sound-Studio"."Artist"."personsCount") FROM "Sound-Studio"."Artist" 
            INNER JOIN "Sound-Studio"."Record" 
            ON "Record"."artistId" = "Artist"."id"
            INNER JOIN "Sound-Studio"."Room" 
            ON "Record"."roomId" = "Room"."id"
            GROUP BY "Sound-Studio"."Record"."date"
            HAVING "Sound-Studio"."Record"."date" > '2023-07-05'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/having-avg', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT AVG("Sound-Studio"."Record"."totalPrice") as Price, "Sound-Studio"."Artist"."name" FROM "Sound-Studio"."Artist" 
            INNER JOIN "Sound-Studio"."Record" 
            ON "Artist"."genre" IN ('Rock', 'Metal')
            INNER JOIN "Sound-Studio"."RecordType" 
            ON "Record"."recordTypeId" = "RecordType"."id"
            GROUP BY "Artist"."name"
            HAVING AVG("Sound-Studio"."Record"."totalPrice") > 4
            ORDER BY "Artist"."name"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/union-not', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT "personsCount" FROM "Sound-Studio"."Room" 
            UNION
            SELECT "personsCount" FROM "Sound-Studio"."Artist" 
            CROSS JOIN "Sound-Studio"."Employee"
            WHERE "Artist"."name" NOT LIKE '% %'
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/union-any', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT * FROM "Sound-Studio"."Record" 
            INNER JOIN "Sound-Studio"."Employee"
            ON "Employee"."workShift" = 3 AND "Record"."employeeId" = "Employee"."id"
            WHERE "Record"."artistId" = ANY(SELECT "id" FROM "Sound-Studio"."Artist")
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/intersect', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT name FROM "Sound-Studio"."Artist" 
            INTERSECT
            SELECT name FROM "Sound-Studio"."Employee"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/intersect-where', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT type FROM "Sound-Studio"."Instrument" 
            WHERE rent < 5
            INTERSECT
            SELECT type FROM "Sound-Studio"."RecordType"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/except-exists', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT type FROM "Sound-Studio"."Instrument" 
            WHERE EXISTS (SELECT * FROM "Sound-Studio"."Room" WHERE "Instrument"."rent" = "Room"."rent")
            EXCEPT
            SELECT type FROM "Sound-Studio"."RecordType"
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})

app.get('/api/except-all', async (req, res) => {
    try {
        const {rows} = await client.query(`
            SELECT "totalPrice" FROM "Sound-Studio"."Record" 
            EXCEPT
            SELECT rent FROM "Sound-Studio"."Room"
            EXCEPT
            SELECT rent FROM "Sound-Studio"."Instrument"
            WHERE rent = ALL(SELECT rent FROM "Sound-Studio"."Room" WHERE rent > 5)
        `)
        res.send(rows)
    }
    catch(e) {
        console.error(e)
    }
})