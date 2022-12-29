// INPUTS:
// r1 error
// r2 Omega
// r3 S5
// r4 S1
// r5 S6
// r6 S2
// r7 S3
// r14 INT_B --
// r15 INT_A/OUTPUT --


let post_add
let omega_kd
let post_dir_mul
let out_n_kd
let post_inv_mul
let int_integ_a
let int_integ_b

addi r1, 0, r1
addi r2, 0, r2
mul r14, r2, post_inv_mul
add post_inv_mul, r1, post_add
muli r2, 13, omega_kd
sari omega_kd, 4, omega_kd
mul omega_kd, post_add, post_dir_mul

//INTEGRAL direct path, the constant is for 10khz
//mulsri post_dir_mul, 6, int_integ_a
//add r15, int_integ_a, r15

add r15, post_dir_mul, r15

muli r15, 13, out_n_kd
sari out_n_kd, 4, out_n_kd


//INTEGRAL inverse path, the constant is for 10khz
//mulsri out_n_kd, 6, int_integ_b
//add r15, int_integ_b, r14

add r15, out_n_kd, r14

stop
