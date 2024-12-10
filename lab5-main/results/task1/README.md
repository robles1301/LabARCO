# Tarea 1
Familiarizarse con el uso de DPC.
En primer lugar copia el código de [src/task1/query.cpp](../../src/task1/query.cpp) en results/task1/src y compilalo con dpcpp.

## ¿Qué salida obtienes?
**Contesta aquí.**

## ¿Qué tipos de selectores tenemos en DPC? ¿Podemos obtener una GPU? ¿Qué pasa si no existe el dispositivo requerido?
**Contesta aquí.**

Es probable que alguno de los dispositivos que te permite seleccionar DPC no los tengas disponibles en tu PC. En ese caso habría que recurrir a buscarlos en otros equipos o emplear soluciones de hardware a través de la nube.

## Prueba a obtener una GPU, si es posible en tu equipo, modificando el programa query.cpp en gpu_query.cpp
**guarda el fichero en results/task1/src.**

## ¿Cómo has obtenido la GPU?
**Contesta aquí.**

## Modifica el programa para obtener más datos del dispositivo.
**guarda el fichero en results/task1/src/more_query.cpp**

------
# Task 1
Get familiar with Intel DPC compiler.
First copy the code in [src/task1/query.cpp](../../src/task1/query.cpp) to results/task1/src and compile it with dpcpp.

## Which output do you obtain?
Device: 11th Gen Intel(R) Core(TM) i5-11400H @ 2.70GHz

## Which different types of selectors do we have in DPC? Can we obtain a GPU? What happens if the requested device doesn't exist?
-cpu_selector
-gpu_selector
-accelerator_selector
-default_selector

Yes, we can obtain gpu information with gpu_selector

if the requested device does not exist the exception "SYCL exception caught" will appear.

It is very likely that some of the devices that can be used with DPC are not available in your PC. In that case, we would look for them in other equipment or use hardware solutions through the cloud.

## Try to obtain a GPU, if it is available in your PC, by the query.cpp program into gpu_query.cpp
**store the resulting file in results/task1/src.**

## How did you obtained the GPU?
We change cpu_selector into gpu_selector.

## Modify the program to obtain more data from the device.
**store the resulting file in results/task1/src/more_query.cpp**
we obtain extra data from cpu because gpu does not gave us information   
