#include <iostream>
#include <assert.h>
#include <sstream>

std::pair<std::string, std::string> generateColorMap(int index) {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = index / 5;
    int j = index % 5;
    return {majorColor[i], minorColor[i]};
}

int printColorMap() {
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            int index = i * 5 + j;
            auto [majorColor, minorColor] = generateColorMap(index);
            std::cout << i * 5 + j << " | " << majorColor << " | " << minorColor << "\n";
        }
    }
    return i * j;
}

void testGenerateColorMap() {
    std::cout << "\nGenerate color map test\n";
    auto [majorColor, minorColor] = generateColorMap(4);
    std::cout <<majorColor   << " " << minorColor << "\n";
    assert(majorColor == "White" && minorColor == "Blue");
}

void testPrintColorMap() {
    std::cout << "\nPrint color map test\n";

    // Redirect output to a stringstream
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(outputStream.rdbuf());

    // Call printColorMap and capture its output
    int result = printColorMap();

    // Restore original std::cout buffer
    std::cout.rdbuf(originalCoutBuffer);

    // Split the captured output into lines
    std::istringstream inputStream(outputStream.str());
    std::string line;

    size_t previousMajorColumnStart = std::string::npos;
    size_t previousMinorColumnStart = std::string::npos;

    while (std::getline(inputStream, line)) {
        size_t majorColumnStart = line.find('|');
        size_t minorColumnStart = line.find('|', majorColumnStart + 1);

        // Ensure the major and minor columns are aligned across rows
        if (previousMajorColumnStart != std::string::npos) {
            assert(majorColumnStart == previousMajorColumnStart);
            assert(minorColumnStart == previousMinorColumnStart);
        }

        previousMajorColumnStart = majorColumnStart;
        previousMinorColumnStart = minorColumnStart;
    }

    // Ensure the total number of rows is correct
    assert(result == 25);

    std::cout << "Column alignment test passed\n";
}