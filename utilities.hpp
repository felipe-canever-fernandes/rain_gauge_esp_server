#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace rainGaugeEspServer
{
	/// @brief Converts a JSON document to its string representation.
	/// @tparam JSON_SIZE The size of the JSON document.
	/// @param json The JSON document to be converted.
	/// @return The string representation of the JSON document.
	template<size_t JSON_SIZE>
	auto fromJsonToString(StaticJsonDocument<JSON_SIZE> const& json) -> String;
}

namespace rainGaugeEspServer
{
	template<size_t JSON_SIZE>
	auto fromJsonToString(StaticJsonDocument<JSON_SIZE> const& json) -> String
	{
		auto string = String();
		serializeJson(json, string);
		return string;
	}
}
