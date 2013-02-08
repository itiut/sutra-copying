var events = require('events');
var emitter = new events.EventEmitter();

var sampleListener = function(arg) {
  console.log(arg);
};

//emitter.on('occurrence', sampleListener);
emitter.once('occurrence', sampleListener);

emitter.emit('occurrence', 'occured once');
emitter.emit('occurrence', 'occured twice');