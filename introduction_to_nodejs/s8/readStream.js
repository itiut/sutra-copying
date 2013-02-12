var fs = require('fs');
var filePath = '/tmp/target.txt';

var rs = fs.createReadStream(filePath, {encoding: 'utf8', bufferSize: 1});
rs.on('data', function(data) {
  console.log(data);
});
rs.on('end', function() {
  console.log('<EOF>');
});
