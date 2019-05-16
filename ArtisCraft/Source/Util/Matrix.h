#include "../Util/GLM.h"

class Camera;
class Entity;

glm::mat4 makeModelMatrix(const Entity& entity);
glm::mat4 makeViewMatrix(const Camera& camera);
glm::mat4 makeProjectionMatrix(float fov);