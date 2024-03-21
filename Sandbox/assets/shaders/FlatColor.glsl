#type vertex
#version 330 core
	
	layout(location = 0) in vec4 a_Position;
	layout(location = 1) in vec3 a_Color;
	layout(location = 2) in vec2 a_UV;
	
	uniform mat4 u_ViewProjection;
	uniform mat4 u_Model;
	out vec3 v_Color;
	out vec2 v_UV;

	void main()
	{
		v_UV = a_UV;
		v_Color = a_Color;
		gl_Position = u_ViewProjection * u_Model * vec4(a_Position.xyz, 1.0);
	}



#type fragment
#version 330 core
	
	layout(location = 0) out vec4 outCol;
	uniform vec3 u_Color;
	in vec3 v_Color;
	in vec2 v_UV;

	void main()
	{
		outCol = vec4(u_Color, 1.0);
	}
