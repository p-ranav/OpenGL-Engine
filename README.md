# OpenGL 3D Rendering Engine

## Quick Start

* Install [Visual Studio 2017 Community Edition](https://www.visualstudio.com/vs/whatsnew/)
* Open Engine.sln
* Ensure that the build is configured for DEBUG | x64
* Select Build => Build Solution
* The Engine should build as a static library (Engine.lib)
* This Engine library is used by all the test projects in Tests/.

## Dependent Libraries

The following libraries are already incorporated in Engine\Dependencies\.

* [FreeGLUT](http://freeglut.sourceforge.net/)
* [GLEW](http://glew.sourceforge.net/)
* [OpenGL Mathematics (GLM)](http://glm.g-truc.net/0.9.8/index.html)
* [Spdlog C++ Logging Library](https://github.com/gabime/spdlog)

## Tests

### Rotating Cube - BMP Texture Loading + Rotation

![Alt text](Tests/Cube/Screenshots/01.png?raw=true "Rotating Cube")

### Icosahedron Subdivision

![Alt text](Tests/Sphere/Screenshots/03.png?raw=true "Icosphere")

# Earth - DDS Texture + Lighting

![Alt text](Screenshots/01.png?raw=true "Earth")