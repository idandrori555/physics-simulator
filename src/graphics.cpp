#include "graphics.hpp"
#include <iostream>

void GraphicsEngine::world_to_screen(double world_x, double world_y, float &screen_x, float &screen_y)
{
  screen_x = static_cast<float>(world_x * m_meters_to_pixels);
  // Invert Y and offset by screen height
  screen_y = static_cast<float>(m_screen_height - (world_y * m_meters_to_pixels));
}

bool GraphicsEngine::init()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("Physics Simulator", m_screen_width, m_screen_height, 0, &m_window, &m_renderer))
  {
    std::cerr << "Window/Renderer Creation Error: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void GraphicsEngine::handle_events(bool &running)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_EVENT_QUIT)
    {
      running = false;
    }
  }
}

void GraphicsEngine::render(const std::vector<Object> &objects)
{
  // Clear screen to dark slate
  SDL_SetRenderDrawColor(m_renderer, 24, 24, 37, 255);
  SDL_RenderClear(m_renderer);

  // Draw floor line at world y = 0
  float floor_x1, floor_y1, floor_x2, floor_y2;
  world_to_screen(0, 0, floor_x1, floor_y1);
  world_to_screen(m_screen_width / m_meters_to_pixels, 0, floor_x2, floor_y2);
  SDL_SetRenderDrawColor(m_renderer, 108, 112, 134, 255);
  SDL_RenderLine(m_renderer, 0.0f, floor_y1, static_cast<float>(m_screen_width), floor_y2);

  // Vector scaling metrics
  const double vel_scale = 0.5;
  const double force_scale = 0.5;

  for (const auto &obj : objects)
  {
    float sx, sy;
    world_to_screen(obj.position.x, obj.position.y, sx, sy);

    // 1. Velocity Vector (Green)
    float vel_end_x, vel_end_y;
    world_to_screen(obj.position.x + obj.velocity.x * vel_scale,
                    obj.position.y + obj.velocity.y * vel_scale,
                    vel_end_x, vel_end_y);
    SDL_SetRenderDrawColor(m_renderer, 166, 227, 161, 255);
    SDL_RenderLine(m_renderer, sx, sy, vel_end_x, vel_end_y);

    // 2. Sigma Force Vector (Red)
    float force_end_x, force_end_y;
    world_to_screen(obj.position.x + obj.sigma_force.x * force_scale,
                    obj.position.y + obj.sigma_force.y * force_scale,
                    force_end_x, force_end_y);
    SDL_SetRenderDrawColor(m_renderer, 243, 139, 168, 255);
    SDL_RenderLine(m_renderer, sx, sy, force_end_x, force_end_y);

    // 3. Object Body (Pastel Pink Square)
    SDL_SetRenderDrawColor(m_renderer, 245, 194, 231, 255);
    SDL_FRect rect{sx - 5.0f, sy - 5.0f, 10.0f, 10.0f};
    SDL_RenderFillRect(m_renderer, &rect);
  }

  SDL_RenderPresent(m_renderer);
}
