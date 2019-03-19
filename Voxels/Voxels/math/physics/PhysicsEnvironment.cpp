#include "PhysicsEnvironment.hpp"

#define COMPARE(a, b) (d1.a + d1.b >= d2.a && d1.a <= d2.a + d2.b)
#define SPRINGINESS 1.0

using namespace physics;

vec3 calculateHit(float m1, float m2, vec3 v1, vec3 v2, vec3 intersectionPoint) {
    vec3 out = (v1 * m1 - (v1 - v2 * 2.0f) * m2) / (m1 + m2);
    
    printf("Length of output vector: %f\n", out.len());
    
    vec3 e1 = v1.copy().normalize() + v2.copy().normalize();
    vec3 e2 = e1 + intersectionPoint;
    
    vec3 normal = math::cross(intersectionPoint, e2);
    vec3 dir = v1 - normal * normal.dot(v1) * 2.0f;
    
    float len = out.len();
    return dir * len * -1;
}

void Env::applyForces() {
    for (int i = 0; i < (int)elements.size(); i++) {
        Element *e = elements[i];
        for (int j = i + 1; j < (int)elements.size(); j++) {
            if (intersect(e, elements[j])) {
                vec3 v1 = calculateHit(elements[j]->mass, e->mass, elements[j]->velocity, e->velocity, e->position);
                vec3 v2 = calculateHit(e->mass, elements[j]->mass, e->velocity, elements[j]->velocity, e->position);
                
                /**printf("\n");
                printf("%f\n", ((elements[j]->velocity) * (elements[j]->mass) + (e->velocity) * (e->mass))[1]);
                printf("%f\n", ((elements[j]->velocity - e->velocity) * (e->mass))[1]);
                printf("%f\n", ((elements[j]->velocity - e->velocity) * (elements[j]->mass))[1]);
                printf("%f\n", elements[j]->mass + e->mass);*/

                e->velocity = v1 * SPRINGINESS;
                elements[j]->velocity = v2 * SPRINGINESS;
                
                if(e->velocity.len() < 0.001) printf("Length of new velocity: %f\n", e->velocity.len());
                
                if((e->velocity - elements[j]->velocity).len() < 0.001) printf("Difference is minimal!? %f\n", (e->velocity - elements[j]->velocity).len());
                
                int steps = 0;
                while(intersect(e, elements[j]) && steps++ < 100) {
                    e->position += e->velocity / 10.0f;
                    elements[j]->position += elements[j]->velocity / 10.0f;
                }
                    
                break;
            }
        }
    }
    
	for (Element *e : elements) {
		vec3 curForce;
		for (forceFunc f : forces) curForce += f(e); // Add the force to the total
		vec3 acceleration = curForce / e->mass; // F = m*a --> a = F/m
		e->velocity += acceleration; // Update velocity
        e->position += e->velocity;
	}
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
