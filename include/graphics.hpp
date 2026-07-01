#pragma once

class Graphics
{
public:
  Graphics(const Graphics &) = delete;
  Graphics &operator=(const Graphics &) = delete;
  Graphics(Graphics &&) = delete;
  Graphics &operator=(Graphics &&) = delete;

  inline static Graphics &instance(void)
  {
    static Graphics instance;
    return instance;
  }

private:
  Graphics(void) noexcept = default;
  ~Graphics(void) noexcept = default;
};
