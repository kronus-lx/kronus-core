#pragma once

#include <filesystem>
#include <vector>
#include <fstream>

namespace fs = std::filesystem;

namespace fsystem
{
	namespace futils
	{
		using char_buffer = std::vector<char>;
		
		template<Traversable T>
		bool fsystem_exists(const T& system_path) noexcept(false) {
			return fs::exists(system_path);
		}

		template<Traversable T>
		char_buffer fsystem_read_file(const T& file_path) noexcept(false) {
			std::ifstream file(file_path, std::ios::binary);
			if (!file) {
				throw std::runtime_error("Could not open file: " + std::string(file_path));
			}
			file.seekg(0, std::ios::end);
			std::streampos file_size = file.tellg();
			file.seekg(0, std::ios::beg);

			futils::char_buffer buffer(file_size);
			file.read(reinterpret_cast<char*>(buffer.data()), file_size);
			return buffer;
		}

		template<Traversable T>
		bool fsystem_is_directory(const T& dir_path) noexcept(false) {
			return fs::is_directory(dir_path);
		}

		template<Traversable T>
		bool fsystem_is_file(const T& file_path) noexcept(false) {
			return fs::is_regular_file(file_path);
		}

		template<Traversable T>
		bool fsystem_create_directory(const T& dir_path) noexcept(false) {
			try {
				fs::create_directory(dir_path);
				return true;
			}
			catch (const fs::filesystem_error& ex) {
				throw std::runtime_error(ex.what());
			}
			return false;
		}

		template<Traversable T>
		uintmax_t fsystem_remove(const T& path) noexcept(false) {
			try {
				if (!fs::exists(path)) {
					return false;
				}

				if (fs::is_directory(path)) {
					uintmax_t files_removed = fs::remove_all(path);
					return files_removed;
				}
				else {
					fs::remove(path);
					return (1);
				}
			}
			catch (const fs::filesystem_error& ex) {
				throw std::runtime_error(ex.what());
			}
		}

		template<Traversable T>
		bool fsystem_copy(const T& old_path, const T& new_path) noexcept(false) {
			try {
				if (!fs::exists(old_path)) return false;
				fs::copy_file(fs::path(old_path), fs::path(new_path));
				return true;
			}
			catch (const fs::filesystem_error& ex) {
				throw std::runtime_error(ex.what());
			}
		}
	}
}