#pragma once

#include <string>

using namespace std;

class NcModel
{
	public:
		string number_of_lines = "		:number_of_lines = ";
		string number_of_columns = "		:number_of_columns = ";

		string latitude_step = "		:latitude_step = ";
		string longitude_step = "		:longitude_step = ";

		string sw_point_latitude = "		:sw_point_latitude = ";
		string sw_point_longitude = "		:sw_point_longitude = ";

		string northernmost_latitude = "		:northernmost_latitude = ";
		string southernmost_latitude = "		:southernmost_latitude = ";
		string westernmost_longitude = "		:westernmost_longitude = ";
		string easternmost_longitude = "		:easternmost_longitude = ";

		string geospatial_lat_max = "		:geospatial_lat_max = ";
		string geospatial_lat_min = "		:geospatial_lat_min = ";
		string geospatial_lon_max = "		:geospatial_lon_max = ";
		string geospatial_lon_min = "		:geospatial_lon_min = ";

		//не использовано
		string spatialResolution = "		:spatialResolution = ";
		string geospatial_lat_resolution = "		:geospatial_lat_resolution = ";
		string geospatial_lon_resolution = "		:geospatial_lon_resolution = ";
};