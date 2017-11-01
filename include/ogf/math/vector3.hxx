#pragma once

#include <cmath>

#include <type_traits>

namespace ogf {

    template<typename T>
    class Vector3 {
    public:
        // Create a Vector{0, 0, 0}.
        constexpr Vector3() noexcept = default;

        // Construct the vector from three values.
        constexpr Vector3(const T x, const T y, const T z) noexcept;

        // Construct the vector from another type of vector. This constructor doesn't replace copy constructor, because
        // it's only called when U != T.
        template<typename U>
        constexpr Vector3(const Vector3<U>& other) noexcept;

        // Get length of the vector. Only works for floating-point T.
        constexpr T length() const noexcept;

        // Get normalized vector. Only works for floating-point T.
        constexpr Vector3 normalize() const noexcept;

        T x{};
        T y{};
        T z{};
    };

    using Vector3I = Vector3<int>;
    using Vector3U = Vector3<unsigned int>;
    using Vector3F = Vector3<float>;
    using Vector3D = Vector3<double>;

    template<typename T>
    constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right) noexcept;

    template<typename T>
    constexpr bool operator<(const Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    constexpr bool operator>(const Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    constexpr bool operator<=(const Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    constexpr bool operator>=(const Vector3<T>& left, const Vector3<T>& right) noexcept;

    template<typename T>
    constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    constexpr Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    constexpr Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    constexpr Vector3<T> operator*(const Vector3<T>& left, const T value) noexcept;
    template<typename T>
    constexpr Vector3<T> operator/(const Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    constexpr Vector3<T> operator/(const Vector3<T>& left, const T value) noexcept;

    template<typename T>
    Vector3<T> operator+=(Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    Vector3<T> operator-=(Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    Vector3<T> operator*=(Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    Vector3<T> operator*=(Vector3<T>& left, const T value) noexcept;
    template<typename T>
    Vector3<T> operator/=(Vector3<T>& left, const Vector3<T>& right) noexcept;
    template<typename T>
    Vector3<T> operator/=(Vector3<T>& left, const T value) noexcept;

    // Implementation.
    
    template<typename T>
    constexpr Vector3<T>::Vector3(const T x, const T y, const T z) noexcept
            : x{x}, y{y}, z{z} {
    }

    template<typename T>
    template<typename U>
    constexpr Vector3<T>::Vector3(const Vector3<U>& other) noexcept
            : x{static_cast<T>(other.x)}, y{static_cast<T>(other.y)}, z{static_cast<T>(z)} {
    }

    template<typename T>
    constexpr T Vector3<T>::length() const noexcept {
        static_assert(std::is_floating_point<T>(), "T must be a floating-point type to get vector length.");
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
    }

    template<typename T>
    constexpr Vector3<T> Vector3<T>::normalize() const noexcept {
        static_assert(std::is_floating_point<T>(), "T must be a floating-point type to get vector length.");
        const auto l = length();
        return Vector3<T>{x / l, y / l, z / l};
    }

    template<typename T>
    constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left.x == right.x && left.y == right.y && left.z == right.z;
    }

    template<typename T>
    constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return !(left == right);
    }

    template<typename T>
    constexpr bool operator<(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left.x < right.x && left.y < right.y && left.z < right.z;
    }

    template<typename T>
    constexpr bool operator>(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left.x > right.x && left.y > right.y && left.z > right.z;
    }

    template<typename T>
    constexpr bool operator<=(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left.x <= right.x && left.y <= right.y && left.z <= right.z;
    }

    template<typename T>
    constexpr bool operator>=(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left.x >= right.x && left.y >= right.y && left.z >= right.z;
    }

    template<typename T>
    constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return Vector3<T>{left.x + right.x && left.y + right.y && left.z + right.z};
    }

    template<typename T>
    constexpr Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return Vector3<T>{left.x - right.x && left.y - right.y && left.z - right.z};
    }

    template<typename T>
    constexpr Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return Vector3<T>{left.x * right.x && left.y * right.y && left.z * right.z};
    }

    template<typename T>
    constexpr Vector3<T> operator*(const Vector3<T>& left, const T value) noexcept {
        return Vector3<T>{left.x * value && left.y * value && left.z * value};
    }

    template<typename T>
    constexpr Vector3<T> operator/(const Vector3<T>& left, const Vector3<T>& right) noexcept {
        return Vector3<T>{left.x / right.x && left.y / right.y && left.z / right.z};
    }

    template<typename T>
    constexpr Vector3<T> operator/(const Vector3<T>& left, const T value) noexcept {
        return Vector3<T>{left.x / value && left.y / value && left.z / value};
    }

    template<typename T>
    Vector3<T> operator+=(Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left = left + right;
    }

    template<typename T>
    Vector3<T> operator-=(Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left = left - right;
    }

    template<typename T>
    Vector3<T> operator*=(Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left = left * right;
    }

    template<typename T>
    Vector3<T> operator*=(Vector3<T>& left, const T value) noexcept {
        return left = left * value;
    }

    template<typename T>
    Vector3<T> operator/=(Vector3<T>& left, const Vector3<T>& right) noexcept {
        return left = left / right;
    }

    template<typename T>
    Vector3<T> operator/=(Vector3<T>& left, const T value) noexcept {
        return left = left / value;
    }

}
