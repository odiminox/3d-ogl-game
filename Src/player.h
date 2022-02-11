#pragma once

#include <iostream>
#include "thing.h"

namespace game
{
  namespace player
  {
    struct Player : thing::Thing
    {
      Player() : Thing(1.0f, 1.0f, 0.0f)
      {
      }

      void init()
      {
        render_data.material.initialise();
        render_data.vertex_object.initialise();
      }

      void update(int delta_time)
      {
        // Do player update stuff here
        if (GetKeyState('W') & 0x8000)
        {
          vector_data.position.y += 0.001 * delta_time;
        }

        if (GetKeyState('S') & 0x8000)
        {
          vector_data.position.y -= 0.001 * delta_time;
        }

        if (GetKeyState('A') & 0x8000)
        {
          vector_data.position.x -= 0.001 * delta_time;
        }

        if (GetKeyState('D') & 0x8000)
        {
          vector_data.position.x += 0.001 * delta_time;
        }


        std::cout << "player location is: " << " x:" << vector_data.position.x <<
          " y:" << vector_data.position.y << " z:" << vector_data.position.z << std::endl;

        update_transform_matrices();
      }
    };
  }
}