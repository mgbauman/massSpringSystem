// ==========================================================================
// Barebones OpenGL Core Profile Boilerplate
//    using the GLFW windowing system (http://www.glfw.org)
//
// Loosely based on
//  - Chris Wellons' example (https://github.com/skeeto/opengl-demo) and
//  - Camilla Berglund's example (http://www.glfw.org/docs/latest/quick.html)
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cstdlib>

#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Spring.h"
#include "Mass.h"
// specify that we want the OpenGL core profile before including GLFW headers
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "camera.h"
#define PI 3.14159265359

using namespace std;
using namespace glm;

//Turn on to see the equilibrium position of the spring
bool DEBUG = false;

//Forward definitions
bool CheckGLErrors(string location);
void QueryGLVersion();
string LoadSource(const string &filename);
GLuint CompileShader(GLenum shaderType, const string &source);
GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader);

void createSpringArrayJelly(int sideLength);
void createJellyMasses(int sideLength);
void createClothMasses(int sideLength);

vec2 mousePos;
bool leftmousePressed = false;
bool rightmousePressed = false;

int mode = 0;
int index = 0;
int clothIndex = 0;
double damping = 0.05;
float deltaT = 0.08;
double g = 9.81;

double g20 = 9.81 * 20;
Camera* activeCamera;

float scaleFactor = 0.25f;
bool animate = true;

GLFWwindow* window = 0;

Camera cam = Camera(vec3(0, 0, -1), vec3(0, 0, 30));
mat4 winRatio = mat4(1.f);


//////////////////////////////////////////////////////////////////////
///////////////////// PART 1 MASSES AND SPRING  //////////////////////
//////////////////////////////////////////////////////////////////////
	vector<Mass*> massesp1;
	vector<Spring*> springsp1;

	Mass mass1p1 = Mass(vec3(0, 30.f, 0));
	Mass mass2p1 = Mass(vec3(0, 28.5f, 0));

	Spring springp1 = Spring(&mass1p1, &mass2p1, 0.5f, 0.25f);
//////////////////////////////////////////////////////////////////////
///////////////// END PART 1 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	

//////////////////////////////////////////////////////////////////////
///////////////////// PART 2 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	vector<Mass*> masses;
	vector<Spring*> springs;

	Mass mass1 = Mass(vec3(-10, 30.f, 0));
	Mass mass2 = Mass(vec3(0, 28.5f, 0));
	Mass mass3 = Mass(vec3(10, 28.5f, 0));
	Mass mass4 = Mass(vec3(20, 28.5f, 0));
	Mass mass5 = Mass(vec3(30, 28.5f, 0));

	Spring spring1 = Spring(&mass1, &mass2);
	Spring spring2 = Spring(&mass2, &mass3);
	Spring spring3 = Spring(&mass3, &mass4);
	Spring spring4 = Spring(&mass4, &mass5);
//////////////////////////////////////////////////////////////////////
///////////////// END PART 2 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
///////////////////// PART 3 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	vector<Mass*> massesJelly;
	vector<Spring*> springsJelly;
	
	Mass massJ1;Mass massJ2;Mass massJ3;Mass massJ4;
	Mass massJ5;Mass massJ6;Mass massJ7;Mass massJ8;
	Mass massJ9;Mass massJ10;Mass massJ11;Mass massJ12;
	Mass massJ13;Mass massJ14;Mass massJ15;Mass massJ16;
	Mass massJ17;Mass massJ18;Mass massJ19;Mass massJ20;
	Mass massJ21;Mass massJ22;Mass massJ23;Mass massJ24;
	Mass massJ25;Mass massJ26;Mass massJ27;
	
//////////////////////////////////////////////////////////////////////
///////////////// END PART 3 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////

	
	
//////////////////////////////////////////////////////////////////////
///////////////////// PART 4 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	vector<Mass*> massesCloth;
	vector<Spring*> springsCloth;
	
//////////////////////////////////////////////////////////////////////
///////////////// END PART 4 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////

	
	

// --------------------------------------------------------------------------
// GLFW callback functions

// reports GLFW errors
void ErrorCallback(int error, const char* description)
{
    cout << "GLFW ERROR " << error << ":" << endl;
    cout << description << endl;
}

// handles keyboard input events
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
        
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		animate = !animate;
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS){
		deltaT = 0.1;
		mode = 1;
		
		cam = Camera(vec3(0, 0, -1), vec3(0, 0, 10));
		scaleFactor = 0.25f;
		
		mass1p1.position = vec3(0, 30.f, 0);
		mass2p1.position = vec3(0, 28.5f, 0);
		
		mass1p1.velocity = vec3(0,0,0);
		mass2p1.velocity = vec3(0,0,0);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS){
		deltaT = 0.1;
		mode = 2;

		cam = Camera(vec3(0, 0, -1), vec3(0, 0, 30));
		scaleFactor = 0.25f;

		mass1.position = vec3(-10, 30.f,0);
		mass2.position = vec3(0, 28.5f, 0);
		mass3.position = vec3(10, 26.5f, 0);
		mass4.position = vec3(20, 24.5f, 0);
		mass5.position = vec3(30, 22.5f, 0);
		
		mass1.velocity = vec3(0,0,0);
		mass2.velocity = vec3(0,0,0);
		mass3.velocity = vec3(0,0,0);
		mass4.velocity = vec3(0,0,0);
		mass5.velocity = vec3(0,0,0);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS){
		mode = 3;
		
		createJellyMasses(10);
		deltaT = 0.05;
		//deltaT = 0.0001;
		
		cam = Camera(vec3(0, 0, -1), vec3(0, 0, 50));	
		
//		cam = Camera(vec3(0, 0, -1), vec3(0, 0, 10));	
		scaleFactor = 0.25f;
		
		for( Spring *s : springsJelly){
			s->updateEquilibriumPosition();
		}
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS){
		mode = 4;
		
		createClothMasses(15);
		deltaT = 0.08;
	
		cam = Camera(vec3(0, 0, -1), vec3(0, 0, 85));
		scaleFactor = 0.25f;
	
		for( Spring *s : springsCloth){
			s->updateEquilibriumPosition();
		}
	}
	/*
	if (key == GLFW_KEY_D && action == GLFW_PRESS){
		DEBUG = !DEBUG;
	}
	*/
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if( (action == GLFW_PRESS) || (action == GLFW_RELEASE) ){
		if(button == GLFW_MOUSE_BUTTON_LEFT)
			leftmousePressed = !leftmousePressed;
		else if(button == GLFW_MOUSE_BUTTON_RIGHT)
			rightmousePressed = !rightmousePressed;
	}
}

void mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);

	vec2 newPos = vec2(xpos/(double)vp[2], -ypos/(double)vp[3])*2.f - vec2(1.f);

	vec2 diff = newPos - mousePos;
	if(leftmousePressed){
		activeCamera->trackballRight(-diff.x);
		activeCamera->trackballUp(-diff.y);
	}
	else if(rightmousePressed){
		float zoomBase = (diff.y > 0) ? 1.f/2.f : 2.f;

		activeCamera->zoom(pow(zoomBase, abs(diff.y)));
	}

	mousePos = newPos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scaleFactor += yoffset*(scaleFactor / (5));
}

void resizeCallback(GLFWwindow* window, int width, int height)
{
	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);

	glViewport(0, 0, width, height);

	int min = min(width,height);

	float minDim = float(min);

	winRatio[0][0] = minDim/float(width);
	winRatio[1][1] = minDim/float(height);
}

//==========================================================================
// TUTORIAL STUFF


//vec2 and vec3 are part of the glm math library. 
//Include in your own project by putting the glm directory in your project, 
//and including glm/glm.hpp as I have at the top of the file.
//"using namespace glm;" will allow you to avoid writing everyting as glm::vec2

struct VertexBuffers{
	enum{ VERTICES=0, NORMALS, INDICES, COUNT};

	GLuint id[COUNT];
};

//Describe the setup of the Vertex Array Object
bool initVAO(GLuint vao, const VertexBuffers& vbo)
{
	glBindVertexArray(vao);		//Set the active Vertex Array

	glEnableVertexAttribArray(0);		//Tell opengl you're using layout attribute 0 (For shader input)
	glBindBuffer( GL_ARRAY_BUFFER, vbo.id[VertexBuffers::VERTICES] );		//Set the active Vertex Buffer
	glVertexAttribPointer(
		0,				//Attribute
		3,				//Size # Components
		GL_FLOAT,	//Type
		GL_FALSE, 	//Normalized?
		sizeof(vec3),	//Stride
		(void*)0			//Offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.id[VertexBuffers::NORMALS]);
	glVertexAttribPointer(
		1,				//Attribute
		3,				//Size # Components
		GL_FLOAT,	//Type
		GL_FALSE, 	//Normalized?
		sizeof(vec3),	//Stride
		(void*)0			//Offset
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.id[VertexBuffers::INDICES]);

	return !CheckGLErrors("initVAO");		//Check for errors in initialize
}


//Loads buffers with data
bool loadBuffer(const VertexBuffers& vbo, 
				const vector<vec3>& points, 
				const vector<vec3> normals, 
				const vector<unsigned int>& indices)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo.id[VertexBuffers::VERTICES]);
	glBufferData(
		GL_ARRAY_BUFFER,				//Which buffer you're loading too
		sizeof(vec3)*points.size(),		//Size of data in array (in bytes)
		&points[0],						//Start of array (&points[0] will give you pointer to start of vector)
		GL_STATIC_DRAW					//GL_DYNAMIC_DRAW if you're changing the data often
										//GL_STATIC_DRAW if you're changing seldomly
		);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.id[VertexBuffers::NORMALS]);
	glBufferData(
		GL_ARRAY_BUFFER,				//Which buffer you're loading too
		sizeof(vec3)*normals.size(),	//Size of data in array (in bytes)
		&normals[0],					//Start of array (&points[0] will give you pointer to start of vector)
		GL_STATIC_DRAW					//GL_DYNAMIC_DRAW if you're changing the data often
										//GL_STATIC_DRAW if you're changing seldomly
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.id[VertexBuffers::INDICES]);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int)*indices.size(),
		&indices[0],
		GL_STATIC_DRAW
		);

	return !CheckGLErrors("loadBuffer");	
}

//Compile and link shaders, storing the program ID in shader array
GLuint initShader(string vertexName, string fragmentName)
{	
	string vertexSource = LoadSource(vertexName);		//Put vertex file text into string
	string fragmentSource = LoadSource(fragmentName);		//Put fragment file text into string

	GLuint vertexID = CompileShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragmentID = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
	
	return LinkProgram(vertexID, fragmentID);	//Link and store program ID in shader array
}

//Initialization
void initGL()
{
	glEnable(GL_DEPTH_TEST);
	glPointSize(15);
	glDepthFunc(GL_LEQUAL);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(0.f, 0.f, 0.f, 0.f);		//Color to clear the screen with (R, G, B, Alpha)
}

bool loadUniforms(GLuint program, mat4 perspective, mat4 modelview)
{
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "modelviewMatrix"),
						1,
						false,
						&modelview[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(program, "perspectiveMatrix"),
						1,
						false,
						&perspective[0][0]);

	return !CheckGLErrors("loadUniforms");
}

