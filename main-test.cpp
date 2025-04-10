#include "gtest/gtest.h"

void testTshirtSize();
void testTshirtSizeEdgeCases();
void testPrintColorMap();
void testGenerateColorMap();
void testWeatherReport();

TEST(TShirt, Size) {
    testTshirtSize();
    testTshirtSizeEdgeCases();
}

TEST(ColorMap, Print) {
    testPrintColorMap();
    testGenerateColorMap();
}

TEST(WeatherReport, Report) {
    testWeatherReport();
}
