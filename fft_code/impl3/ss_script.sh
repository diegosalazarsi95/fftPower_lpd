#!/bin/bash

####################################################
## Instituto Tecnologico de Costa Rica
## Escuela de Ingenieria en Electronica 
## Programa de Maestria en Electronica
## Enfasis en VLSI
##
## Diseno de Bajo Consumo de Potencia
## Profesor: Dr-Ing. Miguel Aguilar
## Profesor: MSc-Ing. Pablo Mendoza 
## 
## Proyecto 1
## Software de Bajo Consumo de Energia y Potencia 
## Creado por:
## MSc-Ing. Johan Solis / Ing. Diego Salazar
##
## II Cuatrimestre, 2019
###################################################

## Set the paths to the project and the tools
#impl
IMPL="impl3"
# c codes
CCODE="/home/dbp/lpd_env/fftPower_lpd/fft_code/${IMPL}/c_code"
# object file generated using simple scalar
SSOBJS="/home/dbp/lpd_env/fftPower_lpd/fft_code/${IMPL}/simplescalar_obj"
#watch results
WATCHRR="/home/dbp/lpd_env/fftPower_lpd/fft_code/${IMPL}/watch_results"
# simple scalar cross compiler
SS_P="/home/dbp/lpd_env/installers/SimpleScalar"
# wattch tool
WT_P="/home/dbp/lpd_env/installers/Wattch"

rm -rf ${SSOBJS}/*
rm -rf ${WATCHRR}/*

pushd .
cd ${CCODE}
for test in `ls *c | sed 's/.c//g'`; do
	echo "---------------------------------------------"

	echo "***** Simple Scalar *****"
	echo "Generating the object file to: " ${test}
	echo "" 
 	echo $test
	
 	## RUN SIMPLESCALAR
	${SS_P}/build/bin/sslittle-na-sstrix-gcc -o ${SSOBJS}/$test ${CCODE}/${test}.c #-Bdynamic

	echo "***** Wattch *****"
	echo "Populating the software to evaluate the performace of: " ${test}
	echo "" 

	#RUN WATCH
	${WT_P}/sim-wattch-1.02d/sim-outorder -cache:dl1 dl1:256:32:1:l -cache:il1 il1:256:32:1:l -cache:il2 dl2 -cache:dl2 dl2:4096:32:1:l ${SSOBJS}/${test} 128 2> ${WATCHRR}/${test}.result 
	
	echo "***** Result *****"
	#realpath ${test}.result
	echo ""

	echo "---------------------------------------------"
done 

echo "Info: All the test were ran succesfully!!"
echo "Result path" ${WATCHRR} 
popd
