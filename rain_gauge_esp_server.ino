#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "utilities.hpp"

using rainGaugeEspServer::fromJsonToString;

constexpr auto wiFiSsid = "";
constexpr auto wiFiPassword = "";

constexpr auto webServerPort = 80;

constexpr auto jsonDocumentSize = size_t(128);

auto webServer = ESP8266WebServer(webServerPort);


/// @brief Sets up the serial port.
auto setUpSerial() -> void;

/// @brief Sets up the Wi-Fi network connection.
auto setUpWiFi() -> void;

/// @brief Sets up the HTTP web server.
auto setUpWebServer() -> void;

/// @brief Handles an HTTP request to the web server.
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
	WiFi.begin(wiFiSsid, wiFiPassword);

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.printf("Connecting to Wi-Fi network \"%s\"...\n", wiFiSsid);
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
