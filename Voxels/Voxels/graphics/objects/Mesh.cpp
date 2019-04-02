#include "Mesh.hpp"

using namespace graphics::objects;

Mesh::Mesh(graphics::Shader *shader, std::vector<physics::vec3> pointsInMesh, Material mat) : Object(shader, pointsInMesh.size()) {
	material = mat;

	vertexData *verticies = new vertexData[pointsInMesh.size()];

	for (int i = 0; i < pointsInMesh.size() / 3; i++) {
		physics::vec3 p1 = pointsInMesh[3 * i + 0];
		physics::vec3 p2 = pointsInMesh[3 * i + 1];
		physics::vec3 p3 = pointsInMesh[3 * i + 2];
		physics::vec3 normal = math::cross(p2 - p1, p3 - p1) * -1;

		verticies[i * 3 + 0] = { p1[0], p1[1], p1[2], 0, 0, normal[0], normal[1], normal[2] };
		verticies[i * 3 + 1] = { p2[0], p2[1], p2[2], 1, 0, normal[0], normal[1], normal[2] };
		verticies[i * 3 + 2] = { p3[0], p3[1], p3[2], 1, 1, normal[0], normal[1], normal[2] };
	}


	GLubyte *indicies = new GLubyte[pointsInMesh.size()];
	for (int i = 0; i < pointsInMesh.size(); i++) indicies[i] = i;

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * pointsInMesh.size(), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexData), POS_OFFSET);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vertexData), UV_OFFSET);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(vertexData), NORMAL_OFFSET);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * pointsInMesh.size(), indicies, GL_STATIC_DRAW);
}