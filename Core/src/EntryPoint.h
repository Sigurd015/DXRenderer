#pragma once

extern DXR::Application* DXR::CreateApplication(DXR::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	auto app = DXR::CreateApplication({ argc, argv });
	app->Run();
	delete app;
}