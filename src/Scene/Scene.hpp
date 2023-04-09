#ifndef SCENE_H
#define SCENE_H

class Scene {
 public:
  virtual void Update() = 0;
  virtual void Render() = 0;
};

#endif
