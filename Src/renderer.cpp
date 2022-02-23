#include "renderer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      ImGui::StyleColorsDark();
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      ImGui_ImplOpenGL3_Init("#version 100");


      return 0;
    }

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    void Renderer::world_render_frame()
    {
      glfwPollEvents();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
      ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();

      if (show_another_window)
      {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
          show_another_window = false;
        ImGui::End();
      }

      glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      for (render_data::RenderData* render_data_object : render_objects)
      {
        render_data_object->material.render_material();
        render_data_object->vertex_object.render_vertex();
      }

      ImGui::Render();
      int display_w, display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
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

    GLFWwindow* Renderer::get_window() const
    {
      return window;
    }
  }
}