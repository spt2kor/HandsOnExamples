var url = require('url');
var adr = 'http://localhost:8080/index.html?year=2019&month=Feb&day=25';

console.log('checking input address: ' + adr);
var q = url.parse(adr,true);
console.log(q);

console.log('url = ' + url);
console.log(q.host);
console.log(q.pathname);
console.log(q.search);

var data = q.query;
console.log(data.year);
console.log(data.month);
console.log(data.day);

//https://www.w3schools.com/nodejs/nodejs_url.asp

/*
Shailendras-MacBook-Pro:Node-Js sharajpu$ node url-parse-node8.js 
checking input address: http://localhost:8080/index.html?year=2019&month=Feb&day=25
Url {
  protocol: 'http:',
  slashes: true,
  auth: null,
  host: 'localhost:8080',
  port: '8080',
  hostname: 'localhost',
  hash: null,
  search: '?year=2019&month=Feb&day=25',
  query: { year: '2019', month: 'Feb', day: '25' },
  pathname: '/index.html',
  path: '/index.html?year=2019&month=Feb&day=25',
  href: 'http://localhost:8080/index.html?year=2019&month=Feb&day=25' }
url = [object Object]
localhost:8080
/index.html
?year=2019&month=Feb&day=25
2019
Feb
25


*/