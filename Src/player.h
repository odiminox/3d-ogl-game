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
        update_transform_matrices();
      }
    };
  }
}