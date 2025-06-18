#include "pythagoras.hpp"
#include <cmath>

math::Pythagoras::Pythagoras(const Pythagoras& other) noexcept
{
	opposite = other.opposite;
	adjacent = other.adjacent;
}

double math::Pythagoras::hypotenuse() noexcept
{
	return std::sqrt(opposite * opposite + adjacent * adjacent);
}
