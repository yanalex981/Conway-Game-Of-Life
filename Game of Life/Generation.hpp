#ifndef SPACE_HPP
#define SPACE_HPP

#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>

namespace std {
	// change long long to long
	template <> struct hash<std::tuple<long, long>>
	{
		inline size_t operator()(const std::tuple<long, long> &t) const
		{
			return (51 + std::get<0>(t)) * 51 + std::get<1>(t);
		}
	};
}

class Generation
{
	std::unordered_set<std::tuple<long, long>> alive;
	std::unordered_map<std::tuple<long, long>, size_t> neighbors;

	std::vector<std::vector<bool>> space;

public:
	void clear();

	void animate(long x, long y);
	void kill(long x, long y);

	bool isAliveAt(long x, long y) const;

	decltype(alive) getLiveOnes() const;
	decltype(neighbors) getNeighbors() const;
};

#endif
