var http = require('http');
var fs = require('fs');
/*
http.createServer(function(req , res){
    fs.readFile('read-file-input6.html',function(err , data){
        res.writeHead(200,{'Content-Type':'text/html'});
        res.write(data);
        res.end();
    });
}).listen(9006);
*/

http.createServer(function(req , res){
    var data1 = 'dummy';
    res.writeHead(200,{'Content-Type':'text/html'});
    //res.write(data1);
    //res.end();

    fs.readFile('read-file-input6.html',function(err , data){
        data1 = data;
        res.write(data1);
        res.end();
    });

    //res.write(data1);
    //res.end();

}).listen(9006);



//https://www.w3schools.com/nodejs/nodejs_filesystem.asp