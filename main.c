// ======
// PROYECTO MODULO 3: ACELERADOR DE FUNCIONES
// Problema: Producto Punto de Dos Vectores
// ======

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000000 // 10 millones de elementos[cite: 8]

// VERSIÓN EN C PURO (NO MODIFICAR)
long long producto_punto_c(int *a, int *b, int n) {
    long long suma = 0;
    for (int i=0; i<n; i++) {
        suma += (long long) a[i] * b[i]; // Multiplica a[i] * b[i] y suma al acumulador
    }
    return suma;
}

// VERSIÓN EN ENSAMBLADOR INLINE (Fase ASM puro usando IMUL y ADD)
long long producto_punto_asm(int *a, int *b, int n) {
    long long suma = 0;
    asm volatile (
        "xor %%rax, %%rax\n\t"             // RAX = 0 (Acumulador para la suma)
        "xor %%rcx, %%rcx\n\t"             // RCX = 0 (Índice 'i' para el bucle)[cite: 9]
        "1:\n\t"                           // Etiqueta local de inicio del bucle
        "cmp %3, %%rcx\n\t"                // Comparar índice RCX con la cantidad de elementos 'n'
        "jge 2f\n\t"                       // Si RCX >= n, salir del bucle saltando a la etiqueta 2[cite: 14]
        "movslq (%1, %%rcx, 4), %%r8\n\t"  // Leer a[i] y extender signo de 32 a 64 bits hacia R8
        "movslq (%2, %%rcx, 4), %%r9\n\t"  // Leer b[i] y extender signo de 32 a 64 bits hacia R9[cite: 8, 9]
        "imul %%r9, %%r8\n\t"              // Multiplicación con signo: R8 = R8 * R9[cite: 9]
        "add %%r8, %%rax\n\t"              // Suma: Agregar el producto al acumulador RAX[cite: 9]
        "inc %%rcx\n\t"                    // Incrementar el índice (i++)[cite: 14]
        "jmp 1b\n\t"                       // Bucle: regresar a la etiqueta 1[cite: 14]
        "2:\n\t"                           // Etiqueta local de fin[cite: 14]
        "mov %%rax, %0\n\t"                // Mover el resultado final a la variable de salida[cite: 14]
        : "=r" (suma)                      // %0: Salida hacia variable 'suma'[cite: 9]
        : "r" (a), "r" (b), "r" ((long long)n) // %1 = a, %2 = b, %3 = n[cite: 9]
        : "%rax", "%rcx", "%r8", "%r9", "cc" // Registros modificados protegidos en clobber[cite: 9]
    );
    return suma;
}

// FUNCIÓN PRINCIPAL (NO MODIFICAR)
int main() {
    srand(42);
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    for (int i=0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    clock_t inicio = clock();
    long long res_c = producto_punto_c(a, b, N);
    clock_t fin = clock();
    double tiempo_c = (double) (fin - inicio) / CLOCKS_PER_SEC;

    inicio = clock();
    long long res_asm = producto_punto_asm(a, b, N);
    fin = clock();
    double tiempo_asm = (double) (fin - inicio) / CLOCKS_PER_SEC;

    printf("Producto punto en C: %lld\n", res_c);
    printf("Producto punto en ASM: %lld\n", res_asm);

    if (res_c == res_asm) {
        printf(" Los resultados coinciden.\n");
    } else {
        printf("X ERROR: Los resultados NO coinciden.\n");
    }

    printf("\nTiempo en C: %.4f s\n", tiempo_c);
    printf("Tiempo en ASM: %.4f s\n", tiempo_asm);
    printf("Mejora: %.2fx\n", tiempo_c / tiempo_asm);

    free(a);
    free(b);
    return 0;
}