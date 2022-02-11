#pragma once

#include <iostream>
#include "thing.h"
#include "physics.h"

namespace game
{
  namespace entity
  {
    struct Entity : thing::Thing
    {
      Entity() : Thing(1.0f, 1.0f, 0.0f)
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

      game::physics::PhysicsData physics_data;
    };
  }
}