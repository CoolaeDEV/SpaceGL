#include "Object.h"

void Material::SetMaterialProperties(float objectDiffuse[3], float objectSpecular[3], float objectShininess) {
	objectDiffuse[0] = objectDiffuse[0];
	objectDiffuse[1] = objectDiffuse[1];
	objectDiffuse[2] = objectDiffuse[2];
	objectSpecular[0] = objectSpecular[0];
	objectSpecular[1] = objectSpecular[1];
	objectSpecular[2] = objectSpecular[2];
	objectShininess = objectShininess;
}


Object::Object(std::string Name, std::vector<Vertex> Vertices, const char* vertexPath, const char* fragmentPath, World& world, ObjectType type) : existingWorld(world){

	material.shader = Shader(vertexPath, fragmentPath);
	name = Name;
	objecTy = type;

	if (objecTy == OBJECT) {
		material.objectColor = glm::vec3(1.0f, 0.0f, 0.0f);
		material.objectDiffuse[0] = 0.5f;
		material.objectDiffuse[1] = 0.5f;
		material.objectDiffuse[2] = 0.5f;
		material.objectSpecular[0] = 0.5f;
		material.objectSpecular[1] = 0.5f;
		material.objectSpecular[2] = 0.5f;
		material.objectShininess = 32.0f;
		material.SetMaterialProperties(material.objectDiffuse, material.objectSpecular, material.objectShininess);
	}

	model = glm::rotate(model, 1.0f * glm::radians(0.0f), Scale);
	model = glm::translate(model, Position);
	model = glm::scale(model, Scale);

	view = glm::lookAt(this->existingWorld.cameraPosition, this->existingWorld.cameraPosition + this->existingWorld.cameraFront, this->existingWorld.cameraUp);
	if (this->existingWorld.mode != nullptr) {
		float aspectRatio = static_cast<float>(this->existingWorld.mode->width) / static_cast<float>(this->existingWorld.mode->height);
		projection = glm::perspective(glm::radians(60.0f), aspectRatio, 1.0f, 100.0f);
	}

	this->existingWorld.addObject(this);

	vertices = Vertices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Object::~Object() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}


void Object::setVertices(std::vector<Vertex> newVertices) {
	vertices = newVertices;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

void Object::setPosition(glm::vec3 newPosition) {
	Position = newPosition;
	model = glm::translate(model, Position);
}
void Object::setRotation(glm::vec3 newRotation) {
	Rotation = newRotation;
	model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Object::setScale(glm::vec3 newScale) {
	Scale = newScale;
	model = glm::scale(model, Scale);
}

void Object::UpdateTransform() {
	model = glm::mat4(1.0f);
	model = glm::translate(model, Position);
	model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, Scale);
}

void Object::draw() {
	view = glm::lookAt(this->existingWorld.cameraPosition, this->existingWorld.cameraPosition + this->existingWorld.cameraFront, this->existingWorld.cameraUp);

	UpdateTransform();

	material.shader.use();

	material.shader.setMat4("model", glm::value_ptr(model));
	material.shader.setMat4("view", glm::value_ptr(view));
	material.shader.setMat4("projection", glm::value_ptr(projection));

	switch (objecTy) {
		case OBJECT:
			material.shader.setVec3("material.ambient", 0, 0, 0);
			material.shader.setVec3("material.diffuse", material.objectDiffuse[0], material.objectDiffuse[1], material.objectDiffuse[2]);
			material.shader.setVec3("material.specular", material.objectSpecular[0], material.objectSpecular[1], material.objectSpecular[2]);
			material.shader.setFloat("material.shininess", material.objectShininess);

			material.shader.setVec3("lightPos", this->existingWorld.GlobalLightPosition.x, this->existingWorld.GlobalLightPosition.y, this->existingWorld.GlobalLightPosition.z);
			material.shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

			material.shader.setFloat("lightBrightness", this->existingWorld.GlobalLightStrength);

			material.shader.setVec3("ObjectColor", material.objectColor.x, material.objectColor.y, material.objectColor.z);
			material.shader.setVec3("viewPos", this->existingWorld.cameraPosition.x, this->existingWorld.cameraPosition.y, this->existingWorld.cameraPosition.z);
			break;
		case LIGHT:
			material.shader.setFloat("vertexBrightness", this->existingWorld.GlobalLightStrength);
			break;
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}