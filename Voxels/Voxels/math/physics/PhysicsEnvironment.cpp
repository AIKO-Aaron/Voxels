#include "PhysicsEnvironment.hpp"

#define COMPARE(a, b) (d1.a + d1.b >= d2.a && d1.a <= d2.a + d2.b)
#define HIT_v1(m1, m2, v1, v2) ((v1) * (m1) + (v2) * (m2) + ((v2) - (v1)) * (m2)) / ((m1) + (m2))
#define HIT_v2(m1, m2, v1, v2) ((v1) * (m1) + (v2) * (m2) - ((v2) - (v1)) * (m1)) / ((m1) + (m2))

using namespace physics;

void Env::applyForces() {
	for (Element *e : elements) {
		vec3 curForce;
		for (forceFunc f : forces) curForce += f(e); // Add the force to the total
		vec3 acceleration = curForce / e->mass; // F = m*a --> a = F/m
		e->velocity += acceleration; // Update velocity
	}
	for (int i = 0; i < (int)elements.size(); i++) {
		Element *e = elements[i];
		for (int j = i + 1; j < (int)elements.size(); j++) {
			if (intersect(e, elements[j])) {
				vec3 v1 = HIT_v1(elements[j]->mass, e->mass, elements[j]->velocity, e->velocity);
				vec3 v2 = HIT_v2(elements[j]->mass, e->mass, elements[j]->velocity, e->velocity);

				e->velocity = v1.mult(createVec(1, -1, 1));
				elements[j]->velocity = v2.mult(createVec(1, -1, 1));

				continue;
			}
		}
	}

	for (Element *e : elements) e->position += e->velocity; // Update position

}

bool Env::intersect(Element *e1, Element *e2) {
	if ((e1->position - e2->position).len() >= 10) return false; // No object's that big? Maybe other check to see if they're too far apart
	for (hitboxData d1 : e1->getHitbox()) {
		for (hitboxData d2 : e2->getHitbox()) {
			//printf("Hitbox 1: %.02f, %.02f, %.02f | %.02f, %.02f, %.02f\n", d1.x, d1.y, d1.z, d1.w, d1.h, d1.z);
			//printf("Hitbox 2: %.02f, %.02f, %.02f | %.02f, %.02f, %.02f\n\n", d2.x, d2.y, d2.z, d2.w, d2.h, d2.z);
			if (COMPARE(x, w) && COMPARE(y, h) && COMPARE(z, d)) return true;
		}
	}
	return false;
}