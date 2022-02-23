#pragma once

#include <cmath>

namespace game
{
  namespace maths
  {
    static float PI = 3.14159f;

    inline float deg_to_radians(const float degrees)
    {
      return (degrees * PI) / 180.0f;
    }

    namespace vector
    {
      struct Vector3
      {
        Vector3() = default;
        Vector3(const float x, const float y, const float z, const float w = 1.0f)
        {
          this->x = x;
          this->y = y;
          this->z = z;
          this->w = w;
        }

        Vector3& operator+=(const Vector3& v)
        {
          x += v.x;
          y += v.y;
          z += v.z;
          return *this;
        }

        Vector3& operator-=(const Vector3& v)
        {
          x -= v.x;
          y -= v.y;
          z -= v.z;
          return *this;
        }

        Vector3& operator*=(const float s)
        {
          x *= s;
          y *= s;
          z *= s;
          return *this;
        }

        Vector3& operator/=(float s)
        {
          s = 1.0f / s;
          x *= s;
          y *= s;
          z *= s;
          return *this;
        }

        float x, y, z, w;
      };

      namespace operations
      {}

      inline Vector3 operator+(const Vector3& lhs, const Vector3 rhs)
      {
        return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
      }

      inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
      {
        return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
      }

      inline Vector3 operator*(const Vector3& v, const float s)
      {
        return { v.x * s, v.y * s, v.z * s };
      }

      inline Vector3 operator/(const Vector3& v, float s)
      {
        s = 1.0f / s;
        return { v.x * s, v.y * s, v.z * s };
      }

      inline Vector3 operator-(const Vector3& v)
      {
        return { -v.x, -v.y, -v.z };
      }

      inline float magnitude(const Vector3& v)
      {
        return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
      }

      inline Vector3 normalize(const Vector3& v)
      {
        return v / magnitude(v);
      }

      inline float dot_product(const Vector3& lhs, const Vector3& rhs)
      {
        return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
      }

      inline Vector3 cross_product(const Vector3& lhs, const Vector3& rhs)
      {
        const float x = lhs.y * rhs.z - lhs.z * rhs.y;
        const float y = lhs.z * rhs.x - lhs.x * rhs.z;
        const float z = lhs.z * rhs.z - lhs.y * rhs.z;

        return { x, y, z };
      }
    }

    namespace matrix
    {
      struct Matrix3
      {
        Matrix3(const float m00, const float m01, const float m02, const float m03,
               const float m10, const float m11, const float m12, const float m13,
               const float m20, const float m21, const float m22, const float m23,
               const float m30, const float m31, const float m32, const float m33 = 1.0f)
        {
          m[0][0] = m00; m[0][1] = m10; m[0][2] = m20; m[0][3] = m03;
          m[1][0] = m01; m[1][1] = m11; m[1][2] = m21; m[1][3] = m13;
          m[2][0] = m02; m[2][1] = m12; m[2][2] = m22; m[2][3] = m23;
          m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
        }

        Matrix3(float homog = 1.0f)
        {
          m[0][0] = 0.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
          m[1][0] = 0.0f; m[1][1] = 0.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
          m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 0.0f; m[2][3] = 0.0f;
          m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = homog;
        }

        Matrix3(float data[4][4])
        {
          m[0][0] = data[0][0]; m[0][1] = data[0][1]; m[0][2] = data[0][2]; m[0][3] = data[0][3];
          m[1][0] = data[1][0]; m[1][1] = data[1][1]; m[1][2] = data[1][2]; m[1][3] = data[1][3];
          m[2][0] = data[2][0]; m[2][1] = data[2][1]; m[2][2] = data[2][2]; m[2][3] = data[2][3];
          m[3][0] = data[3][0]; m[3][1] = data[3][1]; m[3][2] = data[3][2]; m[3][3] = data[3][3];
        }

        float& operator()(const int i, const int j)
        {
          return m[j][i];
        }

        const float& operator()(const int i, const int j) const
        {
          return m[j][i];
        }

        float m[4][4];
      };

