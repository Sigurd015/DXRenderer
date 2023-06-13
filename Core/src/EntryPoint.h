#pragma once

extern DXR::Application* DXR::CreateApplication(DXR::ApplicationCommandLineArgs args);

namespace DXR
{
	int Main(int argc, char** argv)
	{
		auto app = DXR::CreateApplication({ argc, argv });
		app->Run();
		delete app;
		return 0;
	}
}

#ifdef DXR_DIST

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return DXR::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return DXR::Main(argc, argv);
}

#endif
