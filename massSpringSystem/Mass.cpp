#include "Mass.h"

using namespace glm;

Mass::Mass(){
	position = vec3(0,0,0);
	mass= 1.f;
	velocity = vec3(0,0,0);
	forces = vec3(0,0,0);
}

Mass::Mass(vec3 pos) {
    position = pos;
    mass = 1.f;
    velocity = vec3(0,0,0);
    forces = vec3(0,0,0);
}

Mass::Mass(vec3 pos, float mass) {
    position = pos;
    this->mass = mass;
    forces = vec3(0,0,0);
}


Mass::~Mass(){}

void Mass::setPos(glm::vec3 newPos) {
    position = newPos;
}
void Mass::resolveForce(float dt) {

}
