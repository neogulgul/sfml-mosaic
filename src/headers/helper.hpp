#pragma once

#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

namespace fs = std::filesystem;

#define int_dist std::uniform_int_distribution<int>

const float PI = std::numbers::pi;

using keyboard = sf::Keyboard;
using    mouse = sf::Mouse;

struct Press
{
	bool pressedThisFrame = false;
	bool pressedLastFrame = false;
};

enum Alignment { Start, Center, End };

float degToRad(float deg);

float radToDeg(float rad);

void toggle(bool &boolean);

bool pressing(sf::Keyboard::Key key);

bool pressing(sf::Mouse::Button button);

void handlePress(bool pressing, Press &press);

std::string boolToString(bool boolean);

std::string removeFromString(std::string string, int start, int range);

std::string replaceStringSubstring(std::string string, std::string substring, std::string replacement = "");

sf::Vector2f relativeViewPosition(sf::View* view, sf::Vector2f position);

sf::Vector2f align(sf::Vector2f size, Alignment horizontalAlignment, Alignment verticalAlignment, sf::Vector2f position);

void createFile(std::string path);

void createFolder(std::string path);

void writeToFile(std::string path, std::string text);

bool isFile(std::string path);

std::string readFromFile(std::string path);

float getTop   (sf::FloatRect rect);
float getBottom(sf::FloatRect rect);
float getLeft  (sf::FloatRect rect);
float getRight (sf::FloatRect rect);

template <typename T>
void printVector2(sf::Vector2<T> v)
{
	std::cout << "x: " << v.x << ", y: " << v.y << "\n";
}
