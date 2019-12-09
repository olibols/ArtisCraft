#pragma once
#include "States/StateBase.h"
#include "RenderContext.h"

#include <string>
#include <map>

using StateMap = std::map<std::string, std::unique_ptr<StateBase>>;

class Application {
public:
	Application(std::string windowName);

	void runLoop();
	
	StateBase& getState(std::string str);

private:

	StateMap m_states;
	RenderContext* m_context;

	std::string m_currentState;

	void handleWindowEvents();
};