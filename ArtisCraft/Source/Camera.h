#include "Util/GLM.h"
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();

		void update();
		void hookEntity(const Entity& entity);

		const glm::mat4& getViewMatrix()           const noexcept;
		const glm::mat4& getProjMatrix()           const noexcept;
		const glm::mat4& getProjectionViewMatrix() const noexcept;



private:
	glm::vec3 m_worldPosition;
	glm::vec3 m_rotation;
	const Entity* m_pEntity;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projViewMatrx;
};
