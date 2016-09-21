#include <Windows.h>

#include <iostream>
#include <vector>

#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

#include <SFML\System\Clock.hpp>

#include "ConwayModel.hpp"

void render_buffer(ConwayModel &model, sf::RenderWindow &window)
{
	for (auto &v : model.getLiveOnes())
	{
		float rect_width = 6;
		float rect_height = 6;
		auto x = std::get<0>(v);
		auto y = std::get<1>(v);
		sf::RectangleShape rect(sf::Vector2f(rect_width, rect_height));
		rect.setPosition(x * rect_width, y * rect_height);
		rect.setFillColor(sf::Color(171, 220, 24));
		//rect.setOutlineColor(sf::Color(0, 0, 0, 0xFF));
		//rect.setOutlineThickness(1.0f);
		window.draw(rect);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(768, 768), "Conway's Game of Life!");
	ConwayModel model;
	sf::Clock clock;

	bool paused = true;

	model.animate(43, 43);
	model.animate(44, 43);
	model.animate(43, 44);
	model.animate(43, 45);
	model.animate(45, 45);
	model.animate(44, 46);
	model.animate(45, 46);

	model.animate(73, 73);
	model.animate(74, 73);
	model.animate(73, 74);
	model.animate(73, 75);
	model.animate(75, 75);
	model.animate(74, 76);
	model.animate(75, 76);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
					paused = !paused;

				if (event.key.code == sf::Keyboard::F)
					model.next();
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					auto p = sf::Mouse::getPosition(window);
					model.toggle(p.x / 6, p.y / 6);

					std::cout << p.x << ", " << p.y << std::endl;
				}
			}
		}

		window.clear();

		//clock.restart();
		render_buffer(model, window);
		
		if (!paused)
			model.next();
		//std::cout << "FT: " << clock.getElapsedTime().asMilliseconds() << std::endl;

		// draw mouse stuff
		auto p = sf::Mouse::getPosition(window);
		sf::RectangleShape hover(sf::Vector2f(6.0f, 6.0f));
		hover.setPosition(sf::Vector2f((p.x / 6) * 6.0f, (p.y / 6) * 6.0f));
		hover.setFillColor(sf::Color(0, 0, 0, 0));
		hover.setOutlineColor(sf::Color(0xFF, 0xFF, 0xFF, 0xFF));
		hover.setOutlineThickness(1.0f);
		window.draw(hover);

		window.display();

		//Sleep(100);
	}

	return 0;
}
