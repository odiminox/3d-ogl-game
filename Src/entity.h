#pragma once

#include <iostream>
#include "thing.h"

namespace game
{
  namespace entity
  {
    struct Entity : thing::Thing
    {
      Entity() : Thing(1.0f, 1.0f, 0.0f)
      {
       
      }

      void update()
      {
        vector_data.position.x += 1.0f;
      }
    };
  }
}