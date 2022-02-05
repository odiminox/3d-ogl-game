// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>
#include "third_party/glad/include/glad/glad.h"
#include "third_party/glfw3.h"

#include "maths_test.h"
#include "entity.h"

std::vector<game::entity::Entity*> entities;
game::entity::Entity* a = new game::entity::Entity();
game::entity::Entity* b = new game::entity::Entity();
game::entity::Entity* c = new game::entity::Entity();

GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

int init()
{
  std::cout << " INIT! " << std::endl;

  entities.push_back(a);
  entities.push_back(b);
  entities.push_back(c);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(800, 600, "OLG Game", nullptr, nullptr);
  if (window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }


  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void quit()
{
  glfwTerminate();

  a = nullptr;
  delete a;
  b = nullptr;
  delete b;
  c = nullptr;
  delete c;
}

void entity_update(bool loop)
{
  if (loop)
  {
    for (auto entity : entities)
    {
      entity->update();
    }
  }
}

void game_loop(bool loop)
{
  while(loop)
  {
    if ((GetKeyState('X') & 0x8000) || glfwWindowShouldClose(window))
    {
      loop = false;
    }

    std::thread entity_thread(entity_update, loop);

    glfwSwapBuffers(window);
    glfwPollEvents();

    entity_thread.join();
  }


  std::cout << " QUIT! " << std::endl;
}


int main()
{
  std::cout << " START! " << std::endl;

  if (!init())
  {
    std::cout << "FAIL!" << std::endl;
    return -1;
  }

  game_loop(true);

  quit();
  std::cout << " END! " << std::endl;

  return 0;
}