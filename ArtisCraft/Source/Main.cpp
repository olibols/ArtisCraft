#include "Application.h"
#include <Windows.h>
int main() {
	Application app("Minecraft");
	app.runLoop();

	printf("Somehowit exited");
	Sleep(10000);
}