#pragma once

#include <string>

namespace ogf {

    class Image;

    class Texture {
    public:
        ~Texture();

        void load_from_file(const std::string_view filename);
        void load_from_image(const Image& image);   // TODO: Allow making textures from just a part of an image.

        // Remove texture from memory. Does nothing if texture doesn't exist.
        void free() noexcept;

        unsigned int native_handle() const noexcept;

    private:
        friend class Model;

        unsigned int m_texture{};   // Internal OpenGL texture handle.
        unsigned int m_width{};
        unsigned int m_height{};
    };

}
