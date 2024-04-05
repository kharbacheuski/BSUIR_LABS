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
            HAVING Price > 4
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
            WHERE "Record"."artistId" = ANY(SELECT MAX("id") FROM "Sound-Studio"."Artist")
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
            SELECT name FROM "Sound-Studio"."Empoloyee"
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