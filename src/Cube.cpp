#include "Primitives.hpp"
#include <iostream>

Cube::Cube() 
{
	mVertices = {
		// Front
		-1.f, 1.f, 1.f, cubeUVCol[1], cubeUVRow[1],
		-1.f, -1.f, 1.f, cubeUVCol[1], cubeUVRow[2], 
		1.f, -1.f, 1.f, cubeUVCol[2], cubeUVRow[2],
		1.f, 1.f, 1.f, cubeUVCol[2], cubeUVRow[1],
	
		// Back
		-1.f, 1.f, -1.f, cubeUVCol[3], cubeUVRow[1],
		-1.f, -1.f, -1.f, cubeUVCol[3], cubeUVRow[2],
		1.f, -1.f, -1.f, cubeUVCol[4], cubeUVRow[2],
		1.f, 1.f, -1.f, cubeUVCol[4], cubeUVRow[1],
	
		// Left
		-1.f, 1.f, -1.f, cubeUVCol[0], cubeUVRow[1],
		-1.f, -1.f, -1.f, cubeUVCol[0], cubeUVRow[2],
		-1.f, -1.f, 1.f, cubeUVCol[1], cubeUVRow[2],
		-1.f, 1.f, 1.f, cubeUVCol[1], cubeUVRow[1],
	
		// Right
		1.f, 1.f, 1.f, cubeUVCol[2], cubeUVRow[1],
		1.f, -1.f, 1.f, cubeUVCol[2], cubeUVRow[2],
		1.f, -1.f, -1.f, cubeUVCol[3], cubeUVRow[2],
		1.f, 1.f, -1.f, cubeUVCol[3], cubeUVRow[1],
	
		// Top
		-1.f, 1.f, -1.f, cubeUVCol[1], cubeUVRow[0],
		-1.f, 1.f, 1.f, cubeUVCol[1], cubeUVRow[1],
		1.f, 1.f, 1.f, cubeUVCol[2], cubeUVRow[1],
		1.f, 1.f, -1.f, cubeUVCol[2], cubeUVRow[0],
	
		// Bottom
		-1.f, -1.f, 1.f, cubeUVCol[1], cubeUVRow[2],
		-1.f, -1.f, -1.f, cubeUVCol[1], cubeUVRow[3],
		1.f, -1.f, -1.f, cubeUVCol[2], cubeUVRow[3],
		1.f, -1.f, 1.f, cubeUVCol[2], cubeUVRow[2]
	};

	mIndices = {
		// Front
	    	0, 1, 2,
		0, 2, 3,
       	 
		// Back
		4, 5, 6,
		4, 6, 7,

		// Left
		8, 9, 10,
		8, 10, 11,

		// Right
		12, 13, 14,
		12, 14, 15,

		// Top
		16, 17, 18,
		16, 18, 19,

		// Bottom
		20, 21, 22,
		20, 22, 23
	};
}
