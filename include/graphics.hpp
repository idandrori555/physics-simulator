#pragma once

#include "const.hpp"
#include "object.hpp"
#include <SDL3/SDL.h>

class GraphicsEngine
{
private:
  SDL_Window *m_window = nullptr;
  SDL_Renderer *m_renderer = nullptr;

  const int m_screen_width = consts::SCREEN_WIDTH;
  const int m_screen_height = consts::SCREEN_HEIGHT;
  const double m_meters_to_pixels = consts::METERS_TO_PIXELS;

  void world_to_screen(double world_x, double world_y, float &screen_x, float &screen_y);

public:
  bool init();
  void handle_events(bool &running);
  void render(const std::vector<Object> &objects);
  void cleanup();

  ~GraphicsEngine() noexcept;
};
