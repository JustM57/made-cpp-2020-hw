.text

.global count_det
count_det:
    mov r1, #0 
    /* считаем главную диагональ 1-5-9*/
    ldrb r2, [r0], #4 ;i=2
    add r0, #12 ;i=5
    ldrb r3, [r0], #4; i=6
    mul r4, r2, r3
    mov r2, r4
    add r0, #12; i=9
    ldrb r3, [r0], #4; i=10
    mul r4, r2, r3
    add r1, r4; /* пишем к результату */
    /* следующее произведение -(1-6-8)*/ 
    sub r0, #36 ;i=1
    ldrb r2, [r0], #4 ;i=2
    add r0, #16 ;i=6
    ldrb r3, [r0], #4; i=7
    mul r4, r2, r3
    mov r2, r4
    add r0, #4; i=8
    ldrb r3, [r0], #4; i=9
    mul r4, r2, r3
    sub r1, r4; /* пишем к результату */
    /* следующее произведение 2-6-7*/ 
    sub r0, #28 ;i=2
    ldrb r2, [r0], #4 ;i=3
    add r0, #12 ;i=6
    ldrb r3, [r0], #4; i=7
    mul r4, r2, r3
    mov r2, r4
    ldrb r3, [r0], #4; i=8
    mul r4, r2, r3
    add r1, r4; /* пишем к результату */
    /* следующее произведение -(2-4-9)*/ 
    sub r0, #24 ;i=2
    ldrb r2, [r0], #4 ;i=3
    add r0, #4 ;i=4
    ldrb r3, [r0], #4; i=5
    mul r4, r2, r3
    mov r2, r4
    add r0, #16; i=9
    ldrb r3, [r0], #4; i=10
    mul r4, r2, r3
    sub r1, r4; /* пишем к результату */
    /* следующее произведение 3-4-8*/ 
    sub r0, #28 ;i=3
    ldrb r2, [r0], #4 ;i=4
    ldrb r3, [r0], #4; i=5
    mul r4, r2, r3
    mov r2, r4
    add r0, #12; i=8
    ldrb r3, [r0], #4; i=9
    mul r4, r2, r3
    add r1, r4; /* пишем к результату */
    /* следующее произведение -(3-5-7)*/ 
    sub r0, #24 ;i=3
    ldrb r2, [r0], #4 ;i=4
    add r0, #4 ;i=5
    ldrb r3, [r0], #4; i=6
    mul r4, r2, r3
    mov r2, r4
    add r0, #4; i=7
    ldrb r3, [r0], #4; i=8
    mul r4, r2, r3
    sub r1, r4; /* пишем к результату */
    /* следующее произведение */ 
    mov r0, r1
    bx lr
