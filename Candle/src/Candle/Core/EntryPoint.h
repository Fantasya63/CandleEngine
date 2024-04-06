#pragma once

#ifdef USE_GPU
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

#endif

#ifdef CD_PLATFORM_WINDOWS

extern Candle::Application* Candle::CreateApplication();

int main(int argc, char** argv)
{ 
	Candle::Log::Init();

	CD_PROFILE_BEGIN_SESSION("Startup", "CandleProfile-Startup.json");
	auto app = Candle::CreateApplication();
	CD_PROFILE_END_SESSION();

	CD_PROFILE_BEGIN_SESSION("Runtime", "CandleProfile-Runtime.json");
	app->Run();
	CD_PROFILE_END_SESSION();

	CD_PROFILE_BEGIN_SESSION("Shutdown", "CandleProfile-Shutdown.json");
	delete app;
	CD_PROFILE_END_SESSION();
}

#endif // KD_PLATFORM_WINDOWS
