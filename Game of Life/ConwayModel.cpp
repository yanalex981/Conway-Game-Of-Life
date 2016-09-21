#include "ConwayModel.hpp"

// get rid of this. Seems like multiple allocations and moves are much slower than the naive approach...
ConwayModel ConwayModel::next(ConwayModel &prev)
{
	ConwayModel n;

	for (auto &v : alive)
	{
		size_t c = neighbors[v]; // should always exist

		if (c == 2 || c == 3)
			n.animate(std::get<0>(v), std::get<1>(v)); // make animate take a tuple vector
	}

	for (auto &pair : neighbors)
	{
		auto &v = std::get<0>(pair);

		if (!aliveAt(std::get<0>(v), std::get<1>(v)) && neighbors[v] == 3)
			n.animate(std::get<0>(v), std::get<1>(v));
	}

	return n;
}

void ConwayModel::next()
{
	*this = next(*this);
}

void ConwayModel::toggle(long x, long y)
{
	if (alive.find(std::make_tuple(x, y)) == alive.end())
		animate(x, y);
	else
		kill(x, y);
}

// neighbor counts around (x, y) are not affected by the state of life at cell (x, y)
void ConwayModel::animate(long x, long y)
{
	if (aliveAt(x, y)) return;

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

void ConwayModel::kill(long x, long y)
{
	if (!aliveAt(x, y)) return;

	alive.erase(std::make_tuple(x, y));

	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
		{
			if (i == 0 && j == 0) continue;

			--neighbors.at(std::make_tuple(x + j, y + i)); // shouldn't ever go below 0
		}
}

bool ConwayModel::aliveAt(long x, long y) const
{
	return alive.find(std::make_tuple(x, y)) != alive.end();
}

const decltype(ConwayModel::alive) &ConwayModel::getLiveOnes() const
{
	return alive;
}
