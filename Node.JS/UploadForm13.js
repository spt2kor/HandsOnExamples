    var http = require('http');
    var fs = require('fs');
    var formidable = require('formidable');

    http.createServer(function(req,res){
        if(req.url == '/fileupload')
        {
            //console.log(req);
            console.log('*********************************************');
            var form = new formidable.IncomingForm();
            form.parse(req, function (err,fields,files) {
                var oldpath = files.filetoupload.path;
                var newpath = './'+ files.filetoupload.name;

                fs.rename(oldpath , newpath , function(err){
                    if(err) throw err;
                    res.writeHead(200,{'Content-Type':'text/html'});
                    res.write('file Uploaded successfully : ' + newpath );
                    res.write('<h2>Back to File Upload Page</h2>');
                    res.write('<a href="http://localhost:9013"> Upload File Again</a>');

                    res.end();
                }); 
            });
            //console.log(res);
            console.log('*********************************************');
        }
        else
        {
            //console.log(req);
            console.log('*********************************************');
            res.writeHead(200,{'Content-Type':'text/html'});
            res.write('<form action="fileupload" method="post" enctype="multipart/form-data" >');
            res.write('<input type="file" name="filetoupload" > <br/>');
            res.write('<input type="submit">');
            res.write('</form>');
            //console.log(res);
            console.log('*********************************************');
            return res.end();
        }
    }).listen(9013);


   
//https://www.w3schools.com/nodejs/nodejs_uploadfiles.asp

//https://codescracker.com/html/html-action-attribute.htm

