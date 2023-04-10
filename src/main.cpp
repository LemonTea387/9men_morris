#include <iostream>
#include "Game.hpp"

<<<<<<< src/main.cpp

#ifdef _MSC_VER
int WinMain() {
#else
int main(int argc, char* argv[]) {
#endif

  try {
    Game::GetInstance().Run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown Exception!" << std::endl;
  }

  return 0;
}
