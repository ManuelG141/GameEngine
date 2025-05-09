 # GameEngine  

This is a GameEngine test created while following the tutorials of [The Cherno](https://www.youtube.com/@TheCherno) on YouTube about the [Hazel Engine](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT).  

## Features  
- **Event System**: Handles application events like window close events.  
- **Window Management**: Uses GLFW for creating and managing windows.  
- **Logging**: Integrated logging system using spdlog.  

## Requirements  
- C++17 compatible compiler.
- [Visual Studio](https://visualstudio.microsoft.com/es/) to configure and build the project. 
- [Premake](https://github.com/premake/premake-core) to generate the solution files
- [GLFW](https://github.com/ManuelG141/glfw) library for window management.  
- [spdlog](https://github.com/gabime/spdlog) library for logging.  

## How to Build  
1. Clone the repository.
    - Use the command `git clone --recurse-submodules https://github.com/ManuelG141/GameEngine.git` to clone the repository and the submodules.
    - If you already clone the project without `--recurse-submodules` option then use these commands:
        ~~~
          git submodule init
          git submodule update
        ~~~
2. Ensure all dependencies (GLFW, spdlog) are included in the `vendor` directory.
3. Run the `GenerateProject.bat` file to generate the solution files to **Visual Studio** 2022 using premake
  - In case you have a different version of **Visual Studio** you can change the version in the `.bat` file:
    ~~~
      call vendor\bin\premake\premake5.exe [Your Visual Studio Version, example: vs2022]
      PAUSE
    ~~~
5. Use Visual Studio to configure and build the project.  

## How to Run  
1. Build the project.  
2. Run either using **Visual Studio** or with the executable generated in the `bin` directory, under the desired configuration folder.  

## Acknowledgments  
- Inspired by TheCherno's Hazel Engine tutorials.  
- GLFW and spdlog libraries are used for window management and logging, respectively.
- Premake are used to generate the solution files for the project  