const { Counter } = require("../models/counter")
const requestCounter = new Counter();
const app = require("../server")

app.all('/api/*', (req, res, next) => {
    requestCounter.increment()
    next();
})

app.get('/api/getRequestsCount', (req, res) => {
    res.send({requestCount: requestCounter.count})
})