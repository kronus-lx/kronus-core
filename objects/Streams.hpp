#pragma once
/**
 * @file Streams.hpp
 * @brief Asynchronous file I/O utilities for thread-safe reading and writing.
 * @author [Your Name]
 * @date June 2025
 *
 * This header defines classes and utilities in the `types` namespace for performing
 * asynchronous, thread-safe file operations using `std::async` and mutex-protected streams.
 * It includes `StreamWriter` for writing, `StreamReader` for reading, and `StreamFutureManager`
 * for managing asynchronous task futures.
 */


#if __cplusplus < 202002L && (!_MSVC_LANG || _MSVC_LANG < 202002L)
    #error "Compiler does not support C++20 or newer"
#endif

#include <fstream>
#include <stdexcept>
#include <future>
#include <functional>
#include <string>
#include <mutex>
#include <vector>

 /**
  * @namespace types
  * @brief Namespace for modular, reusable C++ classes and utilities.
  *
  * The `types` namespace contains standalone classes for generic and specific purposes,
  * including data structures, functors, and file I/O utilities designed for thread safety
  * and asynchronous operation.
  */
namespace types {

    /**
     * @brief Generic task template with a mutex for thread-safe operations.
     * @tparam T Placeholder type (currently unused, reserved for future extensions).
     */
    template<typename T>
    struct Task {
        /**
         * @brief Nested mutex structure for thread synchronization.
         */
        struct Mutex {
            using Mx = std::mutex; ///< Alias for the mutex type.
            Mx mx; ///< Mutex instance for locking.
        } task_mutex; ///< Mutex instance for task synchronization.
    };

    /**
     * @brief Asynchronous task utility for thread-safe file reading and writing.
     *
     * The `stream_task` struct provides methods for reading from and writing to file streams,
     * protected by a mutex to ensure thread safety. It inherits from `Task<void>` to utilize
     * its mutex.
     */
    struct stream_task : public Task<void> {
        /**
         * @brief Writes a message to an output file stream.
         * @param msg The message to write.
         * @param ofstream The output file stream to write to.
         *
         * Writes the message followed by a newline to the file stream, protected by a mutex
         * to prevent concurrent access. Does nothing if the stream is not open.
         */
        void write(const std::string& msg, std::ofstream& ofstream) {
            std::lock_guard<Mutex::Mx> lk(task_mutex.mx);
            if (ofstream.is_open()) {
                ofstream << msg << std::endl;
            }
        }

        /**
         * @brief Reads a line from an input file stream.
         * @param ifstream The input file stream to read from.
         * @return The line read, or an empty string if reading fails or the stream is closed.
         *
         * Reads a single line from the file stream, protected by a mutex to prevent concurrent
         * access. Returns an empty string if the stream is not open or no line is available.
         */
        std::string read(std::ifstream& ifstream) {
            std::lock_guard<Mutex::Mx> lk(task_mutex.mx);
            std::string line;
            if (ifstream.is_open() && std::getline(ifstream, line)) {
                return line;
            }
            return "";
        }
    };

    /**
     * @brief Non-singleton class for asynchronous, thread-safe file writing.
     *
     * The `StreamWriter` class provides methods to write messages to a file asynchronously
     * using `std::async`. It manages an output file stream and uses `stream_task` for
     * thread-safe writing operations.
     */
    class StreamWriter {
    private:
        std::ofstream file; ///< Output file stream for writing.
        stream_task task; ///< Task instance for thread-safe operations.

        /**
         * @brief Internal method to open a file.
         * @param fname The name of the file to open.
         * @throw std::runtime_error If the file cannot be opened.
         *
         * Opens the file if it is not already open, throwing an exception on failure.
         */
        void i_open(const char* fname) {
            if (!file.is_open()) {
                file.open(fname);
                if (!file.is_open()) {
                    throw std::runtime_error("[ERROR]: Cannot open File");
                }
            }
        }

    public:
        /**
         * @brief Constructs a StreamWriter and opens the specified file.
         * @param fname The name of the file to open.
         * @throw std::runtime_error If the file cannot be opened.
         */
        StreamWriter(const char* fname) {
            i_open(fname);
        }

        /**
         * @brief Destructor that closes the file stream.
         */
        ~StreamWriter() { close(); }

        /// @brief Copy constructor is deleted to prevent copying.
        StreamWriter(const StreamWriter&) = delete;
        /// @brief Copy assignment operator is deleted to prevent copying.
        StreamWriter& operator=(const StreamWriter&) = delete;

        /**
         * @brief Opens a new file for writing.
         * @param fname The name of the file to open.
         * @throw std::runtime_error If the file cannot be opened.
         */
        void open(const char* fname) {
            i_open(fname);
        }

        /**
         * @brief Closes the file stream if open.
         */
        void close() {
            if (file.is_open()) {
                file.close();
            }
        }

