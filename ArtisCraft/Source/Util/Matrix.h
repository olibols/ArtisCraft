#include <GLM.h>

class Entity;
class Camera;

glm::mat4 makeModelMatrix(Entity entity);

glm::mat4 makeViewMatrix(Camera camera);

glm::mat4 makeProjectionMatrix(float fov);