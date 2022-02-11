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

      Vector3 position;
      Vector3 scale;
      Vector3 rotation;
    };

    struct Thing
    {
      Thing(float x, float y, float z)
      {
        set_position(1, 1, 0);
        set_rotation(0);
        set_scale(1);
        thing_id = id_counter++;
      }

      VectorData vector_data;
      Matrix3 transform_matrix;

      render_data::RenderData render_data;

      int thing_id;

      void set_position(float x, float y, float z)
      {
        vector_data.position = Vector3(x, y, z);
      }

      void set_rotation(float amount)
      {
        vector_data.rotation = Vector3(0.0f, 0.0f, amount);
      }

      void set_scale(float amount)
      {
        vector_data.scale = Vector3(amount, amount, amount);
      }

      void update_transform_matrices()
      {
        // L = T * R * S

        Matrix3 translate_matrix = translate(transform_matrix, vector_data.position);
        Matrix3 rotation_matrix = rotate_z(transform_matrix, maths::deg_to_radians(vector_data.rotation.z));
        Matrix3 scale_matrix = scale(transform_matrix, vector_data.scale);

        transform_matrix = translate_matrix * rotation_matrix;
        //transform_matrix = transform_matrix * scale_matrix;
      }

      void cleanup()
      {
      }
    };


  }
}