#pragma once

#include <tiny_gltf.h>

namespace game
{
  namespace mesh
  {

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION


    struct Mesh
    {
      bool load_model();
    };
  }
}