//Draws buffers to screen
void render(GLuint vao, int startElement, int numElements)
{
	glBindVertexArray(vao);		//Use the LINES vertex array

	glDrawElements(
			GL_TRIANGLES,		//What shape we're drawing	- GL_TRIANGLES, GL_LINES, GL_POINTS, GL_QUADS, GL_TRIANGLE_STRIP
			numElements,		//How many indices
			GL_UNSIGNED_INT,	//Type
			(void*)0			//Offset
			);

	//DO NOT FORGET TO UNBIND!
	glBindVertexArray(0);
	CheckGLErrors("render");
}

//Draws buffers to screen
void renderPoints(GLuint vao, int startElement, int numElements)
{
	glBindVertexArray(vao);
	
	glDrawElements(
			GL_POINTS,		//What shape we're drawing	- GL_TRIANGLES, GL_LINES, GL_POINTS, GL_QUADS, GL_TRIANGLE_STRIP
			numElements,		//How many indices
			GL_UNSIGNED_INT,	//Type
			(void*)0			//Offset
			);
	
	//DO NOT FORGET TO UNBIND!
	glBindVertexArray(0);
	CheckGLErrors("renderPoints");
}

//Draws buffers to screen
void renderLines(GLuint vao, int startElement, int numElements)
{
	glBindVertexArray(vao);

	glDrawElements(
			GL_LINE_STRIP,		//What shape we're drawing	- GL_TRIANGLES, GL_LINES, GL_POINTS, GL_QUADS, GL_TRIANGLE_STRIP
			numElements,		//How many indices
			GL_UNSIGNED_INT,	//Type
			(void*)0			//Offset
			);

	//DO NOT FORGET TO UNBIND!
	glBindVertexArray(0);
	CheckGLErrors("renderLines");
}



//Draws buffers to screen
void renderLineStrip(GLuint vao, int startElement, int numElements)
{
	glBindVertexArray(vao);

	glDrawElements(
			GL_LINES,		//What shape we're drawing	- GL_TRIANGLES, GL_LINES, GL_POINTS, GL_QUADS, GL_TRIANGLE_STRIP
			numElements,		//How many indices
			GL_UNSIGNED_INT,	//Type
			(void*)0			//Offset
			);

	//DO NOT FORGET TO UNBIND!
	glBindVertexArray(0);
	CheckGLErrors("renderLines");
}

void generateSquare(vector<vec3>& vertices, vector<vec3>& normals, 
					vector<unsigned int>& indices, float width)
{
	vertices.push_back(vec3(-width*0.5f, -22.f, -width*0.5f));
	vertices.push_back(vec3(width*0.5f, -22.f, -width*0.5f));
	vertices.push_back(vec3(width*0.5f, -22.f, width*0.5f));
	vertices.push_back(vec3(-width*0.5f, -22.f, width*0.5f));

	normals.push_back(vec3(0.8f, 0.8f, 0.8f));
	normals.push_back(vec3(0.8f, 0.8f, 0.8f));
	normals.push_back(vec3(0.8f, 0.8f, 0.8f));
	normals.push_back(vec3(0.8f, 0.8f, 0.8f));
	
	//First triangle
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	//Second triangle
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);
}

GLFWwindow* createGLFWWindow()
{
	// initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
        return NULL;
    }
    glfwSetErrorCallback(ErrorCallback);

    // attempt to create a window with an OpenGL 4.1 core profile context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(512, 512, "Assignment 3", 0, 0);
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return NULL;
    }

    // set keyboard callback function and make our context current (active)
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mousePosCallback);
    glfwSetWindowSizeCallback(window, resizeCallback);
	glfwSetScrollCallback(window, scroll_callback);
    glfwMakeContextCurrent(window);

    return window;
}

void generateBox(vector<vec3>* vertices, vector<vec3>* normals, vector<unsigned int>* indices, float sideLength){
	vec3 nxnyz = vec3(-sideLength, 0, sideLength);
	vec3 nxnynz = vec3(-sideLength, 0, -sideLength);
	vec3 nxynz = vec3(-sideLength, sideLength, -sideLength);
	vec3 nxyz = vec3(-sideLength, sideLength, sideLength);
	
	vec3 xnyz = vec3(sideLength, 0, sideLength);
	vec3 xnynz = vec3(sideLength, 0, -sideLength);
	vec3 xynz = vec3(sideLength, sideLength, -sideLength);
	vec3 xyz = vec3(sideLength, sideLength, sideLength);
	
	vertices->push_back(nxnyz); 
	vertices->push_back(nxnynz);
	vertices->push_back(nxynz);
	vertices->push_back(nxyz);
	
	vertices->push_back(xnyz);
	vertices->push_back(xnynz);
	vertices->push_back(xynz);
	vertices->push_back(xyz);
	
	
	
	for( int i =0; i<1; i++){
		normals->push_back(vec3(1.f,1.f,0.f));
	}
	for( int i =0; i<2; i++){
		normals->push_back(vec3(0,0,1));
	}
	for( int i =0; i<2; i++){
		normals->push_back(vec3(1.f,1.f,0.f));
	}
	for( int i =0; i<2; i++){
		normals->push_back(vec3(0,0,1));
	}
	for( int i =0; i<1; i++){
		normals->push_back(vec3(1.f,1.f,0.f));
	}
	
	//TOP
	indices->push_back(3);indices->push_back(2);indices->push_back(6);
	indices->push_back(6);indices->push_back(7);indices->push_back(3);
	
	//RIGHT
	indices->push_back(5);indices->push_back(6);indices->push_back(7);
	indices->push_back(4);indices->push_back(5);indices->push_back(7);
	
	//BACK
	indices->push_back(1);indices->push_back(2);indices->push_back(6);
	indices->push_back(1);indices->push_back(5);indices->push_back(6);

	//LEFT
	indices->push_back(1);indices->push_back(2);indices->push_back(3);
	indices->push_back(0);indices->push_back(1);indices->push_back(3);

	//FRONT
	indices->push_back(0);indices->push_back(4);indices->push_back(7);
	indices->push_back(0);indices->push_back(7);indices->push_back(3);

	//BOTTOM
	indices->push_back(0);indices->push_back(1);indices->push_back(5);
	indices->push_back(0);indices->push_back(5);indices->push_back(4);
}

