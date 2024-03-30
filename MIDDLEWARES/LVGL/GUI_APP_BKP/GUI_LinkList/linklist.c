#include "linklist.h"

void page_init_handle_null(lv_obj_t *root)
{
}
linklist list_create()
{
    linklist H;
    H = (linklist)malloc(sizeof(listnode)); // malloc()
    if (H == NULL) {
        return H;
    }
    H->next = NULL;
    H->data = NULL;
    return H;
}
linklist list_createfrom_array(data_t *array, int len)
{
    linklist H = list_create();
    if (H == NULL) {
        return H;
    }
    for (int i = 0; i < len; i++) {
        list_push_back(H, *(array + i));
    }
    return H;
}
// value push H
int list_push_back(linklist H, data_t value)
{
    linklist p;
    linklist q;
    if (H == NULL) {
        return -1;
    }
    // create node
    if ((p = (linklist)malloc(sizeof(listnode))) == NULL) {
        return -1;
    }
    p->data = value;
    p->next = NULL; //?
    // find tail node
    q = H;
    while (q->next != NULL) {
        q = q->next;
    }
    // insert
    q->next = p;
    return 0;
}

int list_insert(linklist H, data_t value, int pos)
{
    linklist p, q;
    if (H == NULL) {
        return -1;
    }
    p = list_get(H, pos - 1);

    if (p == NULL) {
        return -1;
    }
    if ((q = (linklist)malloc(sizeof(listnode))) == NULL) {
        return -1;
    }
    q->data = value;
    q->next = p->next;
    p->next = q;
    return 0;
}

linklist list_get(linklist H, int pos)
{
    linklist p;
    int i;
    if (H == NULL) {
        return NULL;
    }

    if (pos < -1) {
        return NULL;
    }

    if (pos == -1) {
        return H;
    }

    p = H;
    i = -1;
    while (i < pos) {
        if (p->next == NULL) {
            return NULL;
        }

        p = p->next;
        i++;
    }

    return p;
}

int list_delete(linklist H, int pos)
{
    linklist p, q;
    if (H == NULL) {
        return -1;
    }
    p = list_get(H, pos - 1);
    if (p == NULL) {
        return -1;
    }
    if (p->next == NULL) {
        return -1;
    }
    q       = p->next;
    p->next = q->next;
    free(q);
    q = NULL;
    return 0;
}

int list_show(linklist H)
{
    linklist p;
    int len = 0;
    if (H == NULL) {
        return -1;
    }

    p = H;

    while (p->next != NULL) {
        p = p->next;
        len++;
    }
    return len;
}

// 回调改一下
int list_reverse(linklist H)
{
    if (H == NULL) {
        return -1;
    }

    if (H->next == NULL || H->next->next == NULL) {
        return 0;
    }

    linklist p, q;
    p             = H->next->next;
    H->next->next = NULL;
    while (p != NULL) {
        q       = p;
        p       = p->next;
        q->next = H->next;
        H->next = q;
    }
    return 0;
}

int list_merge(linklist H1, linklist H2)
{
    if (H1 == NULL || H2 == NULL) {
        return -1;
    }

    linklist p = H1->next;
    linklist q = H2->next;
    linklist r = H1;

    H1->next = NULL;
    H2->next = NULL;

    while (p && q) {
        if (p->data <= q->data) {
            r->next = p;
            // p = p->next;
            r       = r->next;
            r->next = NULL;
        } else {
            r->next = q;
            q       = q->next;
            r       = r->next;
            r->next = NULL;
        }
    }
    if (p == NULL) {
        r->next = q;
    } else {
        r->next = p;
    }
    return 0;
}

linklist list_free(linklist H)
{
    if (H == NULL) {
        return NULL;
    }

    linklist p;
    while (H != NULL) {
        p = H;
        H = H->next;
        free(p);
    }
    return NULL;
}
linklist list_find(linklist H, data_t value)
{
    if (H == NULL) {
        return NULL;
    }
    linklist p = H, q;
    while (p != NULL) {
        if (p->data == value) {
            q = p;
            return q;
        }
        p = p->next;
    }
    return NULL;
}