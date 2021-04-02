# Physically-Based Rendering

A short course on pathtracing for Stamatics Projects '21

## Build Instructions

### Windows

**Requirements:**
- A C++ compiler. Visual Studio is the simplest way to set this up on Windows. Follow the steps [here](https://devblogs.microsoft.com/cppblog/getting-started-with-visual-studio-for-c-and-cpp-development/).
- CMake. Download [here](https://cmake.org/download/). Get the Windows installer (file with .msi extension). Run the setup wizard and install. If there's an option to add something to your PATH, do it. This will allow you to run a `cmake` command from the command prompt.
- git. You can get it [here](https://git-scm.com/downloads). The download can be extremely slow sometimes, let me know if that is the case.
- A text editor. I use [vscode](https://code.visualstudio.com/). For a tutorial to use it with C++, see [this page](https://code.visualstudio.com/docs/cpp/config-msvc). Also install the CMake extension.

**Build:**

Open the "Developer Command Prompt" that was installed with Visual Studio. You will be greeted with something like this
```
C:\...some-path...>_
```
The path mentioned here is the "current directory". All commands entered will be relative to the current directory. You can change the current directory by typing `cd <new-path>` and Enter. Note that if you want to change the drive from C to D, do `d:` first, and then you'll be able to `cd` into any directory in the D drive.

Go to the path where you want to download this repository. I will assume that this is in `D:\code\`. Use git to download the repository
```
git clone https://github.com/mayant15/stamatics-pbr
```
You should now have a folder `D:\code\stamatics-pbr` with all code. Go into this folder with `cd stamatics-pbr`. We can now use CMake to compile the code.
```
mkdir build
cd build
cmake ..
cmake --build .
```

You should now have an executable in `build\bin` or `build\bin\Debug`.
- `mkdir build` creates a new folder called `build` inside the repository. This is going to store temporary data that CMake needs.- `cd build` to go into the `build` folder
- `cmake ..` starts cmake's _configuration step_. This step needs a configuration file with the settings for this project. This file, the `CMakeLists.txt`, has already been provided with the repository.
- `cmake --build .` tells cmake to compile the configured project. This will use our C++ compiler to generate the final executable.

### Ubuntu

**Requirements:**
- A C++ compiler. You can get this by running `sudo apt install build-essential`, which installs `gcc` and `g++`, among other things.
- CMake. Get this via `pip` if you have python installed, with `pip install cmake`. The version in `apt` is fairly old.
- git. You can get this by running `sudo apt install git`.
- A text editor. I use [vscode](https://code.visualstudio.com/). For a tutorial to use it with C++, see [this page](https://code.visualstudio.com/docs/cpp/config-linux). Also install the CMake extension.

**Build:**

Open a terminal. You will be greeted with something like this
```
user@device:path$ _
```
The path mentioned here is the "current directory". All commands entered will be relative to the current directory. You can change the current directory by typing `cd <new-path>` and Enter.

Go to the path where you want to download this repository. I will assume that this is in `~/code/`. Use git to download the repository
```
git clone https://github.com/mayant15/stamatics-pbr
```
You should now have a folder `~/code/stamatics-pbr` with all code. Go into this folder with `cd stamatics-pbr`. We can now use CMake to compile the code.
```
mkdir build
cd build
cmake ..
cmake --build .
```

You should now have an executable in `build/bin` or `build/bin/Debug`.
- `mkdir build` creates a new folder called `build` inside the repository. This is going to store temporary data that CMake needs.- `cd build` to go into the `build` folder
- `cmake ..` starts cmake's _configuration step_. This step needs a configuration file with the settings for this project. This file, the `CMakeLists.txt`, has already been provided with the repository.
- `cmake --build .` tells cmake to compile the configured project. This will use our C++ compiler to generate the final executable.
