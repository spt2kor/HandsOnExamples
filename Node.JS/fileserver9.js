//file seerver
var http = require('http');
var url = require('url');
var fs = require('fs');

http.createServer(function(req , res){
    var q = url.parse(req.url,true);
    var fname = "." + q.pathname;

    fs.readFile(fname , function(err,data){
        if(err){
            res.writeHead(404,{'Content-Type':'text/html'});
            return res.end('404 not found');
        }
        res.writeHead(200,{'Content-Type':'text.html'});
        res.write(data);
        res.end();
    });
}).listen(9009);

//https://www.w3schools.com/nodejs/nodejs_url.asp

/*
http://localhost:9009/summer.html
Summer
I love the sun!

http://localhost:9009/winter.html
Winter
I love the snow!

*/
