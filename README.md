<a id="readme-top"></a>

[![Last Commit][last-commit-shield]][last-commit-url]


<div align="center"> 
    <h1 align="center">2D Map</h1> 
    <p align="center"> <br /> 
        <a href="https://github.com/lazarnagulov/2d-map/issues/new?labels=bug">Report Bug</a> 
    </p> 
</div> 

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#installation">Intallation</a></li>
    <li><a href="#controls">Controls</a></li>
    <li><a href="#controls">Screenshots</a></li>
  </ol>
</details>

## About The Project

![img](./Images/measure-mode.png)

This project is a 2D C++/OpenGL application designed for navigation and distance measurement on a digital map. The rendering pipeline is built using modern OpenGL (3.0+ with programmable shaders).

The main objective of the program is to allow the user to move across a large high-resolution map and measure real-time traversed distance. The application features two interactive modes:

1. *Walking Mode* — the user moves across the map by controlling direction with WASD, while a navigation pin remains fixed at the center of the screen and the map scrolls beneath it. Movement distance is continuously tracked and displayed on screen.
1. *Measurement Mode* — the full map becomes visible, and the user can place multiple points with mouse clicks. Consecutive points form line segments, whose lengths accumulate into a total measured distance. Points can be removed dynamically, updating the total length in real time.

Mode switching is done via keyboard (R) or UI icons (a walker symbol and a ruler symbol depending on active state).
The application keeps state between modes - meaning the current position, traversal distance or placed measurement points remain preserved on swap.

## Built with

This project is implemented entirely in C++ and uses a modern OpenGL programmable pipeline along with several supporting libraries for rendering, input, and texture handling.

* [![C++][C++]][C++-url]
* [![OpenGL][OpenGL]][OpenGL-url]
* [![GLFW][GLFW]][GLFW-url]
* [![GLEW][GLEW]][GLEW-url]
* [![FreeType][FreeType]][FreeType-url]
* [![GLM][GLM]][GLM-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Installation

Follow the steps below to build and run the project locally.

---

#### 1. Clone the repository

If the project includes third-party components inside the repo (fonts, shader sources, textures, etc.),
make sure to clone **recursively**:

```bash
git clone --recursive https://github.com/lazarnagulov/2d-map.git
cd 2d-map
```

If you forgot --recursive:
```bash
git submodule update --init --recursive
```

#### 2. Configure with CMake

Create a build folder and generate project files:
```bash
mkdir build
cd build
cmake ..
```

#### 3. Build & Run

You may now build the project in two ways:
- Open in Visual Studio / run .sln
- Build with CMake directly
```bash
cmake --build . --config Release
./2d-map  
```
<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Controls

| Action | Input |
|-------|-------|
| Move across map (Walking Mode) | **W / A / S / D** |
| Place a point (Measurement Mode) | **Left Mouse Click** |
| Remove a point (when hovering on it)** | **Left Mouse Click** |
| Switch mode (Walk ↔ Measure) | **R** or click mode icon |
| Reset current mode state (distance or path)** | **0** |
| Zoom in (Walking Mode) | **+** |
| Zoom out (Walking Mode) | **-** |
| Exit application | **ESC** |

Cursor is visually represented as a **compass**, with the red needle pointing toward the **upper-left corner**.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Screenshots

| Preview | Description |
|--------|-------------|
| ![walking_mode](./Images/walk-mode.png) | Walking mode with map scrolling under a centered pin |
| ![measurement_mode](./Images/measure-mode.png) | Full-map measurement mode with connected distance points |
| ![cursor](Images/compass.png) | Custom compass cursor with red needle facing top-left |
| ![signature](Images/signature.png) | Semi-transparent label containing student name and index |

<p align="right">(<a href="#readme-top">back to top</a>)</p>


[last-commit-shield]: https://img.shields.io/github/last-commit/lazarnagulov/2d-map?branch=main&style=for-the-badge
[last-commit-url]: https://github.com/lazarnagulov/2d-map/commits/main
[C++]: https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white  
[C++-url]: https://isocpp.org/  
[OpenGL]: https://img.shields.io/badge/OpenGL-5586A4?style=for-the-badge&logo=opengl&logoColor=white  
[OpenGL-url]: https://www.opengl.org/  
[GLFW]: https://img.shields.io/badge/GLFW-232F3E?style=for-the-badge&logo=c&logoColor=white  
[GLFW-url]: https://www.glfw.org/  
[GLEW]: https://img.shields.io/badge/GLEW-000000?style=for-the-badge&logo=opengl&logoColor=white  
[GLEW-url]: http://glew.sourceforge.net/  
[FreeType]: https://img.shields.io/badge/FreeType-1B1F23?style=for-the-badge&logo=font-awesome&logoColor=white  
[FreeType-url]: https://freetype.org/  
[GLM]: https://img.shields.io/badge/GLM-3A3A3A?style=for-the-badge&logo=glm&logoColor=white  
[GLM-url]: https://github.com/g-truc/glm  