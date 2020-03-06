#include "SfmlRenderer.hpp"

namespace Eligos
{

    void SfmlRenderer::CreateWindow()
    {
        m_Window.create({1920, 1080}, "Window SFML", sf::Style::Default);
    }

    SfmlRenderer::SfmlRenderer() {};
 
    void SfmlRenderer::setWindowSize(unsigned int width, unsigned int height)
    {
        m_Window.setSize(sf::Vector2u{width, height});
        const sf::FloatRect NewView{0, 0, float(width), float(height)};
        m_Window.setView(sf::View{NewView});
    }

	void SfmlRenderer::setWindowFrameRate(unsigned int newFrameRate)
    {
        m_Window.setFramerateLimit(newFrameRate);
    }
    void SfmlRenderer::ClearScreen()
    {
        m_Window.clear(ClearColor);
    }
    void SfmlRenderer::setClearColor(int r, int g, int b)
    {
        ClearColor = {sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), 255};
    }
    void SfmlRenderer::Draw(Drawable::Object *Object)
    {
        using namespace Drawable;
        if (Object->m_Type == Object::TYPE::TEXT) {
            m_Window.draw(((Drawable::Text *)Object)->getText());
        } else if (Object->m_Type == Object::TYPE::SPRITE) {
            m_Window.draw(((Drawable::Sprite *)Object)->getSprite());
        }
    }
    void SfmlRenderer::Display(void)
    {
        m_Window.display();
    }
    bool SfmlRenderer::isClose(void)
    {
        sf::Event event;

        while(m_Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_Window.close();
                return true;
            }
        }
        return false;
    }
    Eligos::input_keys SfmlRenderer::getInput()
    {
        /* while (m_Window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space)
                    return input_keys::SPACE;
            }
        } */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                return input_keys::Q;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            return input_keys::DIAG_1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            return input_keys::DIAG_2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return input_keys::DIAG_3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            return input_keys::DIAG_4;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            return input_keys::W;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            return input_keys::E;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            return input_keys::A;            
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return input_keys::S;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            return input_keys::D;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            return input_keys::SPACE;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            return input_keys::UP;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            return input_keys::LEFT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            return input_keys::RIGHT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            return input_keys::DOWN;
        else
            return input_keys::UNKNOW;
        return input_keys::UNKNOW;
    }
} // namespace Eligos
