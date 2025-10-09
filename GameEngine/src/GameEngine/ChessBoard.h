#pragma once

namespace ChessBoard {
	constexpr float xOffset = -0.75f;
	constexpr float yOffset = 0.75f;
	constexpr float boardWidth = 1.5f;
	constexpr float sqSze = boardWidth/8;
	
	constexpr float vertices[3 * 81] = {
		//      x,         y,    z,
		xOffset +      0.0f, yOffset -      0.0f, 0.0f,
		xOffset +     sqSze, yOffset -      0.0f, 0.0f,
		xOffset + 2 * sqSze, yOffset -      0.0f, 0.0f,
		xOffset + 3 * sqSze, yOffset -      0.0f, 0.0f,
		xOffset + 4 * sqSze, yOffset -      0.0f, 0.0f,
		xOffset + 5 * sqSze, yOffset -      0.0f, 0.0f,
		xOffset + 6 * sqSze, yOffset -      0.0f, 0.0f,
		xOffset + 7 * sqSze, yOffset -      0.0f, 0.0f,
		xOffset + 8 * sqSze, yOffset -      0.0f, 0.0f,

		xOffset +      0.0f, yOffset -     sqSze, 0.0f,
		xOffset +     sqSze, yOffset -     sqSze, 0.0f,
		xOffset + 2 * sqSze, yOffset -     sqSze, 0.0f,
		xOffset + 3 * sqSze, yOffset -     sqSze, 0.0f,
		xOffset + 4 * sqSze, yOffset -     sqSze, 0.0f,
		xOffset + 5 * sqSze, yOffset -     sqSze, 0.0f,
		xOffset + 6 * sqSze, yOffset -     sqSze, 0.0f,
		xOffset + 7 * sqSze, yOffset -     sqSze, 0.0f,
		xOffset + 8 * sqSze, yOffset -     sqSze, 0.0f,

		xOffset +      0.0f, yOffset - 2 * sqSze, 0.0f,
		xOffset +     sqSze, yOffset - 2 * sqSze, 0.0f,
		xOffset + 2 * sqSze, yOffset - 2 * sqSze, 0.0f,
		xOffset + 3 * sqSze, yOffset - 2 * sqSze, 0.0f,
		xOffset + 4 * sqSze, yOffset - 2 * sqSze, 0.0f,
		xOffset + 5 * sqSze, yOffset - 2 * sqSze, 0.0f,
		xOffset + 6 * sqSze, yOffset - 2 * sqSze, 0.0f,
		xOffset + 7 * sqSze, yOffset - 2 * sqSze, 0.0f,
		xOffset + 8 * sqSze, yOffset - 2 * sqSze, 0.0f,

		xOffset +      0.0f, yOffset - 3 * sqSze, 0.0f,
		xOffset +     sqSze, yOffset - 3 * sqSze, 0.0f,
		xOffset + 2 * sqSze, yOffset - 3 * sqSze, 0.0f,
		xOffset + 3 * sqSze, yOffset - 3 * sqSze, 0.0f,
		xOffset + 4 * sqSze, yOffset - 3 * sqSze, 0.0f,
		xOffset + 5 * sqSze, yOffset - 3 * sqSze, 0.0f,
		xOffset + 6 * sqSze, yOffset - 3 * sqSze, 0.0f,
		xOffset + 7 * sqSze, yOffset - 3 * sqSze, 0.0f,
		xOffset + 8 * sqSze, yOffset - 3 * sqSze, 0.0f,

		xOffset +      0.0f, yOffset - 4 * sqSze, 0.0f,
		xOffset +     sqSze, yOffset - 4 * sqSze, 0.0f,
		xOffset + 2 * sqSze, yOffset - 4 * sqSze, 0.0f,
		xOffset + 3 * sqSze, yOffset - 4 * sqSze, 0.0f,
		xOffset + 4 * sqSze, yOffset - 4 * sqSze, 0.0f,
		xOffset + 5 * sqSze, yOffset - 4 * sqSze, 0.0f,
		xOffset + 6 * sqSze, yOffset - 4 * sqSze, 0.0f,
		xOffset + 7 * sqSze, yOffset - 4 * sqSze, 0.0f,
		xOffset + 8 * sqSze, yOffset - 4 * sqSze, 0.0f,

		xOffset +      0.0f, yOffset - 5 * sqSze, 0.0f,
		xOffset +     sqSze, yOffset - 5 * sqSze, 0.0f,
		xOffset + 2 * sqSze, yOffset - 5 * sqSze, 0.0f,
		xOffset + 3 * sqSze, yOffset - 5 * sqSze, 0.0f,
		xOffset + 4 * sqSze, yOffset - 5 * sqSze, 0.0f,
		xOffset + 5 * sqSze, yOffset - 5 * sqSze, 0.0f,
		xOffset + 6 * sqSze, yOffset - 5 * sqSze, 0.0f,
		xOffset + 7 * sqSze, yOffset - 5 * sqSze, 0.0f,
		xOffset + 8 * sqSze, yOffset - 5 * sqSze, 0.0f,

		xOffset +      0.0f, yOffset - 6 * sqSze, 0.0f,
		xOffset +     sqSze, yOffset - 6 * sqSze, 0.0f,
		xOffset + 2 * sqSze, yOffset - 6 * sqSze, 0.0f,
		xOffset + 3 * sqSze, yOffset - 6 * sqSze, 0.0f,
		xOffset + 4 * sqSze, yOffset - 6 * sqSze, 0.0f,
		xOffset + 5 * sqSze, yOffset - 6 * sqSze, 0.0f,
		xOffset + 6 * sqSze, yOffset - 6 * sqSze, 0.0f,
		xOffset + 7 * sqSze, yOffset - 6 * sqSze, 0.0f,
		xOffset + 8 * sqSze, yOffset - 6 * sqSze, 0.0f,

		xOffset +      0.0f, yOffset - 7 * sqSze, 0.0f,
		xOffset +     sqSze, yOffset - 7 * sqSze, 0.0f,
		xOffset + 2 * sqSze, yOffset - 7 * sqSze, 0.0f,
		xOffset + 3 * sqSze, yOffset - 7 * sqSze, 0.0f,
		xOffset + 4 * sqSze, yOffset - 7 * sqSze, 0.0f,
		xOffset + 5 * sqSze, yOffset - 7 * sqSze, 0.0f,
		xOffset + 6 * sqSze, yOffset - 7 * sqSze, 0.0f,
		xOffset + 7 * sqSze, yOffset - 7 * sqSze, 0.0f,
		xOffset + 8 * sqSze, yOffset - 7 * sqSze, 0.0f,

		xOffset +      0.0f, yOffset - 8 * sqSze, 0.0f,
		xOffset +     sqSze, yOffset - 8 * sqSze, 0.0f,
		xOffset + 2 * sqSze, yOffset - 8 * sqSze, 0.0f,
		xOffset + 3 * sqSze, yOffset - 8 * sqSze, 0.0f,
		xOffset + 4 * sqSze, yOffset - 8 * sqSze, 0.0f,
		xOffset + 5 * sqSze, yOffset - 8 * sqSze, 0.0f,
		xOffset + 6 * sqSze, yOffset - 8 * sqSze, 0.0f,
		xOffset + 7 * sqSze, yOffset - 8 * sqSze, 0.0f,
		xOffset + 8 * sqSze, yOffset - 8 * sqSze, 0.0f,
	};

