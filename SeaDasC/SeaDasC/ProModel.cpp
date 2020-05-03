#pragma once;

#include <string>
#include <list>

using namespace std;

class ProModel
{
public:
	float Latitude;
	float Longitude;
	float StepLatitudeTime;
	float StepLongitudeTime;
	float Lines;
	float Pixels;
	float LatitudeSize;
	float LongitudeSize;
	//Коэффециенты пересчета
	double A;
	double B;
	float stepLat;
	float stepLon;

	list<int16_t> BrtList;

	int16_t ConvertToTemperature(int16_t brt) {
		if (brt == 0) return 0;
		int16_t value = A * brt + B;
		return value;
	}

	float StepLon() {
		return LongitudeSize / Lines;
	}

	float StepLat() {
		return LatitudeSize / Pixels;
	}
};

