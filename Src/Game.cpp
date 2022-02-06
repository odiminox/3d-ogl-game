// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>
#include <chrono>
#include <future>

#include "third_party/glad/include/glad/glad.h"
#include "third_party/glfw3.h"
#include "third_party/fmod/api/inc/fmod.h"

#include "maths_test.h"
#include "entity.h"
#include "player.h"

std::vector<game::entity::Entity*> entities;
game::entity::Entity* a = new game::entity::Entity();
game::entity::Entity* b = new game::entity::Entity();
game::entity::Entity* c = new game::entity::Entity();

game::player::Player* player = new game::player::Player();

GLFWwindow* window;

bool quit_game = false;

/*
  FSOUND_SAMPLE *sample = FSOUND_Sample_Load(FSOUND_FREE , "sounds/shoot.wav", 0, 0, 0);
  FSOUND_PlaySound(FSOUND_FREE, sample);

 */

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

int init()
{
  std::cout << " INIT! " << std::endl;

  std::cout << "Graphics Booting up..." << std::endl;

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

  if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  std::cout << "initialising world entities" << std::endl;
  entities.push_back(a);
  entities.push_back(b);
  entities.push_back(c);

  return 1;
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

void world_update(double delta_time)
{
  for (auto entity : entities)
  {
    entity->update(delta_time);
  }
}

void world_render()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

int simulation_time = 0;
int time_slice_8ms = 8; 

void game_logic(int delta_time)
{
  const auto player_task = std::async(std::launch::async,
    [delta_time]() {
      player->update(delta_time);
    });

  player_task.wait();

  const auto entity_task = std::async(std::launch::async,
    [delta_time]() {
      for (auto entity : entities)
      {
        entity->update(delta_time);
      }
    });

  entity_task.wait();
}

void game_loop()
{
  while(!quit_game)
  {
    if ((GetKeyState('X') & 0x8000) || glfwWindowShouldClose(window))
    {
      quit_game = false;
      glfwSetWindowShouldClose(window, true);
    }

    auto ts = std::chrono::system_clock::now();
    const auto current_time = std::chrono::duration_cast<std::chrono::seconds>(ts.time_since_epoch()).count();

    // Isolate the simulation time into slices which are ignorant of renderer/network
    while (simulation_time < current_time)
    {
      simulation_time += time_slice_8ms;
      game_logic(time_slice_8ms);
    }
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

  std::thread game_thread(game_loop);
  game_thread.detach();

  while (!quit_game)
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window))
    {
      quit_game = true;
      glfwSetWindowShouldClose(window, true);
    }

    world_render();
  }

  quit();
  std::cout << " END! " << std::endl;

  return 0;
}