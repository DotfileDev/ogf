#pragma once

#include <cmath>

#include <type_traits>

namespace ogf {

    template<typename T>
    class Vector2 {
    public:
        // Create a Vector{0, 0}.
        constexpr Vector2() noexcept = default;

        // Construct the vector from two values.
        constexpr Vector2(const T x, const T y) noexcept;

        // Construct the vector from another type of vector. This constructor doesn't replace copy constructor, because
        // it's only called when U != T.
        template<typename U>
        constexpr Vector2(const Vector2<U>& other) noexcept;

        // Get length of the vector. Only works for floating-point T.
        constexpr T length() const noexcept;

        // Get normalized vector. Only works for floating-point T.
        constexpr Vector2 normalize() const noexcept;

        T x{};
        T y{};
    };

    using Vector2I = Vector2<int>;
    using Vector2U = Vector2<unsigned int>;
    using Vector2F = Vector2<float>;
    using Vector2D = Vector2<double>;

    template<typename T>
    constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right) noexcept;

    template<typename T>
    constexpr bool operator<(const Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    constexpr bool operator>(const Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    constexpr bool operator<=(const Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    constexpr bool operator>=(const Vector2<T>& left, const Vector2<T>& right) noexcept;

    template<typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    constexpr Vector2<T> operator*(const Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    constexpr Vector2<T> operator*(const Vector2<T>& left, const T value) noexcept;
    template<typename T>
    constexpr Vector2<T> operator/(const Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    constexpr Vector2<T> operator/(const Vector2<T>& left, const T value) noexcept;

    template<typename T>
    Vector2<T> operator+=(Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    Vector2<T> operator-=(Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    Vector2<T> operator*=(Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    Vector2<T> operator*=(Vector2<T>& left, const T value) noexcept;
    template<typename T>
    Vector2<T> operator/=(Vector2<T>& left, const Vector2<T>& right) noexcept;
    template<typename T>
    Vector2<T> operator/=(Vector2<T>& left, const T value) noexcept;

    // Implementation.

    template<typename T>
    constexpr Vector2<T>::Vector2(const T x, const T y) noexcept
            : x{x}, y{y} {
    }

    template<typename T>
    template<typename U>
    constexpr Vector2<T>::Vector2(const Vector2<U>& other) noexcept
            : x{static_cast<T>(other.x)}, y{static_cast<T>(other.y)} {
    }

    template<typename T>
    constexpr T Vector2<T>::length() const noexcept {
        static_assert(std::is_floating_point<T>(), "T must be a floating-point type to get vector length.");
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    template<typename T>
    constexpr Vector2<T> Vector2<T>::normalize() const noexcept {
        static_assert(std::is_floating_point<T>(), "T must be a floating-point type to get normalized vector.");
        constexpr auto l = length();
        return {x / l, y / l};
    }

    template<typename T>
    constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return left.x == right.x && left.y == right.y;        
    }

    template<typename T>
    constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return !(left == right);
    }

    template<typename T>
    constexpr bool operator<(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return left.x < right.y && left.y < right.y;
    }

    template<typename T>
    constexpr bool operator>(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return left.x > right.y && left.y > right.y;
    }

    template<typename T>
    constexpr bool operator<=(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return left.x <= right.y && left.y <= right.y;
    }

    template<typename T>
    constexpr bool operator>=(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return left.x >= right.y && left.y >= right.y;
    }

    template<typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return {left.x + right.x, left.y * right.y};
    }

    template<typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return {left.x - right.x, left.y * right.y};
    }

    template<typename T>
    constexpr Vector2<T> operator*(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return {left.x * right.x, left.y * right.y};
    }

    template<typename T>
    constexpr Vector2<T> operator*(const Vector2<T>& left, const T value) noexcept {
        return {left.x * value, left.y * value};
    }

    template<typename T>
    constexpr Vector2<T> operator/(const Vector2<T>& left, const Vector2<T>& right) noexcept {
        return {left.x / right.x, left.y * right.y};
    }

    template<typename T>
    constexpr Vector2<T> operator/(const Vector2<T>& left, const T value) noexcept {
        return {left.x / value, left.y / value};
    }

    template<typename T>
    Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right) noexcept {
        left.x = left.x + right.x;
        left.y = left.y + right.y;
        return left;
    }

    template<typename T>
    Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right) noexcept {
        left.x = left.x - right.x;
        left.y = left.y - right.y;
        return left;
    }

    template<typename T>
    Vector2<T>& operator*=(Vector2<T>& left, const Vector2<T>& right) noexcept {
        left.x = left.x * right.x;
        left.y = left.y * right.y;
        return left;
    }

    template<typename T>
    Vector2<T>& operator*=(Vector2<T>& left, const T value) noexcept {
        left.x = left.x * value;
        left.y = left.y * value;
        return left;
    }

    template<typename T>
    Vector2<T>& operator/=(Vector2<T>& left, const Vector2<T>& right) noexcept {
        left.x = left.x / right.x;
        left.y = left.y / right.y;
        return left;
    }

    template<typename T>
    Vector2<T>& operator/=(Vector2<T>& left, const T value) noexcept {
        left.x = left.x / value;
        left.y = left.y / value;
        return left;
    }

}
