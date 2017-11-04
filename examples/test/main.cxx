#include <ogf/graphics/mesh.hxx>
#include <ogf/system/event.hxx>
#include <ogf/system/window.hxx>
#include <ogf/math/vector2.hxx>
#include <ogf/math/vector3.hxx>

int main() {
    ogf::Window window{};
    window.create("OGF Test", 800, 600);

    ogf::Mesh mesh{};
    mesh.load_from_file("res/chalet.obj");

    while(window.is_open()) {
        ogf::Event event{};
        while(window.poll_event(event)) {
            if(event.type == ogf::EventType::CLOSED) {
                window.close();
            }
        }
        window.clear();
        window.swap_buffers();
    }
    return 0;
}
