// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>
#include <chrono>
#include <future>


#include "third_party/fmod/api/inc/fmod.h"

#include "Game.h"

/*
  FSOUND_SAMPLE *sample = FSOUND_Sample_Load(FSOUND_FREE , "sounds/shoot.wav", 0, 0, 0);
  FSOUND_PlaySound(FSOUND_FREE, sample);

 */

std::vector<game::entity::Entity*> entities;
game::entity::Entity* entity;
game::player::Player* player;

int Game::init()
{
  std::cout << " INIT! " << std::endl;

  entity = new game::entity::Entity();
  player = new game::player::Player();

  entities.push_back(entity);

  player->set_position(0.0f, -0.25f, 1.0f);
  player->set_rotation(0.0f);
  player->set_scale(0.5);

  entity->set_position(0.0f, -0.25f, 1.0f);
  entity->set_rotation(0.0f);
  entity->set_scale(0.5);

  player->render_data.material.shader_transform = &player->transform_matrix;
  renderer.add_new_render_data_object(player->render_data);

  entity->render_data.material.shader_transform = &entity->transform_matrix;
  renderer.add_new_render_data_object(entity->render_data);

  if (!renderer.render_init())
  {
    return -1;
  }

  std::cout << "initialising world entities" << std::endl;

  return 1;
}

void Game::quit()
{
  // Need to sync data across threads 
//  player = nullptr;
//  delete player;
}

void Game::world_update(int delta_time)
{
  for (auto entity : entities)
  {
    entity->update(delta_time);
  }
}

void Game::game_logic(int delta_time)
{
  const auto player_update_task = std::async(std::launch::async,
    [delta_time]() {
      player->update(delta_time);
    });

  player_update_task.wait();

  const auto entity_task = std::async(std::launch::async,
    [delta_time]() {
      for (auto entity : entities)
      {
        entity->update(delta_time);
      }
    });

  entity_task.wait();
}

void Game::game_loop()
{
  while(!quit_game)
  {
    if ((GetKeyState('X') & 0x8000) || renderer.should_renderer_quit_window())
    {
      quit_game = false;
      renderer.render_quit();
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

Game core_game;

void game_loop_threaded()
{
  core_game.game_loop();
}

int main()
{

  std::cout << " START! " << std::endl;

  if (!core_game.init())
  {
    std::cout << "FAIL!" << std::endl;
    return -1;
  }

  std::thread game_thread(game_loop_threaded);
  game_thread.detach();

  core_game.renderer.world_render_loop(core_game.quit_game);

  core_game.quit();
  std::cout << " END! " << std::endl;

  return 0;
}