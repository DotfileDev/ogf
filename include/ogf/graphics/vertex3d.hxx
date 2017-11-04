#pragma once

#include <ogf/math/vector2.hxx>
#include <ogf/math/vector3.hxx>

namespace ogf {

    struct Vertex3D {
        Vector3F position;
        Vector2F tex_coords;
        Vector3F normal;
    };

    bool operator==(const Vertex3D& left, const Vertex3D& right) {
        return left.position == right.position && left.tex_coords == right.tex_coords && left.normal == right.normal;
    }

    bool operator!=(const Vertex3D& left, const Vertex3D& right) {
        return !(left == right);
    }

}

// This solution is recommended by a cppreference.com: http://en.cppreference.com/w/cpp/utility/hash
namespace std {

    template<>
    struct hash<ogf::Vertex3D> {
        size_t operator()(const ogf::Vertex3D& vertex) const {
            return hash<ogf::Vector3F>{}(vertex.position)
                    ^ (hash<ogf::Vector2F>{}(vertex.tex_coords) << 1) >> 1
                    ^ (hash<ogf::Vector3F>{}(vertex.normal) << 1);
        }
    };

}
