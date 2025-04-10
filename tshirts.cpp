#include <iostream>
#include <assert.h>

char size(int cms) {
    char sizeName = '\0';
    if(cms < 38) {
        sizeName = 'S';
    } else if(cms > 38 && cms < 42) {
        sizeName = 'M';
    } else if(cms > 42) {
        sizeName = 'L';
    }
    return sizeName;
}

void testTshirtSize() {
    std::cout << "\nTshirt size test\n";
    assert(size(37) == 'S');
    assert(size(40) == 'M');
    assert(size(43) == 'L');
    std::cout << "All is well (maybe!)\n";
}

void testTshirtSizeEdgeCases() {
    std::cout << "\nTshirt size edge cases test\n";
    // Boundary values
    assert(size(38) == 'M'); // Edge case: exactly 38
    assert(size(42) == 'L'); // Edge case: exactly 42

    std::cout << "Edge case tests passed\n";
}
