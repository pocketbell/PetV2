#include "Critter.h"
#include <iostream>
#include <random>

Critter::Critter(int level)
{
	m_level = level; 
	m_minHealth = m_level * 10;
	m_maxHealth = m_level * 15;
	m_minStr = m_level * 1;
	m_maxStr = m_level * 2;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> healthRange(m_minHealth, m_maxHealth);
	std::uniform_int_distribution<> strRange(m_minStr, m_maxStr);
	m_health = healthRange(gen);
	m_str = strRange(gen);
}
void Critter::AdjustValue(Value value, void(*function)(int&, int), int modifier)
{
	switch (value)
	{
	case Critter::Value::Health: function(m_health, modifier); break;
	}
}
int Critter::GetValue(Value value)
{
	switch (value)
	{
	case Value::Level:		return m_level;
	case Value::Health:		return m_health;
	case Value::Str:		return m_str;
	case Value::MinHealth:		return m_minHealth;
	case Value::MaxHealth:		return m_maxHealth;
	case Value::MinStr:		return m_minStr;
	case Value::MaxStr:		return m_maxStr;
	}
}
