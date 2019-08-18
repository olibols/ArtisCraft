#pragma once
#include <memory>

class World;

struct BaseWorldEvent {
	virtual void handle(World& world) = 0;
};