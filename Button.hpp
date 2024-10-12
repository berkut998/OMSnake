#pragma once
#include "IGameObject.hpp"
#include <functional>

class Button:public IGameObject
{
public:
    bool visible = true;
    enum class AlignVertical
    {
        top,
        bottom,
        center
    };
    enum class AlignHorizontal
    {
        left,
        right,
        center
    };
    Button();
    Button(sf::RenderWindow *_window);
    Button(sf::RenderWindow *_window, sf::Font* font, std::string text);
    ~Button();
    void setOnClickFunction(std::function<void()> callBackFunc);
    void click();
    void setText(std::string text);
    //void setFont(std::string patjToFont); not need
    void setTextColor (sf::Color textColor);
    void setTextSize (unsigned int textSize);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void alignText(AlignHorizontal horiz, AlignVertical vert);
    void setButtonFillColor(sf::Color buttonFillColor);
    void setButtonOutlineColor(sf::Color buttonOutlineColor);
    sf::Vector2f getSize();
    void handleEvent(sf::Event *event) override;
    void draw(sf::RenderWindow *window) override;


private:
    std::function<void()> clickButtonfunc = nullptr;
    sf::Text btnText;
    sf::RectangleShape btnShape;
    sf::Font* font = nullptr;
    AlignVertical alignVert = AlignVertical::top;
    AlignHorizontal alignHoriz = AlignHorizontal::left;
    sf::RenderWindow *window;
};


    Button::Button(sf::RenderWindow *_window , sf::Font* _font, std::string _text){
        window = _window;
        font = _font;
        btnShape = sf::RectangleShape(sf::Vector2f(120,40));
        btnShape.setFillColor(sf::Color::Red);
        btnText.setFont(*font);
        btnText.setFillColor(sf::Color::White);
        btnText.setString(_text);
        btnText.setCharacterSize(14);

    };

    Button::Button(sf::RenderWindow *_window){
        window = _window;
        btnShape = sf::RectangleShape(sf::Vector2f(60,40));
        btnText.setString("Button");
        btnText.setCharacterSize(14);

    };
    Button::Button(){};
    Button::~Button(){};

    void Button::setOnClickFunction(std::function<void()> callBackFunc)
    {
        clickButtonfunc = callBackFunc;
    }

    void Button::click()
    {
        if (clickButtonfunc != nullptr)
            clickButtonfunc();
    }

    // not need until
    // void Button::setFont(std::string pathToFont)
    // {
    //     font.loadFromFile(pathToFont);
    //     btnText.setFont(font);
    // }

    void Button::setText(std::string text)
    {
        btnText.setString(text);
        alignText(alignHoriz,alignVert);
    }
    void Button::setPosition(sf::Vector2f position)
    {
        btnShape.setPosition(position);
        alignText(alignHoriz,alignVert);
    }
    void Button::setSize(sf::Vector2f size)
    {
        btnShape.setSize(size);
        alignText(alignHoriz,alignVert);
    }
    
    void Button::alignText(AlignHorizontal horiz,AlignVertical vert)
    {
        sf::Vector2f position;
        sf::FloatRect btnRect =  btnShape.getGlobalBounds();
         sf::FloatRect textBound =  btnText.getGlobalBounds();
        switch (horiz)
        {
        case AlignHorizontal::left:
            position.x = btnRect.left;
            break;
        case AlignHorizontal::right:
            position.x = btnRect.left + btnRect.width;
            break;
        case AlignHorizontal::center:
            position.x = btnRect.left + btnRect.width/2-textBound.width/2;
            break;
        default:
            position.x = btnRect.left;
            break;
        }
        switch (vert)
        {
        case AlignVertical::top:
            position.y = btnRect.top;
            break;
        case AlignVertical::center:
            position.y = btnRect.top + btnRect.height/2-textBound.height;
            break;
        case AlignVertical::bottom:
            position.y = btnRect.top + btnRect.height;
            break;
        default:
            position.y = btnRect.top;
            break;
        }
        alignHoriz = horiz;
        alignVert = vert;
        btnText.setPosition(position);
    }

    void Button::setTextColor(sf::Color textColor)
    {
        btnText.setFillColor(textColor);
    }

     void Button::setTextSize (unsigned int textSize)
     {
        btnText.setCharacterSize(textSize);
     }
    void  Button::setButtonFillColor(sf::Color buttonFillColor)
    {
        btnShape.setFillColor(buttonFillColor);
    }

    void  Button::setButtonOutlineColor(sf::Color buttonOutlineColor)
    {
        btnShape.setOutlineColor(buttonOutlineColor);
    }

    sf::Vector2f Button::getSize ()
    {
        return btnShape.getSize();
    }
    
    void Button::handleEvent(sf::Event *event)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && visible)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePositionFloat = sf::Vector2f{mousePosition.x,mousePosition.y};
            sf::FloatRect glob = btnShape.getGlobalBounds();
            sf::Vector2f btnPos = btnShape.getPosition();
            sf::FloatRect local = btnShape.getLocalBounds();
            if (btnShape.getGlobalBounds().contains(mousePositionFloat))
                click();
        }
    }
    void Button::draw(sf::RenderWindow *window)
    {
        if (visible)
        {
            window->draw(btnShape);
            window->draw(btnText);     
        }
            
    }
    