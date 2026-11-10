#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

int main() {
    // Полноэкранный режим под текущий дисплей (в Winlator берёт разрешение контейнера)
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Pixel Studio", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    // Пытаемся найти шрифт по нескольким путям (сначала рядом с exe, потом системные)
    sf::Font font;
    std::vector<std::string> fontPaths = {
        "JetBrainsMono-Regular.ttf",
        "arial.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    };
    bool fontLoaded = false;
    for (const auto& p : fontPaths) {
        if (font.loadFromFile(p)) { fontLoaded = true; break; }
    }
    if (!fontLoaded) {
        // Если шрифта нет — просто черный экран и выход, чтобы не падать
        sf::sleep(sf::seconds(2.f));
        return 1;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Pixel Studio");
    title.setCharacterSize(90);
    title.setFillColor(sf::Color(255, 255, 255, 0)); // начинаем с alpha = 0

    // Центрируем по экрану
    sf::FloatRect bounds = title.getLocalBounds();
    title.setOrigin(bounds.left + bounds.width / 2.f,
                    bounds.top + bounds.height / 2.f);
    title.setPosition(desktop.width / 2.f, desktop.height / 2.f);

    sf::Clock clock;
    const float START_DELAY = 2.f; // 2 секунды тишины
    const float FADE_DUR    = 2.f; // 2 секунды плавного появления
    const float HOLD_DUR    = 2.f; // 2 секунды держим на экране

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            if (e.type == sf::Event::KeyPressed &&
                e.key.code == sf::Keyboard::Escape) window.close();
        }

        float t = clock.getElapsedTime().asSeconds();

        // По истечении таймлайна закрываем окно
        if (t >= START_DELAY + FADE_DUR + HOLD_DUR) {
            window.close();
            continue;
        }

        // Считаем прозрачность надписи
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
