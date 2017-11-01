#include <ogf/system/event.hxx>
#include <ogf/system/window.hxx>

int main() {
    ogf::Window window{};
    window.create("OGF Test", 800, 600);
    ogf::Event event{};
    while(window.is_open()) {
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
