/*
created with obj2opengl.pl
source file    : ./cube.obj
vertices       : 8
faces          : 12
normals        : 6
texture coords : 0
// include generated arrays
#import "./cube.h"
// set input data to arrays
glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
glNormalPointer(GL_FLOAT, 0, cubeNormals);
// draw data
glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);
*/

unsigned int cubeNumVerts = 36;

float cubeVerts [] = {
  // f  1//2  7//2  5//2
  -0.5, -0.5, -0.5,
  0.5, 0.5, -0.5,
  0.5, -0.5, -0.5,
  // f  1//2  3//2  7//2
  -0.5, -0.5, -0.5,
  -0.5, 0.5, -0.5,
  0.5, 0.5, -0.5,
  // f  1//6  4//6  3//6
  -0.5, -0.5, -0.5,
  -0.5, 0.5, 0.5,
  -0.5, 0.5, -0.5,
  // f  1//6  2//6  4//6
  -0.5, -0.5, -0.5,
  -0.5, -0.5, 0.5,
  -0.5, 0.5, 0.5,
  // f  3//3  8//3  7//3
  -0.5, 0.5, -0.5,
  0.5, 0.5, 0.5,
  0.5, 0.5, -0.5,
  // f  3//3  4//3  8//3
  -0.5, 0.5, -0.5,
  -0.5, 0.5, 0.5,
  0.5, 0.5, 0.5,
  // f  5//5  7//5  8//5
  0.5, -0.5, -0.5,
  0.5, 0.5, -0.5,
  0.5, 0.5, 0.5,
  // f  5//5  8//5  6//5
  0.5, -0.5, -0.5,
  0.5, 0.5, 0.5,
  0.5, -0.5, 0.5,
  // f  1//4  5//4  6//4
  -0.5, -0.5, -0.5,
  0.5, -0.5, -0.5,
  0.5, -0.5, 0.5,
  // f  1//4  6//4  2//4
  -0.5, -0.5, -0.5,
  0.5, -0.5, 0.5,
  -0.5, -0.5, 0.5,
  // f  2//1  6//1  8//1
  -0.5, -0.5, 0.5,
  0.5, -0.5, 0.5,
  0.5, 0.5, 0.5,
  // f  2//1  8//1  4//1
  -0.5, -0.5, 0.5,
  0.5, 0.5, 0.5,
  -0.5, 0.5, 0.5,
};

float cubeNormals [] = {
  // f  1//2  7//2  5//2
  0, 0, -1,
  0, 0, -1,
  0, 0, -1,
  // f  1//2  3//2  7//2
  0, 0, -1,
  0, 0, -1,
  0, 0, -1,
  // f  1//6  4//6  3//6
  -1, 0, 0,
  -1, 0, 0,
  -1, 0, 0,
  // f  1//6  2//6  4//6
  -1, 0, 0,
  -1, 0, 0,
  -1, 0, 0,
  // f  3//3  8//3  7//3
  0, 1, 0,
  0, 1, 0,
  0, 1, 0,
  // f  3//3  4//3  8//3
  0, 1, 0,
  0, 1, 0,
  0, 1, 0,
  // f  5//5  7//5  8//5
  1, 0, 0,
  1, 0, 0,
  1, 0, 0,
  // f  5//5  8//5  6//5
  1, 0, 0,
  1, 0, 0,
  1, 0, 0,
  // f  1//4  5//4  6//4
  0, -1, 0,
  0, -1, 0,
  0, -1, 0,
  // f  1//4  6//4  2//4
  0, -1, 0,
  0, -1, 0,
  0, -1, 0,
  // f  2//1  6//1  8//1
  0, 0, 1,
  0, 0, 1,
  0, 0, 1,
  // f  2//1  8//1  4//1
  0, 0, 1,
  0, 0, 1,
  0, 0, 1,
};

