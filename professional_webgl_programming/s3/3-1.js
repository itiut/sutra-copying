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
  }

  function setupBuffers0() {
    vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    var triangleVertices = [
       0.0,  0.5, 0.0,
      -0.5, -0.5, 0.0,
       0.5, -0.5, 0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(triangleVertices), gl.STATIC_DRAW);
    vertexBuffer.itemSize = 3;
    vertexBuffer.numberOfItems = 3;
  }

  function setupBuffers1() {
    vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    var meshVertexPositions = [
      0.5, 1.0, 0.0,
      0.0, 1.0, 0.0,
      0.5, 0.5, 0.0,

      0.5, 0.5, 0.0,
      0.0, 1.0, 0.0,
      0.0, 0.5, 0.0,

      0.5, 0.5, 0.0,
      0.0, 0.5, 0.0,
      0.5, 0.0, 0.0,

      0.5, 0.0, 0.0,
      0.0, 0.5, 0.0,
      0.0, 0.0, 0.0,

      1.0, 0.5, 0.0,
      0.5, 0.5, 0.0,
      1.0, 0.0, 0.0,

      1.0, 0.0, 0.0,
      0.5, 0.5, 0.0,
      0.5, 0.0, 0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(meshVertexPositions), gl.STATIC_DRAW);
    vertexBuffer.itemSize = 3;
    vertexBuffer.numberOfItems = meshVertexPositions.length / 3;
  }

  function setupBuffers2() {
    vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    var meshVertexPositions = [
      0.5, 1.0, 0.0,
      0.0, 1.0, 0.0,
      0.5, 0.5, 0.0,
      0.0, 0.5, 0.0,
      0.5, 0.0, 0.0,
      0.0, 0.0, 0.0,

      0.0, 0.0, 0.0,
      1.0, 0.5, 0.0,

      1.0, 0.5, 0.0,
      0.5, 0.5, 0.0,
      1.0, 0.0, 0.0,
      0.5, 0.0, 0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(meshVertexPositions), gl.STATIC_DRAW);
    vertexBuffer.itemSize = 3;
    vertexBuffer.numberOfItems = meshVertexPositions.length / 3;
  }

  function setupBuffers3() {
    vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    var meshVertexPositions = [
      0.5, 1.0, 0.0,
      0.0, 1.0, 0.0,
      0.5, 0.5, 0.0,
      0.0, 0.5, 0.0,
      0.5, 0.0, 0.0,
      0.0, 0.0, 0.0,

      1.0, 0.5, 0.0,
      0.5, 0.5, 0.0,
      1.0, 0.0, 0.0,
      0.5, 0.0, 0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(meshVertexPositions), gl.STATIC_DRAW);
    vertexBuffer.itemSize = 3;
    vertexBuffer.numberOfItems = meshVertexPositions.length / 3;

    indexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
    var meshIndex = [
      0, 1, 2, 3, 4, 5,
      5, 6,
      6, 7, 8, 9
    ];
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(meshIndex), gl.STATIC_DRAW);
    indexBuffer.itemSize = 1;
    indexBuffer.numberOfItems = meshIndex.length;
  }

  function draw(type) {
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT);

    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, vertexBuffer.itemSize, gl.FLOAT, false, 0, 0);

    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

    if (indexBuffer) {
      gl.drawElements(type, indexBuffer.numberOfItems, gl.UNSIGNED_SHORT, 0);
    } else {
      gl.drawArrays(type, 0, vertexBuffer.numberOfItems);
    }
  }

  canvas = document.getElementById('myGLCanvas');
  if (!canvas) {
    return;
  }

  gl = WebGLDebugUtils.makeDebugContext(createGLContext(canvas));
  setupShaders();
  // setupBuffers1();
  // setupBuffers2();
  setupBuffers3();
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  // draw(gl.TRIANGLES);
  // draw(gl.TRIANGLE_STRIP);
  draw(gl.TRIANGLE_STRIP);
}, false);
