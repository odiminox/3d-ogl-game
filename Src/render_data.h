#pragma once

#include <iostream>
#include "third_party/glad/include/glad/glad.h"
#include "third_party/glfw3.h"

#include "maths.h"

namespace game
{
  namespace render_data
  {
    struct Material
    {
      maths::matrix::Matrix3* shader_transform = new maths::matrix::Matrix3(1);

      const char* vertex_shader_code = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 transform;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

      const char* fragment_shader_code = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

      unsigned int shader_program_id;

      //static int material_id;

      int initialise()
      {
        //material_id++;
        std::cout << "Creating shader program for material: " << std::endl;

        unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
        glCompileShader(vertex_shader);

        int  success;
        char infoLog[512];
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
          glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
          std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

          return -1;
        }

        unsigned int fragment_shader;
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
          glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
          std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

          return -1;
        }

        shader_program_id = glCreateProgram();
        glAttachShader(shader_program_id, vertex_shader);
        glAttachShader(shader_program_id, fragment_shader);
        glLinkProgram(shader_program_id);

        glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);

        if (!success)
        {
          glGetProgramInfoLog(shader_program_id, 512, nullptr, infoLog);
          std::cout << "ERROR:SHADER_PROGRAM::CREATION_FAILED\n" << infoLog << std::endl;

          return -1;
        }

        glUseProgram(shader_program_id);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return 0;
      }

      void render_material() const
      {
        glUseProgram(shader_program_id);
        unsigned int transformLoc = glGetUniformLocation(shader_program_id, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, *shader_transform->m);
      }

      void cleanup()
      {
        shader_transform = nullptr;
        delete shader_transform;
      }
    };

    struct VertexObject
    {
      unsigned int vertex_array_object;
      unsigned int element_buffer_object;

      int initialise()
      {
        float vertices[] = {
           0.5f,  0.5f, 0.0f,  // top right
           0.5f, -0.5f, 0.0f,  // bottom right
          -0.5f, -0.5f, 0.0f,  // bottom left
          -0.5f,  0.5f, 0.0f   // top left 
        };
        unsigned int indices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        // this is not an ideal way to do this. We want to batch all the vertices into a single buffer and call all this once - 
        // but works for now as a quick n dirty means to get multiple objects up
        unsigned int vertex_buffer_object;
        glGenBuffers(1, &vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glGenVertexArrays(1, &vertex_array_object);
        glGenBuffers(1, &element_buffer_object);

        glBindVertexArray(vertex_array_object);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        return 0;
      }

      void render_vertex() const
      {
        glBindVertexArray(vertex_array_object);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      }
    };

    struct RenderData
    {
      Material material;
      VertexObject vertex_object;
    };
  }
}