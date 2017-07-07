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
* [SOIL2](https://bitbucket.org/SpartanJ/soil2)
* [Spdlog C++ Logging Library](https://github.com/gabime/spdlog)

## Scenes

### Rotating Cube

![Alt text](Tests/Cube/Screenshots/01.png?raw=true "Cube")

### Icosahedron Subdivision

![Alt text](Tests/Sphere/Screenshots/05.png?raw=true "Sphere")

### Earth

* DDS Texture Loading + Lighting + Cubemap Skybox

![Alt text](Tests/Earth/Screenshots/01.png?raw=true "Earth")

### Solar System

* Multiple icospheres for the celestial bodies
* DDS textures for the planets and moons
* Emissive + Ambient + Diffuse Lighting
* Cube Map for Milky Way Skybox
* Planet Rotation & Revolution 

![Alt text](Tests/Solar-System/Screenshots/01.png?raw=true "Earth")

![Alt text](Tests/Solar-System/Screenshots/02.png?raw=true "System")