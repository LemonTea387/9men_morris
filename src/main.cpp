#include <iostream>

#include "Game.hpp"

int main(int argc, char* argv[]) {

  try {
    Game::GetInstance().Run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown Exception!" << std::endl;
  }

  return 0;
}
