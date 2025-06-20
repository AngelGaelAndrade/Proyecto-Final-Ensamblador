section .text
global PrintMaze
extern putchar

PrintMaze:
    ; Prólogo estándar Windows x64
    push rbp
    mov rbp, rsp
    sub rsp, 32         ; Shadow space para Windows x64
    push r12            ; Preservar registros no volátiles
    push r13
    push r14

    ; Parámetros Windows x64:
    ; rcx = puntero a matriz (primer parámetro)
    ; rdx = filas (segundo parámetro) 
    ; r8 = columnas (tercer parámetro)
    mov r12, rcx        ; r12 = puntero a matriz
    mov r13, rdx        ; r13 = número de filas
    mov r14, r8         ; r14 = número de columnas

    xor r9, r9          ; i = 0 (contador de filas)

.loop_filas:
    cmp r9, r13         ; ¿i < filas?
    jge .fin            ; Si no, terminar

    xor r10, r10        ; j = 0 (contador de columnas)

.loop_columnas:
    cmp r10, r14        ; ¿j < columnas?
    jge .nueva_linea    ; Si no, saltar a nueva línea

    ; Calcular posición: matriz[i][j] = matriz + (i * columnas + j)
    mov rax, r9         ; rax = i
    imul rax, r14       ; rax = i * columnas
    add rax, r10        ; rax = i * columnas + j
    
    ; Cargar carácter y preparar para putchar
    movzx rcx, byte [r12 + rax]  ; rcx = matriz[i][j]
    
    ; Guardar registros que putchar puede modificar
    push r9
    push r10
    call putchar
    
    ; Imprimir espacio después del carácter
    mov rcx, 32         ; ' ' (espacio)
    call putchar
    pop r10
    pop r9
    
    inc r10             ; j++
    jmp .loop_columnas

.nueva_linea:
    ; Imprimir salto de línea
    mov rcx, 10         ; '\n'
    push r9             ; Guardar contador de filas
    call putchar
    pop r9              ; Restaurar contador de filas
    
    inc r9              ; i++
    jmp .loop_filas

.fin:
    ; Epílogo de la función
    pop r14
    pop r13
    pop r12
    add rsp, 32         ; Restaurar shadow space
    pop rbp
    ret