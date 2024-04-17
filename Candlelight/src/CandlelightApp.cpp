#include <Candle.h>

#include "EditorLayer.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Candle
{

	class Candlelight : public Application
	{
	public:
		Candlelight()
			: Application("Candlelight")
		{
			//ExampleLayer* layer = new ExampleLayer();
			PushLayer(new EditorLayer());

		}
		~Candlelight()
		{

		}

	private:
	};


	Application* Candle::CreateApplication()
	{
		return new Candlelight();
	}
}

#include "Candle/Core/EntryPoint.h"