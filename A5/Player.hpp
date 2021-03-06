#pragma once

#include "Collidable.hpp"
#include <glm/glm.hpp>

class Player : public Collidable {
  double direction;
  double oldDirection;
  double t;
  glm::vec3 inertialVelocity;
  glm::vec3 inputVelocity;
  void setDirection(double direction);
public:
  Player(glm::vec3 Fg);
  double getDirection();
  float mass;
  float runningSpeed;
  float jumpingSpeed;
  float power;
  glm::vec3 g;
  glm::vec3 position;
  glm::vec3 acceleration;
  Hitbox getHitbox();

  glm::vec3 getVelocity();
  void setInputVelocity(glm::vec3);
  void setDirection(glm::vec3);
  void setVelocity(glm::vec3);
  void setInertialVelocity(glm::vec3);
};
