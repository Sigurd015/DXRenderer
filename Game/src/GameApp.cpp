#include "DXR.h"
#include "EntryPoint.h"

class GameApp :public DXC::Application
{
public:
	GameApp(const DXC::ApplicationSpecification& specification) : DXC::Application(specification)
	{
		
	}
	~GameApp()
	{

	}
};

DXC::Application* DXC::CreateApplication(DXC::ApplicationCommandLineArgs args)
{
	DXC::ApplicationSpecification spec;
	spec.Name = "DxCraft";
	spec.WorkingDirectory = "../Game";
	spec.CommandLineArgs = args;
	spec.EnableImGui= true;

	return new GameApp(spec);
}