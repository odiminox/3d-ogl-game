#pragma once

#include <iostream>
#include <vector>

#include "third_party/glad/include/glad/glad.h"
#include "glfw3.h"
#include "render_data.h"

namespace game
{
  namespace renderer
  {
    class Renderer
    {
    private:
      GLFWwindow* window;
      std::vector<render_data::RenderData*> render_objects;

    public:
      static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
      int render_init();
      void world_render_frame();
      void world_render_loop(bool quit_game);
      void render_quit();
      void renderer_quit_window() const;
      bool should_renderer_quit_window() const;

      void add_new_render_data_object(render_data::RenderData& render_data);

      GLFWwindow* get_window() const;
    };


  }
}