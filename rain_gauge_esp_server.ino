#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

constexpr auto wiFiSSID = "";
constexpr auto wiFiPassword = "";

constexpr auto webServerPort = 80;

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

	Serial.printf("Web server started on port %d.\n", webServerPort);
}

auto handleRequest() -> void
{
	auto const clientIP = webServer.client().remoteIP();

	Serial.print("A request was made from ");
	Serial.print(clientIP);
	Serial.print(".\n");

	webServer.send
	(
		200,
		"text/plain",
		"Hello from the rain gauge ESP server!\n"
	);
}
