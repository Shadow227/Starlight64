#include <starlight.h>

class GameApp : public SLE::Application
{
public:
	GameApp() {};
	~GameApp() {};
};

SLE::Application* SLE::CreateApp() 
{
	return new GameApp();
}
