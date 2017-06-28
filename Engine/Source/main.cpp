/**
 * Author: Pranav Srinivas Kumar 
 */

// User-defined Headers
#include "Core\shader_loader.h"
#include "Core\models.h"

// External Headers
#include "glew.h"
#include "freeglut.h"

// System Headers
#include <iostream>

Models::ModelManager* model_manager;
GLuint program;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 1.0, 1.0);

	//use the created program
	glUseProgram(program);

	//draw 3 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void closeCallback()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init()
{
	glEnable(GL_DEPTH_TEST);

	model_manager = new Models::ModelManager();
	model_manager->CreateTriangleModel("test_triangle");

	// Load and compile shaders from file
	Core::ShaderLoader shader_loader;
	program = shader_loader.CreateProgram("Shaders\\vertex_shader.glsl", "Shaders\\fragment_shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");
	glewInit();
	
	Init();

	// Register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);
	glutMainLoop();
	glDeleteProgram(program);
	return 0;
}