#include "electrical.hpp"

double math::electrical::calculateOhmsLaw(OHMS_LAW type, double input_1, double input_2)
{
	switch (type) {
		case OHMS_LAW::VOLTAGE:
			return input_1 * input_2;
		case OHMS_LAW::CURRENT: 
			return input_1 / input_2;
		case OHMS_LAW::RESISTANCE:
			return input_1 / input_2;
		default:
			return 0.0;
	}
}