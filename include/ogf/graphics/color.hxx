#pragma once

#include <ogf/types.hxx>

namespace ogf {

    class Color {
    public:
        // Create opaque black.
        constexpr Color() noexcept = default;

        // Create color from given values. Each color component should be in range [0.0f .. 1.0f].
        constexpr Color(const float r, const float g, const float b, const float a = 1.0f) noexcept;
        
        float r{0.0f};
        float g{0.0f};
        float b{0.0f};
        float a{1.0f};

        static const Color BLACK;
        static const Color WHITE;
    };

    constexpr Color::Color(const float r, const float g, const float b, const float a) noexcept
            : r{r}, g{g}, b{b}, a{a} {
    }

}
