#pragma once

#include "Renderer.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

//sf::Event::Resized
//sf::FloatRec plop {0, 0, event.size.width, event.size.height}
//window.setView(sfView{plop});

namespace Eligos
{
    class SfmlRenderer : public RendererAPI
    {
    public:

        SfmlRenderer();
        virtual ~SfmlRenderer() = default;
    public:
        virtual void CreateWindow();
        virtual void setWindowSize(unsigned int width, unsigned int height);
        virtual void setWindowFrameRate(unsigned int width);
        virtual void ClearScreen();
        virtual void setClearColor(int r, int g, int b);
        virtual void Draw(Drawable::Object *);
        virtual void Display(void);
        virtual bool isClose(void);
        input_keys getInput();
        // virtual sf::RenderWindow &getWindow() const = 0;

    private :
        sf::RenderWindow m_Window;
        sf::Color ClearColor = sf::Color::Black;
    };
}