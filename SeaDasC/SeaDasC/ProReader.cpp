#pragma once;

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

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
			double d8;
			clock_t start, end;
			start = clock();

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

				in.read((char*)&d8, doubleType);
				std::cout << "A: " << d8 << std::endl;
				proModel.A = d8;

				in.read((char*)&d8, doubleType);
				std::cout << "B: " << d8 << std::endl;
				proModel.B = d8;

				proModel.stepLat = proModel.StepLat();
				proModel.stepLon = proModel.StepLon();

				in.seekg(Reserve, std::ios_base::cur);

				in.seekg(NoradDataAndÑorrection, std::ios_base::cur);

				int32_t** matrix = new int32_t* [proModel.Lines];;
				for (int32_t i = 0; i < proModel.Lines; i++)
				{
					matrix[i] = new int[proModel.Pixels];
				}

				int lines = static_cast<int16_t>(proModel.Lines)-1;
				for (int32_t i = lines; i >= 0; i--)
				{
				
					for (int32_t j = 0; j < proModel.Pixels; j++)
					{
						in.read((char*)&i2, unsignedType);
						matrix[i][j] = i2;
					
						//in.read((char*)&i2, unsignedType);
						//proModel.BrtList.push_back(i2);
					}
				}

				for (int32_t i = 0; i < proModel.Lines; i++)
				{
					for (int32_t j = 0; j < proModel.Pixels; j++)
					{
						proModel.BrtList.push_back(matrix[i][j]);
					}
				}

				in.close();
				end = clock();

				cout << endl << "Time " << (((double)end - start) / ((double)CLOCKS_PER_SEC)) << endl;
			}
		}
};
