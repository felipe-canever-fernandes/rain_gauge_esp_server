#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "utilities.hpp"

using rain_gauge_esp_server::fromJsonToString;

constexpr auto wiFiSSID = "";
constexpr auto wiFiPassword = "";

constexpr auto webServerPort = 80;

constexpr auto jsonDocumentSize = size_t(128);

auto webServer = ESP8266WebServer(webServerPort);

auto setUpSerial() -> void;
auto setUpWiFi() -> void;
auto setUpWebServer() -> void;

auto handleRequest() -> void;

auto setup() -> void
{
	setUpSerial();
	setUpWiFi();
	setUpWebServer();
}

auto loop() -> void
{
	webServer.handleClient();
}

auto setUpSerial() -> void
{
	constexpr auto baudRate = 9600uL;
	Serial.begin(baudRate);
}

auto setUpWiFi() -> void
{
	WiFi.begin(wiFiSSID, wiFiPassword);

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.printf("Connecting to Wi-Fi network \"%s\"...\n", wiFiSSID);
		delay(1000uL);
	}

	Serial.print("Connected to Wi-Fi network at ");
	Serial.print(WiFi.localIP());
	Serial.print(".\n");
}

auto setUpWebServer() -> void
{
	webServer.on("/", handleRequest);
	webServer.begin();

	Serial.print("Web server started at ");
	Serial.print(WiFi.localIP());
	Serial.printf(":%d.\n", webServerPort);
}

auto handleRequest() -> void
{
	auto const clientIPAddress = webServer.client().remoteIP();

	Serial.print("A request was made from ");
	Serial.print(clientIPAddress);
	Serial.print(".\n");

	auto json = StaticJsonDocument<jsonDocumentSize>();
	json["message"] = "Hello from the rain gauge ESP server!";

	webServer.send(200, "application/json", fromJsonToString(json));
}