      inline Matrix3 operator*(Matrix3& a, Matrix3& b)
      {
        // Row 1
        const float m00 = a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0);
        const float m01 = a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) + a(0, 3) * b(3, 1);
        const float m02 = a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2) + a(0, 3) * b(3, 2);
        const float m03 = a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3) * b(3, 3);

        // Row 2
        const float m10 = a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0) + a(1, 3) * b(3, 0);
        const float m11 = a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) + a(1, 3) * b(3, 1);
        const float m12 = a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2) + a(1, 3) * b(3, 2);
        const float m13 = a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3) * b(3, 3);

        // Row 3
        const float m20 = a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0) + a(2, 3) * b(3, 0);
        const float m21 = a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1) + a(2, 3) * b(3, 1);
        const float m22 = a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) + a(2, 3) * b(3, 2);
        const float m23 = a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3) * b(3, 3);

        // Row 4
        const float m30 = a(3, 0) * b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) + a(3, 3) * b(3, 0);
        const float m31 = a(3, 0) * b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) + a(3, 3) * b(3, 1);
        const float m32 = a(3, 0) * b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) + a(3, 3) * b(3, 2);
        const float m33 = a(3, 0) * b(0, 3) + a(3, 1) * b(1, 3) + a(3, 2) * b(2, 3) + a(3, 3) * b(3, 3);

        return { m00, m01, m02, m03,
                 m10, m11, m12, m13,
                 m20, m21, m22, m23,
                 m30, m31, m32, m33 };
      }

      inline vector::Vector3 operator*(const Matrix3& m, const vector::Vector3& v)
      {
        const float x = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w;
        const float y = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w;
        const float z = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w;
        const float w = m(3, 0) * v.x + m(3, 1) * v.y + m(3, 3) * v.z + m(3, 3) * v.w;

        return { x, y, z, w };
      }

      inline float determinant(const Matrix3& m)
      {
        return m(0, 0) * m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1) +
               m(0, 1) * m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2) +
               m(2, 0) * m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0);
      }

      inline Matrix3 scale(Matrix3& mat, vector::Vector3& scale)
      {
        float scale_matrix_data[4][4] = {
          {scale.x, 0.0f,    0.0f,    0.0f},
          {0.0f,    scale.y, 0.0f,    0.0f},
          {0.0f,    0.0f,    scale.z, 1.0f}
        };

        Matrix3 scale_matrix(scale_matrix_data);
        Matrix3 res = scale_matrix * mat;

        return res;
      }

      inline Matrix3 translate(Matrix3& mat, vector::Vector3& trans)
      {
        float translate_matrix_data[4][4] = {
          {1.0f, 0.0f, 0.0f, trans.x},
          {0.0f, 1.0f, 0.0f, trans.y},
          {0.0f, 0.0f, 1.0f, trans.z},
          {0.0f, 0.0f, 0.0f, 1.0f},
        };

        Matrix3 translate_matrix(translate_matrix_data);

        return translate_matrix;
      }

      inline Matrix3 rotate_x(float a)
      {
        const float cosine_of_a = cos(a);
        const float sine_of_a = sin(a);

        float rotation_matrix_data[4][4] = {
          {1.0f, 0.0f,        0.0f,         0.0f},
          {0.0f, cosine_of_a, -sine_of_a,   0.0f},
          {0.0f, sine_of_a,   cosine_of_a,  0.0f},
          {0.0f, 0.0f,        0.0f,         1.0f}
        };

        Matrix3 rotation_matrix(rotation_matrix_data);
        return rotation_matrix;
      }
      
      inline Matrix3 rotate_y(float a)
      {
        const float cosine_of_a = cos(a);
        const float sine_of_a = sin(a);

        float rotation_matrix_data[4][4] = {
          {cosine_of_a, 0.0f, sine_of_a,   0.0f},
          {0.0f,        1.0f, 0.0f,        0.0f},
          {-sine_of_a,  0.0f, cosine_of_a, 0.0f},
          {0.0f,        0.0f, 0.0f,        1.0f}
        };

        Matrix3 rotation_matrix(rotation_matrix_data);
        return rotation_matrix;
      }
      
      inline Matrix3 rotate_z(float a)
      {
        const float cosine_of_a = cos(a);
        const float sine_of_a = sin(a);

        float rotation_matrix_data[4][4] = {
          {cosine_of_a, -sine_of_a,  0.0f, 0.0f},
          {sine_of_a,   cosine_of_a, 0.0f, 0.0f},
          {0.0f,        0.0f,        0.0f, 0.0f},
          {0.0f,        0.0f,        0.0f, 1.0f}
        };

        Matrix3 rotation_matrix(rotation_matrix_data);
        return rotation_matrix;
      }

    }

    namespace camera
    {
      inline matrix::Matrix3 frustrum(float left, float right, float bottom, float top, float near_plane, float far_plane)
      {
        const float a = 2.0f * near_plane / (right - left);
        const float b = 2.0f * near_plane / (top - bottom);
        const float c = (right + left) / (right - left);
        const float d = (top + bottom) / (top - bottom);
        const float e = -(far_plane + near_plane) / (far_plane - near_plane);
        const float f = -left;
        const float g = -(2 * far_plane * near_plane) / (far_plane - near_plane);
        const float h = 0.0f;

        float frustrum_matrix_data[4][4] = {
          {a,    0.0f, c, 0.0f},
          {0.0f, b,    d, 0.0f},
          {0.0f, 0.0f, e, g},
          {0.0f, 0.0f, f, h},
        };

        matrix::Matrix3 frustrum_matrix(frustrum_matrix_data);
        return frustrum_matrix;
      }

      inline matrix::Matrix3 perspective(float fov, float aspect, float front, float back)
      {
        float tangent = tanf(deg_to_radians((fov / 2)));
        float height = front * tangent;
        float width = height * aspect;

        matrix::Matrix3 perspective_matrix = frustrum(-width, 
          width, 
          -height, 
          height, 
          front, back);
        return perspective_matrix;
      }
    }
  }
}