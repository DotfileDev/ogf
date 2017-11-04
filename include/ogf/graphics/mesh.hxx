#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <ogf/graphics/vertex3d.hxx>
#include <ogf/types.hxx>

namespace ogf {

    // Supported formats are: ASCII OBJ.
    // NOTE: Doesn't support animation yet.
    // NOTE: Doesn't support materials yet.
    class Mesh {
    public:
        // Optimization means vertex deduplication.
        void load_from_file(const std::string_view filename);

    private:
        void load_obj(const std::string_view filename);
        
        std::vector<Vertex3D> m_vertices;
        std::vector<Uint32>   m_indices;
    };

}
