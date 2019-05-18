#include "Context.h"


class Application {
public:
	Application(std::string name);

	void runLoop();
private:
	RenderContext* m_context = new RenderContext(windowName, 1280, 720);

	std::string windowName;
};