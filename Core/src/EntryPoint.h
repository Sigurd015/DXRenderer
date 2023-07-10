#pragma once

extern DXC::Application* DXC::CreateApplication(DXC::ApplicationCommandLineArgs args);

namespace DXC
{
	int Main(int argc, char** argv)
	{
		auto app = DXC::CreateApplication({ argc, argv });
		app->Run();
		delete app;
		return 0;
	}
}

#ifdef DXC_DIST

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return DXC::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return DXC::Main(argc, argv);
}

#endif
