#!/bin/bash
# seadas_c.sh

# Путь к .pro файлу
SOURCEFILE=$1

NETCDF_DIR="C:\\Program Files\\netCDF 4.7.4\\bin"
PROCESSPATH=${HOME}/SeaDasC/SeaDasC/x64/Debug/SeaDasC
#конечный файл
OUTPUTFILE="path in Params.cpp";
#файл из которого ведется запись в OUTPUTFILE
TEMPFILE="path in Params.cpp"

${PROCESSPATH} $SOURCEFILE;

$NETCDF_DIR/ncgen.exe "-o" "${OUTPUTFILE}" "${TEMPFILE}"