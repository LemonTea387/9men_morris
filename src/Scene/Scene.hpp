#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>

#include "ui/UI.hpp"

/**
 * A base Scene class that represents a scene to be displayed and ran by Game
 * class. This Scene class acts as screen for the game to be ran. It provides
 * Update and Render function that should be called by the Game in order to
 * progress the 'scene'. It will store a vector of UI elements and static
 * drawables, which both can be rendered and UI be updated.
 */
class Scene {
 public:
  /**
   * Function to progress the Scene based on sf::Event that has occured, called
   * by Game to pass down the event. Usually, this is called passing down the
   * hierarchy to pass down the sf::Event. It is usually a bad design to call it
   * internally in the class or call a higher hierarchy' object's Update() from
   * a lower hierarchy' object as that can lead to unexpected results.
   */
  virtual void Update(sf::Event event);

  /**
   * Function to draw objects (usually sf::Drawable's) onto the screen with
   * passed in RenderWindow context. This function is used to render any
   * gameobject onto the renderwindow and is called for every frame.
   * So in any scene's Render function we would just need `window.draw(obj)`.
   */
  virtual void Render(sf::RenderWindow& window);

  /**
   * Adds the UI element into internal ui vector for ease of updating/rendering.
   */
  void addUI(graphics::UI* ui);

  /**
   * Adds the drawable element into internal drawable vector for ease of
   * rendering.
   */
  void addDrawable(sf::Drawable* drawable);

  /**
   * Default Constructor, usually the main way to make the base Scene, called
   * when creating any Derived Scenes.
   */
  Scene();

  /**
   * Virtual Destructor, each specific scene should handle their own clean-up.
   */
  virtual ~Scene();

 protected:
  /**
   * The flag for determining if this scene is to be 'killed' or popped during
   * the update.
   */
  bool m_IsKilled{false};

  /**
   * Vector for storing all UI elements, use for ease of updating/rendering
   */
  std::vector<graphics::UI*> m_ui{};

  /**
   * Vector for storing all Drawable elements, use for ease of rendering
   */
  std::vector<sf::Drawable*> m_draw{};
};

#endif
