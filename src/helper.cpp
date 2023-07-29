#include <SFML/Graphics.hpp>

#include "headers/helper.hpp"

float degToRad(float deg)
{
	return deg * (PI / 180);
}

float radToDeg(float rad)
{
	return rad * (180 / PI);
}

void toggle(bool &boolean)
{
	boolean = !boolean;
}

bool pressing(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool pressing(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

void handlePress(bool pressing, Press &press)
{
	press.pressedThisFrame = false;

	if (pressing)
	{
		if (!press.pressedLastFrame)
		{
			press.pressedLastFrame = true;
			press.pressedThisFrame = true;
		}
	}
	else
	{
		press.pressedLastFrame = false;
	}
}

std::string boolToString(bool boolean)
{
	return boolean ? "True" : "False";
}

std::string removeFromString(std::string string, int start, int range)
{
	std::string returnString;

	if (start < 0 || range < 0 || start + range > string.size()) { return "Error!"; } // invalid start and/or range

	for (int i = 0; i < string.size(); i++)
	{
		if (i >= start && i < start + range) { continue; }

		returnString += string[i];
	}

	return returnString;
}

std::string replaceStringSubstring(std::string string, std::string substring, std::string replacement)
{
	string.replace(string.find(substring), substring.size(), replacement);
	return string;
}

sf::Vector2f relativeViewPosition(sf::View* view, sf::Vector2f position)
{
	return {view->getCenter().x - view->getSize().x / 2 + position.x, view->getCenter().y - view->getSize().y / 2 + position.y};
}

sf::Vector2f align(sf::Vector2f size, Alignment horizontalAlignment, Alignment verticalAlignment, sf::Vector2f position)
{
	switch (horizontalAlignment)
	{
		case Start:
			position.x -= 0;
			break;

		case Center:
			position.x -= size.x / 2;
			break;

		case End:
			position.x -= size.x;
			break;
	}

	switch (verticalAlignment)
	{
		case Start:
			position.y -= 0;
			break;

		case Center:
			position.y -= size.y / 2;
			break;

		case End:
			position.y -= size.y;
			break;
	}

	return position;
}

bool isFile(std::string path)
{
	return fs::is_regular_file(path);
}

void createFile(std::string path)
{
	if (fs::is_directory(path))
	{
		fs::remove_all(path);
	}
	if (!isFile(path))
	{
		std::ofstream file(path);
		file.close();
	}
}

void createFolder(std::string path)
{
	if (isFile(path))
	{
		fs::remove(path);
	}
	if (!fs::is_directory(path))
	{
		fs::create_directory(path);
	}
}

void writeToFile(std::string path, std::string text)
{
	if (!isFile(path)) { createFile(path); }
	std::ofstream file(path);
	file << text;
	file.close();
}

std::string readFromFile(std::string path)
{
	std::stringstream ss;

	if (isFile(path))
	{
		std::ifstream file(path);
		while (file >> ss.rdbuf());
		file.close();
	}

	return ss.str();
}

float getTop   (sf::FloatRect rect) { return rect.top; }
float getBottom(sf::FloatRect rect) { return rect.top + rect.height; }
float getLeft  (sf::FloatRect rect) { return rect.left; }
float getRight (sf::FloatRect rect) { return rect.left + rect.width; }
