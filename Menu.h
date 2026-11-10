#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(sf::Font& font, sf::Vector2u windowSize);
    
    // Возвращает индекс нажатой кнопки (0-5) или -1, если клика не было
    int handleInput(const sf::Event& event, sf::RenderWindow& window); 
    
    // Обновляет визуал (подсветка при наведении мыши)
    void update(sf::Vector2f mousePos);
    
    // Рисует меню
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::Text> m_buttons;
    sf::RectangleShape m_background;
};
