# 2d-ogl-game
## Small, silly 2D game using OGL 3.3

### Overview
Tasked myself to create a simple 2D C++ game in OpenGL 3.3 using as few external libs as possible.
I have tried to use C++ in a manner that is friendly to games with the following tenants:
- Avoid any unnecessary levels of abstraction by using OOP in its most simplest and practical forms (goodbye vtables)
- Limit usage of heavy std libraries (some will be used for early development to speed up implementation and improved later)
- Limit usage of template programming
- Don't over-engineer the design with loads of design patterns that don't really offer anything
- Try and code in a C style

### Implemented Features
- Bespoke maths lib for vectors/matrices
- Multithreaded with worker tasks
- Fixed simulation time for game logic step isolated from renderer/network logic
- FMOD audio

### Planned Features
- Custom physics system for basic integration
- Communicate with AWS services for score leaderboard
