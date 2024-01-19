| Platform  | Build Status                                                                                                                                                                   |
|-----------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Windows   | [![Windows build](https://github.com/alspin8/Orion/actions/workflows/build-windows.yml/badge.svg)](https://github.com/alspin8/Orion/actions/workflows/build-windows.yml)       |
| Ubuntu    | [![Ubuntu build](https://github.com/alspin8/Orion/actions/workflows/build-ubuntu.yml/badge.svg)](https://github.com/alspin8/Orion/actions/workflows/build-ubuntu.yml)          |
| Macos ARM | [![Macos arm build](https://github.com/alspin8/Orion/actions/workflows/build-macos-arm.yml/badge.svg)](https://github.com/alspin8/Orion/actions/workflows/build-macos-arm.yml) |
| Macos     | [![Macos build](https://github.com/alspin8/Orion/actions/workflows/build-macos.yml/badge.svg)](https://github.com/alspin8/Orion/actions/workflows/build-macos.yml)             |


## Installation

### Clone repo
````bash
git clone https://github.com/alspin8/Orion.git
````

### Configure
````bash
xmake f --mode=<debug|release> --unittest=<y|n> --nogpu=<y|n> --sandbox=<y|n>
````

### Build
````bash
xmake
````

## Credits
* [OpenGL](https://www.opengl.org)
* [glfw](https://github.com/glfw/glfw.github.io)
* [glew](https://github.com/nigels-com/glew)
* [doctest](https://github.com/doctest/doctest)
* [stb](https://github.com/nothings/stb)

