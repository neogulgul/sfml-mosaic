#include "headers/App.hpp"

int colorDiff(sf::Color c1, sf::Color c2)
{
	return std::sqrt(
		std::pow(c1.r - c2.r, 2)
		+
		std::pow(c1.g - c2.g, 2)
		+
		std::pow(c1.b - c2.b, 2)
	);
}

int charToHexInt(char c)
{
	int i = (int)c;

	// numbers
	if (i >= '0' && i <= '9') { i -= '0'; }
	// uppercase letters
	if (i >= 'A' && i <= 'Z') { i -= 'A'; i += 10; }
	// lowercase letters
	if (i >= 'a' && i <= 'z') { i -= 'a'; i += 10; }

	return i;
}

sf::Color hexColor(std::string hexString)
{
	int r = -1, g = -1, b = -1, a = -1;

	if (hexString[0] == '#')
	{
		// alpha not specified
		if (hexString.size() == 7)
		{
			r = charToHexInt(hexString[1]) * 16 + charToHexInt(hexString[2]);
			g = charToHexInt(hexString[3]) * 16 + charToHexInt(hexString[4]);
			b = charToHexInt(hexString[5]) * 16 + charToHexInt(hexString[6]);
			a = 255;
		}
		// alpha specified
		else if (hexString.size() == 9)
		{
			r = charToHexInt(hexString[1]) * 16 + charToHexInt(hexString[2]);
			g = charToHexInt(hexString[3]) * 16 + charToHexInt(hexString[4]);
			b = charToHexInt(hexString[5]) * 16 + charToHexInt(hexString[6]);
			a = charToHexInt(hexString[7]) * 16 + charToHexInt(hexString[8]);
		}
	}

	if (r < 0 || r > 255) { r = 0; }
	if (g < 0 || g > 255) { g = 0; }
	if (b < 0 || b > 255) { b = 0; }
	if (a < 0 || a > 255) { a = 0; }

	return sf::Color(r, g, b, a);
}

sf::Color Black     = hexColor("#21252b");
sf::Color White     = hexColor("#d6d9df");
sf::Color Red       = hexColor("#d55a4d");
sf::Color Brown     = hexColor("#8e5236");
sf::Color Orange    = hexColor("#c7804f");
sf::Color Yellow    = hexColor("#dfbe6c");
sf::Color Green     = hexColor("#8ec379");
sf::Color Turquoise = hexColor("#26a69a");
sf::Color Cyan      = hexColor("#61adcb");
sf::Color Blue      = hexColor("#2a5cb9");
sf::Color Purple    = hexColor("#9373dd");
sf::Color Pink      = hexColor("#c678dd");

static const std::vector<sf::Color> mosaicColors = {
	Black,
	White,
	Red,
	Brown,
	Orange,
	Yellow,
	Green,
	Turquoise,
	Cyan,
	Blue,
	Purple,
	Pink
};

App::App(unsigned int targetFPS, sf::Vector2f viewSize, sf::Vector2u windowSize, std::string windowTitle, std::string imagePath)
: Root(targetFPS, viewSize, windowSize, windowTitle)
{
	_00Texture.loadFromFile("assets/textures/_00.jpg"); _00Sprite.setTexture(_00Texture); _00Sprite.setScale(1.f / _00Texture.getSize().x, 1.f / _00Texture.getSize().y);
	_01Texture.loadFromFile("assets/textures/_01.jpg"); _01Sprite.setTexture(_01Texture); _01Sprite.setScale(1.f / _01Texture.getSize().x, 1.f / _01Texture.getSize().y);
	_02Texture.loadFromFile("assets/textures/_02.jpg"); _02Sprite.setTexture(_02Texture); _02Sprite.setScale(1.f / _02Texture.getSize().x, 1.f / _02Texture.getSize().y);
	_03Texture.loadFromFile("assets/textures/_03.jpg"); _03Sprite.setTexture(_03Texture); _03Sprite.setScale(1.f / _03Texture.getSize().x, 1.f / _03Texture.getSize().y);
	_04Texture.loadFromFile("assets/textures/_04.jpg"); _04Sprite.setTexture(_04Texture); _04Sprite.setScale(1.f / _04Texture.getSize().x, 1.f / _04Texture.getSize().y);
	_05Texture.loadFromFile("assets/textures/_05.jpg"); _05Sprite.setTexture(_05Texture); _05Sprite.setScale(1.f / _05Texture.getSize().x, 1.f / _05Texture.getSize().y);
	_06Texture.loadFromFile("assets/textures/_06.jpg"); _06Sprite.setTexture(_06Texture); _06Sprite.setScale(1.f / _06Texture.getSize().x, 1.f / _06Texture.getSize().y);
	_07Texture.loadFromFile("assets/textures/_07.jpg"); _07Sprite.setTexture(_07Texture); _07Sprite.setScale(1.f / _07Texture.getSize().x, 1.f / _07Texture.getSize().y);
	_08Texture.loadFromFile("assets/textures/_08.jpg"); _08Sprite.setTexture(_08Texture); _08Sprite.setScale(1.f / _08Texture.getSize().x, 1.f / _08Texture.getSize().y);
	_09Texture.loadFromFile("assets/textures/_09.jpg"); _09Sprite.setTexture(_09Texture); _09Sprite.setScale(1.f / _09Texture.getSize().x, 1.f / _09Texture.getSize().y);
	_10Texture.loadFromFile("assets/textures/_10.jpg"); _10Sprite.setTexture(_10Texture); _10Sprite.setScale(1.f / _10Texture.getSize().x, 1.f / _10Texture.getSize().y);
	_11Texture.loadFromFile("assets/textures/_11.jpg"); _11Sprite.setTexture(_11Texture); _11Sprite.setScale(1.f / _11Texture.getSize().x, 1.f / _11Texture.getSize().y);

	imageTexture.loadFromFile(imagePath);
	imageSprite.setTexture(imageTexture);
	imageSprite.setScale(
		viewSize.x / imageTexture.getSize().x,
		viewSize.y / imageTexture.getSize().y
	);
	image = imageTexture.copyToImage();

	sf::Vector2f imageViewRatio(
		image.getSize().x / viewSize.x,
		image.getSize().y / viewSize.y
	);

	for (int x = 0; x < viewSize.x; x++)
	{
		compressedImagePixels.push_back({});
		mosaicPixels.push_back({});
		for (int y = 0; y < viewSize.y; y++)
		{
			sf::Color pixel = image.getPixel(
				std::floor((x / viewSize.x) * image.getSize().x),
				std::floor((y / viewSize.y) * image.getSize().y)
			);
			compressedImagePixels[x].push_back(pixel);

			int closestColorDiff = -1;
			sf::Color closestColor;

			for (sf::Color color : mosaicColors)
			{
				int currColorDiff = colorDiff(pixel, color);
				if (currColorDiff < closestColorDiff || closestColorDiff == -1)
				{
					closestColorDiff = currColorDiff;
					closestColor = color;
				}
			}

			mosaicPixels[x].push_back(closestColor);
		}
	}
}

