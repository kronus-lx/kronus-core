#pragma once

// Enforce C++20 or newer
#if defined(_MSVC_LANG)
#if _MSVC_LANG < 202002L
#error "Compiler does not support C++20 or newer"
#endif
#else
#if __cplusplus < 202002L
#error "Compiler does not support C++20 or newer"
#endif
#endif

namespace fsystem {};

#include <string>
#include <concepts>
#include <filesystem>
#include <type_traits>

namespace fsystem {

	template<typename T>
	concept Traversable = requires(T t) {
		{ std::filesystem::path(t) };
	} || std::same_as<T, std::string> || std::same_as<T, const char*>;

	namespace storage::futils {
		class File;
		class Files;
	}
	namespace media::images {
		class RasterImage;
	}
}

#include "media/raster_image.hpp"
#include "futils/futils.hpp"
#include "storage/system_files.hpp"