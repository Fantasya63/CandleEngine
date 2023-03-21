#include <Candle.h>

class Sandbox : public Candle::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

private:

};

Candle::Application* Candle::CreateApplication()
{
	return new Sandbox();
}