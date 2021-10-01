#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;
    in vec3 color;

    out vec3 Color;

    void main()
    {
	Color = color;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

const GLchar* fragmentSource = R"glsl(
    #version 150 core

    in vec3 Color;

    out vec4 outColor;

    void main()
    {
        outColor = vec4(Color, 1.0);
    }
)glsl";

int main(){

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "openglDemo", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);

    //initialize glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


    //create the vertex array object
    //this must be made before the vertex buffer object
    //there can be only one, and it holds the vertex buffer objects
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //create vertices
    //upload vertices to graphics card
    float vertices[] = {
	 0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
    };
    //create the vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    //make it the active object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //vertices into buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //create shaders

    //vertex shader
    //create shader object
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //load sourcecode into it
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    //compile it
    glCompileShader(vertexShader);
    //get and report any errors
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

    //fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);

    //now connect the shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //LOAD THE DAMN COLORS
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    //link the shaders
    glLinkProgram(shaderProgram);
    //now use the damn thing
    //only one program can be active at a time
    glUseProgram(shaderProgram);

    //set the vertex attribute i guess
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

    //set the color attribute
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

    //not doing this in the loop makes really fuckin cool glitchy art
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

    while(!glfwWindowShouldClose(window)){
	glfwSwapBuffers(window);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
