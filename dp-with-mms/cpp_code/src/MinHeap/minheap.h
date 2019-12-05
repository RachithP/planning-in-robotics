#pragma once

#include <vector>
#include <iostream>

namespace fp
{
/*! \class MinHeap minHeap.h "src/MinHeap/minHeap.h"
 * \brief MinHeap class for creating a minHeap for Dijkstra or similar algorithms which uses key === location, value == weight/cost for search.
 *  \headerfile minHeap.h
 */
	class MinHeap
	{
		public:

			//! Constructor
			MinHeap(){}
			
			//! Member Functions
			bool empty();
			std::size_t size();
			void push(std::pair<unsigned char, double> element);
			std::pair<unsigned char, double> top();
			void qsort();
			void pop();

			//! Destructor
			~MinHeap(){}
		
		protected:
			std::vector<std::pair<unsigned char, double> > heap_;
		
	};

	class myComparator
	{
		public:
			bool operator()(std::pair<unsigned char, double> const& a, std::pair<unsigned char, double> const& b )
			{
				return (a.second > b.second);
			}
	};
	
	struct Comp
	{
		Comp(unsigned char const& s) : _s(s) { }

		bool operator() (std::pair<unsigned char, double> const& p)
		{
			return (p.first == _s);
		}

		unsigned char _s;
	};
}

