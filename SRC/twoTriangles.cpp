#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char* vertexSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const GLchar* fragmentSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const GLchar* yellow = "#version 330 core\n"
    "out vec4 YellowColor;\n"
    "void main()\n"
    "{\n"
    "   YellowColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

unsigned int VBOs[2], VAOs[2];
GLuint shaderProgram, shader2;

void glInit(){
    float triangle1[] = {
	//triangle 1
	-0.5f,  0.5f, // Top-left
	 0.5f,  0.5f, // Top-right
	 0.5f, -0.5f, // Bottom-right
    };
    //second triangle
    float triangle2[] = {

	-0.8f, -0.7f, 1.0f, 0.0f, 0.0f,
	-0.3f, -0.7f, 0.0f, 0.0f, 0.0f,
	-0.3f, -1.0f, 0.0f, 0.0f, 1.0f,

	//-0.5f, 1.0f, 1.0f, 0.0f, 0.0f, //top left
	//0.5f, 1.0f, 0.0f, 1.0f, 0.0f, //top right
	//0.5, 0.5f, 0.0f, 0.0f, 1.0f, //bottom right
    };

    //you can create multiple buffers at once
    //unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    //but you have to bind them one at a time
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}


void initShaders(){
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

    //yellow shader
    GLuint yellowShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yellowShader, 1, &yellow, NULL);
    glCompileShader(yellowShader);
    glGetShaderiv(yellowShader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(yellowShader, 512, NULL, buffer);

    //now connect the shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    shader2 = glCreateProgram();
    glAttachShader(shader2, vertexShader);
    glAttachShader(shader2, yellowShader);

    //LOAD THE DAMN COLORS
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    //link the shaders
    glLinkProgram(shaderProgram);
    glLinkProgram(shader2);
    //now use the damn thing
    //only one program can be active at a time
//    glUseProgram(shaderProgram);

    //set the vertex attribute i guess
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

    //set the color attribute
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),
	    (void*)(2*sizeof(float)));

    //cleanup - delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void render(GLFWwindow* window){
    float black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glClearBufferfv(GL_COLOR, 0, black);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shader2);

    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();
    
    glfwSwapBuffers(window);
}

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


    glInit();
    initShaders();

    //not doing this in the loop makes really fuckin cool glitchy art
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

    /*for(int i = 0; i < 1000; i++){
    render(window);
    }*/

   while(!glfwWindowShouldClose(window)){
	render(window);
    }

    glfwTerminate();

    return 0;
}
