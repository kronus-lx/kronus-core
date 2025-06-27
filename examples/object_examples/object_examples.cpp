#include "Object.hpp"
#include "Matrix.hpp"
#include "Streams.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace types;
using namespace std::chrono;

auto main() -> int {

    // Create Object with vector<int> and lambda that counts even numbers
    Object<std::vector<int>, std::function<int(const std::vector<int>&)>> my_object(
        "even_counter",
        std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        [](const std::vector<int>& col) {
            int even_count = 0;
            std::for_each(col.begin(), col.end(), [&even_count](int v) {
                if (v % 2 == 0) {
                    even_count++;
                }
                });
            return even_count;
        }
    );

    // Run the operation and print result
    std::cout << "Number of even numbers: " << my_object.run() << "\n";

    Matrix<int> matrix_data = {
        {1,2,4,5},
        {1,3,5,6}
    };

    try {
        // Create test files with 5 lines each
        {
            StreamWriter writer1("test1.txt");
            StreamWriter writer2("test2.txt");
            StreamFutureManager fm;
            for (int i = 1; i <= 5; ++i) {
                fm.add_write_future(writer1.write("Line " + std::to_string(i) + " file 1"));
                fm.add_write_future(writer2.write("Line " + std::to_string(i) + " file 2"));
            }
            fm.wait_writes();
        }

        // Test concurrent reading with multiple StreamReaders
        StreamReader reader1("test1.txt");
        StreamReader reader2("test2.txt");
        StreamFutureManager fm;
        auto start = high_resolution_clock::now();

        // Launch 10 concurrent read operations (5 per file)
        for (int i = 0; i < 5; ++i) {
            fm.add_read_future(reader1.read());
            fm.add_read_future(reader2.read());
        }

        // Wait for all reads and filter out empty results
        auto results = fm.wait_reads();
        auto end = high_resolution_clock::now();

        // Print results
        for (size_t i = 0; i < results.size(); ++i) {
            if (!results[i].empty()) {
                std::cout << "Read " << i << ": " << results[i] << std::endl;
            }
        }

        // Print timing
        std::cout << "Time for concurrent reads: "
            << duration_cast<milliseconds>(end - start).count()
            << " ms" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

	return 0;
}