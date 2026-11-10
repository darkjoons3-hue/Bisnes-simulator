#include "Menu.h"
#include <iostream>

Menu::Menu(sf::Font& font, sf::Vector2u windowSize) {
    // Заглушка вместо фона (темно-серый цвет)
    m_background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    m_background.setFillColor(sf::Color(30, 30, 30)); 

    // Текст кнопок
    std::vector<std::string> labels = {
        "Начать новую игру",
        "Продолжить игру",
        "Достижения",
        "Настройки",
        "Титры",
        "Выйти"
    };

    float startY = windowSize.y / 2.f - (labels.size() * 50.f) / 2.f;

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(40); // Размер шрифта кнопок
        text.setFillColor(sf::Color::White);

        // Центрируем каждую кнопку
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        text.setPosition(windowSize.x / 2.f, startY + i * 60.f);

        m_buttons.push_back(text);
    }
}

void Menu::update(sf::Vector2f mousePos) {
    for (auto& button : m_buttons) {
        if (button.getGlobalBounds().contains(mousePos)) {
            button.setFillColor(sf::Color(0, 255, 255)); // Подсветка (голубой) при наведении
        } else {
            button.setFillColor(sf::Color::White);
        }
    }
}

int Menu::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // В Winlator координаты клика могут немного отличаться от десктопа, 
        // поэтому берем позицию мыши прямо из окна
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        
        for (size_t i = 0; i < m_buttons.size(); ++i) {
            if (m_buttons[i].getGlobalBounds().contains(mousePos)) {
                return i; // Возвращаем номер нажатой кнопки
            }
        }
    }
    return -1; // Ничего не нажато
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(m_background);
    for (const auto& button : m_buttons) {
        window.draw(button);
    }
}
