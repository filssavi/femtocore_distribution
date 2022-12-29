itf r1, r1       // current word
ldc r3, 52.0  // current LSB constant
mul r1, r3, r1   // ERROR

ldc r3, 1.0    // Kp

mul r1, r3, r3   // R3 (KPE) = Kp*Error
nop
add r3, r0, r15 // R15 (out) = KPE+sogi_out
nop
////////////  saturate out    ////////////////
ldc r6, -20.0 // lim_int_n
nop
bgt r6, r15, r7  // cmp_low_neg
nop
and r7, r6, r9
not r7, r7
nop
and r7, r15, r15
nop
add r15, r9, r15
ldc r6, 20.0   // lim_int_p
nop
bgt r15, r6, r7   // cmp_high_neg
nop
and r7, r6, r9
not r7, r7
nop
and r7, r15, r15
nop
add r15, r9, r15

//////////////////////////////////////////////

ldc r6, 0.02 // 1/Vdc = 1/50 = 0.02
nop
mul r15, r6, r15 // duty cycle

ldc r6, 0.5
nop
add r15, r6, r15

ldc r6, 65535.0
nop
mul r15, r6, r15   //duty cycle 16bit
nop
fti r15, r15
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
stop
