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
# working area
WA_P="/home/dbp/lpd_env/project"
# c codes
CCODE="/home/dbp/lpd_env/fftPower_lpd/array_code/impl1/c_code"
# object file generated using simple scalar
OBJS_P="/home/dbp/lpd_env/project/simplescalar_objs"
# results of wattch
WTR_P="/home/dbp/lpd_env/project/wattch_results"
# simple scalar cross compiler
SS_P="/home/dbp/lpd_env/installers/SimpleScalar"
# wattch tool
WT_P="/home/dbp/lpd_env/installers/Wattch"


for test in `ls $CCODE/*c | sed 's/.c//g'`; do
	echo "---------------------------------------------"

	echo "***** Simple Scalar *****"
	echo "Generating the object file to: " ${test}
	echo "" 
 	echo $test
	
	
	cd ${OBJS_P}
	${SS_P}/build/bin/sslittle-na-sstrix-gcc -o $test ${test}.c #-Bdynamic

	echo "***** Wattch *****"
	echo "Populating the software to evaluate the performace of: " ${test}
	echo "" 

	cd ${WTR_P}
	#${WT_P}/sim-wattch-1.02d/sim-outorder -cache:dl1 dl1:256:32:1:l -cache:il1 il1:256:32:1:l -cache:il2 dl2 -cache:dl2 dl2:4096:32:1:l ${OBJS_P}/${test} 128 > ${test}.result 

	#${WT_P}/sim-wattch-1.02d/sim-outorder -cache:dl1 dl1:256:32:1:l -cache:il1 il1:256:32:1:l -cache:il2 dl2 -cache:dl2 dl2:4096:32:1:l ${OBJS_P}/${test} 128 2> ${test}.result 
	${WT_P}/sim-wattch-1.02d/sim-outorder -cache:dl1 dl1:256:32:1:l -cache:il1 il1:256:32:1:l -cache:il2 dl2 -cache:dl2 dl2:4096:32:1:l ${OBJS_P}/${test} 128 

	echo "***** Result *****"
	#realpath ${test}.result
	echo ""

	echo "---------------------------------------------"
done 

echo "Info: All the test were ran succesfully!!"
echo "Result path" ${WTR_P} 
