const express = require('express');
const app = express();
const fs = require("fs");
const path = require('path');

app.get('/', async (req,res) => {
    res.sendFile(path.join(__dirname,'score.html'));
})

app.get('/state', async (req, res) => {
    // Set headers to keep the connection alive and tell the client we're sending event-stream data
    res.setHeader('Content-Type', 'text/event-stream');
    res.setHeader('Cache-Control', 'no-cache');
    res.setHeader('Connection', 'keep-alive');

    //send json
    const intervalId = setInterval(function() {
        //sync so its blocking
        data = fs.readFileSync(path.join(__dirname, "../state.json"));
        res.json(JSON.parse(data));
    }, 500);

    // When client closes connection, stop sending events
    req.on('close', () => {
        clearInterval(intervalId);
        res.end();
    });
});

app.listen(8080);