document.addEventListener('DOMContentLoaded', function() {
  console.log('loaded!');

  var gl;
  var canvas;
  var shaderProgram;
  var hexagonVertexBuffer;
  var triangleVertexBuffer;
  var triangleVertexColorBuffer;
  var stripVertexBuffer;
  var stripElementBuffer;

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

  function loadShaderFromDOM(id) {
    var shaderScript = document.getElementById(id);
    if (!shaderScript) {
      return null;
    }

    var shaderSource = '';
    var currentChild = shaderScript.firstChild;
    while (currentChild) {
      if (currentChild.nodeType == 3) {
        shaderSource += currentChild.textContent;
      }
      currentChild = currentChild.nextSibling;
    }

    var shader;
    if (shaderScript.type == "x-shader/x-fragment") {
      shader = gl.createShader(gl.FRAGMENT_SHADER);
    } else if (shaderScript.type == "x-shader/x-vertex") {
      shader = gl.createShader(gl.VERTEX_SHADER);
    } else {
      return null;
    }

    gl.shaderSource(shader, shaderSource);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
      alert(gl.getShaderInfoLog(shader));
      return null;
    }
    return shader;
  }

  function setupShaders() {
    var vertexShader = loadShaderFromDOM('shader-vs');
    var fragmentShader = loadShaderFromDOM('shader-fs');

    shaderProgram = gl.createProgram();
    gl.attachShader(shaderProgram, vertexShader);
    gl.attachShader(shaderProgram, fragmentShader);
    gl.linkProgram(shaderProgram);

    if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
      alert('Failed to setup shaders');
    }

    gl.useProgram(shaderProgram);

    shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, 'aVertexPosition');
    shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, 'aVertexColor');

    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
  }

  function setupBuffers() {
    hexagonVertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, hexagonVertexBuffer);
    var hexagonVertices = [
      -0.3, 0.6, 0.0,
      -0.4, 0.8, 0.0,
      -0.6, 0.8, 0.0,
      -0.7, 0.6, 0.0,
      -0.6, 0.4, 0.0,
      -0.4, 0.4, 0.0,
      -0.3, 0.6, 0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(hexagonVertices), gl.STATIC_DRAW);
    hexagonVertexBuffer.itemSize = 3;
    hexagonVertexBuffer.numberOfItems = 7;

    triangleVertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexBuffer);
    var triangleVertices = [
      0.3, 0.4, 0.0,
      0.7, 0.4, 0.0,
      0.5, 0.8, 0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(triangleVertices), gl.STATIC_DRAW);
    triangleVertexBuffer.itemSize = 3;
    triangleVertexBuffer.numberOfItems = 3;

    triangleVertexColorBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);
    var colors = [
      1.0, 0.0, 0.0, 1.0,
      0.0, 1.0, 0.0, 1.0,
      0.0, 0.0, 1.0, 1.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
    triangleVertexColorBuffer.itemSize = 4;
    triangleVertexColorBuffer.numberOfItems = 3;

    stripVertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, stripVertexBuffer);
    var stripVertices = [
      -0.5,  0.2, 0.0,
      -0.4,  0.0, 0.0,
      -0.3,  0.2, 0.0,
      -0.2,  0.0, 0.0,
      -0.1,  0.2, 0.0,
       0.0,  0.0, 0.0,
       0.1,  0.2, 0.0,
       0.2,  0.0, 0.0,
       0.3,  0.2, 0.0,
       0.4,  0.0, 0.0,
       0.5,  0.2, 0.0,

      -0.5, -0.3, 0.0,
      -0.4, -0.5, 0.0,
      -0.3, -0.3, 0.0,
      -0.2, -0.5, 0.0,
      -0.1, -0.3, 0.0,
       0.0, -0.5, 0.0,
       0.1, -0.3, 0.0,
       0.2, -0.5, 0.0,
       0.3, -0.3, 0.0,
       0.4, -0.5, 0.0,
       0.5, -0.3, 0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(stripVertices), gl.STATIC_DRAW);
    stripVertexBuffer.itemSize = 3;
    stripVertexBuffer.numberOfItems = 22;

    stripElementBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, stripElementBuffer);
    var indices = [
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
      10, 10, 11,
      11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
    ];
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
    stripElementBuffer.numberOfItems = 25;
  }

  function draw() {
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT);

    gl.disableVertexAttribArray(shaderProgram.vertexColorAttribute);
    gl.vertexAttrib4f(shaderProgram.vertexColorAttribute, 0.0, 0.0, 0.0, 1.0);
    gl.bindBuffer(gl.ARRAY_BUFFER, hexagonVertexBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, hexagonVertexBuffer.itemSize, gl.FLOAT, false, 0, 0);
    gl.drawArrays(gl.LINE_STRIP, 0, hexagonVertexBuffer.numberOfItems);

    gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
    gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, triangleVertexBuffer.itemSize, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, triangleVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0);
    gl.drawArrays(gl.TRIANGLES, 0, triangleVertexBuffer.numberOfItems);

    gl.disableVertexAttribArray(shaderProgram.vertexColorAttribute);
    gl.bindBuffer(gl.ARRAY_BUFFER, stripVertexBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, stripVertexBuffer.itemSize, gl.FLOAT, false, 0, 0);
    gl.vertexAttrib4f(shaderProgram.vertexColorAttribute, 1.0, 1.0, 0.0, 1.0);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, stripElementBuffer);
    gl.drawElements(gl.TRIANGLE_STRIP, stripElementBuffer.numberOfItems, gl.UNSIGNED_SHORT, 0);
    gl.vertexAttrib4f(shaderProgram.vertexColorAttribute, 0.0, 0.0, 0.0, 1.0);

    gl.drawArrays(gl.LINE_STRIP, 0, 11);
    gl.drawArrays(gl.LINE_STRIP, 11, 11);
  }

  canvas = document.getElementById('myGLCanvas');
  if (!canvas) {
    return;
  }

  gl = WebGLDebugUtils.makeDebugContext(createGLContext(canvas));
  setupShaders();
  setupBuffers();
  gl.clearColor(1.0, 1.0, 1.0, 1.0);

  gl.frontFace(gl.CCW);
  gl.enable(gl.CULL_FACE);
  gl.cullFace(gl.BACK);
  draw();
}, false);
