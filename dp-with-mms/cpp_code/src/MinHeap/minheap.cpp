#include "minheap.h"
#include <algorithm>
#include <iostream>

bool fp::MinHeap::empty()
{
	return heap_.empty();
}

std::size_t fp::MinHeap::size()
{
	return heap_.size();
}

void fp::MinHeap::push(std::pair<unsigned char, double> element)
{
	auto ref = std::find_if(heap_.begin(), heap_.end(), Comp(element.first));
	if( ref != heap_.end() ){
		ref->second = element.second;
	}
	else {
		heap_.push_back(element);
	}
	qsort();
}

std::pair<unsigned char, double> fp::MinHeap::top()
{
	return heap_.back();
}

void fp::MinHeap::pop()
{
	qsort();
	heap_.pop_back();
}

void fp::MinHeap::qsort()
{
	std::sort(heap_.begin(), heap_.end(), myComparator());
}