#pragma once
#include "States/StateBase.h"

#include <string>
#include <map>

class Application {
public:
	Application(std::string windowName);

	void runLoop();
	void handleWindowEvents();

private:

	std::map<std::string, StateBase> m_states;

};