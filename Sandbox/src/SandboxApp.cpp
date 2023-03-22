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
		CD_INFO("EXAMPLE LAYER UPDATE");
	}

	void OnEvent(Candle::Event& event) override
	{
		CD_INFO("EXAMPLE LAYER EVENT");
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