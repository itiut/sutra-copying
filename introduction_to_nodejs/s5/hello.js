var count = 0;

module.exports = {
  say: function(name) {
    count++;
    console.log('Hello ' + name);
  },

  getCount: function() {
    return count;
  },

  resetCount: function() {
    count = 0;
  },

  getDirName: function() {
    console.log('__dirname = %s', __dirname);
  },

  getFileName: function() {
    console.log('__filename = %s', __filename);
  }
};
