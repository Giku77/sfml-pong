#include "stdafx.h"
#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen;

void Utils::Init()
{
    gen.seed(rd());
}

float Utils::RandomValue()
{
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    return dist(gen);
}

int Utils::RandomRange(int min, int maxExclude)
{
    std::uniform_int_distribution<int> dist(min, maxExclude - 1);
	return dist(gen);
}

float Utils::RandomRange(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect rect)
{
    sf::Vector2f newOrigin(rect.width, rect.height);
    newOrigin.x *= ((int)preset % 3) * 0.5f;
    newOrigin.y *= ((int)preset / 3) * 0.5f;
    obj.setOrigin(newOrigin);
    return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

float Utils::Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;

    return value;
}

sf::Vector2f Utils::Clamp(const sf::Vector2f& value, const sf::Vector2f& min, const sf::Vector2f& max)
{
    return {
        Clamp(value.x, min.x, max.x),
        Clamp(value.y, min.y, max.y)
    };
}

float Utils::Clamp01(float value)
{
    return Clamp(value, 0.f, 1.f);
}

float Utils::Magitude(const sf::Vector2f& vec)
{
    return std::sqrtf(SqrMagitude(vec));
}

float Utils::SqrMagitude(const sf::Vector2f& vec)
{
    return vec.x * vec.x + vec.y + vec.y;
}

sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
{
    float mag = Magitude(vec);
    if (mag < std::numeric_limits<float>::epsilon()) return { 0.f, 0.f }; // 같은 0처럼 보여도 비트값의 차이로 인해서 부정확한 0이므로

    return vec / mag;
}

void Utils::Normalize(sf::Vector2f& vec)
{
    float mag = Magitude(vec);
    if (mag > std::numeric_limits<float>::epsilon()) {
        vec / mag;
    }
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return Magitude(p1 - p2);
}

float Utils::Lerp(float min, float max, float t, bool clamp)
{
    if (clamp) t = Clamp01(t);


    return min + (max - min) * t;
}

sf::Vector2f Utils::Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t, bool clamp)
{
    if (clamp) t = Clamp01(t);


    return min + (max - min) * t;
}


//sf::Color Utils::operator*(const sf::Color& color, float t)
//{
//    return sf::Color(
//        static_cast<sf::Uint8>(color.r * t),
//        static_cast<sf::Uint8>(color.g * t),
//        static_cast<sf::Uint8>(color.b * t),
//        static_cast<sf::Uint8>(color.a * t)
//    );
//}
//
//sf::Color Utils::operator+(const sf::Color& a, const sf::Color& b)
//{
//    return sf::Color(
//        static_cast<sf::Uint8>(a.r + b.r),
//        static_cast<sf::Uint8>(a.g + b.g),
//        static_cast<sf::Uint8>(a.b + b.b),
//        static_cast<sf::Uint8>(a.a + b.a)
//    );
//}
//
//sf::Color Utils::operator-(const sf::Color& a, const sf::Color& b)
//{
//    return sf::Color(
//        static_cast<sf::Uint8>(a.r - b.r),
//        static_cast<sf::Uint8>(a.g - b.g),
//        static_cast<sf::Uint8>(a.b - b.b),
//        static_cast<sf::Uint8>(a.a - b.a)
//    );
//}

sf::Color Utils::Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp)
{
    if (clamp) t = Clamp01(t);

    //return min + (max - min) * sf::Color(t);

    return sf::Color(
        (sf::Uint8)Lerp(min.r, max.r, t, clamp),
        (sf::Uint8)Lerp(min.g, max.g, t, clamp),
        (sf::Uint8)Lerp(min.b, max.b, t, clamp),
        (sf::Uint8)Lerp(min.a, max.a, t, clamp)
    );
}

