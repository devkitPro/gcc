/* { dg-do compile } */
/* { dg-additional-options "-march=rv32gcv_zvfh -mabi=ilp32d -mrvv-vector-bits=scalable -fdump-tree-optimized-details -fno-vect-cost-model" } */

#include "ternop-1.c"

/* { dg-final { scan-tree-dump-times "COND_LEN_FMA" 3 "optimized" } } */
/* { dg-final { scan-assembler-not {\tvmv} } } */
