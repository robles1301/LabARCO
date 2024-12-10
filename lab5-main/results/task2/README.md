# Tarea 2
El código en [src/task2/buffer.cpp](../../src/task2/buffer.cpp) debería representar el siguiente flujo:
1. Inicializar el buffer A
2. Sumar al valor de cada posición de A el índice de la iteración
3. Inicializar el buffer B Del mismo modo que A
4. Calcular B como resultado del valor de B multiplicado por A

## Comprueba el resultado y muéstralo a continuación
**Contesta aquí.**

## ¿Qué abstracción se está usando para los contenedores de datos?
**Contesta aquí.**

## ¿Cómo se está formando el DAG? ¿implicitamente? ¿explicitamente?
**Contesta aquí.**

## Enumera todas las dependencias y el tipo de dependencias
**Contesta aquí**

----

# Task 2
Code in [src/task2/buffer.cpp](../../src/task2/buffer.cpp) should represent the following flow:
1. Initialize buffer A
2. Add to each item in A the index of the iteration
3. Initialize buffer B the same way than A
4. Compute B as the result of B multiplied by A

## Check the result and show it below
0
2
8
18
32
50
72
98
128
162
200
242
288
338
392
450

## Which abstraction is being used for data containers?
sycl buffer that manage movement host and device (read_only, write_only).

## How is the DAG being built implicitly or explicitly?
The DAG is built implicitly by sycl based on buffer dependeces

## Enumerate all dependencies and their types
Kernel 1 → Kernel 2.
Type: Intra-buffer dependency.


Kernel 1 → Kernel 4.
Type: Read-after-write (RAW).


Kernel 2 → Kernel 4.
Type: Read-after-write (RAW).

Kernel 3 → Kernel 4.
Type: Read-after-write (RAW).
