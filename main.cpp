#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

// Состояния игры
enum class GameState { Splash, Menu };

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "Game", sf::Style::None);
    
    sf::Font font;
    if (!font.loadFromFile("JetBrainsMono-Regular.ttf")) {
        std::cerr << "Font not loaded!" << std::endl;
        return 1; 
    }

    // --- НАСТРОЙКА ЗАСТАВКИ ---
    sf::Text splashText;
    splashText.setFont(font);
    splashText.setString("Pixel Studio");
    splashText.setCharacterSize(60); // УМЕНЬШИЛИ ШРИФТ
    splashText.setFillColor(sf::Color(255, 255, 255, 0)); 

    sf::FloatRect bounds = splashText.getLocalBounds();
    splashText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    splashText.setPosition(desktop.width / 2.f, desktop.height / 2.f);

    // --- НАСТРОЙКА МЕНЮ ---
    Menu menu(font, window.getSize());

    GameState currentState = GameState::Splash;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) window.close();

            // Если мы в меню, передаем клики в Menu.cpp
            if (currentState == GameState::Menu) {
                int clickedButton = menu.handleInput(e, window);
                if (clickedButton != -1) {
                    std::cout << "Нажата кнопка номер: " << clickedButton << std::endl;
                    if (clickedButton == 5) { // Кнопка "Выйти"
                        window.close();
                    }
                }
            }
        }

        // Обновление логики
        if (currentState == GameState::Splash) {
            float t = clock.getElapsedTime().asSeconds();
            
            if (t < 2.f) { // Ждем 2 секунды
                splashText.setFillColor(sf::Color(255, 255, 255, 0));
            } else if (t < 4.f) { // Плавно появляемся
                float k = (t - 2.f) / 2.f;
                splashText.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(k * 255.f)));
            } else if (t < 6.f) { // Держим
                splashText.setFillColor(sf::Color::White);
            } else {
                // Время вышло — переключаемся на Меню!
                currentState = GameState::Menu;
            }
        } else if (currentState == GameState::Menu) {
            menu.update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }

        // Отрисовка
        window.clear(sf::Color::Black);
        
        if (currentState == GameState::Splash) {
            window.draw(splashText);
        } else if (currentState == GameState::Menu) {
            menu.draw(window);
        }
        
        window.display();
    }

    return 0;
}
