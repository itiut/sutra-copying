var fs = require('fs');
var filePath = '/tmp/target.txt';

fs.writeFile(filePath, 'some data', 'utf8', function(err) {
  if (err) {
    throw err;
  }
  fs.readFile(filePath, 'utf8', function(err, data) {
    if (err) {
      throw err;
    }
    console.log(data);
  });
});
