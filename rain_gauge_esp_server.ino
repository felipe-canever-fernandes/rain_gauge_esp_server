#include <Arduino.h>
#include <ESP8266WiFi.h>

auto set_up_serial() -> void;
auto set_up_wi_fi() -> void;

auto setup() -> void
{
	set_up_serial();
	set_up_wi_fi();

	Serial.println("Hello, rain gauge ESP server world!");
}

auto loop() -> void {}

auto set_up_serial() -> void
{
	constexpr auto baud_rate = 9600uL;
	Serial.begin(baud_rate);
}

auto set_up_wi_fi() -> void
{
	constexpr auto ssid = "Felipe's Galaxy S20+";
	constexpr auto password = "esgv1755";

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.printf("Connecting to Wi-Fi network \"%s\"...\n", ssid);
		delay(1000uL);
	}

	Serial.print("Connected to Wi-Fi network at ");
	Serial.print(WiFi.localIP());
	Serial.print(".\n");
}
