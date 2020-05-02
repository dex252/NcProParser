#pragma once;

#include <iostream>
#include <filesystem>

#include "Params.cpp"
#include "ProReader.cpp"
#include "NcWriter.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    //Заглушка
    
 /*   argc = 2;
    string path = "C:\\Users\\dex25\\Desktop\\NcProParser\\SeaDasC\\Resources\\n85113_2.pro";
    
    */

    if (argc != 2)
    {
        cout << "Error. Path parameter expected." << endl;
      //  system("pause");
        return -1;
    }
    
    //Чтение из .pro
    //ProReader proReader(path);
    ProReader proReader(argv[1]);

    //Запись в temp.cdl
    NcWriter ncWriter(proReader.proModel);

    //Запуск процесса ncgen.exe - желательно со скрипта на баше
    /*
     string command = "cd " + netCDFFolder +"\\ncgen.exe -o \"" + outputFile + "\" \"" + tempFile + "\"";
    const char* process = command.c_str();
    cout << process << endl;
    system(process);
    */
   

   // system("pause");
}