#include <iostream>

#include "maths.h"

inline void maths_test()
{
  using namespace game::maths::vector;

  std::cout << "-------------------vector tests-------------------" << std::endl;
  Vector3 vec1(1.0f, 1.0f, 0.0f);
  Vector3 vec2(1.0f, 2.0f, 0.0f);
  std::cout << "vec1  x:" << vec1.x << " y:" << vec1.y << " z:" << vec1.z << std::endl;
  std::cout << "vec2  x:" << vec2.x << " y:" << vec2.y << " z:" << vec1.z << std::endl;

  {
    Vector3 res = vec1 + vec2;
    std::cout << "vec1 + vec2 = x:" << res.x << " y:" << res.y << " z:" << res.z << std::endl;
  }

  {
    Vector3 res = vec1 * 4;
    std::cout << "vec1 * 4 = x:" << res.x << " y:" << res.y << " z:" << res.z << std::endl;
  }

  {
    Vector3 res = vec1 - vec2;
    std::cout << "vec1 - vec2 = x:" << res.x << " y:" << res.y << " z:" << res.z << std::endl;
  }

  {
    Vector3 res = vec1 / 0.5;
    std::cout << "vec1 / 0.5 = x: " << res.x << " y:" << res.y << " z:" << res.z << std::endl;
  }

  {
    std::cout << "magnitude(vec1) = " << magnitude(vec1) << std::endl;
  }

  {
    Vector3 res = normalize(vec1);
    std::cout << "normalize(vec1) = x: " << res.x << " y:" << res.y << " z:" << res.z << std::endl;
  }

  {
    float res = dot_product(vec1, vec2);
    std::cout << "dot_product(vec1, vec) = " << res << std::endl;
  }

  {
    Vector3 res = cross_product(vec1, vec2);
    std::cout << "cross_product(vec1, vec2) = x:" << res.x << " y:" << res.y << " z:" << res.z << std::endl;
  }
}