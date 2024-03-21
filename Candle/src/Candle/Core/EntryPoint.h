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

	auto app = Candle::CreateApplication();
	app->Run();
	delete app;
}

#endif // KD_PLATFORM_WINDOWS
