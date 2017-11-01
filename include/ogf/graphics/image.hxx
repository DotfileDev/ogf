#pragma once

#include <string>
#include <tuple>
#include <vector>

#include <ogf/graphics/color.hxx>

namespace ogf {

    class Image {
    public:
        void load_from_file(const std::string_view filename);
        //void save_to_file(const std::string_view filename);

        void destroy();

        void set_pixel(const unsigned int x, const unsigned int y, const Color& color);
        Color pixel(const unsigned int x, const unsigned int y) const;

        std::tuple<unsigned int, unsigned int> size();

    private:
        std::vector<Uint8> m_pixels{};
        unsigned int       m_width{};
        unsigned int       m_height{};
    };

}
