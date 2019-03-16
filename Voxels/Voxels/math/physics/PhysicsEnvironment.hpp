#pragma once

#include "PhysicsElement.hpp"
#include <vector>

namespace physics {

	typedef vec3(*forceFunc)(Element *element);

	class Env {
	private:
		std::vector<forceFunc> forces;
		std::vector<Element*> elements;
	
	public:

		inline void addElement(Element *elmt) { elements.push_back(elmt); }
		inline void addForceFunc(forceFunc func) { forces.push_back(func); }

		void applyForces();

	};

}