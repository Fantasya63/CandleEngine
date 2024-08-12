#type vertex
#version 330 core
	
	layout(location = 0) in vec4 a_Position;
	layout(location = 1) in vec2 a_UV;
	
	uniform mat4 u_ViewProjection;
	uniform mat4 u_Model;
	out vec2 v_UV;

	void main()
	{
		v_UV = a_UV;
		gl_Position = u_ViewProjection * u_Model * vec4(a_Position.xyz, 1.0);
	}



#type fragment
#version 330 core
	
	layout(location = 0) out vec4 outCol;

	uniform sampler2D u_AlbedoTex;
	uniform vec4 u_TintColor;
	uniform vec2 u_TilingFactor;
	in vec2 v_UV;

	void main()
	{
		outCol = vec4(1.0, 1.0, 1.0, 1.0);
	}
