#pragma once
#include <iostream>
#include <random>

class Critter
{
public:
	enum class Value
	{
		Level,
		Health,
		Str,
		MinHealth,
		MaxHealth,
		MinStr,
		MaxStr
	};
private:
	int m_level{};
	int m_health{};
	int m_str{};
	int m_minHealth{};
	int m_maxHealth{};
	int m_minStr{};
	int m_maxStr{};
public:
	Critter(int level);
	void AdjustValue(Value value, void(*function)(int&, int), int modifier);
	int GetValue(Value value);
};