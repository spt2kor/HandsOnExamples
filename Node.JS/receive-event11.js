
var event = require('events');
console.log('started event testing');
var eventEmit = new event.EventEmitter();
var eventRecev = new event.EventEmitter();

var eventHandler = function(){
    console.log('Event received !!');
}

eventEmit.on('Scream', eventHandler);

eventEmit.emit('Scream');

console.log('ending event testing');


//https://www.w3schools.com/nodejs/nodejs_events.asp


