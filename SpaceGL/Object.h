#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "World.h"
#include <vector>


class World;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
};


struct Material {
	glm::vec3 objectColor;
	float objectDiffuse[3];
	float objectSpecular[3];
	float objectShininess;

	Shader shader;

	void SetMaterialProperties(float objectDiffuse[3], float objectSpecular[3], float objectShininess);
};

enum ObjectType {
	OBJECT,
	LIGHT
};

class Object {
public:
	World& existingWorld;
	Material material;

	glm::vec3 Position = glm::vec3(0, 0, 0);
	glm::vec3 Rotation = glm::vec3(0, 0, 0);
	glm::vec3 Scale = glm::vec3(1, 1, 1);

	std::string name;
	ObjectType objecTy;

	Object(std::string Name, std::vector<Vertex> vertices, const char* vertexPath, const char* fragmentPath, World& world, ObjectType type);
	~Object();

	void setVertices(std::vector<Vertex> newVertices);
	void setPosition(glm::vec3 newPosition);
	void setRotation(glm::vec3 newRotation);
	void setScale(glm::vec3 newScale);

	void UpdateTransform();
	void draw();

private:
	std::vector<Vertex> vertices;
	unsigned int VBO;
	unsigned int VAO;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
};

#endif