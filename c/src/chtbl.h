#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list.h"

//  Define a structure for chained hash tables
typedef struct CHTbl_ {
    int         buckets;
    int         size;
    int         (*hash)(const void* key);
    int         (*match)(const void* key1, const void* key2);
    void        (*destroy)(void* data);
    List*       table;
} CHTbl;

//  --------------------------- Public Interface ---------------------------
CHTbl* chtbl_create(int buckets, int(*match)(const void* key1, const void* key2));

void chtbl_destroy(CHTbl* htbl);

int chtbl_insert(CHTbl* htbl, const void* data);

int chtbl_remove(CHTbl* htbl, void** data);

int chtbl_lookup(const CHTbl* htbl, void** data);

unsigned int hashpjw(const void* key);

#define chtbl_size(htbl) ((htbl)->size)

#endif
