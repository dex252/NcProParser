#pragma once;

#include "ProModel.cpp"
#include "NcModel.cpp"
#include "Params.cpp"

#include <fstream>
#include <iostream>

class NcWriter
{
	public:
		NcWriter(ProModel proModel) {
			StartWrite(proModel);
		}
	private:
		
		void StartWrite(ProModel proModel) {

			NcModel ncModel;

			std::string line;
			std::ifstream in(originsCdlFile);
			std::ofstream out;

			out.open(tempFile);
			if (in.is_open() && out.is_open())
			{
				std::cout << std::endl << "Start re-write cdl file..." << std::endl;

				while (getline(in, line))
				{
					line = LineModule(line, ncModel, proModel);

					out << line << std::endl;
				}

				std::cout << std::endl  << "Re-write is ready." << std::endl;
			}

			out.close();
			in.close();
		}

		std::string LineModule(std::string line, NcModel ncModel, ProModel proModel) {

			std::string equal;

			equal = Equal(ncModel.number_of_lines);
			if (line.find(equal) != std::string::npos) {
				return (ncModel.number_of_lines + std::to_string(proModel.Lines) + " ;");
			}

			equal = Equal(ncModel.number_of_columns);
			if (line.find(equal) != std::string::npos) {
				return (ncModel.number_of_columns + std::to_string(proModel.Pixels) + " ;");
			}

			equal = Equal(ncModel.latitude_step);
			if (line.find(equal) != std::string::npos) {
				return (ncModel.latitude_step + std::to_string(proModel.StepLatitudeTime) + " ;");
			}

			equal = Equal(ncModel.longitude_step);
			if (line.find(equal) != std::string::npos) {
				return (ncModel.longitude_step + std::to_string(proModel.StepLongitudeTime) + " ;");
			}

			equal = Equal(ncModel.sw_point_latitude);
				if (line.find(equal) != std::string::npos) {
				return (ncModel.sw_point_latitude + std::to_string(proModel.Latitude) + " ;");
			}

			equal = Equal(ncModel.sw_point_longitude);
				if (line.find(equal) != std::string::npos) {
				return (ncModel.sw_point_longitude + std::to_string(proModel.Longitude) + " ;");
			}

			equal = Equal(ncModel.northernmost_latitude);
				if (line.find(equal) != std::string::npos) {
				float north = proModel.Latitude + proModel.LatitudeSize;
				return (ncModel.northernmost_latitude + std::to_string(north) + " ;");
			}

			equal = Equal(ncModel.geospatial_lat_max);
				if (line.find(equal) != std::string::npos) {
				float north = proModel.Latitude + proModel.LatitudeSize;
				return (ncModel.geospatial_lat_max + std::to_string(north) + " ;");
			}

			equal = Equal(ncModel.southernmost_latitude);
				if (line.find(equal) != std::string::npos) {
				float south = proModel.Latitude;
				return (ncModel.southernmost_latitude + std::to_string(south) + " ;");
			}

			equal = Equal(ncModel.geospatial_lat_min);
				if (line.find(equal) != std::string::npos) {
				float south = proModel.Latitude;
				return (ncModel.geospatial_lat_min + std::to_string(south) + " ;");
			}

			equal = Equal(ncModel.westernmost_longitude);
				if (line.find(equal) != std::string::npos) {
				float west = proModel.Longitude;
				return (ncModel.westernmost_longitude + std::to_string(west) + " ;");
			}

			equal = Equal(ncModel.geospatial_lon_max);
				if (line.find(equal) != std::string::npos) {
				float west = proModel.Longitude;
				return (ncModel.geospatial_lon_max + std::to_string(west) + " ;");
			}

			equal = Equal(ncModel.easternmost_longitude);
				if (line.find(equal) != std::string::npos) {
				float east = proModel.Longitude + proModel.LongitudeSize;
				return (ncModel.easternmost_longitude + std::to_string(east) + " ;");
			}

			equal = Equal(ncModel.geospatial_lon_min);
				if (line.find(equal) != std::string::npos) {
				float east = proModel.Longitude + proModel.LongitudeSize;
				return (ncModel.geospatial_lon_min + std::to_string(east) + " ;");
			}

			return line;
		}

		std::string Equal(std::string equal) {
			return equal.substr(equal.find(':'), equal.find('='));
		}
};