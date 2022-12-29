ldc r1, 0.0
ldc r2, 6144
ldc r3, 1
ldc r4, 6144
nop
efi r1, r2, r10
efi r3, r2, r11
nop
nop
ldc r4, 0.000030518
itf r11, r9
itf r12, r8
mul r9, r4, r6
mul r8, r4, r7
nop
nop
stop


    angle               cos              sin
 360   = 0xffff          1                0
 270   = 0xBFFD          0                -1
 180   = 0x7FFF         -1                0
  90   = 0x3FFF          0                1
  45   = 0x1FFF          0.707           0.707
  22.5 = 0xfff           0.9238          0.382
   0   = 0               1               0