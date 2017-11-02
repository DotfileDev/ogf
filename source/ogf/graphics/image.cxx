#include <ogf/graphics/image.hxx>

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace ogf {

    void Image::load_from_file(const std::string_view filename) {
        free();
        int width{}, height{}, channels{};
	    auto data = stbi_load(filename.data(), &width, &height, &channels, 4);
        if(data == nullptr) {
            throw std::runtime_error{"Failed to open image \"" + std::string{filename} + "\"."};
        }
        m_pixels.resize(width * height * 4);
        std::copy(data, data + width * height * 4, m_pixels.begin());
        m_width = width;
        m_height = height;
        stbi_image_free(data);
    }

    void Image::free() {
        m_pixels.clear();
        m_width = 0;
        m_height = 0;
    }

    void Image::set_pixel(const unsigned int x, const unsigned int y, const Color& color) {
        m_pixels.at(x + y * m_width) = color.r;
        m_pixels[x + y * m_width + 1] = color.g;
        m_pixels[x + y * m_width + 2] = color.b;
        m_pixels[x + y * m_width + 3] = color.a;
    }

    Color Image::pixel(const unsigned int x, const unsigned int y) const {
        Color color{};
        color.r = m_pixels.at(x + y * m_width);
        color.g = m_pixels[x + y * m_width + 1];
        color.b = m_pixels[x + y * m_width + 2];
        color.a = m_pixels[x + y * m_width + 3];
        return color;
    }

    std::tuple<unsigned int, unsigned int> Image::size() {
        return std::make_tuple(m_width, m_height);
    }
  
}
