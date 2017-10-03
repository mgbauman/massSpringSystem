#include "Spring.h"
//#include "glm\glm.hpp"

using namespace glm;
using namespace std;
//Use the actual number for equilibrium distance when doing
//the calculation but always update the POINT to the center
Spring::Spring() {
	a = NULL;
	b = NULL;
	equilibriumPos = vec3(0,0,0);
	
	// Good for the mass on a spring
	// k = 0.5
	// damping = 0.25;
	
	// Good for the pendulum
	/* = 0.0015f;
	damping = 10.15;
	eqDistance = 5.f;*/
	
	/* Cube
	k = 7.5f;
	damping = 2.65;
	eqDistance = 10.f; 
	 7.5 or 2.5
	 */
	
	
	 //Good for cloth
	k = 5.45f;
	damping = 0.01;
	eqDistance = 10.f;
	
	/*
	//Good Cube
	k = 40.45f;
	damping = 0.01;
	eqDistance = 10.f;
	 */
	
	/*
	//Good for cloth
	k = 1.45f;
	damping = 0.01;
	eqDistance = 10.f;
	*/
}

Spring::Spring(Mass * initStart, Mass * initEnd) {
	a = initStart;
	b = initEnd;
	equilibriumPos = vec3(initStart->position.x, initStart->position.y - 3.f,initStart->position.z);
	
	// Good for the mass on a spring
	// k = 0.5
	// damping = 0.25;
	
	// Good for the pendulum
	/*k = 1.45f;
	damping = 0.85;
	eqDistance = 3.f;
*/

// Good for the pendulum
	k = 1.45f;
	damping = 0.05;
	eqDistance = 3.f;
}

Spring::Spring(Mass * initStart, Mass * initEnd, vec3 equilibrium) {
	a = initStart;
	b = initEnd;
	equilibriumPos = equilibrium;
	k = 0.1;
	damping = 0.5;
	eqDistance = 3.f;
}

Spring::Spring(Mass * initStart, Mass * initEnd, float k, float d) {
	a = initStart;
	b = initEnd;
	equilibriumPos = vec3(initStart->position.x, initStart->position.y - 3.f,initStart->position.z);
	this->k = k;
	damping = d;
	eqDistance = 3.f;
}
Spring::~Spring(){}

void Spring::updateMass1(vec3 update) {
	a->position = update;
}
void Spring::updateMass2(vec3 update) {
	b->position = update;
}

float Spring::getDistance() {
	return distance(a->position, b->position);
}

void Spring::updateEquilibriumPosition(){
	//cout <<"Equilibrium x: " << equilibriumPos.x<<"Equilibrium y: " <<equilibriumPos.y<<"Equilibrium z: " <<equilibriumPos.z<<endl; 
	vec3 unit = normalize(  b->position - a->position );
	equilibriumPos = a->position + unit * eqDistance;
	
	vec3 unitA = normalize(  a->position - b->position );
	
	equilibriumPosA = b->position + unitA * eqDistance;

	//equilibriumPos = a->position + unit * (getDistance()/2.f);
		
}