float magnitude(vec3 v){
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

// Play with gravity here to make the movement appear more correct
void updateVelocity(vec3 currentPosition, float &v, vec3 maxHeight){
	float h = currentPosition.y;
	float H = maxHeight.y;
	
	v = sqrt( 2 * g * (H-h));
}

float getVelocity(vec3 currentPosition, vec3 maxHeight){
	float h = currentPosition.y;
	float H = maxHeight.y;
	
	return sqrt( 2 * g * (H-h));
}

/**
 * k - Spring Coefficient
 * x - Displacement
 * xo - equilibrium displacement
 */
vec3 calculateSpringForce(float k, vec3 x, vec3 xo) {
	return -k*( x - xo);
}

/**
* b- damping coefficient/constant
*/
vec3 calculateDampingForce(vec3 velocity, float b) {
	return -b*velocity;
}

vec3 calculateTotalForce( vec3 fS, vec3 fD) {
	return fS + fD;
}

vec3 calculateNewVelocity(vec3 initialVelocity, vec3 acceleration){
	return initialVelocity + acceleration * deltaT;
}

vec3 calculateNewPosition(vec3 initialPosition, vec3 velocity){
	return initialPosition + velocity * deltaT;
}

void loadMasses(vector<vec3>& vertices, vector<vec3>& normals, vector<unsigned int>& indices, vector<Mass*>& masses) {
	vertices.clear();
	normals.clear();
	indices.clear();
	for (int i = 0; i < int(masses.size()); i++) {
		vertices.push_back(masses[i]->position);
		normals.push_back(vec3(1, 1, 0));
		indices.push_back(i);
	}	
}


void loadSprings(vector<vec3>& vertices, vector<vec3>& normals, vector<unsigned int>& indices, vector<Spring*>& springs) {
	vertices.clear();
	normals.clear();
	indices.clear();
	int pointIndex = 1;
	
	for (int i = 0; i < int(springs.size()); i++) {
		vertices.push_back(springs[i]->a->position);
		vertices.push_back(springs[i]->b->position);
		
		normals.push_back(vec3(1, 1, 0));
		normals.push_back(vec3(1, 1, 0));
		
		indices.push_back(pointIndex-1);
		indices.push_back(pointIndex);
		
		pointIndex+=2;
	}	
}

// Start with just passing this function 7 for a side length
// That will create 49 masses
void createClothMasses(int sideLength){
	for( int i = 0; i < sideLength; i ++){
		for( int j = 0; j < sideLength; j ++){
			massesCloth[(sideLength*i)+j]->position =  vec3(float(-50  + 10.f*j),50.f- i, float(0.f - 10.f*i));
			massesCloth[(sideLength*i)+j]->mass = 1;
			massesCloth[(sideLength*i)+j]->velocity = vec3(0,0,0);
		}
	}
}

// 2*((sideLength-1)^2) + (sideLength * (sideLength -1)) +  (sideLength * (sideLength -1))
void intitializeSpringClothVector(int sideLength){
	int until = 2*((sideLength-1) * (sideLength -1)) + (sideLength * (sideLength -1)) +  (sideLength * (sideLength -1));
	for(int i = 0; i < until; i++){
		springsCloth.push_back(new Spring());
	}
}

void intitializeMassClothVector(int sideLength){
	for(int i = 0; i < (sideLength * sideLength); i++){
		massesCloth.push_back(new Mass());
	}
}

void createSpringArrayCloth(int sideLength){
	for( int i = 0; i < sideLength; i ++){
		for( int j = 0; j < sideLength; j ++){
			if ( i != sideLength-1) { 
				springsCloth[clothIndex]->a = massesCloth[(sideLength*i)+(j)];
				springsCloth[clothIndex]->b = massesCloth[(sideLength*i)+(j)+sideLength];

				springsCloth[clothIndex]->eqDistance = springsCloth[clothIndex]->getDistance();
				clothIndex++;
			}
			if ( (i != sideLength-1) && (j != sideLength-1)) { 
				springsCloth[clothIndex]->a = massesCloth[(sideLength*i)+(j)];
				springsCloth[clothIndex]->b = massesCloth[(sideLength*i)+(j)+sideLength+1];
				
				springsCloth[clothIndex]->eqDistance = springsCloth[clothIndex]->getDistance();
				clothIndex++;
			}
			if ( (i != sideLength-1) && (j != 0)) { 
				springsCloth[clothIndex]->a = massesCloth[(sideLength*i)+(j)];
				springsCloth[clothIndex]->b = massesCloth[(sideLength*i)+(j)+sideLength-1];
			
				springsCloth[clothIndex]->eqDistance = springsCloth[clothIndex]->getDistance();
				clothIndex++;
			}
			if ( j!= sideLength-1) {
				springsCloth[clothIndex]->a = massesCloth[(sideLength*i)+(j)];
				springsCloth[clothIndex]->b = massesCloth[(sideLength*i)+(j)+1];
			
				springsCloth[clothIndex]->eqDistance = springsCloth[clothIndex]->getDistance();
				clothIndex++;
			}
		}
	}
}



void intitializeMassJellyVector(int sideLength){
	for(int i = 0; i < (sideLength * sideLength * sideLength); i++){
		massesJelly.push_back(new Mass());
	}
}
// Start with just passing this function 3 for a side length
// That will create 27 masses
void createJellyMasses(int sideLength){
	int s2 = sideLength * sideLength;
	
	for( int i = 0; i < sideLength; i ++){
		for( int j = 0; j < sideLength; j ++){
			for( int k = 0; k < sideLength; k ++){
				massesJelly[(s2*i) + (sideLength*j) + (k)]->position =  vec3(float(k-1) *10.f, float(j-1)*10.f, float(i-1)*10.f);
				massesJelly[(s2*i) + (sideLength*j) + (k)]->mass = 1;
				massesJelly[(s2*i) + (sideLength*j) + (k)]->velocity = vec3(0.f);
				
			}
		}
	}
}
//148
//74 
//74 * 2 -10
//86 for 3 
//252 for 4 
//1040 for 6
void intitializeSpringJellyVector(){
	for(int i = 0; i < ((8856)); i++){
		springsJelly.push_back(new Spring());
		springsJelly[i]->k = 60.45f;
		springsJelly[i]->damping = 0.01;
	}
}

void createSpringArrayJelly(int sideLength){
	int s2 = sideLength * sideLength;
	
	for( int i = 0; i < sideLength; i ++){
		for( int j = 0; j < sideLength; j ++){
			for( int k = 0; k < sideLength; k ++){
					
				// Add edge spring connections	
				if (k!=sideLength-1){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2 *i) + (sideLength*j) + (k) + 1];
					
					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				}
				
				if (j!=sideLength-1){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + sideLength];
					
					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				}
				
				if (i!=sideLength-1){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + s2];
					
					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;	
				}
				
				if ( (i!=(sideLength-1)) && ( j != (sideLength - 1)) && ( k != (sideLength -1)) ){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + (s2) + sideLength + 1];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				} 
				
				if ( (i!=(sideLength-1)) && ( j != (sideLength - 1)) && ( k != 0) ){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + (s2) + sideLength - 1];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				} 
				
				if ( (i!=(sideLength-1)) && ( j != 0) && ( k != (sideLength -1)) ){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + (s2) - sideLength + 1];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				} 
				
				
				if ( (i!=(sideLength-1)) && ( j != (0)) && ( k != 0) ){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + (s2) - sideLength - 1];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				} 
				
				if ( (i!=(sideLength-1)) && ( j != 0) ) {
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + (s2) - sideLength];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				} 
				
				
				if ( (i!=(sideLength-1)) && ( j != (sideLength-1)) ){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + (s2) + sideLength];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				} 
				
				
				if ( (i!=(sideLength-1)) && ( k != (sideLength -1)) ){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + (s2) + 1];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				} 
				
				if ( (i!=(sideLength-1)) && ( k != 0) ){
					springsJelly[index]->a = massesJelly[(s2*i) + (sideLength*j) + (k)];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k) + (s2) - 1];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				} 
				
				
				/* 
				// Add center spring connections	
				if (  ( (i != 1) && (j != 1) ) || ( (j!= 1) && (k != 1) ) || ( (i !=1) && ( k != 1) )  ){
					springsJelly[index]->a = massesJelly[13];
					springsJelly[index]->b = massesJelly[(s2*i) + (sideLength*j) + (k)];

					springsJelly[index]->eqDistance = springsJelly[index]->getDistance();
					index++;
				}
				*/ 
			}
		}
	}
}

