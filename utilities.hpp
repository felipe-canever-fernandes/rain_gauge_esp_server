#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace rain_gauge_esp_server
{
	template<size_t JSON_SIZE>
	auto fromJsonToString(StaticJsonDocument<JSON_SIZE> const& json) -> String;
}

namespace rain_gauge_esp_server
{
	template<size_t JSON_SIZE>
	auto fromJsonToString(StaticJsonDocument<JSON_SIZE> const& json) -> String
	{
		auto string = String();
		serializeJson(json, string);
		return string;
	}
}