#include <gtest/gtest.h>
#include <gmock/gmock.h>

#if defined(ARDUINO)
#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    ::testing::InitGoogleMock();
}

void loop()
{
    // Run tests
    if (RUN_ALL_TESTS())
        ;
    // sleep for 1 sec
    delay(1000);
}

#else
int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    if (RUN_ALL_TESTS())
        ;

    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
#endif