#include <Model/Model.h>
#include <time.h>
#include <GLM.h>
#include <VertexFormat.h>

class Cube : public Model {
public:
	Cube();
	~Cube();

	void create();
	virtual void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override final;
	virtual void update() override final;

private:
	time_t timer;

};