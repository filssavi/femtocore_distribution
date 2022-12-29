/* MICRO PROGRAM TO TEST ADDITIONS */
ldc r4, 100.0
ldc r5, 200.0
add r4, r5, r6
for(i=0;i<2; i++){
    #pragma unroll
    ldc r4, 100.0
    add r4, r5, r6
    for(k=2;k<0; k--){
        #pragma unroll
        nop
    }
}
stop

