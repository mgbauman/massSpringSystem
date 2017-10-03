#ifndef SPRING_H
#define SPRING_H

#include "Mass.h"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

class Spring {
public:
	float k;
	glm::vec3 equilibriumPos;
	glm::vec3 equilibriumPosA;

    Mass *a;
    Mass *b;
    float stiffness;
    float damping;

	float eqDistance;

	void updateMass1(glm::vec3 update);
	void updateMass2(glm::vec3 update);
	float getDistance();
	void updateEquilibriumPosition();
	
	Spring();
	Spring(Mass *initStart, Mass *initEnd);
	Spring(Mass *initStart, Mass *initEnd, glm::vec3 equilibrium);
	Spring(Mass *initStart, Mass *initEnd, float k, float d);
	
	~Spring();
};

#endif
