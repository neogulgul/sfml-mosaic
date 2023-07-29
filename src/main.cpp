#include "headers/App.hpp"

#define targetFPS    60
#define viewWidth    128
#define viewHeight   128
#define windowWidth  1024
#define windowHeight 1024
#define windowTitle  "hello, world"

template <typename T>
bool includes(std::vector<T> v, T x)
{
	return std::find(v.begin(), v.end(), x) != v.end();
}

template <typename T>
void printVector(std::vector<T> v)
{
	std::cout << "[";
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v[i];
		if (i < v.size() - 1) { std::cout << ", "; }
	}
	std::cout << "]" << "\n";
}

std::vector<std::string> split(std::string s, char splitChar)
{
	std::vector<std::string> v;
	std::string currString = "";

	for (int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if (c == splitChar)
		{
			v.push_back(currString);
			currString = "";
		}
		else if (i == s.size() - 1)
		{
			currString.push_back(c);
			v.push_back(currString);
		}
		else
		{
			currString.push_back(c);
		}
	}

	return v;
}

std::vector<std::string> valid_image_formats = {"jpg", "png"};

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "Too few arguments. Need to specify image path." << "\n";
	} else if (argc > 2) {
		std::cout << "Too many arguments. Only need to specify image path." << "\n";
	}
	if (argc != 2) {
		std::cout << "Example: ./mosaic path/to/file" << "\n";
		return -1;
	}

	std::string image_path = argv[1];
	if (!isFile(image_path)) {
		std::cout << "File doesn't exist." << "\n";
		return -1;
	}

	std::vector<std::string> image_path_split = split(image_path, '.');
	std::string image_path_format = image_path_split.back();

	if(!includes(valid_image_formats, image_path_format))
	{
		std::cout << "Invalid image format. Valid formats: ";
		printVector(valid_image_formats);
		return -1;
	}

	App app(targetFPS, {viewWidth, viewHeight}, {windowWidth, windowHeight}, windowTitle, image_path);

	app.run();

	return 0;
}
