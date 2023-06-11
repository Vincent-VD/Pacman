GitHub repo link: https://github.com/Vincent-VD/Pacman

Engine implementation:
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