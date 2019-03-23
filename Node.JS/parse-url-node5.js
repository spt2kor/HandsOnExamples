var httpServer = require('http');
var url = require('url');

httpServer.createServer(function(req, res){
    res.writeHead(200,{'Content-Type':'text/html'});
    res.write(req.url + '   ->    ') ;
    var date = url.parse(req.url,true).query;
    var txt = date.year+ '  ' + date.month;
    res.end(txt);

} ).listen(9005);

//https://www.w3schools.com/nodejs/nodejs_http.asp
