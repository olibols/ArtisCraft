#include "Context.h"
#include "Settings.h"
#include "Camera.h"
#include "Renderer/Shaders/MainShader.h"
#include "Entity/Player.h"

class Application {
public:
	Application(std::string windowName);

	inline sf::RenderWindow& getWindow() { return m_pContext->window; };
	//inline Camera& getCamera() { return *m_pCamera; };

	void runLoop();

	void handleEvents();

private:

	bool shouldUpdate = true;

	MainShader* m_pShader = nullptr;

	RenderContext* m_pContext = nullptr;
	Camera* m_pCamera = nullptr;
	Player* m_pPlayer = nullptr;
};