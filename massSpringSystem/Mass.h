#ifndef MASS_H
#define MASS_H


#include "glm/glm.hpp"
#include <cstdio>

class Mass {
public:
    glm::vec3 velocity;
    glm::vec3 position;
    
    glm::vec3 forces;
    
    float mass;
    float force;

    void setPos(glm::vec3 newPos);
    void resolveForce(float dt);

	Mass();
    Mass(glm::vec3 pos);
    Mass(glm::vec3 pos, float mass);

    ~Mass();
};

#endif
