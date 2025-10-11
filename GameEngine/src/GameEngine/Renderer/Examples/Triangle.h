#pragma once

namespace Triangle {
	float vertices[3 * (3 + 4)] = {
		// Vertex (first 3),    Color (Last 4)
		-0.5f, -0.5f, 1.0f,     0.85f, 0.3f, 0.64f, 1.0f,
		 0.5f, -0.5f, 1.0f,     0.65f, 0.1f, 0.68f, 1.0f,
		 0.0f,  0.5f, 1.0f,     0.9f, 0.8f, 0.34f, 1.0f
	};

	constexpr unsigned int totalIndices = 3;

	unsigned int indices[totalIndices] = {
		0, 1, 2
	};

	constexpr const char* vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}

		)";

	constexpr const char* fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		in vec4 v_Color;

		void main()
		{
			//color = vec4(v_Position + 0.5, 1.0); // To translate from pixel position to (0-1) range
			color = v_Color;
		}
	)";
}