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

      Vector3 *position = new Vector3();
      Vector3 *scale = new Vector3();
      Vector3 *rotation = new Vector3();
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
        vector_data.position = new Vector3(x, y, z);
      }

      void set_rotation(float amount)
      {
        vector_data.rotation = new Vector3(0.0f, 0.0f, amount);
      }

      void set_scale(float amount)
      {
        vector_data.scale = new Vector3(amount, amount, 0.0f);
      }

      void update_transform_matrices()
      {
        // L = T * R * S

        transform_matrix = translate(transform_matrix, *vector_data.position);

        /*transform_matrix = rotate_x(transform_matrix, maths::deg_to_radians(vector_data.rotation->x));
        transform_matrix = rotate_y(transform_matrix, maths::deg_to_radians(vector_data.rotation->y));
        transform_matrix = rotate_z(transform_matrix, maths::deg_to_radians(vector_data.rotation->z));

        transform_matrix = scale(transform_matrix, *vector_data.scale);*/
      }

      void cleanup()
      {
        vector_data.position = nullptr;
        delete vector_data.position;
        vector_data.rotation = nullptr;
        delete vector_data.scale;
        vector_data.rotation = nullptr;
        delete vector_data.rotation;
      }
    };


  }
}