/*	JAIME VILLAR	*/

#include "multmatrix_stub.h"

multmatrix_stub::multmatrix_stub()
{
    conn = initClient("172.31.91.5", 60000);
}

matrix_t *multmatrix_stub::readMatrix(const char *fileName)
{
}

matrix_t *multmatrix_stub::multMatrices(matrix_t *m1, matrix_t *m2)
{
}

void multmatrix_stub::writeMatrix(matrix_t *m, const char *fileName)
{
}

matrix_t *multmatrix_stub::createIdentity(int rows, int cols)
{
}

matrix_t *multmatrix_stub::createRandMatrix(int rows, int cols)
{
    int *result = 0;
    int bufferSize = 0;
    int *buffer = 0;

    int op = OP_RAND;

    sendMSG(0, (void *)&op, sizeof(int));

    sendMSG(0, (void *)&rows, sizeof(int));
    sendMSG(0, (void *)&cols, sizeof(int));
    recvMSG(0, (void **)&buffer, &bufferSize);

    result = buffer;

    matrix_t *m = new matrix_t[1];
    m->rows = rows;
    m->cols = cols;
    m->data = result;

    delete[] buffer;
    return m;
}

multmatrix_stub::~multmatrix_stub()
{
}