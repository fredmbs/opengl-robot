/*
 * Maths.h
 */

#ifndef PLANETASMATH_H_
#define PLANETASMATH_H_

#include <math.h>
#define M_PI		3.14159265358979323846

// reduz o vetor normail para unidade
void ReduceToUnit(double vector[3]);
// calcula o vetor normal dado três pontos no espaço
void calcNormal(double v[3][3], double out[3]);
// Produto vetoral
void prodVet(double p[], double v[], double w[]);
// Cria vetor v baseado nos pontoa A e B
void vetorAB(double v[], double A[], double B[]);
// Módulo ou norma vetorial
double normaVet(double v[]);
// distancia entre o ponto P e a reta formada pelos pontos Q e R
double distPontoP_RetaQR(double P[], double Q[], double R[]);
// Distancia entre dois pontos
double distPontoPQ(double P[],double Q[]);

// multiplicação de matrizes 4x4 por vetor 4
void MultiplyMatrixByVector4by4(double *resultvector, const double *matrix, const double *pvector);

void MultiplyMatrices4by4(double *result, double *matrix1, double *matrix2);
int InvertMatrixf2(double *out, double *m);

#endif /* PLANETASMATH_H_ */
