#include "PhysicsEnvironment.hpp"

using namespace physics;

void Env::applyForces() {
	for (Element *e : elements) {
		vec3 curForce;
		for (forceFunc f : forces) curForce += f(e); // Add the force to the total
		vec3 acceleration = curForce / e->mass; // F = m*a --> a = F/m
		e->velocity += acceleration; // Update velocity
		e->position += e->velocity; // Update position
	}
}