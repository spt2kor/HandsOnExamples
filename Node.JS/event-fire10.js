var fs = require('fs');

var read = fs.createReadStream('./winter.html');

read.on('open',function(){
    console.log('file open event is detected : ./winter.html');
});
//https://www.w3schools.com/nodejs/nodejs_events.asp




