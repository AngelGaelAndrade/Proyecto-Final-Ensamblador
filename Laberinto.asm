section .text
    global PrintMaze
    global GameTime
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

GameTime:
    ; Prólogo estándar Windows x64
    push rbp
    mov rbp, rsp
    sub rsp, 32         ; Shadow space para Windows x64
    push r12            ; Preservar registros no volátiles
    push r13
    push r14
    push r15

    ; Parámetros Windows x64:
    ; rcx = puntero a matriz
    ; rdx = filas
    ; r8 = columnas
    ; r9 = movimiento (carácter)
    mov r12, rcx        ; r12 = puntero a matriz
    mov r13, rdx        ; r13 = número de filas
    mov r14, r8         ; r14 = número de columnas
    mov r15, r9         ; r15 = movimiento

    ; Encontrar posición actual del jugador 'P'
    xor r9, r9          ; i = 0 (contador de filas)

.buscar_jugador_fila:
    cmp r9, r13         ; ¿i < filas?
    jge .jugador_no_encontrado

    xor r10, r10        ; j = 0 (contador de columnas)

.buscar_jugador_columna:
    cmp r10, r14        ; ¿j < columnas?
    jge .siguiente_fila_buscar

    ; Calcular posición: matriz[i][j] = matriz + (i * columnas + j)
    mov rax, r9         ; rax = i
    imul rax, r14       ; rax = i * columnas
    add rax, r10        ; rax = i * columnas + j

    ; Verificar si es el jugador 'P'
    cmp byte [r12 + rax], 'P'
    je .jugador_encontrado

    inc r10             ; j++
    jmp .buscar_jugador_columna

.siguiente_fila_buscar:
    inc r9              ; i++
    jmp .buscar_jugador_fila

.jugador_encontrado:
    ; r9 = fila actual del jugador
    ; r10 = columna actual del jugador
    
    ; Calcular nueva posición basada en el movimiento
    mov r11, r9         ; r11 = nueva fila
    mov rax, r10        ; rax = nueva columna

    ; Verificar movimiento y calcular nueva posición
    cmp r15b, 'u'       ; Salir del juego
    je .salir_juego
    cmp r15b, 'U'       ; Salir del juego (mayúscula)
    je .salir_juego
    cmp r15b, 'w'       ; Arriba
    je .mover_arriba
    cmp r15b, 's'       ; Abajo
    je .mover_abajo
    cmp r15b, 'a'       ; Izquierda
    je .mover_izquierda
    cmp r15b, 'd'       ; Derecha
    je .mover_derecha
    jmp .movimiento_invalido

.salir_juego:
    mov rax, 2          ; Retornar 2 (salir del juego)
    jmp .fin_game

.mover_arriba:
    dec r11             ; nueva_fila--
    jmp .verificar_limites

.mover_abajo:
    inc r11             ; nueva_fila++
    jmp .verificar_limites

.mover_izquierda:
    dec rax             ; nueva_columna--
    jmp .verificar_limites

.mover_derecha:
    inc rax             ; nueva_columna++
    jmp .verificar_limites

.verificar_limites:
    ; Verificar si la nueva posición está dentro de los límites
    cmp r11, 0
    jl .movimiento_invalido
    cmp r11, r13
    jge .movimiento_invalido
    cmp rax, 0
    jl .movimiento_invalido
    cmp rax, r14
    jge .movimiento_invalido

    ; Calcular posición en memoria de la nueva celda
    push r9             ; Guardar posición actual
    push r10
    mov r9, r11         ; r9 = nueva fila
    mov r10, rax        ; r10 = nueva columna
    
    mov rax, r9         ; rax = nueva_fila
    imul rax, r14       ; rax = nueva_fila * columnas
    add rax, r10        ; rax = nueva_fila * columnas + nueva_columna

    ; Verificar contenido de la nueva celda
    movzx rcx, byte [r12 + rax]  ; rcx = contenido de nueva celda

    ; Verificar colisiones
    cmp rcx, '#'        ; ¿Es un muro?
    je .colision_muro
    cmp rcx, 'X'        ; ¿Es la salida?
    je .llegada_salida
    cmp rcx, '.'        ; ¿Es espacio libre?
    je .movimiento_valido

    ; Si no es ninguno de los anteriores, tratar como espacio libre
    jmp .movimiento_valido

.colision_muro:
    pop r10             ; Restaurar posición actual
    pop r9
    mov rax, -1         ; Retornar -1 (colisión con muro)
    jmp .fin_game

.llegada_salida:
    ; Mover jugador a la salida
    mov byte [r12 + rax], 'P'   ; Colocar 'P' en la nueva posición
    
    ; Limpiar posición anterior
    pop r10             ; Restaurar posición anterior
    pop r9
    mov rcx, r9         ; rcx = fila anterior
    imul rcx, r14       ; rcx = fila_anterior * columnas
    add rcx, r10        ; rcx = fila_anterior * columnas + columna_anterior
    mov byte [r12 + rcx], '.'   ; Colocar '.' en la posición anterior
    
    mov rax, 1          ; Retornar 1 (llegada a la salida)
    jmp .fin_game

.movimiento_valido:
    ; Realizar el movimiento
    mov byte [r12 + rax], 'P'   ; Colocar 'P' en la nueva posición
    
    ; Limpiar posición anterior
    pop r10             ; Restaurar posición anterior
    pop r9
    mov rcx, r9         ; rcx = fila anterior
    imul rcx, r14       ; rcx = fila_anterior * columnas
    add rcx, r10        ; rcx = fila_anterior * columnas + columna_anterior
    mov byte [r12 + rcx], '.'   ; Colocar '.' en la posición anterior
    
    mov rax, 0          ; Retornar 0 (movimiento exitoso)
    jmp .fin_game

.movimiento_invalido:
    mov rax, -1         ; Retornar -1 (movimiento inválido)
    jmp .fin_game

.jugador_no_encontrado:
    mov rax, -1         ; Retornar -1 (jugador no encontrado)

.fin_game:
    ; Epílogo de la función
    pop r15
    pop r14
    pop r13
    pop r12
    add rsp, 32         ; Restaurar shadow space
    pop rbp
    ret