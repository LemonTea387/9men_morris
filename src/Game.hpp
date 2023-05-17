#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <memory>
#include <vector>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Scene;

/**
 * The Game class that is responsible for setup and running Scenes. This
 * Singleton Game class has a stack of scenes and does the Update/Render
 * GameLoop on whatever is at the back of the "stack". It is also responsible
 * for globally creatubg and exposing the application's Window via
 * GetWindow() and for  * glboally being able to Push and/or Pop Scenes to
 * switch between Scenes.
 */
class Game {
 private:
  typedef std::unique_ptr<Scene> ScenePtr;
  typedef std::vector<ScenePtr> SceneStack;

  /**
   * Background color of the program. This is to draw the background color of
   * the program.
   */
  sf::RectangleShape m_BackgroundColor;

  /**
   * The Stack of Scenes within the game. These Scenes are stored using
   * std::vector containing smart pointers (Following PIMPL) to the interface
   * `Scene`.
   */
  SceneStack m_Scenes;

 private:
  /**
   * Privatise Constructor. The Constructor is set to private to ensure only 1
   * copy can be made (which is done via the static method GetWindow, which has
   * access to this constructor and which will only ever call the constructor
   * once no matter how many times it is called).
   */
  Game();

  /**
   * Privatise Destructor. No particular reason for making this private, but
   * since the class is constructed in GetWindow() as a static member, it will
   * still be called on its destruction.
   */
  ~Game();

  /**
   * Runs the Main Game Loop of Update/Render. Does the Update/Render cycle of
   * the scene at the back of the stack, as well as does some checking if the
   * window is closed and terminate if needed.
   */
  void Loop() const;

 public:
  /**
   * The publicly accessible constant default Window Width.
   */
  static constexpr int WINDOW_WIDTH = 1000;

  /**
   * The publicly accsesible constant default Window Height.
   */
  static constexpr int WINDOW_HEIGHT = 1000;

  /**
   * Gets the context of the application's window. Retrieves a single Window
   * that ensures that all classes can use the same Window to render on.
   * Might deprecate in the future in favour of Render() function taking in
   * a sf::RenderTarget
   */
  static sf::RenderWindow& GetWindow() {
    static sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                   "EverythingNMM",
                                   sf::Style::Titlebar | sf::Style::Close);

    return window;
  }

 public:
  /**
   * Deletes the copy constructor. We don't want to be able to have multiple
   * instances of the Game class, so we don't allow copying it.
   */
  Game(Game const&) = delete;

  /**
   * Deletes the assignment operator. Similarly to the copy constructor, we
   * don't want to be able to assign the GetWindow() to any other object since
   * we only want a single instance of the class to be available., so we don't
   * allow it.
   */
  void operator=(const Game&) = delete;

  /**
   * Gets the global instance of the Game. We only want a single instance of the
   * Game. This static method is the only way to retrieve it since only here can
   * it call its own constructor since the constructor is privated and thus
   * inaccessible anywhere else.
   */
  static Game& GetInstance() {
    static Game instance;
    return instance;
  }

  /**
   * Starts the Game. Starts off with the MenuScene, and loops through the Scene
   * stack running the Loop() function until all Scenes are popped off the
   * stack.
   */
  void Run();

  /**
   * Add a new Scene to the game. Creates a new Scene that will then be executed
   * next, while still preserving the previous Scene to be able to be returned
   * later via PopScene(). Note that I use something called an rvalue reference
   * as the argument. This allows, similarly to Rust, the object can be "moved"
   * to be the function's responsibility instead, hopefully not invoking any
   * copy constructors at all.
   * So to use this function, the argument must be an r-value reference.
   * So you can do something like `PushScene(new MyScene())`, or
   * `PushScene(std::move(myScene))` where `myScene`
   * is a previously defined `MyScene` variable, and will not be in a usable
   * state after calling the PushScene function.
   */

  void PushScene(ScenePtr&&);

  /**
   * Removes the current Scene, returning the previously Pushed scene.
   * Pops out the most recent scene from the stack, and returns to the previous
   * one. For example, Pushing a MenuScene, then pushing a GameScene, then
   * Popping to remove the GameSceneand return to the MenuScene.
   */
  void PopScene();
};

#endif
