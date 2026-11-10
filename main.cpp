#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

int main() {
    // Получаем разрешение экрана
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    
    // ВМЕСТО Fullscreen используем окно без рамок (None) на весь экран.
    // Это самый стабильный вариант для Winlator.
    sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "Pixel Studio", sf::Style::None);
    
    // Убрали setVerticalSyncEnabled(true) — в эмуляторах это часто вешает игру.

    // Ищем шрифт
    sf::Font font;
    std::vector<std::string> fontPaths = {
        "JetBrainsMono-Regular.ttf",
        "C:/windows/fonts/arial.ttf"
    };
    bool fontLoaded = false;
    for (const auto& p : fontPaths) {
        if (font.loadFromFile(p)) { fontLoaded = true; break; }
    }
    
    if (!fontLoaded) {
        std::cerr << "Font not loaded!" << std::endl;
        return 1; 
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Pixel Studio");
    title.setCharacterSize(90);
    title.setFillColor(sf::Color(255, 255, 255, 0)); 

    // Центрируем
    sf::FloatRect bounds = title.getLocalBounds();
    title.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    title.setPosition(desktop.width / 2.f, desktop.height / 2.f);

    sf::Clock clock;
    const float START_DELAY = 2.f; // 2 секунды тишины
    const float FADE_DUR    = 2.f; // 2 секунды появления
    const float HOLD_DUR    = 2.f; // 2 секунды держим

    std::cout << "Game started, loop begins..." << std::endl;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            // В Winlator сенсорный экран может эмулировать клик, 
            // добавим закрытие по клику, чтобы можно было выйти
            if (e.type == sf::Event::MouseButtonPressed) window.close(); 
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) window.close();
        }

        float t = clock.getElapsedTime().asSeconds();

        if (t >= START_DELAY + FADE_DUR + HOLD_DUR) {
            window.close();
            continue;
        }

        float alpha = 0.f;
        if (t < START_DELAY) {
            alpha = 0.f;
        } else if (t < START_DELAY + FADE_DUR) {
            float k = (t - START_DELAY) / FADE_DUR;
            alpha = k * 255.f;
        } else {
            alpha = 255.f;
        }

        title.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

        window.clear(sf::Color::Black);
        window.draw(title);
        window.display();
    }

    return 0;
}
