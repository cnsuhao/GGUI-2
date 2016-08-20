# GGUI
High Performance GUI using OpenGL.

Build instructions:

1.  mkdir build bin
2.  cp Content bin/Debug/Content
3.  cd build
4.  cmake .. -G "*YOUR GENERATOR*"

Visual Studio 14 2015:

1. Set the startup project to be "GGUI" within Visual Studio 2015
2. Go into the "GGUI" project "Properties"
3. Under "General" set "Platform Toolset" to Visual Studio 2013 (v120)

Xcode:

1. Set target to GGUI
2. Within Scheme set the working directory to be bin/Debug
3. Within Scheme set the build config to Release
Note: The debug build config doesnt work

Currently supported/working generators:

- Visual Studio 14 2015
- Xcode

