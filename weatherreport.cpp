#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

namespace WeatherSpace
{    
    class IWeatherSensor {
        public:
            virtual double TemperatureInC() const = 0;
            virtual int Precipitation() const = 0;
            virtual int Humidity() const = 0;
            virtual int WindSpeedKMPH() const = 0;
    };
    /// <summary>
    /// This is a stub for a weather sensor. For the sake of testing 
    /// we create a stub that generates weather data and allows us to
    /// test the other parts of this application in isolation
    /// without needing the actual Sensor during development
    /// </summary>
    class SensorStub : public IWeatherSensor {
        int Humidity() const override {
            return 72;
        }

        int Precipitation() const override {
            return 70;
        }

        double TemperatureInC() const override {
            return 26;
        }

        int WindSpeedKMPH() const override {
            return 52;
        }
    };

    class HighPrecipitationStub : public IWeatherSensor {
        int Humidity() const override {
            return 80; // Arbitrary value
        }

        int Precipitation() const override {
            return 70; // High precipitation (>60)
        }

        double TemperatureInC() const override {
            return 26; // Above 25°C
        }

        int WindSpeedKMPH() const override {
            return 40; // Low wind speed (<50)
        }
    };

    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        // precipitation < 20 is a sunny day
        string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25)
        {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }
    
    void TestRainy()
    {
        SensorStub sensor;
        string report = Report(sensor);
        cout << report << endl;
        assert(report.find("rain") != string::npos);
    }

    void TestHighPrecipitation()
    {
        // This instance of stub needs to be different-
        // to give high precipitation (>60) and low wind-speed (<50)
        HighPrecipitationStub sensor;

        // strengthen the assert to expose the bug
        // (function returns Sunny day, it should predict rain)
        string report = Report(sensor);
        assert(report.length() > 0);
        assert(report.find("rain") != string::npos);
    }
}

void testWeatherReport() {
    cout << "\nWeather report test\n";
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitation();
    cout << "All is well (maybe)\n";
}
