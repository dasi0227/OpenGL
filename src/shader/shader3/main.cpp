#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <init.h>
#include <shader.h>
#include <iostream>
#include <cmath>

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  GLFWwindow* window = InitOpenGL(SCR_WIDTH, SCR_HEIGHT);
  Shader myShader("src/shader/shader3/vshader.txt","src/shader/shader3/fshader.txt");

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f, -0.5f, 0.0f, // right 
    0.0f,  0.5f, 0.0f  // top   
  }; 

  // 绑定VAO
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // 绑定VBO
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // VBO添加数据
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // VAO定义属性
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // 渲染循环
  while (!glfwWindowShouldClose(window)) {
    // 处理输入
    processInput(window);
    // 清除颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // 激活着色器
    myShader.use();
    // 设置unifrom
    float timeValue = glfwGetTime();
    float colorValues[3];
    for (int i=0; i < 3; i++) {
      colorValues[i] = sin(timeValue+i) / 2.0f + 0.5f;
    }
    myShader.setColor("uniColor", colorValues);
    // 绘制三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // 显示
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // 解绑VAO和VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0); 
  // 清理资源
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  myShader.deleteProgram();
  glfwTerminate();
  return 0;
}