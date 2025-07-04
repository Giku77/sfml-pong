#pragma once

struct InputType {
	enum class Type { Keyboard, Mouse };
	Type type;
	int code = 0;

	bool operator==(const InputType& o) const {
		return type == o.type && code == o.code;
	}
};

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo {
	Axis axis;
	std::list<InputType> positivies; // 1.f
	std::list<InputType> negativies; // -1.f

	float senssi = 10.f;
	float value = 0.f;
};

class InputMgr
{
private:
	/*static std::list<sf::Keyboard::Key> downKeys;
	static std::list<sf::Keyboard::Key> heldKeys;
	static std::list<sf::Keyboard::Key> upKeys;*/

	static std::list<InputType> downKeys;
	static std::list<InputType> heldKeys;
	static std::list<InputType> upKeys;


	static std::unordered_map<Axis, AxisInfo> axisInfoMap;

	/*static sf::Mouse::Button downButton;
	static sf::Mouse::Button upButton;*/


public:
	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static bool GetKeyDown(InputType key);
	static bool GetKeyUp(InputType key);
	static bool GetKey(InputType key);

	static bool Contains(const std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key);
	static bool Contains(const std::list<InputType>& list, InputType key);
	static void Remove(std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key);
	static void Remove(std::list<InputType>& list, InputType key);

	static float GetAxisRaw(Axis axis);
	static float GetAxis(Axis axis);

	static bool GetMouseButtonDown(InputType key);
	static bool GetMouseButtonUp(InputType key);
	static bool GetMouseButton(InputType key);

	//static void ResetMosueButton();


	static sf::Vector2i GetMousePosition();
};

