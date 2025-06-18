#pragma once

namespace math {

	struct Pythagoras {
		
		double opposite, adjacent;

		Pythagoras()
			: opposite(0), adjacent(0) {
		}
		Pythagoras (double hypotenuse, double opposite, double adjacent)
			: opposite(opposite), adjacent(adjacent){ }

		/**
		 * @brief Copy constructor
		 * @param other 
		 */
		Pythagoras(const Pythagoras& other) noexcept;

		/**
		 * @brief Delete assginment operator
		 * @param other 
		 * @return 
		 */
		Pythagoras& operator=(const Pythagoras& other) = delete;

		/**
		 * @brief hypotenuse calculation
		 * @return 
		 */
		double hypotenuse() noexcept;
	};
}