#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "error_callbacks.h"
#include "utilities.h"
#include "vertex.h"

int main(int argc, char ** argv){

    //basic setup
    glfwSetErrorCallback(error_callback);
    
    glfwInit();

    //tell user needed version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, argv[0], nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glClearColor(.2f, .2f, .6f, 0.f);
    //setup complete
    
    std::vector<DrawDetails> ourDrawDetails;
    {
	//create object to display points
	std::vector<Vertex> obj_pts;
	obj_pts.emplace_back(.5f, -.5f, 0.f);
	obj_pts.emplace_back(-.5f, -.5f, 0.f);
	obj_pts.emplace_back(0.f, -.5f, 0.f);

	std::vector<uint32_t> elem = {0, 1, 2};

	ourDrawDetails.push_back(UploadMesh(obj_pts, elem));
    }

    while(!glfwWindowShouldClose(window)){
	glClear(GL_COLOR_BUFFER_BIT);
	Draw(ourDrawDetails);

	//render
	glfwSwapBuffers(window);
	//read input
	glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
