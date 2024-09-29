#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

// 回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// 键盘输入函数
void processInput(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  // 初始化GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置主版本为3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 设置次版本为3
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置使用核心模式

  // 创建窗口
  GLFWwindow* window = glfwCreateWindow(800, 600, "Simple Triangle", nullptr, nullptr);
  if (!window) {
    cerr << "Failed to create GLFW window" << endl;
    return -1;
  }
  glfwMakeContextCurrent(window); // 设置为上下文

  // 初始化GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    cout << "Failed to initialize GLAD" << endl;
    return -1;
  }

  // 初始化视口
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // 渲染循环
  while (!glfwWindowShouldClose(window)) {
    // 输入
    processInput(window);
    // 渲染
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // 呈现
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // 销毁窗口
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
