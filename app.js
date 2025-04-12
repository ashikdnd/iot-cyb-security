const express = require('express');
const path = require('path');
const axios = require('axios');

const app = express();
const serverPort = 3000;


// Serve static files from the public folder (our HTML page)
app.use(express.static(path.join(__dirname, 'public')));

// API endpoint to control the LED
app.get('/led/:state', (req, res) => {
    const state = req.params.state;
    console.log('state', state)
    if (state === 'on' || state === 'off') {
        const command = state === 'on' ? 'on' : 'off';
        axios.get('http://192.168.1.15/led?state=' + state)
            .then(response => {
                console.log(response.data)
                res.send(response.data)
            })
            .catch(error => console.error('Error:', error));
    } else {
        res.status(400).send('Invalid state');
    }
});

// Start the Node.js server
app.listen(serverPort, () => {
    console.log(`Server running at http://localhost:${serverPort}`);
});
