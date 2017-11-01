#pragma once

namespace ogf {

    class Shader;
    class Window;

    class Drawable {
    public:
        virtual ~Drawable() = default;

    private:
        friend class Window;

        // TODO: Introduce RenderTarget class, as you can draw not only to windows, but also to textures.
        virtual void draw(const Window& window, Shader& shader) const;
    };

}
