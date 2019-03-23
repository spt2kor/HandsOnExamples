var fs = require('fs');

fs.appendFile('file1Update.txt','appendFunction,Creating New file!',
    function (err) {
        if(err) throw err;
        console.log('File1Update.txt is created successgully by append');;
    });


fs.open('OpenFile1.txt', 'w',function(err,file){
    if(err) throw err;
    console.log('Open file is successful ! OpenFile1.txt');

});

fs.writeFile('OpenFile1.txt', "trying WriteFile function ", function(err){
    if(err) throw err;
    console.log('WriteFile Done');
});

fs.appendFile('OpenFile1.txt', 'trying to append again !!!', function(err){
    if(err) throw err;
    console.log('append file successful');
});

fs.unlink('file1Update.txt',function(err){
    if(err) throw err;
    console.log('file deleted successfully , file1Update.txt');
});

fs.rename('OpenFile1.txt', 'OpenFile2.txt',function(err){
    if(err) throw err;
    console.log('file renamed to OpenFile2.txt');
});
//https://www.w3schools.com/nodejs/nodejs_filesystem.asp