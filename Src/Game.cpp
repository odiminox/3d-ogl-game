// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>
#include "third_party/glfw3.h"

#include "maths_test.h"
#include "entity.h"

std::vector<game::entity::Entity*> entities;
game::entity::Entity* a = new game::entity::Entity();
game::entity::Entity* b = new game::entity::Entity();
game::entity::Entity* c = new game::entity::Entity();

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
  GLFWwindow* window = glfwCreateWindow(800, 600, "OLG Game", nullptr, nullptr);
  if (window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
}


void render()
{

}

void quit()
{
  a = nullptr;
  delete a;
  b = nullptr;
  delete b;
  c = nullptr;
  delete c;
}

void update(bool loop)
{
  while(loop)
  {
    if (GetKeyState('X') & 0x8000)
    {
      loop = false;
    }

    for (auto entity : entities)
    {
      entity->update();
    }
  }

  std::cout << " QUIT! " << std::endl;
  quit();
}


int main()
{
  std::cout << " START! " << std::endl;

  if (!init())
  {
    std::cout << "FAIL!" << std::endl;
    return -1;
  }

  std::thread t1(update, 3);

  t1.join();
  std::cout << " END! " << std::endl;

  return 0;
}