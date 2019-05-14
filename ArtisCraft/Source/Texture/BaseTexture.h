#include <string>
#include <GL\glew.h>


class BaseTexture
{
public:
	BaseTexture() = default;
	BaseTexture(std::string filename);

	~BaseTexture();

	void loadFromFile(std::string filename);

	void bindTexture();

private:
	GLuint m_id;
};

