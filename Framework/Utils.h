#pragma once
#include <random>

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static void Init();

	// Random
	static float RandomValue(); // 0.0f ~ 1.0f
	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);

	// Math
	static float Clamp(float value, float min, float max);
	static sf::Vector2f Clamp(const sf::Vector2f& value, const sf::Vector2f& min, const sf::Vector2f& max);
	static float Clamp01(float value);

	static float Magitude(const sf::Vector2f& vec);
	static float SqrMagitude(const sf::Vector2f& vec);

	static sf::Vector2f GetNormal(const sf::Vector2f& vec);
	static void Normalize(sf::Vector2f& vec);

	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	static float Lerp(float min, float max, float t, bool clamp = true);
	static sf::Vector2f Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t, bool clamp = true);
	static sf::Color Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp = true);

	//static sf::Color operator*(const sf::Color& color, float t);
	//static sf::Color operator+(const sf::Color& a, const sf::Color& b);
	//static sf::Color operator-(const sf::Color& a, const sf::Color& b);
};


