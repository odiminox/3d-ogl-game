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
      maths::matrix::Matrix3 model = maths::matrix::Matrix3(1.0f);
      maths::matrix::Matrix3 view = maths::matrix::Matrix3(1.0f);
      maths::matrix::Matrix3 projection = maths::matrix::Matrix3(1.0f);

      const char* vertex_shader_code = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"

        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
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

        model = maths::matrix::rotate_x(maths::deg_to_radians(-1.0f));
        maths::vector::Vector3 translation(0.0f, 0.1f, -15.0f);
        view = maths::matrix::translate(view, translation);
        projection = maths::camera::perspective(maths::deg_to_radians(45.0f), 
          800.0f / 600.0f, 
          0.1f, 
          100.0f);


        return 0;
      }

      void render_material() const
      {
        glUseProgram(shader_program_id);
        unsigned int modelLoc = glGetUniformLocation(shader_program_id, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, *shader_transform->m);

        unsigned int viewLoc = glGetUniformLocation(shader_program_id, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, *view.m);

        unsigned int projectionLoc = glGetUniformLocation(shader_program_id, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, *view.m);
      }

      void cleanup()
      {
        shader_transform = nullptr;
        delete shader_transform;
      }
    };

    struct VertexObject
    {
      unsigned int element_buffer_object;
      unsigned int vertex_array_object;
      unsigned int vertex_buffer_object;

      int initialise()
      {
        float vertices[] = {
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        // this is not an ideal way to do this. We want to batch all the vertices into a single buffer and call all this once - 
        // but works for now as a quick n dirty means to get multiple objects up

        glGenVertexArrays(1, &vertex_array_object);
        glGenBuffers(1, &vertex_buffer_object);

        glBindVertexArray(vertex_array_object);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        return 0;
      }

      void render_vertex() const
      {
        glBindVertexArray(vertex_array_object);
        glDrawArrays(GL_TRIANGLES, 0, 36);
      }
    };

    struct RenderData
    {
      Material material;
      VertexObject vertex_object;
    };
  }
}