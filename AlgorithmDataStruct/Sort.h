#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

template<typename T>
int partition(std::vector<T> &vec, int low, int high)
{
	T pivot = vec[low];
	while (low < high)
	{
		// high value
		while (high > low && pivot <= vec[high])
			high--;
		vec[low] = vec[high];

		// low value
		while (low < high && pivot >= vec[low])
			low++;
		vec[high] = vec[low];

	}
	// set the mid position value to pivot
	// low == high
	vec[low] = pivot;

	return low;
}

template<typename T>
bool quickSort(std::vector<T> &vec)
{
	int low = 0;
	int high = vec.size()-1;
	if (high <= low) return false;

	std::stack<int> s;
	int mid = partition<T>(vec, low, high);
	if (low < (mid - 1))
	{
		s.push(low);
		s.push(mid - 1);
	}
	if ((mid + 1) < (high - 1))
	{
		s.push(mid + 1);
		s.push(high - 1);
	}

	while (!s.empty())
	{
		int high_new = s.top();
		s.pop();
		int low_new = s.top();
		s.pop();
		int mid_new = partition(vec, low_new, high_new);
		if (low_new < mid_new - 1) {
			s.push(low_new);
			s.push(mid_new - 1);
		}
		if (mid_new + 1 < high_new) {
			s.push(mid_new + 1);
			s.push(high_new);
		}
	}

	return true;
}