// ==========================================================================
// PROGRAM ENTRY POINT

int main(int argc, char *argv[])
{   
    window = createGLFWWindow();
    if(window == NULL)
    	return -1;

    //Initialize glad
    if (!gladLoadGL())
	{
		cout << "GLAD init failed" << endl;
		return -1;
	}

    // query and print out information about our OpenGL environment
    QueryGLVersion();

	initGL();

	//Initialize shader
	GLuint program = initShader("vertex.glsl", "fragment.glsl");
	GLuint vao, vaoEQ, vaoSquare;
	VertexBuffers vbo, vboEQ, vboSquare;

	//Generate object ids
	glGenVertexArrays(1, &vao);
	glGenBuffers(VertexBuffers::COUNT, vbo.id);

	initVAO(vao, vbo);
	
	glGenVertexArrays(1, &vaoEQ);
	glGenBuffers(VertexBuffers::COUNT, vboEQ.id);

	initVAO(vaoEQ, vboEQ);
	
	//Generate object ids
	glGenVertexArrays(1, &vaoSquare);
	glGenBuffers(VertexBuffers::COUNT, vboSquare.id);

	initVAO(vaoSquare, vboSquare);

	//Geometry information
	vector<vec3> points, normals;
	vector<unsigned int> indices;
	//Geometry information
	vector<vec3> pointsEQ, normalsEQ;
	vector<unsigned int> indicesEQ;
	
	vector<vec3> pointsSquare, normalsSquare;
	vector<unsigned int> indicesSquare;

	generateSquare(pointsSquare, normalsSquare, indicesSquare, 200.f);

	loadBuffer(vboSquare, pointsSquare, normalsSquare, indicesSquare);
//////////////////////////////////////////////////////////////////////
///////////////////// PART 1 MASSES AND SPRING  //////////////////////
//////////////////////////////////////////////////////////////////////
	massesp1.push_back(&mass1p1);
	massesp1.push_back(&mass2p1);
	
	springsp1.push_back(&springp1);
//////////////////////////////////////////////////////////////////////
///////////////// END PART 1 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	

//////////////////////////////////////////////////////////////////////
///////////////////// PART 2 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	masses.push_back(&mass1);
	masses.push_back(&mass2);
	masses.push_back(&mass3);
	masses.push_back(&mass4);
	masses.push_back(&mass5);
	
	springs.push_back(&spring1);
	springs.push_back(&spring2);
	springs.push_back(&spring3);
	springs.push_back(&spring4);
//////////////////////////////////////////////////////////////////////
///////////////// END PART 2 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	
	
	
//////////////////////////////////////////////////////////////////////
///////////////////// PART 3 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	
	massesJelly.push_back(&massJ1);massesJelly.push_back(&massJ2);massesJelly.push_back(&massJ3);
	massesJelly.push_back(&massJ4);massesJelly.push_back(&massJ5);massesJelly.push_back(&massJ6);
	massesJelly.push_back(&massJ7);massesJelly.push_back(&massJ8);massesJelly.push_back(&massJ9);
	
	
	massesJelly.push_back(&massJ10);massesJelly.push_back(&massJ11);massesJelly.push_back(&massJ12);
	massesJelly.push_back(&massJ13);massesJelly.push_back(&massJ14);massesJelly.push_back(&massJ15);
	massesJelly.push_back(&massJ16);massesJelly.push_back(&massJ17);massesJelly.push_back(&massJ18);
	
	
	massesJelly.push_back(&massJ19);massesJelly.push_back(&massJ20);massesJelly.push_back(&massJ21);
	massesJelly.push_back(&massJ22);massesJelly.push_back(&massJ23);massesJelly.push_back(&massJ24);
	massesJelly.push_back(&massJ25);massesJelly.push_back(&massJ26);massesJelly.push_back(&massJ27);
	
	massesJelly.clear();
	intitializeMassJellyVector(10);
	createJellyMasses(10);
	intitializeSpringJellyVector();
	createSpringArrayJelly(10);
	for( Spring *s : springsJelly){
		s->updateEquilibriumPosition();
	}
	
			 
//////////////////////////////////////////////////////////////////////
///////////////// END PART 3 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////


		
//////////////////////////////////////////////////////////////////////
///////////////////// PART 4 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	intitializeMassClothVector(15);
	createClothMasses(15);
	intitializeSpringClothVector(15);
	createSpringArrayCloth(15);
	for( Spring *s : springsCloth){
		s->updateEquilibriumPosition();
	}
	
//////////////////////////////////////////////////////////////////////
///////////////// END PART 4 MASSES AND SPRINGS //////////////////////
//////////////////////////////////////////////////////////////////////
	
	
	//Camera cam = Camera(vec3(0, 0, -1), vec3(0, 0, 10));
	mat4 model = mat4(1.f);
	activeCamera = &cam;
	
	//float fovy, float aspect, float zNear, float zFar
	mat4 perspectiveMatrix = perspective(radians(80.f), 1.f, 0.1f, 200.f);
    
    // run an event-triggered main loop
    while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//Clear color and depth buffers (Haven't covered yet)
		
		// If mode is 1 then do the basic mass on spring
		if (mode == 1){	
			//Update equilibrium position of each spring
			//spring1.updateEquilibriumPosition();
			int i = 0;
			for( Spring *s : springsp1){
				s->updateEquilibriumPosition();
				// Calculate force for each spring
				vec3 totalForce = calculateTotalForce(calculateSpringForce(s->k, s->b->position, s->equilibriumPos), calculateDampingForce(s->b->velocity, s->damping));		
				
				//Add gravity to the total force, divide by mass to make acceleration
				vec3 acceleration = (totalForce+ (vec3(0,-g,0)*float((massesp1.size()-1)-i)))/float((massesp1.size()-1)-i);
				vec3 newVelocity = calculateNewVelocity(s->b->velocity, acceleration);
				vec3 newPosition = calculateNewPosition(s->b->position, newVelocity);
			
				s->b->velocity = newVelocity;
				s->b->setPos(newPosition);
				i++;
			}
			loadMasses(points, normals, indices, massesp1);
			loadUniforms(program, winRatio*perspectiveMatrix*cam.getMatrix(), scale(model, vec3(scaleFactor)));
			
			loadBuffer(vbo, points, normals, indices);
			renderPoints(vao, 0, indices.size());
			renderLines(vao, 0, indices.size());
			
			// Displays the equilibrium position of gthe first spring in red
			if (DEBUG == true){
				pointsEQ.clear();
				normalsEQ.clear();
				indicesEQ.clear();
				unsigned int i = 0;
				
				for ( Spring *s : springsp1) {
					pointsEQ.push_back(s->equilibriumPos);
					normalsEQ.push_back(vec3(1,0,0));
					indicesEQ.push_back(i);
					i++;
				}
				loadBuffer(vboEQ, pointsEQ, normalsEQ, indicesEQ);
				renderPoints(vaoEQ, 0, indicesEQ.size());
			}
		}
		
		// If mode is 2 then do the pendulum version
		if (mode == 2){	
			 //Update equilibrium position of each spring
			for( Spring *s : springs){
				// Calculate force for each spring
				vec3 totalForce = calculateTotalForce(calculateSpringForce(s->k, s->b->position, s->equilibriumPos), calculateDampingForce(s->b->velocity, s->damping));
			
				s->b->forces += totalForce;
			
				totalForce = calculateTotalForce(calculateSpringForce(s->k, s->a->position, s->equilibriumPosA), calculateDampingForce(s->a->velocity, s->damping));
			
				s->a->forces += totalForce;	
			}
			 
			 for( Mass * m : masses){
				 if ( (m != masses[0] )){
					 // potentially multiply gravity by mass before you add it to total force
					m->forces += (vec3(0,-g, 0)*(m->mass));
					//Add gravity to the total force, divide by mass to make acceleration
					vec3 acceleration = (m->forces)/ (m->mass);
					vec3 newVelocity = calculateNewVelocity(m->velocity, acceleration);
					vec3 newPosition = calculateNewPosition(m->position, newVelocity);
			
					m->velocity = newVelocity;
					m->setPos(newPosition);
				}
			}
			  
			for( Spring *s : springs){
				s->updateEquilibriumPosition();
				s->a->forces  = vec3(0,0,0);	
				s->b->forces  = vec3(0,0,0);	
				
			}
			
			loadMasses(points, normals, indices, masses);
			loadUniforms(program, winRatio*perspectiveMatrix*cam.getMatrix(), scale(model, vec3(scaleFactor)));
			
			loadBuffer(vbo, points, normals, indices);
			renderPoints(vao, 0, indices.size());
			renderLines(vao, 0, indices.size());
			
			// Displays the equilibrium position of gthe first spring in red
			if (DEBUG == true){
				pointsEQ.clear();
				normalsEQ.clear();
				indicesEQ.clear();
				unsigned int i = 0;
				
				for ( Spring *s : springs) {
					pointsEQ.push_back(s->equilibriumPos);
					normalsEQ.push_back(vec3(1,0,0));
					indicesEQ.push_back(i);
					i++;
				}
				loadBuffer(vboEQ, pointsEQ, normalsEQ, indicesEQ);
				renderPoints(vaoEQ, 0, indicesEQ.size());
			}
		}
		
		// If mode is 3 then do the jelly cube version
		if (mode == 3){	
			 //Update equilibrium position of each spring
			for( Spring *s : springsJelly){
				// Calculate force for each spring
				vec3 totalForce = calculateTotalForce(calculateSpringForce(s->k, s->b->position, s->equilibriumPos), calculateDampingForce(s->b->velocity, s->damping));
				
				s->b->forces += totalForce;
				
				totalForce = calculateTotalForce(calculateSpringForce(s->k, s->a->position, s->equilibriumPosA), calculateDampingForce(s->a->velocity, s->damping));
				
				s->a->forces += totalForce;		
			}
			 
			  
			 for( Mass * m : massesJelly){
				if (m->position.y < -20) {
					m->position.y = -20;
				}
			 }
			  
			 
			 for( Mass * m : massesJelly){
				m->forces += (vec3(0,-g, 0)*(m->mass));
				
				vec3 acceleration = (m->forces)/ (m->mass);
				vec3 newVelocity = calculateNewVelocity(m->velocity, acceleration);
				vec3 newPosition = calculateNewPosition(m->position, newVelocity);
			
				m->velocity = newVelocity;
				m->setPos(newPosition);
			 }
			
			for( Spring *s : springsJelly){
				s->updateEquilibriumPosition();
				s->a->forces  = vec3(0,0,0);	
				s->b->forces  = vec3(0,0,0);	
				
			}
			
			loadMasses(points, normals, indices, massesJelly);
			loadUniforms(program, winRatio*perspectiveMatrix*cam.getMatrix(), scale(model, vec3(scaleFactor)));
			loadBuffer(vbo, points, normals, indices);
			//renderPoints(vao, 0, indices.size());
			
			loadSprings(points, normals, indices, springsJelly);
			loadUniforms(program, winRatio*perspectiveMatrix*cam.getMatrix(), scale(model, vec3(scaleFactor)));
			loadBuffer(vbo, points, normals, indices);
			renderLineStrip(vao, 0, indices.size());
	
	
			// Displays the equilibrium position of gthe first spring in red
			if (DEBUG == true){
				pointsEQ.clear();
				normalsEQ.clear();
				indicesEQ.clear();
				unsigned int i = 0;
				
				for ( Spring *s : springsJelly) {
					pointsEQ.push_back(s->equilibriumPos);
					if( i%2){
						normalsEQ.push_back(vec3(0,1,0));
					} else {
						normalsEQ.push_back(vec3(1,0,0));
					}
					indicesEQ.push_back(i);
					i++;
				}
				loadBuffer(vboEQ, pointsEQ, normalsEQ, indicesEQ);
				renderPoints(vaoEQ, 0, indicesEQ.size());
			}
			
		}
		
		
		
		// If mode is 4 then do the hagning cloth version
		if (mode == 4){
			 //Update equilibrium position of each spring
			int i =0; 
			for( Spring *s : springsCloth){
				if ( (i != 0) || (i != 6) ){
					// Calculate force for each spring
					vec3 totalForce = calculateTotalForce(calculateSpringForce(s->k, s->b->position, s->equilibriumPos), calculateDampingForce(s->b->velocity, s->damping));
				
					s->b->forces += totalForce;
				
					totalForce = calculateTotalForce(calculateSpringForce(s->k, s->a->position, s->equilibriumPosA), calculateDampingForce(s->a->velocity, s->damping));
				
					s->a->forces += totalForce;	
				}	
				i++;
			}
			 
			 i =0; 
			 for( Mass * m : massesCloth){
				 if ( (m != massesCloth[0] )){if ( (m != massesCloth[2] )){ if ( (m != massesCloth[4] )){
					if ( (m != massesCloth[6] )){if ( (m != massesCloth[8] )){if ( (m != massesCloth[10] )){
						if ( (m != massesCloth[12] )){ if ( (m != massesCloth[14] )){
						m->forces += (vec3(0,-g, 0)*(m->mass));
						
						//Add gravity to the total force, divide by mass to make acceleration
						vec3 acceleration = (m->forces)/ (m->mass);
						vec3 newVelocity = calculateNewVelocity(m->velocity, acceleration);
						vec3 newPosition = calculateNewPosition(m->position, newVelocity);
				
						m->velocity = newVelocity;
						m->setPos(newPosition);
			}}}}}}}}}
			  
			for( Spring *s : springsCloth){
				s->updateEquilibriumPosition();
				s->a->forces  = vec3(0,0,0);	
				s->b->forces  = vec3(0,0,0);	
				
			}
			
			loadMasses(points, normals, indices, massesCloth);
			loadUniforms(program, winRatio*perspectiveMatrix*cam.getMatrix(), scale(model, vec3(scaleFactor)));
			loadBuffer(vbo, points, normals, indices);
			//renderPoints(vao, 0, indices.size());
			
			loadSprings(points, normals, indices, springsCloth);
			loadUniforms(program, winRatio*perspectiveMatrix*cam.getMatrix(), scale(model, vec3(scaleFactor)));
			loadBuffer(vbo, points, normals, indices);
			renderLineStrip(vao, 0, indices.size());
	
			// Displays the equilibrium position of gthe first spring in red
			if (DEBUG == true){
				pointsEQ.clear();
				normalsEQ.clear();
				indicesEQ.clear();
				unsigned int i = 0;
				
				for ( Spring *s : springsCloth) {
					pointsEQ.push_back(s->equilibriumPos);
					if( i%2){
						normalsEQ.push_back(vec3(0,1,0));
					} else {
						normalsEQ.push_back(vec3(1,0,0));
					}
					indicesEQ.push_back(i);
					i++;
				}
				loadBuffer(vboEQ, pointsEQ, normalsEQ, indicesEQ);
				renderPoints(vaoEQ, 0, indicesEQ.size());
			}
			
		}
		
        // scene is rendered to the back buffer, so swap to front for display
        glfwSwapBuffers(window);

        // sleep until next event before drawing again
        glfwPollEvents();
	}

	// clean up allocated resources before exit
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(VertexBuffers::COUNT, vbo.id);
	glDeleteBuffers(VertexBuffers::COUNT, vboEQ.id);
	glDeleteProgram(program);


	glfwDestroyWindow(window);
	glfwTerminate();

   return 0;
}

