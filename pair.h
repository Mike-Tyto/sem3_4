#pragma once

#include <iostream>

template <typename T1, typename T2>
class Pair
{
public:
	T1 first;
	T2 last;
	Pair()
	    : first(T1())
	    , last(T2())
	{
	}

	Pair(const T1& val1, const T2& val2)
	    : first(val1)
	    , last(val2)
	{
	}

	Pair(const Pair<T1, T2>& other)
	    : first(other.first)
	    , last(other.last)
	{
	}

	~Pair()
	{
	}

	T1 GetFirst() const noexcept
	{
		return first;
	}

	T2 GetLast() const noexcept
	{
		return last;
	}

	Pair<T1, T2>& operator=(const Pair<T1, T2>& other)
	{
		this->first = other.first;
		this->last = other.last;

		return *this;
	}

	bool operator==(const Pair<T1, T2>& other) const
	{
		return first == other.first && last == other.last;
	}

	friend std::ostream& operator<<(std::ostream& os, const Pair<T1, T2>& pair)
	{
		os << "(";
		os << pair.first;
		os << ", ";
		os << pair.last;
		os << ")";
		return os;
	}
};