#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "callbacks.h"


void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//super janky way of compiling a vertex shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

//super janky way of compiling a fragment shader
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0"; 

int main(){
    //initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
 
    //make window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);

    //initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
    }  

    //set dimensions of viewport
    glViewport(0, 0, 800, 600);

    //set viewport to resize with window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //make things to draw
    /*float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
    };*/
    float triangle1 [] = {
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
    };

    float triangle2 [] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
    };

    //set up vertex shader 
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //compile the shader above
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //setup fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //check if linking was successful 
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    //use shader
    glUseProgram(shaderProgram);
    //cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //opengl still needs to be told how to interpret the vertex data

    unsigned int VBO[2], VAO[2];
    //triangle2
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then
    // configure vertex attributes(s).
    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1)*2, triangle1, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the
    // vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this
    // VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind
    // VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    //render loop
    while(!glfwWindowShouldClose(window)){
	
	processInput(window);

	//render commands go here
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//draw
	// draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]); // seeing as we only have a single VAO there's no need
	// to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

	//swap the buffers and check for input
	glfwSwapBuffers(window);
	glfwPollEvents();    
    }

    //clean up and exit
    glfwTerminate();
    return 0;
}
