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

unsigned int shader_program;
unsigned int vertex_array_object;
unsigned int element_buffer_object;

/*
  FSOUND_SAMPLE *sample = FSOUND_Sample_Load(FSOUND_FREE , "sounds/shoot.wav", 0, 0, 0);
  FSOUND_PlaySound(FSOUND_FREE, sample);

 */

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}


int render_init()
{
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

  float vertices[] = {
       0.5f,  0.5f, 0.0f,  // top right
       0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f   // top left 
  };
  unsigned int indices[] = {
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
  };

  std::cout << "compiling vertex shader..." << std::endl;

  const char* vertex_shader_code = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
  glCompileShader(vertex_shader);

  int  success;
  char infoLog[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

    return -1;
  }

  std::cout << "compiling fragment shader..." << std::endl;

  const char* fragment_shader_code = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


  unsigned int fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

    return -1;
  }

  std::cout << "Creating shader program" << std::endl;

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

  if (!success)
  {
    glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
    std::cout << "ERROR:SHADER_PROGRAM::CREATION_FAILED\n" << infoLog << std::endl;

    return -1;
  }

  glUseProgram(shader_program);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  glGenVertexArrays(1, &vertex_array_object);
  glGenBuffers(1, &element_buffer_object);

  glBindVertexArray(vertex_array_object);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  std::cout << "Graphics stage booted up" << std::endl;
}

int init()
{
  std::cout << " INIT! " << std::endl;

  if (!render_init())
  {
    return -1;
  }

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

void world_update(int delta_time)
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

  glUseProgram(shader_program);
  glBindVertexArray(vertex_array_object);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
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