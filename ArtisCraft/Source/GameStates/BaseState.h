#include <SFML/Graphics.hpp>

class MasterRenderer;
class Application;

class BaseState {
public:
	BaseState(Application &app) : m_pApplication(&app) {}

	virtual ~BaseState() noexcept = default;
	
	virtual void handleEvent(sf::Event e) = 0;
	virtual void handleInput() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(MasterRenderer& renderer) = 0;

protected:
	Application* m_pApplication;

};