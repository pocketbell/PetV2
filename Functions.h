#pragma once

namespace Funct
{

	template <typename T>
	void MaxValue(T& base, T modifier)
	{
		(base > modifier) ? (base = modifier) : (base = base);
	}
	template <typename T>
	void MinValue(T& base, T modifier)
	{
		(base < modifier) ? (base = modifier) : (base = base);
	}
	template <typename T>
	void RaiseValue(T& base, T modifier)
	{
		base += modifier;
	}
	template <typename T>
	void LowerValue(T& base, T modifier)
	{
		base -= modifier;
	}
	template <typename T>
	void SetValue(T& base, T modifier)
	{
		base = modifier;
	}

}