# Starlight Game Engine - A Vulkan Based Game Engine:

Starlight Game Engine is an open source game engine that will be built in multiple "layers" by both myself (George Skaggs) and contributors from the internet and Full Sail University. The goal of this engine is to allow anyone to learn more about game engine development, while also providing a useful tool anyone can use in the future. In the future, I want to make the engine less API dependent, allow for use of multiple graphics API's.

#How to Setup the project workspace:

The Starlight Game Engine aims to have as little outside libraries as possible, however some things do need to be initialized as we are using Vulkan. In the future, I will be moving this project into a CMake project however please know you have to have the Vulkan API (version 1.3.283.0) installed to your C drive, as well as GLFW (version 3.4) also installed to your C Drive. The other library the engine will use is actually itself.

#Layout of the engine:

Starlight will be a 3 part engine. The first part is the core engine, which builds as a .lib file. The second will be an editor that will be created in the future. The third is the application/game you build using Starlight.

#Code Review Process:

Starlight is an open source game engine, which means that anyone with a computer can contribute to the project. While all contributions will be appreciated, there will be a standard to try and keep the engine clean and understandable by everyone involved. Once the core of the engine is setup, the repository will be split into 3 main branches, Development, Nightly, and Stable. The Development branch will become the main branch you can make contributions to, I (George Skaggs) will be managing the nightly and stable builds based on engine stability. For the most part, I will accept most contributions, if there is a major issue I will reach out to you if possible to explain why the request was rejected.

## Currently Done:
- Vulkan API setup with GLFW
- Core engine structure setup started.

## TODO:
I will be updating this section as I mark off features that I wish to have in this project.

- Math Library
- Basic rendering setup
- Game Objects and Game Scenes
- Keyboard support
- UI drawing
- Engine Editor
- DEBUG MODE
- Game States
- And much, much more!


## Authors

- [@George Skaggs](https://github.com/Shadow227)
