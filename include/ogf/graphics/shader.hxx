#pragma once

#include <mutex>
#include <string>

namespace ogf {

    enum class ShaderType {
        VERTEX, GEOMETRY, FRAGMENT
    };

    class Shader {
    public:
        Shader() noexcept = default;
        ~Shader();

        // Load shader of given type from a file.
        void load_from_file(const std::string_view filename, const ShaderType type);

        // Load vertex and fragment shaders from files.
        void load_from_file(const std::string_view vertex_filename, const std::string_view fragment_filename);

        // Load vertex, geometry and fragment shaders from files.
        void load_from_file(const std::string_view vertex_filename, const std::string_view geometry_filename,
                const std::string_view fragment_filename);

        // Load shader of given type from a memory.
        void load_from_memory(const std::string_view source, const ShaderType type);

        // Load vertex and fragment shaders from memory.
        void load_from_memory(const std::string_view vertex_source, const std::string_view fragment_source);

        // Load vertex, geometry and fragment shaders from memory.
        void load_from_memory(const std::string_view vertex_source, const std::string_view geometry_source,
                const std::string_view fragment_source);

        // Get the underlying OpenGL handle of the shader.
        unsigned int native_handle() const noexcept;

    private:
        void compile(const char* vertex_source, const char* geometry_source, const char* fragment_source);

        unsigned int m_program{0};
        std::mutex   m_mutex{};
    };

}
