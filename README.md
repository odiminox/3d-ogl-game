# 3d-ogl-game
## Small, silly 3D game using OGL 3.3

### Overview
Tasked myself to create a simple 2D C++ game in OpenGL 3.3 using as few external libs as possible in as little time as possible.
I have tried to use C++ in a manner that is friendly to games with the following tenants:
- Avoid any unnecessary levels of abstraction by using OOP in its most simplest and practical forms, favouring composition and aggregation
- Limit usage of heavy std libraries (some will be used for early development to speed up implementation and improved later)
- Limit usage of template programming
- Don't over-engineer the design with loads of design patterns that don't really offer anything
- Try and code in a C style
- If exceptions are used, they must be sandboxed otherwise assert and static asserts

### Game Design
- Simple platformer with basic physics

### Implemented Features
- Bespoke maths lib for vectors/matrices (not optimised at all. Written for readability at the moment)
- Multithreaded with worker tasks
- Fixed simulation time for game logic step isolated from renderer/network logic
- FMOD audio
- Custom physics system for basic integration
- Dear Imgui

### Planned Features
- Particles
- glTF asset handling
- Communicate with AWS services for score leaderboard

### TODO
- Sync data across threads
- load textures
- batch vertex data
