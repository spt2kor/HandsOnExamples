var nodemailer = require('nodemailer');
var http = require('http');

http.createServer( function ( req , res ){

    res.writeHead(200, {'Content-Type':'text/html'});
  

var transporter = nodemailer.createTransport({
    service:'gmail',
    auth:{
        user:'shailendra.usa2016@gmail.com',
        pass:'ic006495'
    }
});


var mailoption = {
    from:'shailendra.usa2016@gmail.com',
    to:'sharajpu@adobe.com',
    subject:'test mail from node.js example',
    test:'hello sharajpu'
};


transporter.sendMail(mailoption , function(err,info){
    if(err)
        console.log('unable to send mail' + err);
    else
        console.log('mail sent successfully ') ; 
});
res.end();
}).listen(9014);