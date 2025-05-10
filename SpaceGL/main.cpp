#include "World.h"
#include <glad/glad.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Triangle", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    
    std::vector<Vertex> vertices = {
       {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
       {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
       {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
       {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
       {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
       {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},

       {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
       {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
       {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
       {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
       {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
       {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},

       {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
       {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
       {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
       {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
       {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
       {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},

       {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
       {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
       {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
       {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
       {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
       {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},

       {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
       {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
       {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
       {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
       {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
       {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},

       {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
       {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
       {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
       {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
       {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
       {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)}
    };

    World world;
	world.window = window;

	Object mainCube = Object("mainCube", vertices, "C:/Users/marce/source/repos/SpaceGL/SpaceGL/vertex.glsl", "C:/Users/marce/source/repos/SpaceGL/SpaceGL/fragment.glsl", world, ObjectType::OBJECT);

    Object secondCube = Object("secondCube", vertices, "C:/Users/marce/source/repos/SpaceGL/SpaceGL/vertex.glsl", "C:/Users/marce/source/repos/SpaceGL/SpaceGL/fragment.glsl", world, ObjectType::OBJECT);
    mainCube.material.objectColor = glm::vec3(0.0f, 1.0f, 0.0f);
	mainCube.setPosition(glm::abs(glm::vec3(0.0f, 0.0f, 0.0f)));
	secondCube.setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
    secondCube.setScale(glm::vec3(0.5f, 2.0f, 0.5f));

    Object thirdCube = Object("thridCube", vertices, "C:/Users/marce/source/repos/SpaceGL/SpaceGL/vertex.glsl", "C:/Users/marce/source/repos/SpaceGL/SpaceGL/fragment.glsl", world, ObjectType::OBJECT);
	thirdCube.setPosition(glm::vec3(0.0f, 0.0f, 2.0f));


	Object lightObject = Object("lightObject", vertices, "C:/Users/marce/source/repos/SpaceGL/SpaceGL/lightVertexShader.glsl", "C:/Users/marce/source/repos/SpaceGL/SpaceGL/lightFragmentShader.glsl", world, ObjectType::LIGHT);
	lightObject.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

    static int selectdItem = 0;


	std::string newObjectName = "New Object";

    float backgroundColor[3] = { 0, 0.1, 0.0 };

    while (!glfwWindowShouldClose(window)) {
        std::string title = "OpenGL - FPS: [" + std::to_string(ImGui::GetIO().Framerate) + "]";
        glfwSetWindowTitle(window, title.c_str());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        std::vector<const char*> objectNames;  
        for (const auto& objPtr : world.objects) {  
            if (objPtr) {  
                objectNames.push_back(objPtr->name.c_str()); 
            }  
        }

        ImGui::Begin("Main Window");
        ImGui::ListBox("Objects", &selectdItem, objectNames.data(), static_cast<int>(objectNames.size()));
        
		ImGui::Text("Selected Object Properties:");
		ImGui::SliderFloat3("Position", &world.objects[selectdItem]->Position.x, -100.0f, 100.0f);
		ImGui::SliderFloat3("Rotation", &world.objects[selectdItem]->Rotation.x, -100.0f, 100.0f);
		ImGui::SliderFloat3("Scale", &world.objects[selectdItem]->Scale.x, 0.0f, 100.0f);
		ImGui::ColorEdit3("Object Color", &world.objects[selectdItem]->material.objectColor.x);
		ImGui::SliderFloat3("Object Diffuse", &world.objects[selectdItem]->material.objectDiffuse[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Object Specular", &world.objects[selectdItem]->material.objectSpecular[0], 0.0f, 1.0f);
		ImGui::SliderFloat("Object Shininess", &world.objects[selectdItem]->material.objectShininess, 0.0f, 128.0f);

        ImGui::Text("New Object Creation:");
		ImGui::InputText("Object Name: ", &newObjectName[0], newObjectName.size() + 1);
        if (ImGui::Button("New Object")) {
			Object* newObject = new Object(newObjectName, vertices, "C:/Users/marce/source/repos/SpaceGL/SpaceGL/vertex.glsl", "C:/Users/marce/source/repos/SpaceGL/SpaceGL/fragment.glsl", world, ObjectType::OBJECT);
			newObject->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
			newObject->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
			newObject->material.objectColor = glm::vec3(1.0f, 1.0f, 1.0f);
        }

        ImGui::Text("Delete Object");
        if (ImGui::Button("Delete Currently Selected Object")) {
            if (selectdItem >= 0 && selectdItem < static_cast<int>(world.objects.size())) {
                delete world.objects[selectdItem]; // Delete the object
                world.objects.erase(world.objects.begin() + selectdItem); // Remove the pointer from the vector

                // Adjust selectdItem to remain valid
                if (selectdItem >= static_cast<int>(world.objects.size())) {
                    selectdItem = static_cast<int>(world.objects.size()) - 1;
                }
            }
        }

        ImGui::Text("Background Color:");
		ImGui::ColorEdit3("Background Color", backgroundColor);

        ImGui::SliderFloat3("Global Light Position", &world.GlobalLightPosition.x, -100.0f, 100.0f);
        ImGui::SliderFloat("Global Light Strength", &world.GlobalLightStrength, 0.f, 2.0f);
		ImGui::End();

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1);
       

        
        secondCube.setRotation(glm::vec3(0.0f, glm::cos(glfwGetTime()) * 20, glm::sin(glfwGetTime()) * 20));


        lightObject.setPosition(world.GlobalLightPosition);

        world.Run();
        
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}


