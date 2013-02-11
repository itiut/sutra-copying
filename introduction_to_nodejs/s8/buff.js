var size = 16;
var buf = new Buffer(size);
var arr = [1,2,3,4,5,6];
var arrayBuf = new Buffer(arr);
var str = 'sample';
var stringBuf = new Buffer(str);

console.log(buf);
console.log(arrayBuf);
console.log(stringBuf);

var a = 'bufferr contents';
buf.write(a, 0, a.length, 'utf8');

console.log(buf.toString());
for (var i = 0; i < buf.length; i++) {
  console.log(buf[i]);
}

var buf2 = buf.slice(0, 6);
buf2.write('i', 1, 1);
console.log(buf.toString());
