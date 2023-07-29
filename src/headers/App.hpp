#pragma once

#include <SFML/Graphics.hpp>

#include "Root.hpp"

#define screenshotKey           keyboard::F1
#define stateSpriteKey          keyboard::Num1
#define stateCompressedKey      keyboard::Num2
#define stateMosaicPixelatedKey keyboard::Num3
#define stateMosaicKey          keyboard::Num4

struct App : Root
{
	Press screenshotPress;
	Press stateSpritePress;
	Press stateCompressedPress;
	Press stateMosaicPixelatedPress;
	Press stateMosaicPress;

	enum class State { Sprite, Compressed, MosaicPixelated, Mosaic };
	State state = State::Sprite;

	sf::Texture imageTexture;
	sf::Sprite imageSprite;
	sf::Image image;

	std::vector<std::vector<sf::Color>> compressedImagePixels;
	std::vector<std::vector<sf::Color>> mosaicPixels;

	sf::Texture _00Texture; sf::Sprite _00Sprite;
	sf::Texture _01Texture; sf::Sprite _01Sprite;
	sf::Texture _02Texture; sf::Sprite _02Sprite;
	sf::Texture _03Texture; sf::Sprite _03Sprite;
	sf::Texture _04Texture; sf::Sprite _04Sprite;
	sf::Texture _05Texture; sf::Sprite _05Sprite;
	sf::Texture _06Texture; sf::Sprite _06Sprite;
	sf::Texture _07Texture; sf::Sprite _07Sprite;
	sf::Texture _08Texture; sf::Sprite _08Sprite;
	sf::Texture _09Texture; sf::Sprite _09Sprite;
	sf::Texture _10Texture; sf::Sprite _10Sprite;
	sf::Texture _11Texture; sf::Sprite _11Sprite;

	App(unsigned int targetFPS, sf::Vector2f viewSize, sf::Vector2u windowSize, std::string windowTitle, std::string imagePath);

	virtual void handleWindowEvents();

	void handleMouseWheelMoved(sf::Event event);

	void handleTextEntered(sf::Event event);

	virtual void update();

	virtual void draw();

	void drawCompressed();

	void drawMosaicPixelated();

	void drawMosaic();
};
