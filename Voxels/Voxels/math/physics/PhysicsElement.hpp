#pragma once

#include "PhysicUtil.hpp"

namespace physics {

	typedef struct {
		float x, y, z, w, h, d;
	} hitboxData;

	class Element {
	private:

	public:
		vec3 position, velocity; // Of the center of mass
		float mass = 1.0f;

		virtual std::vector<hitboxData> getHitbox() = 0;

		Element();
	};

}
