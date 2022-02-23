#pragma once

#include <assert.h>
#include "maths.h"

namespace game
{
  namespace physics
  {
    using namespace maths::vector;

    static float G = 0.1f;

    struct PhysicsData
    {
      Vector3 velocity{0.0f, 0.0f, 0.0f};
      Vector3 acceleration{0.0f, -0.0001f, 0.0f};
      float damping{0.001f};
      float inverse_mass{0.1f};
    };

    inline void integrate(Vector3& position, PhysicsData& physics_data, float time)
    {
      if (physics_data.inverse_mass <= 0.0f)
      {
        return;
      }

      assert(time > 0.0f);

      position += (physics_data.velocity * time) + physics_data.acceleration;

      //std::cout << position.x << " " << position.y << std::endl;

      physics_data.velocity *= powf(physics_data.damping, time);
    }
  }
}