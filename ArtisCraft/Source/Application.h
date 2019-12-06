#pragma once
#include "States/StateBase.h"
#include "RenderContext.h"

#include <string>
#include <map>

class Application {
public:
	Application(std::string windowName);

	void runLoop();
	
	StateBase& getState(std::string str);

private:

	std::map<std::string, std::unique_ptr<StateBase>> m_states;
	RenderContext* m_context;

	void handleWindowEvents();
};