// ==========================================================================
// SUPPORT FUNCTION DEFINITIONS

// --------------------------------------------------------------------------
// OpenGL utility functions

void QueryGLVersion()
{
    // query opengl version and renderer information
    string version  = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    string glslver  = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

    cout << "OpenGL [ " << version << " ] "
         << "with GLSL [ " << glslver << " ] "
         << "on renderer [ " << renderer << " ]" << endl;
}

bool CheckGLErrors(string location)
{
    bool error = false;
    for (GLenum flag = glGetError(); flag != GL_NO_ERROR; flag = glGetError())
    {
        cout << "OpenGL ERROR:  ";
        switch (flag) {
        case GL_INVALID_ENUM:
            cout << location << ": " << "GL_INVALID_ENUM" << endl; break;
        case GL_INVALID_VALUE:
            cout << location << ": " << "GL_INVALID_VALUE" << endl; break;
        case GL_INVALID_OPERATION:
            cout << location << ": " << "GL_INVALID_OPERATION" << endl; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            cout << location << ": " << "GL_INVALID_FRAMEBUFFER_OPERATION" << endl; break;
        case GL_OUT_OF_MEMORY:
            cout << location << ": " << "GL_OUT_OF_MEMORY" << endl; break;
        default:
            cout << "[unknown error code]" << endl;
        }
        error = true;
    }
    return error;
}

