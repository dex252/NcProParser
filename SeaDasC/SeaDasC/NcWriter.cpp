#pragma once;

#include <fstream>
#include <iostream>
#include <filesystem>
#include <ctime>

#include "ProModel.cpp"
#include "Params.cpp"

class NcWriter
{
public:
	NcWriter(ProModel proModel) {
		HardStartWrite(proModel);
	}
private:

	//������� ����������� ������� �������
	void HardStartWrite(ProModel proModel)
	{
		std::string line;
		std::ifstream in(originsCdlFile);
		std::ofstream out;

		clock_t start, end;
		start = clock();

		out.open(tempFile);
		if (in.is_open() && out.is_open())
		{
			std::cout << std::endl << "Start write..." << std::endl;

			//	������ ����� � ������� ��� pro � 1 �� 2 ������ ������������
			for (size_t i = 0; i < 2; i++)
			{
				getline(in, line);
				out << line << std::endl;
			}
			//������ �������� � �����
			for (size_t i = 0; i < 2; i++)
			{
				getline(in, line);
			}
			out << "	lat = " << proModel.Lines << " ;" << std::endl;
			out << "	lon = " << proModel.Pixels << " ;" << std::endl;
			//	������ ����� � ������� ��� pro � 4 �� 58 ������ ������������
			for (size_t i = 4; i < 58; i++)
			{
				getline(in, line);
				out << line << std::endl;
			}
		
			//�������� �������� - ���������� ������ � 58 �� 70
			for (size_t i = 58; i < 70; i++)
			{
				getline(in, line);
			}
			//��������� ������������ ����������
			float north = proModel.Latitude + proModel.LatitudeSize;
			float south = proModel.Latitude;
			float west = proModel.Longitude;
			float east = proModel.Longitude + proModel.LongitudeSize;

			out << "		:northernmost_latitude = " << north << " ;" << std::endl;
			out << "		:southernmost_latitude = " << south << " ;" << std::endl;
			out << "		:westernmost_longitude = " << west << " ;" << std::endl;
			out << "		:easternmost_longitude = " << east << " ;" << std::endl;

			out << "		:geospatial_lat_max = " << north << " ;" << std::endl;
			out << "		:geospatial_lat_min = " << south << " ;" << std::endl;
			out << "		:geospatial_lon_max = " << east << " ;" << std::endl;
			out << "		:geospatial_lon_min = " << west << " ;" << std::endl;

			out << "		:latitude_step = " << proModel.StepLatitudeTime << " ;" << std::endl;
			out << "		:longitude_step = " << proModel.StepLongitudeTime << " ;" << std::endl;
			out << "		:sw_point_latitude = " << proModel.Latitude << " ;" << std::endl;
			out << "		:sw_point_longitude = " << proModel.Longitude << " ;" << std::endl;
			//����� ���������� � 58 �� 70
		
			//���������� � ���������� (�� ���� ��� �����)
			for (size_t i = 70; i < 75; i++)
			{
				getline(in, line);
				out << line << std::endl;
			}

			//���������� � ����� ����� � ��������
			for (size_t i = 75; i < 77; i++)
			{
				getline(in, line);
			}

			out << "		:number_of_lines = " << proModel.Lines << " ;" << std::endl;
			out << "		:number_of_columns = " << proModel.Pixels << " ;" << std::endl;

			//���������� ���������� ����� global global attributes � 78 �� 102 ������������ (� �������� ������ DataSet)

			for (size_t i = 77; i < 102; i++)
			{
				getline(in, line);
				out << line << std::endl;
			}

			end = clock();
			cout << endl << "Time header " << (((double)end - start) / ((double)CLOCKS_PER_SEC)) << endl;
			
			//���������� DataSet`��. ������� ��������� ����������� ����������� ������ sst, ����� ������ lat � ����� ������� lon
			
			//sst �����, ����������� ��������������� �� 25 �����
			out << " sst = " << endl << "	";

			int16_t count = 0; // ������� ��� ��������
			int16_t last = proModel.BrtList.back(); //�������� ��������� �������, � ����� � ���� ����� ��������� ;
			proModel.BrtList.pop_back(); // ������� ��������� �������
			for (int16_t point : proModel.BrtList) {
				int16_t temperature = point;//proModel.ConvertToTemperature(point);
				
				if (temperature == 0) out << "_";
				else out << temperature;

				out << ", ";

				count++;
				if (count % 25 == 0) 
				{
					count = 0;
					out << endl << "	";
				}
			}
			// ���������� ��������� �������
			int16_t temperature = last; //proModel.ConvertToTemperature(last);
			if (temperature == 0) out << "_";
			else out << temperature;
			out << " ;" << endl;

			end = clock();
			cout << endl << "Time sst part " << (((double)end - start) / ((double)CLOCKS_PER_SEC)) << endl;
			//����� sst �����

			//lat �����, ����������� �� 6 ��� 7 �����
			out << " lat = ";
			for (size_t i = 1; i < proModel.Pixels; i++)
			{
				out << proModel.Latitude + i * proModel.stepLat << ", ";
				if (i % 7 == 0) out << endl << "	";
			}
			out << proModel.Latitude + proModel.Pixels * proModel.stepLat << " ;" << endl; // ��������� ����� ������������ �� ;
			//����� lat �����
			end = clock();
			cout << endl << "Time lat part " << (((double)end - start) / ((double)CLOCKS_PER_SEC)) << endl;
			//lon �����, ����������� �� 6 ��� 7 �����

			out << " lon = ";
			for (size_t i = 1; i < proModel.Lines; i++)
			{
				out << proModel.Longitude + i * proModel.stepLon << ", ";
				if (i % 7 == 0) out << endl << "	";
			}
			out << proModel.Longitude + proModel.Lines * proModel.stepLon << " ;" << endl; // ��������� ����� ������������ �� ;

			//����� lon �����
			
			//����� DataSet
			end = clock();
			cout << endl << "Time lon part " << (((double)end - start) / ((double)CLOCKS_PER_SEC)) << endl;
			//��������� ������ �� ���������� ����� 102 �� 160:
			for (size_t i = 102; i < 160; i++)
			{
				getline(in, line);
				out << line << std::endl;
			}

			//�����
			std::cout << std::endl << "Write is ready." << std::endl;
		}

		out.close();
		in.close();
	}
};