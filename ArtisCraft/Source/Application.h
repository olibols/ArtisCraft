#include <vector>

#include "GameStates/PlayingState.h"
#include "Renderer/MasterRenderer.h"
#include "Camera.h"
#include "RenderContext.h"

class Application
{
public:
	Application(std::string&& name);

	void runLoop();

	template<typename T, typename... Args>
	void pushState(Args&&... args)
	{
		m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		auto& s = m_states.back();
	}

	void popState();

private:
	void handleEvents();

	std::vector<std::unique_ptr<BaseState>> m_states;

	RenderContext m_context;
	MasterRenderer m_masterRenderer;
	Camera m_camera;


	bool m_isPopState = false;
};