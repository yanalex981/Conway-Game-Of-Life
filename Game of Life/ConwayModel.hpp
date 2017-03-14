#ifndef CONWAY_MODEL_HPP
#define CONWAY_MODEL_HPP

#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>

namespace std {
	// change long long to long
	// needed because tuple<long,long> do not have a default hash implementation
	template <> struct hash<std::tuple<long, long>>
	{
		inline size_t operator()(const std::tuple<long, long> &t) const
		{
			return (51 + std::get<0>(t)) * 51 + std::get<1>(t);
		}
	};
}

// Model of the universe, stores all live cells
class ConwayModel
{
	std::unordered_set<std::tuple<long, long>> alive; // stores live cells
	std::unordered_map<std::tuple<long, long>, size_t> neighbors; // keeps track of neighboring cells of live cells

	ConwayModel next(ConwayModel &prev);

public:
	void next();

	void toggle(long x, long y);
	void animate(long x, long y);
	void kill(long x, long y);

	bool aliveAt(long x, long y) const;

	const decltype(alive) &getLiveOnes() const;
};

#endif
