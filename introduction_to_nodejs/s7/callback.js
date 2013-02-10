var events = require('events');
var util = require('util');

// function SyncCB(cb) {
//   if (cb) cb();
// }
function AsyncCB(cb) {
  if (cb) {
    process.nextTick(function() {
      cb();
    });
  }
}

// util.inherits(SyncCB, events.EventEmitter);
util.inherits(AsyncCB, events.EventEmitter);

// SyncCB.prototype.setbaz = function(arg) {
//   this.baz = arg;
// };
AsyncCB.prototype.setbaz = function(arg) {
  this.baz = arg;
};

// var foo = new SyncCB(function() {
//   foo.setbaz('bar');
//   console.log(foo.baz);
// });
var foo = new AsyncCB(function() {
  foo.setbaz('bar');
  console.log(foo.baz);
});
