#include "Context.h"
#include "Settings.h"
#include "Camera.h"
#include "States/StateBase.h"
#include "Renderer/MasterRenderer.h"

#include <vector>

class Application {
public:
	Application(std::string windowName);

	inline sf::RenderWindow& getWindow() { return m_pContext->window; };
	inline Camera& getCamera() { return *m_pCamera; };

	template<typename T, typename... Args>
	inline void pushState(Args&&... args)
	{
		m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		auto& s = m_states.back();
		//s->onOpen();
	}

	void runLoop();

	void handleEvents();

private:

	std::vector<std::unique_ptr<StateBase>> m_states;

	bool m_shouldUpdate = true;

	MasterRenderer m_renderer;

	RenderContext* m_pContext = nullptr;
	Camera* m_pCamera = nullptr;
};