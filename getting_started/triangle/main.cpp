#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

const GLchar* vs_source =
    "#version 330 core                      \n"
    "                                       \n"
    "layout (location = 0) in vec3 position;\n"
    "                                       \n"
    "void main()                            \n"
    "{                                      \n"
    "    gl_Position = vec4(position, 1.0); \n"
    "}                                      \n";

const GLchar* fs_orange_source =
    "#version 330 core                              \n"
    "                                               \n"
    "out vec4 color;                                \n"
    "                                               \n"
    "void main()                                    \n"
    "{                                              \n"
    "       color = vec4(1.0f, 0.5f, 0.2f, 1.0f);   \n"
    "}                                              \n";

const GLchar* fs_yellow_source =
    "#version 330 core                              \n"
    "                                               \n"
    "out vec4 color;                                \n"
    "                                               \n"
    "void main()                                    \n"
    "{                                              \n"
    "       color = vec4(1.0f, 1.0f, 0.0f, 1.0f);   \n"
    "}                                              \n";

GLuint getProgram(const GLchar* vs_source, const GLchar* fs_source)
{
    GLuint program = 0;

    GLuint vs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n"
                  << infoLog << std::endl;
    }

    GLuint fs;
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n"
                  << infoLog << std::endl;
    }

    program = glCreateProgram();

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    GLFWwindow* window = initWindow();
    if (!window) {
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLuint program[] = {getProgram(vs_source, fs_orange_source), getProgram(vs_source, fs_yellow_source)};

    GLfloat vertices[][9] = {{
        0.5f, 0.5f, 0.0f, // right top
        0.5f, -0.5f, 0.0f, // right bottom
        -0.5f, 0.5f, 0.0f // left top
    }, {
        0.5f, -0.5f, 0.0f, // right bottom
        -0.5f, -0.5f, 0.0f, // left bottom
        -0.5f, 0.5f, 0.0f // left top
    }};

    GLuint vao[2];
    glGenVertexArrays(2, vao);

    GLuint vbo[2];
    glGenBuffers(2, vbo);

    for(int i = 0; i < 2; ++i) {
        glBindVertexArray(vao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(int i = 0; i < 2; ++i) {
            glUseProgram(program[i]);
            glBindVertexArray(vao[i]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(2, vao);
    glDeleteBuffers(2, vbo);

    glfwTerminate();

    return 0;
}
