// C++ Standard Library
#include <cstdio> // print and flush

// OpenGL and GLFW
#include <GL/glew.h> // OpenGL implementation
#include <GLFW/glfw3.h> // Give me windowing powers

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


int main(int, char**)
{ // setup, loop, and cleanup
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

    const bool fullscreen = false;
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

    // Shader stuff starts here
    // LEFT OFF HERE
    /* Shader shader(); */


    /* =====[ LOOP ]===== */
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

    }
    
    /* =====[ CLEANUP ]===== */

    glfwDestroyWindow(window);
    glfwTerminate();

    printf("Bob out.");

    return 0;
}
// vim:fdm=syntax:
