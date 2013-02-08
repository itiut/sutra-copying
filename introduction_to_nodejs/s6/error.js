process.on('uncaughtException', function(err) {
  console.log(err);
});

throw new Error('An error occured.');