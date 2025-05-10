#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Object.h"
#include <vector>

class Object;

class World {
public:

    GLFWwindow* window;

    float yaw = 0.0f;
    float pitch = 0.0f;

    bool firstMouse = true;

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);


    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 direction;


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLFWvidmode* mode = (GLFWvidmode*)glfwGetVideoMode(monitor);

    std::vector<Object*> objects;
    glm::vec3 GlobalLightPosition = glm::vec3(5.0f, 0.0f, 0.0f);
	float GlobalLightStrength = 10.0f;

	// Shadow Maps
    unsigned int depthMapFBO;
    unsigned int shadowMap;
	unsigned int shadowMapWidth = 1024;
	unsigned int shadowMapHeight = 1024;

    void addObject(Object* object);

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    void processCameraMovement(GLFWwindow* window);

    void Run();
    World();
    ~World();
};