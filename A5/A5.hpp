#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/MeshConsolidator.hpp"

#include "SceneNode.hpp"
#include "Animation.hpp"
#include "Keyframe.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <chrono>
#include <set>

struct LightSource {
  glm::vec3 position;
  glm::vec3 rgbIntensity;
};

class A5 : public CS488Window {
public:
  A5();
  virtual ~A5();

protected:
  virtual void init() override;
  virtual void appLogic() override;
  virtual void guiLogic() override;
  virtual void draw() override;
  virtual void cleanup() override;

  //-- Virtual callback methods
  virtual bool cursorEnterWindowEvent(int entered) override;
  virtual bool mouseMoveEvent(double xPos, double yPos) override;
  virtual bool mouseButtonInputEvent(int button, int actions, int mods) override;
  virtual bool mouseScrollEvent(double xOffSet, double yOffSet) override;
  virtual bool windowResizeEvent(int width, int height) override;
  virtual bool keyInputEvent(int key, int action, int mods) override;

  //-- One time initialization methods:
  std::shared_ptr<SceneNode> readLuaSceneFile(const std::string& filename);
  void createShaderProgram();
  void enableVertexShaderInputSlots();
  void uploadVertexDataToVbos(const MeshConsolidator & meshConsolidator);
  void mapVboDataToVertexShaderInputLocations();
  void initViewMatrix();
  void initLightSources();

  void initPerspectiveMatrix();
  void uploadCommonSceneUniforms();
  void renderSceneGraph(SceneNode &node, glm::mat4 model = glm::mat4());
  void renderAnimatedSceneGraph(
    SceneNode &node,
    Animation& animation,
    glm::mat4 model = glm::mat4()
  );
  void renderArcCircle();

  glm::mat4 m_perpsective;
  glm::mat4 m_view;

  LightSource m_light;

  //-- GL resources for mesh geometry data:
  GLuint m_vao_meshData;
  GLuint m_vbo_vertexPositions;
  GLuint m_vbo_vertexNormals;
  GLint m_positionAttribLocation;
  GLint m_normalAttribLocation;
  ShaderProgram m_shader;

  //-- GL resources for trackball circle geometry:
  GLuint m_vbo_arcCircle;
  GLuint m_vao_arcCircle;
  GLint m_arc_positionAttribLocation;
  ShaderProgram m_shader_arcCircle;

  // BatchInfoMap is an associative container that maps a unique MeshId to a BatchInfo
  // object. Each BatchInfo object contains an index offset and the number of indices
  // required to render the mesh with identifier MeshId.
  BatchInfoMap m_batchInfoMap;

  std::string m_luaSceneFile;

  std::shared_ptr<SceneNode> blockSceneNode;
  std::shared_ptr<SceneNode> puppetSceneNode;

private:
  struct Mouse {
    double x;
    double y;
    double prevX;
    double prevY;
    bool isRightButtonPressed = false;
    bool isLeftButtonPressed = false;
    bool isMiddleButtonPressed = false;
  } mouse;

  double animationStartTime;
  Animation playerWalkingAnimation;
  Animation playerStandingAnimation;
  Animation* currentAnimation;

  std::set<int> keysPressed;

  struct Player {
    double direction = 3.14; // computed value of velocity for rendering purposes
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
  } player;

  struct Block {
    glm::vec3 position;
    glm::vec3 size;
    Block(glm::vec3 position, glm::vec3 size);
  };

  std::vector<Block> blocks;

  bool isKeyPressed(int key);
};
