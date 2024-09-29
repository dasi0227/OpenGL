// 平移加旋转

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <init.h>
#include <shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;
using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float redColor = 0.5f;
float greenColor = 0.5f;

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
    redColor += 0.001f;
    if (redColor > 1.0f){
      redColor = 1.0f;
      cout << "当前颜色的R值已经是最大！" << endl;
    }
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
    redColor -= 0.001f;
    if (redColor < 0.0f){
      redColor = 0.0f;
      cout << "当前颜色的R值已经是最小！" << endl;
    }
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
    greenColor += 0.001f;
    if (greenColor > 1.0f){
      greenColor = 1.0f;
      cout << "当前颜色的G值已经是最大！" << endl;
    }
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
    greenColor -= 0.001f;
    if (greenColor < 0.0f){
      greenColor = 0.0f;
      cout << "当前颜色的G值已经是最小！" << endl;
    }
  }
}

int main(){
  // 初始化
  GLFWwindow* window = InitOpenGL(SCR_WIDTH,SCR_HEIGHT);
  // 自定义着色器和数据
  Shader myShader("src/transform/transform2/vshader.txt","src/transform/transform2/fshader.txt");
  float vertices[] = {
    -0.3f, -0.3f, 0.0f, // left
    0.3f, -0.3f, 0.0f, // right 
    0.0f,  0.3f, 0.0f  // top
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
    // 使用着色器
    myShader.use();
    // 设置颜色
    float color[3] = {redColor, greenColor, 0.0f};
    myShader.setColor("myColor", color);
    // 设置变换
    mat4 transform = mat4(1.0f);
    float time = (float)glfwGetTime();
    float radius = 0.5f;
    float angle = time;
    float x = radius * cos(angle);
    float y = radius * sin(angle);
    float scaleFactor = 1.0f + sin(time);
    transform = scale(transform, vec3(scaleFactor, scaleFactor, 1.0f));
    // transform = translate(transform, vec3(x, y, 0.0f));
    transform = rotate(transform, time, vec3(0.0f, 0.0f, 1.0f));
    myShader.setMat4("myTransform", transform);
    // 绘制图形
    glBindVertexArray(VAO);
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