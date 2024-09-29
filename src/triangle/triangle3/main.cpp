#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// 着色器编程
// 向下偏移
const char *vertexShaderSource1 = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main() {\n"
  " gl_Position = vec4(aPos.x, aPos.y-0.3, aPos.z, 1.0);\n"
  "}\0";
// 向上偏移
const char *vertexShaderSource2 = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main() {\n"
  " gl_Position = vec4(aPos.x, -aPos.y+0.3, aPos.z, 1.0);\n"
  "}\0";
// 红色
const char *fragmentShaderSource1 = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  " FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
  "}\0";
// 蓝色
const char *fragmentShaderSource2 = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  " FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
  "}\0";

int main() {
  // glfw初始化
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 创建窗口
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // 初始化glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD" << endl;
    return -1;
  }

  // 编译顶点着色器
  unsigned int vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader1, 1, &vertexShaderSource1, NULL);
  glCompileShader(vertexShader1);
  // 编译片段着色器
  unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
  glCompileShader(fragmentShader1);
  // 链接着色器
  unsigned int shaderProgram1 = glCreateProgram();
  glAttachShader(shaderProgram1, vertexShader1);
  glAttachShader(shaderProgram1, fragmentShader1);
  glLinkProgram(shaderProgram1);
  // 删除着色器
  glDeleteShader(vertexShader1);
  glDeleteShader(fragmentShader1);

  // 编译顶点着色器
  unsigned int vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
  glCompileShader(vertexShader2);
  // 编译片段着色器
  unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
  glCompileShader(fragmentShader2);
  // 链接着色器
  unsigned int shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2, vertexShader2);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);
  // 删除着色器
  glDeleteShader(vertexShader2);
  glDeleteShader(fragmentShader2);

  // 顶点数据
  float vertices[] = {
    -0.3f, -0.3f, 0.0f, // left
    0.3f, -0.3f, 0.0f, // right 
    0.0f,  0.3f, 0.0f  // top
  };

  // 绑定VAO和VBO
  unsigned int VAOs[2];
  glGenVertexArrays(2, VAOs);
  unsigned int VBOs[2];
  glGenBuffers(2, VBOs);

  // 用第一个VAO处理第一个VBO
  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // 用第二个VAO处理第二个VBO
  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // 渲染循环
  while (!glfwWindowShouldClose(window)) {
    // 处理输入
    processInput(window);
    // 清除颜色
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // 使用着色器1
    glUseProgram(shaderProgram1);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // 使用着色器2
    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // 显示
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // 解绑VAO和VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0); 

  // 清理资源
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgram1);
  glDeleteProgram(shaderProgram2);
  glfwTerminate();
  return 0;
}