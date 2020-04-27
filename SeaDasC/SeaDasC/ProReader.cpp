#pragma once;

#include <string>
#include <fstream>
#include <iostream>

#include "Params.cpp"
#include "ProModel.cpp"

class ProReader
{
	public: 
		ProModel proModel;

		ProReader(std::string path)
		{
			StartRead(path);
		};

	private:
		void StartRead(std::string path) 
		{
			int16_t i2;
			float f4;

			std::ifstream in(path.c_str(), std::ios::binary);

			if (!in.bad())
			{
				std::cout << std::endl << "ProModel: " + path << std::endl;

				in.seekg(skipProHeaders, std::ios_base::cur);
			
				in.read((char*)&i2, unsignedType);
				std::cout << "Lines: " << i2 << std::endl;
				proModel.Lines = i2;

				in.read((char*)&i2, unsignedType);
				std::cout << "Pixels: " << i2 << std::endl;
				proModel.Pixels = i2;

				in.read((char*)&f4, floatType);
				std::cout << "Latitude: " << f4 << std::endl;
				proModel.Latitude = f4;

				in.read((char*)&f4, floatType);
				std::cout << "Longitude: " << f4 << std::endl;
				proModel.Longitude = f4;

				in.read((char*)&f4, floatType);
				std::cout << "LatitudeSize: " << f4 << std::endl;
				proModel.LatitudeSize = f4;

				in.read((char*)&f4, floatType);
				std::cout << "LongitudeSize: " << f4 << std::endl;
				proModel.LongitudeSize = f4;

				in.read((char*)&f4, floatType);
				std::cout << "StepLatitudeTime: " << f4 << std::endl;
				proModel.StepLatitudeTime = f4;

				in.read((char*)&f4, floatType);
				std::cout << "StepLongitudeTime: " << f4 << std::endl;
				proModel.StepLongitudeTime = f4;

				std::cout << std::endl;
				in.close();
			}
		}
};
