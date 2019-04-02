#pragma once

#include <vector>
#include "Object.hpp"

namespace graphics {
	namespace objects {

		class Mesh : public Object {
		private:

		public:
			Mesh(Shader *shader, std::vector<physics::vec3> pointsInMesh, Material m);

			inline std::vector<physics::hitboxData> getHitbox() override { return std::vector<physics::hitboxData>(); } // No hitbox (triangle is only 2D)
		};

	}
}