var http = require('http');
var uc = require('upper-case');

console.log('hello world!!');
console.log(uc('hello wrold!!'));

http.createServer(function(req,res){
    res.writeHead(200,{'Content-Type':'text/html'});
    res.write(uc('Welcome Here! testing upper case'));
    res.end();
}).listen(8080);

