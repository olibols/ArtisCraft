#include "../Util/GLM.h"

class Camera;

glm::mat4 makeViewMatrix(Camera camera);

glm::mat4 makeProjectionMatrix(float fov);