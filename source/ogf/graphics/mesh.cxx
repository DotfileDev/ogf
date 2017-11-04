#include <ogf/graphics/mesh.hxx>

#include <array>
#include <stdexcept>
#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader.h>

#include <ogf/utils/io_utils.hxx>

namespace ogf {

    void Mesh::load_from_file(const std::string_view filename) {
        const auto ext = get_file_extension(filename);
        if(ext == "obj") {
            load_obj(filename);
        } else {
            throw std::runtime_error{"Unknown model format: \"" + std::string{filename} + "\"."};
        }
    }

    void Mesh::load_obj(const std::string_view filename) {
        tinyobj::attrib_t attrib{};
        std::vector<tinyobj::shape_t> shapes{};
        std::string error_msg{};
        if (!tinyobj::LoadObj(&attrib, &shapes, nullptr, &error_msg, filename.data())) {
            throw std::runtime_error(error_msg);
        }
        std::unordered_map<Vertex3D, unsigned int> unique_vertices{};
        for (const auto& shape : shapes) {
            for(const auto& index : shape.mesh.indices) {
                Vertex3D vertex{};
                vertex.position.x = attrib.vertices[index.vertex_index * 3];
                vertex.position.y = attrib.vertices[index.vertex_index * 3 + 1];
                vertex.position.z = attrib.vertices[index.vertex_index * 3 + 2];
                if(attrib.texcoords.size() != 0) {
                    vertex.tex_coords.x = attrib.texcoords[index.texcoord_index * 2];
                    vertex.tex_coords.y = 1.0f - attrib.texcoords[index.texcoord_index * 2 + 1];
                }
                if(attrib.normals.size() != 0) {
                    vertex.normal.x = attrib.normals[index.normal_index * 3];
                    vertex.normal.y = attrib.normals[index.normal_index * 3 + 1];
                    vertex.normal.z = attrib.normals[index.normal_index * 3 + 2];
                }
                if(unique_vertices.count(vertex)) {
                    unique_vertices[vertex] = static_cast<uint32_t>(m_vertices.size());
                    m_vertices.push_back(vertex);
                }
                m_indices.push_back(unique_vertices[vertex]);
            }
        }
    }
    
}
