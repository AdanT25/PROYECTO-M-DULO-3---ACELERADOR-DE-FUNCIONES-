# Proyecto Módulo 3: Acelerador de Funciones

**Nombre del Alumno:** Torres Enriquez Braulio Adan

## Descripción del Proyecto
Este proyecto desarrolla un programa en C híbrido que compara el rendimiento computacional de calcular el producto punto de dos vectores de enteros (32 bits) usando un bucle estándar en C puro frente a una función optimizada de ensamblador inline (x86-64). 

## Instrucciones de Compilación y Ejecución
Para asegurar una comparación justa y evitar problemas con librerías del sistema, se recomienda compilar y enlazar directamente a través del compilador nativo GCC:
1. Abre tu terminal integrada o CMD en la carpeta donde guardaste tu `main.c`.
2. Compila el ejecutable con el comando: `gcc -O0 main.c -o acelerador.exe`.
3. Ejecuta el archivo generado: `acelerador.exe`

## Análisis de Resultados y Optimizaciones
- **Bucle de C Puro:** Realiza la lectura del arreglo usando el cálculo de punteros por cada elemento en iteración con el compilador determinando la asignación de registros y la verificación de saltos.
- **Versión ASM Inline:** Se gestionó el acceso a la memoria de 32 a 64 bits combinando las instrucciones `movslq` (Move with Sign-Extension) para cargar datos, `imul` (multiplicación con signo) y `add`. Operar sobre registros directamente (`%rax` y `%rcx` nativos) acelera la manipulación del indexado.

## Capturas de Pantalla
<img width="1420" height="266" alt="image" src="https://github.com/user-attachments/assets/9d81447d-ca39-408e-80dd-35af8e3e0cda" />
