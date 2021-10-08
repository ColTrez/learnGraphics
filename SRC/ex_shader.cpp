#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

unsigned int createAndLoadVertices(){
    //first three floats are position, last three are color
    float vertices[] = {
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s),
    // and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}

void render(GLFWwindow* window, unsigned int vao){
    float black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glClearBufferfv(GL_COLOR, 0, black);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
}

int main(){
    
    //glfw initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "openglDemo", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);

    //glad initialization
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    unsigned int vao = createAndLoadVertices();
    
    Shader bigGay("/home/coltrez/Programs/C++/graphics/learnGraphics/SRC/shaders/outputPos.glsl",
	    "/home/coltrez/Programs/C++/graphics/learnGraphics/SRC/shaders/inputPos.glsl");
    bigGay.use();
    
    //initialize uniform
    //int offsetLocation = bigGay.getUniformLocation("offset");
    //glUniform3f(offsetLocation, 0.2f, 0.0f, 0.0f);

    while(!glfwWindowShouldClose(window)){
	glfwPollEvents();

	render(window, vao);
    }

    glfwTerminate();

    return 0;
}
