var httsserver = require("http");

httsserver.createServer(function(req,res){
    res.writeHead(200,{'Content-Type':'text/html'});
    res.write('Welcome ! How are you');
    res.end();
}).listen(9000);

'use strict';
var promiseCount = 0;

function testPromise() {
    let thisPromiseCount = ++promiseCount;

    let log = document.getElementById('log');
    log.insertAdjacentHTML('beforeend', thisPromiseCount +
        ') Started (<small>Sync code started</small>)<br/>');

        window.setTimeout(
            function() {
                let x= 100;
            }, Math.random() * 2000 + 1000);
    // We make a new promise: we promise a numeric count of this promise, starting from 1 (after waiting 3s)
    let p1 = new Promise(
        // The executor function is called with the ability to resolve or
        // reject the promise
       (resolve, reject) => {
            log.insertAdjacentHTML('beforeend', thisPromiseCount +
                ') Promise started (<small>Async code started</small>)<br/>');
            // This is only an example to create asynchronism
            window.setTimeout(
                function() {
                    // We fulfill the promise !
                    resolve(thisPromiseCount);
                }, Math.random() * 2000 + 1000);
        }
    );
    window.setTimeout(
        function() {
            let x= 100;
        }, Math.random() * 2000 + 1000);
    // We define what to do when the promise is resolved with the then() call,
    // and what to do when the promise is rejected with the catch() call
    p1.then(
        // Log the fulfillment value
        function(val) {
            log.insertAdjacentHTML('beforeend', val +
                ') Promise fulfilled (<small>Async code terminated</small>)<br/>');
        }).catch(
        // Log the rejection reason
       (reason) => {
            console.log('Handle rejected promise ('+reason+') here.');
        });
        window.setTimeout(
            function() {
                let x= 100;
            }, Math.random() * 2000 + 1000);
    log.insertAdjacentHTML('beforeend', thisPromiseCount +
        ') Promise made (<small>Sync code terminated</small>)<br/>');
}

if ("Promise" in window) {
  let btn = document.getElementById("btn");
  btn.addEventListener("click",testPromise);
} 

else {
  log = document.getElementById('log');
  log.innerHTML = "Live example not available as your browser doesn't support the <code>Promise<code> interface.";
}
