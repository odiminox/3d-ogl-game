#pragma once

#include "maths.h"

namespace game
{
  namespace thing
  {
    using namespace maths::vector;

    static int id_counter = 0;

    struct VectorData
    {
      VectorData() = default;

      Vector3 position{};
      Vector3 scale{};
      Vector3 rotation{};
    };

    struct Thing
    {
      Thing(float x = 0.0f, float y = 0.0f, float z = 0.0f)
      {
        set_position(x, y, z);
        id = id_counter++;
        vector_data;
      }

      ~Thing()
      {

      }

      VectorData vector_data;
      int id;

      void set_position(float x = 0.0f, float y = 0.0f, float z = 0.0f)
      {
        vector_data.position = Vector3(x, y, z);
      }

      void set_rotation(float amount = 0.0f)
      {
        vector_data.rotation = Vector3(0.0f, 0.0f, amount);
      }

      void set_scale(float amount = 0.0f)
      {
        vector_data.scale = Vector3(amount, amount, 0.0f);
      }
    };


  }
}