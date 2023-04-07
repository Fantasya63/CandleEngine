#include <Candle.h>


class ExampleLayer : public Candle::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Candle::Input::IsKeyPressed(CD_KEY_A))
		{
			
		}
	}

	void OnEvent(Candle::Event& event) override
	{
		
	}
};

class Sandbox : public Candle::Application
{
public:
	Sandbox()
	{
		ExampleLayer* layer = new ExampleLayer();
		PushLayer(layer);

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