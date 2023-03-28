#include <Arduino.h>

auto setup() -> void
{
	constexpr auto baud_rate = 9600uL;
	Serial.begin(baud_rate);
}

auto loop() -> void
{
	Serial.println("Hello, rain gauge ESP server world!");
	delay(1000uL);
}
