var path = require('path');
var fs = require('fs');

var filePath = path.join(__dirname, 'write.txt');
var writeStream = fs.createWriteStream(filePath);

writeStream.write('Hello world!\n');
writeStream.end();

writeStream.on('error', function(err) {
  console.log('An error occured');
  console.log(err);
});
writeStream.on('close', function() {
  console.log('writeable stream closed');
});
