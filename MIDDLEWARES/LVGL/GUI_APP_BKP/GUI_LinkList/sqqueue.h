#ifndef __SQQUEUE__H__
#define __SQQUEUE__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int sqdata_t;
typedef struct
{
    sqdata_t *data;
    int front, rear;
} sqqueue;
static int _container;
sqqueue *sqqueue_create(int container);
int sqqueue_push(sqqueue *q, sqdata_t value);
sqdata_t sqqueue_pop(sqqueue *q);
int sqqueue_empty(sqqueue *q);
int sqqueue_full(sqqueue *q);
int sqqueue_clear(sqqueue *q);
sqqueue *sqqueue_free(sqqueue *q);
#endif //!__SQQUEUE__H__