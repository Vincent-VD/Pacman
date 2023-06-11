# Engine Implementation

1) Level loading:
    - Levels get loaded from a txt file. This allows me greater flexibility and faster iteration when designing
    the levels without a proper level editor.
    - When going to the next level, the current scene gets deleted, and the next one gets loaded from its txt file.
    Each scene has a vector of persistant objects, which are a subset of the gameobjects in the scene, which get carried
    between level loads.
    - The reasons I delete a scene when I load in the next one, and not just load in all scene at once, and simply switch
    between those are 2: memory usage, simplicity
        - Memory usage: having easch scene exist in memory seems like a waste to me, even if they are small enough that they
        could reasonably fit.
        - Simplicity: If I have to take into account reading all levels at the start, I would need to take that into
        account when creating my gameobjects, which would involce too much micromanaging. Furthermore, I would need an
        entity to keep track if I need to restore a level if I return to it to recreate the gameobjects that were destroyed.
        Deactivating them is an option, but why would I do that? They would simply not get used anymore, so it makes
        more sense to destroy them.
2) Ghost AI:
    - The ghost AI is rather simple, because this course isn't Gameplay Programming.
    - AI and sprite iteration handled through state because difference in sprites and behavior with each state.
        -> Disabled when InputComponent is active
3) Level files:
    - Each file contains configurations for all 3 game modes
    - Files get read depending on the game mode selected in the main menu
        - This is why the LoadMain function only does a small amount of work
4) Input Axis system:
    - In most 2D games, you can control the character with both the analog stick and the dpad. However, because of how
    XInput is structured, those to are inherintely compatible, so I created a map to, well, map the depad buttons
    to axis values, so I could use the left stick and dpad interchangeably without needing too much extra code on the outside.
    Because of this, I did the same thing for the WASD keyboard commands.

# Minigin

Minigin is a very small project using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

# Goal

Minigin can/may be used as a start project for the exam assignment in the course 'Programming 4' at DAE. In that assignment students need to recreate a popular 80's arcade game with a game engine they need to program themselves. During the course we discuss several game programming patterns, using the book '[Game Programming Patterns](https://gameprogrammingpatterns.com/)' by Robert Nystrom as reading material. These patterns need to be applied (when applicable) as well as all (most) [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

# Disclaimer

Minigin is, despite perhaps the suggestion in its name, not a game engine. It is just a very simple sdl2 ready project. None of the patterns discussed in the course are used (except singleton which use we challenge during the course). It is up to the students to implement their own vision for their engine, apply patterns as they see fit, create their game as efficient as possible.

# Use

Download the latest release of this project and compile/run in visual studio. Since students need to have their work on github too, they can use this repository as a template.
