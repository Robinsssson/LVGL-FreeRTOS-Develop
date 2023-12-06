#include "sqqueue.h"
sqqueue *sqqueue_create(int container)
{
    sqqueue *q;
    _container = container + 1;
    if ((q = (sqqueue *)malloc(sizeof(sqqueue))) == NULL)
    {
        printf("malloc failed!\n");
        return NULL;
    }
    if ((q->data = (sqdata_t *)malloc(sizeof(sqdata_t) * container)) == NULL)
    {
        printf("data malloc failed!\n");
        return q;
    }
    memset(q->data, -1, sizeof(q->data));
    q->front = 0;
    q->rear = 0;
    return q;
}
int sqqueue_push(sqqueue *q, sqdata_t value)
{
    if (q == NULL)
    {
        printf("q is NULL\n");
        return -1;
    }
    if (sqqueue_full(q) != 0)
    {
        printf("push error\n");
        return -1;
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % _container;

    return 0;
}
sqdata_t sqqueue_pop(sqqueue *q)
{
    sqdata_t index;
    index = q->data[q->front];
    q->front = (q->front + 1) % _container;
    return index;
}

int sqqueue_full(sqqueue *q)
{
    return ((q->rear + 1) % _container == q->front ? 1 : 0);
}
