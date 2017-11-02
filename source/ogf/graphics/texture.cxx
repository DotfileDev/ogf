#include <ogf/graphics/texture.hxx>

#include <glad/glad.h>

#include <ogf/graphics/image.hxx>

namespace ogf {

    Texture::~Texture() {
        free();
    }

    void Texture::load_from_file(const std::string_view filename) {
        Image image{};
        image.load_from_file(filename);
        load_from_image(image);
    }

    void Texture::load_from_image(const Image& image) {
        if(m_texture != 0) {
            free();
        }
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.m_width, image.m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                image.m_pixels.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        m_width = image.m_width;
        m_height = image.m_height;
    }

    void Texture::free() noexcept {
        if(m_texture == 0) {
            return;
        }
        glDeleteTextures(1, &m_texture);
        m_texture = 0;
    }

}