        /**
         * @brief Asynchronously writes a message to the file.
         * @param msg The message to write.
         * @return A future representing the asynchronous write operation.
         * @throw std::runtime_error If the async operation fails.
         *
         * Launches an asynchronous write operation using `std::async`, returning a future
         * to track completion. The actual write is performed by `stream_task::write`.
         */
        std::future<void> write(const std::string& msg) {
            try {
                return std::async(
                    std::launch::async,
                    [this, msg]() {
                        task.write(msg, file);
                    }
                );
            }
            catch (const std::exception& ex) {
                throw std::runtime_error(ex.what());
            }
        }
    };

    /**
     * @brief class for asynchronous, thread-safe file reading.
     *
     * The `StreamReader` class provides methods to read lines from a file asynchronously
     * using `std::async`. It manages an input file stream and uses `stream_task` for
     * thread-safe reading operations.
     */
    class StreamReader {
    private:
        std::ifstream file; ///< Input file stream for reading.
        stream_task task; ///< Task instance for thread-safe operations.

        /**
         * @brief Internal method to open a file.
         * @param fname The name of the file to open.
         * @throw std::runtime_error If the file cannot be opened.
         *
         * Opens the file if it is not already open, throwing an exception on failure.
         */
        void i_open(const char* fname) {
            if (!file.is_open()) {
                file.open(fname);
                if (!file.is_open()) {
                    throw std::runtime_error("[ERROR]: Cannot open File");
                }
            }
        }

    public:
        /**
         * @brief Constructs a StreamReader and opens the specified file.
         * @param fname The name of the file to open.
         * @throw std::runtime_error If the file cannot be opened.
         */
        StreamReader(const char* fname) {
            i_open(fname);
        }

        /**
         * @brief Destructor that closes the file stream.
         */
        ~StreamReader() { close(); }

        /// @brief Copy constructor is deleted to prevent copying.
        StreamReader(const StreamReader&) = delete;
        /// @brief Copy assignment operator is deleted to prevent copying.
        StreamReader& operator=(const StreamReader&) = delete;

        /**
         * @brief Opens a new file for reading.
         * @param fname The name of the file to open.
         * @throw std::runtime_error If the file cannot be opened.
         */
        void open(const char* fname) {
            i_open(fname);
        }

        /**
         * @brief Closes the file stream if open.
         */
        void close() {
            if (file.is_open()) {
                file.close();
            }
        }

        /**
         * @brief Asynchronously reads a line from the file.
         * @return A future containing the line read or an empty string if reading fails.
         * @throw std::runtime_error If the async operation fails.
         *
         * Launches an asynchronous read operation using `std::async`, returning a future
         * with the read line. The actual read is performed by `stream_task::read`.
         */
        std::future<std::string> read() {
            try {
                return std::async(
                    std::launch::async,
                    [this]() {
                        return task.read(file);
                    }
                );
            }
            catch (const std::exception& ex) {
                throw std::runtime_error(ex.what());
            }
        }
    };

    /**
     * @brief Utility for managing asynchronous file I/O futures.
     *
     * The `StreamFutureManager` struct manages collections of futures from `StreamReader`
     * and `StreamWriter` operations, allowing concurrent task execution and result collection.
     */
    struct StreamFutureManager {
        std::vector<std::future<std::string>> read_futures; ///< Futures for read operations.
        std::vector<std::future<void>> write_futures; ///< Futures for write operations.

        /**
         * @brief Adds a read future to the manager.
         * @param fut The future to add, representing an asynchronous read operation.
         */
        void add_read_future(std::future<std::string> fut) {
            read_futures.push_back(std::move(fut));
        }

        /**
         * @brief Adds a write future to the manager.
         * @param fut The future to add, representing an asynchronous write operation.
         */
        void add_write_future(std::future<void> fut) {
            write_futures.push_back(std::move(fut));
        }

        /**
         * @brief Waits for all read futures and returns their results.
         * @return A vector of strings containing the lines read.
         *
         * Waits for all valid read futures to complete, collects their results, and clears
         * the read futures list.
         */
        std::vector<std::string> wait_reads() {
            std::vector<std::string> results;
            for (auto& fut : read_futures) {
                if (fut.valid()) {
                    results.push_back(fut.get());
                }
            }
            read_futures.clear();
            return results;
        }

        /**
         * @brief Waits for all write futures to complete.
         *
         * Waits for all valid write futures to complete and clears the write futures list.
         */
        void wait_writes() {
            for (auto& fut : write_futures) {
                if (fut.valid()) {
                    fut.get();
                }
            }
            write_futures.clear();
        }

        /**
         * @brief Waits for all read and write futures to complete.
         *
         * Calls `wait_reads` and `wait_writes` to ensure all asynchronous operations are complete.
         */
        void wait_all() {
            wait_reads();
            wait_writes();
        }
    };

} // namespace types