// --------------------------------------------------------------------------
// OpenGL shader support functions

// reads a text file with the given name into a string
string LoadSource(const string &filename)
{
    string source;

    ifstream input(filename.c_str());
    if (input) {
        copy(istreambuf_iterator<char>(input),
             istreambuf_iterator<char>(),
             back_inserter(source));
        input.close();
    }
    else {
        cout << "ERROR: Could not load shader source from file "
             << filename << endl;
    }

    return source;
}

// creates and returns a shader object compiled from the given source
GLuint CompileShader(GLenum shaderType, const string &source)
{
    // allocate shader object name
    GLuint shaderObject = glCreateShader(shaderType);

    // try compiling the source as a shader of the given type
    const GLchar *source_ptr = source.c_str();
    glShaderSource(shaderObject, 1, &source_ptr, 0);
    glCompileShader(shaderObject);

    // retrieve compile status
    GLint status;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
        string info(length, ' ');
        glGetShaderInfoLog(shaderObject, info.length(), &length, &info[0]);
        cout << "ERROR compiling shader:" << endl << endl;
        cout << source << endl;
        cout << info << endl;
    }

    return shaderObject;
}

// creates and returns a program object linked from vertex and fragment shaders
GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    // allocate program object name
    GLuint programObject = glCreateProgram();

    // attach provided shader objects to this program
    if (vertexShader)   glAttachShader(programObject, vertexShader);
    if (fragmentShader) glAttachShader(programObject, fragmentShader);

    // try linking the program with given attachments
    glLinkProgram(programObject);

    // retrieve link status
    GLint status;
    glGetProgramiv(programObject, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &length);
        string info(length, ' ');
        glGetProgramInfoLog(programObject, info.length(), &length, &info[0]);
        cout << "ERROR linking shader program:" << endl;
        cout << info << endl;
    }

    return programObject;
}

// ==========================================================================
