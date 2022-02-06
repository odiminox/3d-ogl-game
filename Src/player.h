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

      void update(int delta_time)
      {
        vector_data.position.x += 1.0f;
      }
    };
  }
}