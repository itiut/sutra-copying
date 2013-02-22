document.addEventListener('DOMContentLoaded', function() {
  console.log('loaded!');

  var gl;
  var canvas;
  var shaderProgram;
  var vertexBuffer;
  var indexBuffer = null;

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
    gl.enableVertexAttribArray(shaderProgram.vertesColorAttribute);
  }

  function setupBuffers() {
    vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    var triangleVertices = [
       0.0,  0.5, 0.0, 255,   0,   0, 255,
      -0.5, -0.5, 0.0,   0, 255,   0, 255,
       0.5, -0.5, 0.0,   0,   0, 255, 255
    ];
    var nbrOfVertices = 3;
    var vertexSizeInBytes = 3 * Float32Array.BYTES_PER_ELEMENT + 4 * Uint8Array.BYTES_PER_ELEMENT;
    var vertexSizeInFloats = vertexSizeInBytes / Float32Array.BYTES_PER_ELEMENT;

    var buffer = new ArrayBuffer(nbrOfVertices * vertexSizeInBytes);
    var positionView = new Float32Array(buffer);
    var colorView = new Uint8Array(buffer);

    var positionOffsetInFloats = 0;
    var colorOffsetInBytes = 12;
    for (var i = 0, k = 0; i < nbrOfVertices; i++, k += 7) {
      positionView[positionOffsetInFloats] = triangleVertices[k];
      positionView[positionOffsetInFloats + 1] = triangleVertices[k + 1];
      positionView[positionOffsetInFloats + 2] = triangleVertices[k + 2];
      colorView[colorOffsetInBytes] = triangleVertices[k + 3];
      colorView[colorOffsetInBytes + 1] = triangleVertices[k + 4];
      colorView[colorOffsetInBytes + 2] = triangleVertices[k + 5];
      colorView[colorOffsetInBytes + 3] = triangleVertices[k + 6];

      positionOffsetInFloats += vertexSizeInFloats;
      colorOffsetInBytes += vertexSizeInBytes;
    }

    gl.bufferData(gl.ARRAY_BUFFER, buffer, gl.STATIC_DRAW);
    vertexBuffer.positionSize = 3;
    vertexBuffer.colorSize = 4;
    vertexBuffer.numberOfItems = 3;
  }

  function draw() {
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT);

    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, vertexBuffer.positionSize, gl.FLOAT, false, 16, 0);
    gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, vertexBuffer.colorSize, gl.UNSIGNED_BYTE, true, 16, 12);

    gl.drawArrays(gl.TRIANGLES, 0, vertexBuffer.numberOfItems);
  }

  canvas = document.getElementById('myGLCanvas');
  if (!canvas) {
    return;
  }

  gl = WebGLDebugUtils.makeDebugContext(createGLContext(canvas));
  setupShaders();
  setupBuffers();
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  draw();
}, false);
