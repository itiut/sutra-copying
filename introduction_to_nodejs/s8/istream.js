var path = require('path');
var fs = require('fs');

var filePath = path.join(__dirname, 'test.txt');

var readStream = fs.createReadStream(filePath, {encoding: 'utf8'});
readStream.on('data', function(data) {
  console.log(data);
});
readStream.on('end', function() {
  console.log('end');
});
readStream.on('error', function(err) {
  console.log('An error occured');
  console.log(err);
});
