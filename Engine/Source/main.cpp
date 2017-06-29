/**
 * Author: Pranav Srinivas Kumar 
 */

// User-defined Headers
#include "Managers\shader_manager.h"
#include "Core\models.h"

// External Headers
#include "glew.h"
#include "freeglut.h"

// System Headers
#include <iostream>

Managers::ShaderManager* shader_manager;
Models::ModelManager* model_manager;
GLuint program;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Use the created program
	glUseProgram(program);

	// Draw 3 vertices as triangles
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

	// Create Triangle Model 
	model_manager = new Models::ModelManager();
	model_manager->CreateTriangleModel("test_triangle");

	// Load and compile the shaders
	shader_manager = new Managers::ShaderManager();
	shader_manager->CreateProgram("color_shader", "Shaders\\vertex_shader.glsl", "Shaders\\fragment_shader.glsl");
	program = Managers::ShaderManager::GetShader("color_shader");
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
	delete model_manager;
	delete shader_manager;
	return 0;
}