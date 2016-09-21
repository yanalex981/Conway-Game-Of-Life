#include "Generation.hpp"

// neighbor counts around (x, y) are not affected by the state of life at cell (x, y)
void Generation::animate(long x, long y)
{
	if (isAliveAt(x, y)) return;

	alive.insert(std::make_tuple(x, y));

	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
		{
			if (i == 0 && j == 0) continue;

			if (neighbors.find(std::make_tuple(x + j, y + i)) == neighbors.end())
				neighbors.insert(std::make_pair<std::tuple<long, long>, size_t>(std::make_tuple(x + j, y + i), 1));
			else
				++neighbors.at(std::make_tuple(x + j, y + i)); // shouldn't ever exceed 8
		}
}

void Generation::kill(long x, long y)
{
	if (!isAliveAt(x, y)) return;

	alive.erase(std::make_tuple(x, y));

	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
		{
			if (i == 0 && j == 0) continue;

			--neighbors.at(std::make_tuple(x + j, y + i)); // shouldn't ever go below 0
		}
}

bool Generation::isAliveAt(long x, long y) const
{
	return alive.find(std::make_tuple(x, y)) != alive.end();
}

decltype(Generation::alive) Generation::getLiveOnes() const
{
	return alive;
}

decltype(Generation::neighbors) Generation::getNeighbors() const
{
	return neighbors;
}

void Generation::clear()
{
	alive.clear();
	neighbors.clear();
}
