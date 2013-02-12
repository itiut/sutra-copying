var fs = require('fs');
var filePath = '/tmp/target.txt';

var stdin = process.stdin;
var output = fs.createWriteStream(filePath, {flags: 'a+'});

stdin.resume();
stdin.pipe(output);