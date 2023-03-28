#include <Arduino.h>
#include <ESP8266WiFi.h>

auto setUpSerial() -> void;
auto setUpWiFi() -> void;

auto setup() -> void
{
	setUpSerial();
	setUpWiFi();

	Serial.println("Hello, rain gauge ESP server world!");
}

auto loop() -> void {}

auto setUpSerial() -> void
{
	constexpr auto baudRate = 9600uL;
	Serial.begin(baudRate);
}

auto setUpWiFi() -> void
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
