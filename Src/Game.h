#pragma once

#include "entity.h"
#include "player.h"
#include "renderer.h"

class Game
{
private:
  int simulation_time = 0;
  int time_slice_8ms = 8;

public:
  Game() : renderer(){}

  int init();
  void quit();
  void world_update(int delta_time);
  void integrate_physics(int delta_time);
  void things_update(int delta_time);
  void game_loop();

  bool quit_game = false;
  game::renderer::Renderer renderer;
};