	constexpr unsigned int totalIndices = 3 * 64;

	constexpr unsigned int whiteIndices[totalIndices] = {
		 0,  9, 10,
		 0,  1, 10,
		 2, 11, 12,
		 2,  3, 12,
		 4, 13, 14,
		 4,  5, 14,
		 6, 15, 16,
		 6,  7, 16,

		10, 19, 20,
		10, 11, 20,
		12, 21, 22,
		12, 13, 22,
		14, 23, 24,
		14, 15, 24,
		16, 25, 26,
		16, 17, 26,

		18, 27, 28,
		18, 19, 28,
		20, 29, 30,
		20, 21, 30,
		22, 31, 32,
		22, 23, 32,
		24, 33, 34,
		24, 25, 34,

		28, 37, 38,
		28, 29, 38,
		30, 39, 40,
		30, 31, 40,
		32, 41, 42,
		32, 33, 42,
		34, 43, 44,
		34, 35, 44,

		36, 45, 46,
		36, 37, 46,
		38, 47, 48,
		38, 39, 48,
		40, 49, 50,
		40, 41, 50,
		42, 51, 52,
		42, 43, 52,

		46, 55, 56,
		46, 47, 56,
		48, 57, 58,
		48, 49, 58,
		50, 59, 60,
		50, 51, 60,
		52, 61, 62,
		52, 53, 62,

		54, 63, 64,
		54, 55, 64,
		56, 65, 66,
		56, 57, 66,
		58, 67, 68,
		58, 59, 68,
		60, 69, 70,
		60, 61, 70,

		64, 73, 74,
		64, 65, 74,
		66, 75, 76,
		66, 67, 76,
		68, 77, 78,
		68, 69, 78,
		70, 79, 80,
		70, 71, 80
	};

	constexpr unsigned int blackIndices[totalIndices] = {
		 1, 10, 11,
		 1,  2, 11,
		 3, 12, 13,
		 3,  4, 13,
		 5, 14, 15,
		 5,  6, 15,
		 7, 16, 17,
		 7,  8, 17,

		 9, 18, 19,
		 9, 10, 19,
		11, 20, 21,
		11, 12, 21,
		13, 22, 23,
		13, 14, 23,
		15, 24, 25,
		15, 16, 25,

		19, 28, 29,
		19, 20, 29,
		21, 30, 31,
		21, 22, 31,
		23, 32, 33,
		23, 24, 33,
		25, 34, 35,
		25, 26, 35,

		27, 36, 37,
		27, 28, 37,
		29, 38, 39,
		29, 30, 39,
		31, 40, 41,
		31, 32, 41,
		33, 42, 43,
		33, 34, 43,

		37, 46, 47,
		37, 38, 47,
		39, 48, 49,
		39, 40, 49,
		41, 50, 51,
		41, 42, 51,
		43, 52, 53,
		43, 44, 53,

		45, 54, 55,
		45, 46, 55,
		47, 56, 57,
		47, 48, 57,
		49, 58, 59,
		49, 50, 59,
		51, 60, 61,
		51, 52, 61,

		55, 64, 65,
		55, 56, 65,
		57, 66, 67,
		57, 58, 67,
		59, 68, 69,
		59, 60, 69,
		61, 70, 71,
		61, 62, 71,

		63, 72, 73,
		63, 64, 73,
		65, 74, 75,
		65, 66, 75,
		67, 76, 77,
		67, 68, 77,
		69, 78, 79,
		69, 70, 79
	};

	constexpr const char* vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}

		)";

	constexpr const char* whiteFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			//in vec3 v_Position;

			void main()
			{
				//color = vec4((v_Position + 0.75)/1.5, 1.0); // To translate from pixel position to (0-1) range
				color = vec4(0.921, 0.925, 0.816, 1.0); // Chess white square color
			}

		)";

	constexpr const char* blackFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				//color = vec4(1.0, 1.0, 1.0, 1.0); // Pure black color
				color = vec4(0.456, 0.584, 0.321, 1.0); // Chess black square color
			}

		)";
}