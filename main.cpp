// C++ Standard Library
#include <cstdio> // print and flush

// OpenGL and GLFW
#include <GL/glew.h> // OpenGL implementation
#include <GLFW/glfw3.h> // Give me windowing powers

// Stuffs I made myself
#include "colors.h"

/* =====[ SHADERS ]===== */

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

/* =====[ CALLBACKS ]===== */

static void glfw_error_callback(int error, const char* description)
{ // Executes when a GLFW error occurs.
    // Show me the error code and a UTF-8 encoded string describing the error.
    printf("GLFW Error %d: %s\n", error, description);
    fflush(stdout);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{ // Executes when window size changes (by OS or user resize)
    // Match viewport to new window dimensions
    glViewport(0, 0, width, height);
    // Show me the new window size
    printf("New window size: %d x %d\n", width, height);
    fflush(stdout);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{ // Executes when user does a key

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int, char**)
{ // setup, setup_shaders, loop, loop_render, and cleanup
    /* =====[ SETUP ]===== */
    printf("Bob in.\n");
    fflush(stdout);

    // Windowing stuff starts here

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        printf("ERROR: cannot initialize the GLFW library.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Get info about this monitor.
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    printf("VideoMode width: %d, height: %d\n", mode->width, mode->height);
    fflush(stdout);

    const bool fullscreen = true;
    GLFWwindow* window = NULL;

    if (fullscreen)
    {
        // Create fullscreen window
        window = glfwCreateWindow(
            // Use full width and height to avoid Sony Bravia "scene select"
            mode->width, // use full width
            mode->height, // use full height
            "RENDER-TEXT",  // const char* title
            /* NULL, // GLFWmonitor* monitor - NULL be WINDOWED*/
            monitor, // Go FULLSCREEN
            NULL  // GLFWwindow* share
            );
    }
    else
    {
        // Create fullscreen window
        window = glfwCreateWindow(
            672, // int width
            392, // int height
            "672x392",  // const char* title
            NULL, // GLFWmonitor* monitor - NULL be WINDOWED
            NULL  // GLFWwindow* share
            );
    }

    if (window == NULL)
    {
        printf("ERROR: cannot create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    // Callback this callback if window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // OpenGL stuff starts here

    // Initialize GLEW
    GLenum error_code = glewInit();
    if (GLEW_OK != error_code)
    { // ERROR
        printf("ERROR: cannot initialize glew\n");
        glfwTerminate();
        return -1;
    }
    else
    { // Show me what version stuffs I'm using
        // Show me the GLEW version
        printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
        // Show me the OpenGL version
        GLint major = 0;
        GLint minor = 0;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        printf("Using OpenGL %d.%d\n", major, minor);
        fflush(stdout);
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* =====[ SETUP_SHADERS ]===== */

    // Make this:
    unsigned int shaderProgram = glCreateProgram();
    { // Compile the shader programs.
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        { // Vertex Shader
            glShaderSource(
                    // write new shader source to vertexShader
                    vertexShader, // GLuint shader:
                    // only 1  element in arrays `string` and `length`
                    1,            // GLsizei count:
                    // pointer to str that is the new shader source code
                    &vertexShaderSource, // const GLchar **string:
                    // array of `string` lengths (NULL means each string is NULL terminated)
                    NULL          // const GLint *length
                    );
            glCompileShader(vertexShader);
            // check for shader compile errors
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s",infoLog);
                fflush(stdout);
            }
            else
            {
                printf("Compiled vertex shader.\n");
                fflush(stdout);
            }
        }
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        { // Fragment Shader
            glShaderSource(
                    fragmentShader, // write new shader source to fragmentShader
                    1,              // all the source is in just 1 string
                    &fragmentShaderSource, // this be the string with the shader
                    NULL // the string be NULL terminated
                    );
            glCompileShader(fragmentShader);
            // check for shader compile errors
            int success;
            char infoLog[512];
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s",infoLog);
                fflush(stdout);
            }
            else
            {
                printf("Compiled fragment shader.\n");
                fflush(stdout);
            }
        }
        { // link shaders
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            // check for linking errors
            int success;
            char infoLog[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s",infoLog);
                fflush(stdout);
            }
            else
            {
                printf("Linked shader program.\n");
                fflush(stdout);
            }
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    // Do a triangle?
    unsigned int VBO, VAO; // vertex buffer object, vertex array object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first
    glBindVertexArray(VAO);
    // Then bind and set vertex buffer(s)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // And then configure vertex attributes(s).
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // - VBO registered as the vertex attribute's bound vertex buffer object
    // - OK to unbind.
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    // Draw wireframe polygons.
    /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

    /* =====[ LOOP ]===== */
    while (!glfwWindowShouldClose(window))
    {
        /* // Get the window size */
        /* int width, height; */
        /* glfwGetFramebufferSize(window, &width, &height); */

        /* =====[ LOOP_RENDER ]===== */

        // Make background coffee colored
        glClearColor(
                bwc_coffee.r, // GLclampf red,
                bwc_coffee.g, // GLclampf green,
                bwc_coffee.b, // GLclampf blue,
                bwc_coffee.a  // GLclampf alpha
                );
        glClear(GL_COLOR_BUFFER_BIT);

        // Render a big old triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // TODO: deal with keyboard/mouse events
        // TODO: render stuff

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    
    /* =====[ CLEANUP ]===== */

    glfwDestroyWindow(window);
    glfwTerminate();

    printf("Bob out.");

    return 0;
}
// vim:fdm=syntax:
