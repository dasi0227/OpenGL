#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace glm;

class Shader {
  public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();  
    void deleteProgram();
    void setColor(const string &name, const float* values) const;
    void setTexture(const string &name, const int index) const;
    void setFloat(const string &name, const float value) const;
    void setMat4(const string &name, const mat4 matrix) const;
};

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
  // 打开shader
  string vertexCode;
  string fragmentCode;
  ifstream vertexShaderFile;
  ifstream fragmentShaderFile;
  stringstream vertexShaderStream;
  stringstream fragmentShaderStream;
  vertexShaderFile.open(vertexPath);
  fragmentShaderFile.open(fragmentPath);

  // 检测shader是否打开成功
  if (!vertexShaderFile.is_open()) {
    cerr << "Failed to open vertex shader file: " << vertexPath << endl;
    return;
  }
  if (!fragmentShaderFile.is_open()) {
    cerr << "Failed to open fragment shader file: " << fragmentPath << endl;
    return;
  }

  // 读取shader
  vertexShaderStream << vertexShaderFile.rdbuf();
  fragmentShaderStream << fragmentShaderFile.rdbuf();
  vertexShaderFile.close();
  fragmentShaderFile.close();
  vertexCode = vertexShaderStream.str();
  fragmentCode = fragmentShaderStream.str();
  const char* vertexShaderCode = vertexCode.c_str();
  const char* fragmentShaderCode = fragmentCode.c_str();

  int success;
  // 编译vertexShader
  unsigned int vertex;
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexShaderCode, NULL);
  glCompileShader(vertex);
  // 检测vertexShader是否编译成功
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if(!success) {
    char infoLog[512];
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    cerr << "Failed to complile vertexShader" << endl << infoLog << endl;
    return ;
  };

  // 编译fragmentShader
  unsigned int fragment;
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
  glCompileShader(fragment);
  // 检测fragmentShader是否编译成功
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if(!success) {
    char infoLog[512];
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    cerr << "Failed to complile fragmentShader" << endl << infoLog << endl;
    return ;
  }

  // 链接着色器
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // 检测着色器是否链接成功
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if(!success) {
    char infoLog[512];
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    cerr << "Failed to link shader" << endl << infoLog << endl;
    return ;
  }
  
  // 删除着色器
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::deleteProgram() {
  glDeleteProgram(ID);
}

void Shader::setColor(const string &name, const float* values) const {
  int uniformIndex = glGetUniformLocation(ID, name.c_str());
  glUniform3f(uniformIndex, values[0], values[1], values[2]);
}

void Shader::setTexture(const string &name,const int index) const {
  int uniformIndex = glGetUniformLocation(ID, name.c_str());
  glUniform1i(uniformIndex, index);
}

void Shader::setFloat(const string &name, const float value) const {
  int uniformIndex = glGetUniformLocation(ID, name.c_str());
  glUniform1f(uniformIndex, value);
}

void Shader::setMat4(const string &name, const mat4 matrix) const{
  int uniformIndex = glGetUniformLocation(ID, name.c_str());
  glUniformMatrix4fv(uniformIndex, 1, GL_FALSE, value_ptr(matrix));
}

#endif