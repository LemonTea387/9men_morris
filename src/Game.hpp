#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>

class Scene;
class Game {
 private:
  typedef std::unique_ptr<Scene> ScenePtr;
  typedef std::vector<ScenePtr> SceneStack;

  SceneStack m_Scenes;

 private:
  // Privatise Constructor
  Game();
  ~Game();
  void Loop() const;

 public:
  static constexpr int WINDOW_WIDTH = 800;
  static constexpr int WINDOW_HEIGHT = 800;

 public:
  // Delete copy and assignment constructor
  Game(Game const&) = delete;
  void operator=(const Game&) = delete;

  static Game& GetInstance() {
    static Game instance;
    return instance;
  }

  void Run();
  void PushScene(ScenePtr&&);
  void PopScene();
};

#endif
