// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>
#include <chrono>
#include <future>


#include "third_party/fmod/api/inc/fmod.h"

#include "maths_test.h"
#include "entity.h"
#include "player.h"
#include "renderer.h"

std::vector<game::entity::Entity*> entities;
game::entity::Entity* a = new game::entity::Entity();
game::entity::Entity* b = new game::entity::Entity();
game::entity::Entity* c = new game::entity::Entity();

game::player::Player* player = new game::player::Player();



bool quit_game = false;



/*
  FSOUND_SAMPLE *sample = FSOUND_Sample_Load(FSOUND_FREE , "sounds/shoot.wav", 0, 0, 0);
  FSOUND_PlaySound(FSOUND_FREE, sample);

 */




int init()
{
  std::cout << " INIT! " << std::endl;

  if (!game::renderer::render_init())
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
    if ((GetKeyState('X') & 0x8000) || game::renderer::should_renderer_quit_window())
    {
      quit_game = false;
      game::renderer::render_quit();
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

  game::renderer::world_render_loop(quit_game);

  quit();
  std::cout << " END! " << std::endl;

  return 0;
}