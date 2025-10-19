/**
 * @file Matrix.hpp
 * @brief Type definitions and concepts for matrix array types.
 * @author Joel Manning
 * @date June 2025
 *
 * This header-only library defines a `Matrix` type alias and associated concepts
 * for working with 2D matrix data structures in the `types` namespace. It uses
 * C++20 concepts to enforce type constraints for matrix operations.
 */

#pragma once

#if __cplusplus < 202002L && (!_MSVC_LANG || _MSVC_LANG < 202002L)
#error "Compiler does not support C++20 or newer"
#endif

#include <type_traits>
#include <vector>

 /**
  * @namespace types
  * @brief Namespace for modular, reusable C++ classes and utilities.
  *
  * The `types` namespace contains standalone classes, type aliases, and concepts
  * for generic and specific purposes, including data structures, functors, and
  * file I/O utilities designed for flexibility and type safety.
  */
namespace types {

	/**
	 * @brief Concept to constrain types to 2D matrix structures.
	 * @tparam T The type to check.
	 *
	 * The `MatrixType` concept ensures that a type `T` is a `std::vector` of
	 * `std::vector`s, where the inner vector’s `value_type` and `allocator_type`
	 * match those of `T`. This enforces that `T` represents a valid 2D matrix.
	 *
	 * @par Example
	 * @code
	 * static_assert(MatrixType<std::vector<std::vector<int>>>); // Valid
	 * static_assert(!MatrixType<std::vector<int>>); // Invalid
	 * @endcode
	 */
	template<typename T>
	concept MatrixType =
		std::is_same_v<T, std::vector<std::vector<typename T::value_type, typename T::allocator_type>>>;

	/**
	 * @brief Type alias for a 2D matrix.
	 * @tparam T The element type of the matrix (e.g., `int`, `double`).
	 *
	 * The `Matrix` type alias defines a 2D matrix as a `std::vector` of
	 * `std::vector<T>`, providing a convenient and flexible representation for
	 * matrix data structures.
	 *
	 * @par Example
	 * @code
	 * types::Matrix<int> mat = {{1, 2}, {3, 4}};
	 * @endcode
	 */
	template<typename T>
	using Matrix = std::vector<std::vector<T>>;

} // namespace types