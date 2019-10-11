#include "Context.h"
#include "Settings.h"
#include "Camera.h"
#include "States/StateBase.h"

#include <vector>

class Application {
public:
	Application(std::string windowName);

	inline sf::RenderWindow& getWindow() { return m_pContext->window; };
	inline Camera& getCamera() { return *m_pCamera; };


	void runLoop();

	void handleEvents();

private:

	std::vector<std::unique_ptr<StateBase>> m_states;

	bool m_shouldUpdate = true;

	RenderContext* m_pContext = nullptr;
	Camera* m_pCamera = nullptr;
};