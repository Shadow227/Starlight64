#pragma once

#ifdef SLE_PLATEFORM_WINDOWS
extern SLE::Application* SLE::CreateApp();

int main(int argc, char** argv)
{
	auto app = SLE::CreateApp();

	app->startApp("Collectathon | Starlight", 1280, 720, 0);
	delete app;
}
#endif