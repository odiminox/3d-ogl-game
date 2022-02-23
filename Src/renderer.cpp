#include "renderer.h"

namespace game
{
  namespace renderer
  {
    void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
      glViewport(0, 0, width, height);
    }

    int Renderer::render_init()
    {
      std::cout << "Graphics Booting up..." << std::endl;

      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      window = glfwCreateWindow(800, 600, "OGL Game", nullptr, nullptr);

      if (window == nullptr)
      {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
      }
      glfwMakeContextCurrent(window);

      if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
      {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
      }

      glEnable(GL_DEPTH_TEST);

      glViewport(0, 0, 800, 600);
      glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

      for (render_data::RenderData* render_data_object : render_objects)
      {
        render_data_object->material.initialise();
        render_data_object->vertex_object.initialise();
      }

      std::cout << "Graphics stage booted up" << std::endl;

      return 0;
    }

    void Renderer::world_render_frame()
    {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      for (render_data::RenderData* render_data_object : render_objects)
      {
        render_data_object->material.render_material();
        render_data_object->vertex_object.render_vertex();
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    void Renderer::world_render_loop(bool quit_game)
    {
      while (!quit_game)
      {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window))
        {
          quit_game = true;
          glfwSetWindowShouldClose(window, true);
        }

        world_render_frame();
      }
    }

    void Renderer::render_quit()
    {
      glfwTerminate();

      for (render_data::RenderData* render_data_object : render_objects)
      {
        render_data_object->material.cleanup();
      }
    }

    void Renderer::renderer_quit_window() const
    {
      glfwSetWindowShouldClose(window, true);
    }

    bool Renderer::should_renderer_quit_window() const
    {
      return  glfwWindowShouldClose(window);
    }

    void Renderer::add_new_render_data_object(render_data::RenderData& render_data)
    {
      render_objects.push_back(&render_data);
    }
  }
}