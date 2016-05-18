#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

#include "particle.hpp"


particle::particle() {
	vao = 0;
	vertexbuffer = 0;
	indexbuffer = 0;
	vertexarray = NULL;
	indexarray = NULL;
	nverts = 0;
	ntris = 0;
}

particle::~particle() {
    clean();
}


void particle::clean() {

	if(glIsVertexArray(vao)) {
		glDeleteVertexArrays(1, &vao);
	}
	vao = 0;

	if(glIsBuffer(vertexbuffer)) {
		glDeleteBuffers(1, &vertexbuffer);
	}
	vertexbuffer = 0;

	if(glIsBuffer(indexbuffer)) {
		glDeleteBuffers(1, &indexbuffer);
	}
	indexbuffer = 0;

	if(vertexarray) {
		delete[] vertexarray;
	}
	if(indexarray) 	{
		delete[] indexarray;
	}
	nverts = 0;
	ntris = 0;
}



void particle::createParticle() {


    const GLfloat vertex_array_data[] = {
         //positions        //normals       //st coord      //color
         xPos, yPos, zPos, 0.0f, 0.0f, 1.0f , 0.5f,0.5f, xCol, yCol, zCol

     };
    const GLuint index_array_data[] = {
        0,0,0
    };

    //vertices and index
    nverts = 1;
    ntris = 1;


    vertexarray = new GLfloat[11*nverts];
    indexarray = new GLuint[3*ntris];

    //copy over everything
    for(int i=0; i<11*nverts; i++) {
        vertexarray[i]=vertex_array_data[i];
    }
    for(int i=0; i<3*ntris; i++) {
        indexarray[i]=index_array_data[i];
    }


	// Generate one vertex array object (VAO) and bind it
	glGenVertexArrays(1, &(vao));
	glBindVertexArray(vao);

	// Generate two buffer IDs
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &indexbuffer);
 	// Activate the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
 	// Present our vertex coordinates to OpenGL
	glBufferData(GL_ARRAY_BUFFER,
		11*nverts * sizeof(GLfloat), vertexarray, GL_STREAM_DRAW);
	// Specify how many attribute arrays we have in our VAO
	glEnableVertexAttribArray(0); // Vertex coordinates
	glEnableVertexAttribArray(1); // Normals
	glEnableVertexAttribArray(2); // Texture coordinates
	glEnableVertexAttribArray(3); // color coordinates
	// Specify how OpenGL should interpret the vertex buffer data:
	// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
	// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
	// Type GL_FLOAT
	// Not normalized (GL_FALSE)
	// Stride 8 floats (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3 or 6 floats (offset into first vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		11*sizeof(GLfloat), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		11*sizeof(GLfloat), (void*)(3*sizeof(GLfloat))); // normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		11*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
		11*sizeof(GLfloat), (void*)(9*sizeof(GLfloat))); // texcoords


 	// Activate the index buffer
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
 	// Present our vertex indices to OpenGL
 	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	 	3*ntris*sizeof(GLuint), indexarray, GL_STREAM_DRAW);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the index buffer while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void particle::render() {

	glBindVertexArray(vao);

	glPointSize(2.0f);
    glDrawElements(GL_POINTS, 3 * ntris, GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}

