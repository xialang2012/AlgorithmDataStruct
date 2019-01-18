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

	void Seqfinder(const T& value);

private:
	// data
	std::vector<T>& data;
};


template<typename T>
void Finder<T>::Seqfinder(const T& value)
{
	std::cout << "Seq finder: " << std::endl;
	int i = data.size()-1;
	while (data[i] != value && i >= 0)
	{
		--i;
	}
	std::cout << "Find out value at position of: " << i << std::endl;
}