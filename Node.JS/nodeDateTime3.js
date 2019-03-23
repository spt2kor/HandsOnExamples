var httpSer = require('http');
var dateTime = require('./myDateTime2');

httpSer.createServer(function(req,res){
    res.writeHead(200, {'Content-Type':'text/html'});
    res.write('Welcome Again! current date and time are: ' + dateTime.myDateTime());
    res.end();
}).listen(9001);