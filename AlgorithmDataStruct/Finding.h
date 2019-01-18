#pragma once
#include "stdafx.h"
#include "ADTTree.h"

template<typename T>
class Finder
{
public:
	Finder() {};
	Finder(std::vector<T>& d) : data(d) {}

	~Finder() {};

	void SeqFinder(const T& value);

	void BinaryFinder(const T& value);

private:
	// data
	std::vector<T>& data;
};


template<typename T>
void Finder<T>::SeqFinder(const T& value)
{
	std::cout << "Seq finder: " << std::endl;
	int i = data.size()-1;
	while (data[i] != value && i >= 0)
	{
		--i;
	}
	std::cout << "Find out value at position of: " << i << std::endl;
}

template<typename T>
void Finder<T>::BinaryFinder(const T& value)
{
	std::cout << "binary finder: " << std::endl;
	int length = data.size();
	int mid = static_cast <int>(length / 2);

	for (int i = 0; i < length; ++i)
	{
		if (data[mid] > value)
		{
			length = mid;
			mid = static_cast <int>(length / 2);
		}
		else if (data[mid] < value)
		{
			i = mid;
			mid = mid + static_cast <int>((length- mid) / 2);
		}
		else
		{
			std::cout << "Find out value at position of: " << i << std::endl;
			break;
		}
	}
}