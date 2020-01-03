#pragma once
#include "States/StateBase.h"
#include "RenderContext.h"
#include "Renderer/MasterRenderer.h"
#include "Camera.h"

#include <string>
#include <map>

using StateMap = std::map<std::string, std::unique_ptr<StateBase>>;

class Application {
public:
	Application(std::string windowName);

	void runLoop();
	
	StateBase& getState(std::string str);
	void switchState(std::string str);

	inline Camera& getCamera() { return *m_camera; };
	inline RenderContext& getContext() { return *m_context; };

private:

	StateMap m_states;
	std::string m_currentState;

	RenderContext* m_context;
	MasterRenderer* m_renderer;
	Camera* m_camera;

	void handleWindowEvents();
};