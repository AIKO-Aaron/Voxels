#pragma once

#include "PhysicUtil.hpp"

namespace physics {

	class Element {
	private:

	public:
		vec3 position, velocity; // Of the center of mass
		float mass = 1.0f;

		Element();
	};

}