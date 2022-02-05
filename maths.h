#pragma once

#include <cmath>

namespace game
{
  namespace maths
  {
    namespace vector
    {
      struct Vector3
      {
        Vector3() = default;
        Vector3(const float x, const float y, const float z)
        {
          this->x = x;
          this->y = y;
          this->z = z;
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

        float x, y, z;
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
      struct Matrix
      {
        Matrix() = default;
        Matrix(const float m00, const float m01, const float m02,
               const float m10, const float m11, const float m12,
               const float m20, const float m21, const float m22)
        {
          m[0][0] = m00; m[0][1] = m10; m[0][2] = m20;
          m[1][0] = m01; m[1][1] = m11; m[1][2] = m21;
          m[2][0] = m02; m[2][1] = m12; m[2][2] = m22;
        }

        Matrix(const vector::Vector3& a,
          const vector::Vector3& b,
          const vector::Vector3& c)
        {
          m[0][0] = a.x; m[0][1] = a.y; m[0][2] = a.z;
          m[1][0] = b.x; m[1][1] = b.y; m[1][2] = b.z;
          m[2][0] = c.x; m[2][1] = c.y; m[2][2] = c.z;
        }

        float& operator()(const int i, const int j)
        {
          return m[j][i];
        }

        const float&  operator()(const int i, const int j) const
        {
          return m[j][i];
        }

        float m[3][3];
      };

      inline Matrix operator*(Matrix& a, Matrix& b)
      {
        const float m00 = a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0);
        const float m01 = a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1);
        const float m02 = a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2);
        const float m10 = a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0);
        const float m11 = a(1, 0) * b(1, 0) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 2);
        const float m12 = a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2);
        const float m20 = a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0);
        const float m21 = a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1);
        const float m22 = a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2);

        return { m00, m01, m02,
                 m10, m11, m12,
                 m20, m21, m22 };
      }


      inline vector::Vector3 operator*(const Matrix& m, const vector::Vector3& v)
      {
        const float x = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z;
        const float y = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z;
        const float z = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z;

        return { x, y, z };
      }

      inline float determinant(const Matrix& m)
      {
        return m(0, 0) * m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1) +
          m(0, 1) * m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2) +
          m(2, 0) * m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0);
      }

      inline Matrix rotate_x(float a)
      {
        const float cosine_of_a = cos(a);
        const float sine_of_a = sin(a);

        const float m00 = 1.0f; const float m01 = 0.0f;        const float m02 = 0.0f;
        const float m10 = 0.0f; const float m11 = cosine_of_a; const float m12 = -sine_of_a;
        const float m20 = 0.0f; const float m21 = sine_of_a;   const float m22 = cosine_of_a;

        return { m00, m01, m02,
                 m10, m11, m12,
                 m20, m21, m22 };

      }

      inline Matrix rotate_y(float a)
      {
        const float cosine_of_a = cos(a);
        const float sine_of_a = sin(a);

        const float m00 = cosine_of_a; const float m01 = 0.0f; const float m02 = sine_of_a;
        const float m10 = 0.0f;        const float m11 = 1.0f; const float m12 = 0.0f;
        const float m20 = -sine_of_a;  const float m21 = 0.0f; const float m22 = cosine_of_a;

        return { m00, m01, m02,
                 m10, m11, m12,
                 m20, m21, m22 };
      }

      inline Matrix rotate_z(float a)
      {
        const float cosine_of_a = cos(a);
        const float sine_of_a = sin(a);

        const float m00 = cosine_of_a; const float m01 = -sine_of_a;  const float m02 = 0.0f;
        const float m10 = sine_of_a;   const float m11 = cosine_of_a; const float m12 = 0.0f;
        const float m20 = 0.0f;        const float m21 = 0.0f;        const float m22 = 1.0f;

        return { m00, m01, m02,
                 m10, m11, m12,
                 m20, m21, m22 };
      }

    }
  }
}