void App::handleWindowEvents()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseWheelMoved:
				handleMouseWheelMoved(event);
				break;

			case sf::Event::TextEntered:
				handleTextEntered(event);
				break;
		}
	}
}

void App::handleMouseWheelMoved(sf::Event event)
{
	switch (event.mouseWheel.delta)
	{
		case MouseWheel::Forward:
			break;

		case MouseWheel::Backward:
			break;
	}
}

void App::handleTextEntered(sf::Event event)
{
	char character = static_cast<char>(event.text.unicode);
	// ...
}

void App::update()
{
	handlePress(pressing(screenshotKey), screenshotPress);
	if (screenshotPress.pressedThisFrame) { takeScreenshot = true; }

	handlePress(pressing(stateSpriteKey), stateSpritePress);
	if (stateSpritePress.pressedThisFrame) { state = State::Sprite; }

	handlePress(pressing(stateCompressedKey), stateCompressedPress);
	if (stateCompressedPress.pressedThisFrame) { state = State::Compressed; }

	handlePress(pressing(stateMosaicPixelatedKey), stateMosaicPixelatedPress);
	if (stateMosaicPixelatedPress.pressedThisFrame) { state = State::MosaicPixelated; }

	handlePress(pressing(stateMosaicKey), stateMosaicPress);
	if (stateMosaicPress.pressedThisFrame) { state = State::Mosaic; }
}

void App::draw()
{
	switch (state)
	{
		case State::Sprite:
			window.draw(imageSprite);
			break;
		case State::Compressed:
			drawCompressed();
			break;
		case State::MosaicPixelated:
			drawMosaicPixelated();
			break;
		case State::Mosaic:
			drawMosaic();
			break;
	}

	// text.draw("FPS: " + std::to_string(FPS), Start, Start, relativeViewPosition(&view, {1, 1}));
}

void App::drawCompressed()
{
	for (int x = 0; x < compressedImagePixels.size(); x++)
	{
		for (int y = 0; y < compressedImagePixels[0].size(); y++)
		{
			drawPixel({(float)x, (float)y}, compressedImagePixels[x][y]);
		}
	}
}

void App::drawMosaicPixelated()
{
	for (int x = 0; x < mosaicPixels.size(); x++)
	{
		for (int y = 0; y < mosaicPixels[0].size(); y++)
		{
			drawPixel({(float)x, (float)y}, mosaicPixels[x][y]);
		}
	}
}

void App::drawMosaic()
{
	for (int x = 0; x < mosaicPixels.size(); x++)
	{
		for (int y = 0; y < mosaicPixels[0].size(); y++)
		{
			sf::Color pixel = mosaicPixels[x][y];

			sf::Sprite* sprite;

			     if (pixel == mosaicColors[ 0]) { sprite = &_00Sprite; }
			else if (pixel == mosaicColors[ 1]) { sprite = &_01Sprite; }
			else if (pixel == mosaicColors[ 2]) { sprite = &_02Sprite; }
			else if (pixel == mosaicColors[ 3]) { sprite = &_03Sprite; }
			else if (pixel == mosaicColors[ 4]) { sprite = &_04Sprite; }
			else if (pixel == mosaicColors[ 5]) { sprite = &_05Sprite; }
			else if (pixel == mosaicColors[ 6]) { sprite = &_06Sprite; }
			else if (pixel == mosaicColors[ 7]) { sprite = &_07Sprite; }
			else if (pixel == mosaicColors[ 8]) { sprite = &_08Sprite; }
			else if (pixel == mosaicColors[ 9]) { sprite = &_09Sprite; }
			else if (pixel == mosaicColors[10]) { sprite = &_10Sprite; }
			else if (pixel == mosaicColors[11]) { sprite = &_11Sprite; }

			sprite->setPosition(x, y);
			window.draw(*sprite);
		}
	}
}
