document.addEventListener('DOMContentLoaded', function() {
  console.log('loaded!');

  var gl;
  var canvas;
  var shaderProgram;
  var vertexBuffer;

  function createGLContext(canvas) {
    var names = ['webgl', 'experimental-webgl'];
    var context = null;
    for (var i = 0; i < names.length; i++) {
      try {
        context = canvas.getContext(names[i]);
      } catch(e) {
      }
      if (context) {
        break;
      }
    }
    if (context) {
      context.viewportWidth = canvas.width;
      context.viewportHeight = canvas.height;
    } else {
      alert('Failed to create WebGL context!');
    }
    return context;
  }

  function loadShader(type, shaderSource) {
    var shader = gl.createShader(type);
    gl.shaderSource(shader, shaderSource);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
      alert('Error compiling shader:' + gl.getShaderInfoLog(shader));
      gl.deleteShader(shader);
      return null;
    }
    return shader;
  }

});
