#include <ogf/graphics/shader.hxx>

#include <fstream>
#include <optional>
#include <sstream>

#include <glad/glad.h>

namespace ogf {

    namespace {

        std::optional<std::string> get_file_content(const std::string_view filename) {
            std::ifstream file{filename.data()};
            if(!file.good()) {
                return {};
            }
            std::stringstream file_content{};
            while(!file.eof()) {
                std::string line{};
                std::getline(file, line);
                file_content << line << '\n';
            }
            return file_content.str();
        }

    }

    Shader::~Shader() {
        glDeleteProgram(m_program);
    }

    void Shader::load_from_file(const std::string_view filename, const ShaderType type) {
        const auto source = get_file_content(filename);
        if(!source.has_value()) {
            throw std::runtime_error{"Failed to open shader file \"" + std::string{filename} + "\"."};
        }
        load_from_memory(source.value(), type);
    }

    void Shader::load_from_file(const std::string_view vertex_filename, const std::string_view fragment_filename) {
        const auto vertex_source = get_file_content(vertex_filename);
        if(!vertex_source.has_value()) {
            throw std::runtime_error{"Failed to open vertex shader file \"" + std::string{vertex_filename} + "\"."};
        }
        const auto fragment_source = get_file_content(fragment_filename);
        if(!fragment_source.has_value()) {
            throw std::runtime_error{"Failed to open fragment shader file \"" + std::string{fragment_filename} + "\"."};
        }
        load_from_memory(vertex_source.value(), fragment_source.value());
    }

    void Shader::load_from_file(const std::string_view vertex_filename, const std::string_view geometry_filename,
            const std::string_view fragment_filename) {
        const auto vertex_source = get_file_content(vertex_filename);
        if(!vertex_source.has_value()) {
            throw std::runtime_error{"Failed to open vertex shader file \"" + std::string{vertex_filename} + "\"."};
        }
        const auto geometry_source = get_file_content(geometry_filename);
        if(!geometry_source.has_value()) {
            throw std::runtime_error{"Failed to open geometry shader file \"" + std::string{geometry_filename} + "\"."};
        }
        const auto fragment_source = get_file_content(fragment_filename);
        if(!fragment_source.has_value()) {
            throw std::runtime_error{"Failed to open fragment shader file \"" + std::string{fragment_filename} + "\"."};
        }
        load_from_memory(vertex_source.value(), geometry_source.value(), fragment_source.value());
    }

    void Shader::load_from_memory(const std::string_view source, const ShaderType type) {
        switch(type) {
            case ShaderType::VERTEX: {
                compile(source.data(), nullptr, nullptr);
            }
            case ShaderType::GEOMETRY: {
                compile(nullptr, source.data(), nullptr);
            }
            case ShaderType::FRAGMENT: {
                compile(nullptr, nullptr, source.data());
            }
        }
    }

    void Shader::load_from_memory(const std::string_view vertex_source, const std::string_view fragment_source) {
        compile(vertex_source.data(), nullptr, fragment_source.data());
    }

    void Shader::load_from_memory(const std::string_view vertex_source, const std::string_view geometry_source,
            const std::string_view fragment_source) {
        compile(vertex_source.data(), geometry_source.data(), fragment_source.data());
    }

    unsigned int Shader::native_handle() const noexcept {
        return m_program;
    }

    void Shader::compile(const char* vertex_source, const char* geometry_source, const char* fragment_source) {
        std::lock_guard<std::mutex> mutex_lock{m_mutex};
        if(m_program != 0) {
            glDeleteProgram(m_program);
            m_program = 0;
        }
        unsigned int program = glCreateProgram();
        if(vertex_source != nullptr) {
            unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
            glCompileShader(vertex_shader);
            int success{};
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
            if(!success) {
                std::string message(1024, '\0');
                glGetShaderInfoLog(vertex_shader, 1024, nullptr, message.data());
                glDeleteShader(vertex_shader);
                glDeleteProgram(program);
                throw std::runtime_error{"Failed to compile vertex shader. Reason: " + std::string{message} + "\n"};
            }
            glAttachShader(program, vertex_shader);
            glDeleteShader(vertex_shader);
        }
        if(geometry_source != nullptr) {
            unsigned int geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry_shader, 1, &geometry_source, nullptr);
            glCompileShader(geometry_shader);
            int success{};
            glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &success);
            if(!success) {
                std::string message(1024, '\0');
                glGetShaderInfoLog(geometry_shader, 1024, nullptr, message.data());
                glDeleteShader(geometry_shader);
                glDeleteProgram(program);
                throw std::runtime_error{"Failed to compile geometry shader. Reason: " + std::string{message} + "\n"};
            }
            glAttachShader(program, geometry_shader);
            glDeleteShader(geometry_shader);
        }
        if(fragment_source != nullptr) {
            unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
            glCompileShader(fragment_shader);
            int success{};
            glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
            if(!success) {
                std::string message(1024, '\0');
                glGetShaderInfoLog(fragment_shader, 1024, nullptr, message.data());
                glDeleteShader(fragment_shader);
                glDeleteProgram(program);
                throw std::runtime_error{"Failed to compile fragment shader. Reason: " + std::string{message} + "\n"};
            }
            glAttachShader(program, fragment_shader);
            glDeleteShader(fragment_shader);
        }
        glLinkProgram(program);
        int success{};
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success) {
            std::string message(1024, '\0');
            glGetProgramInfoLog(program, 1024, nullptr, message.data());
            glDeleteProgram(program);
            throw std::runtime_error{"Failed to compile shader program. Reason: " + std::string{message} + "\n"};
        }
        m_program = program;
        glFlush();
    }

}
