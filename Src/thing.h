#pragma once

#include "maths.h"
#include "render_data.h"

namespace game
{
  namespace thing
  {
    using namespace maths::vector;
    using namespace maths::matrix;

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
        thing_id = id_counter++;
      }

      VectorData vector_data;
      Matrix3 transform_matrix;

      render_data::RenderData render_data;

      int thing_id;

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

      void update_transform_matrices()
      {
        // L = T * R * S

        translate(transform_matrix, vector_data.position);

        rotate_x(transform_matrix, vector_data.rotation.x);
        rotate_y(transform_matrix, vector_data.rotation.y);
        rotate_z(transform_matrix, vector_data.rotation.z);

        scale(transform_matrix, vector_data.scale);
      }
    };


  }
}