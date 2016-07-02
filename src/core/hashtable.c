#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "hashtable.h"

hashtable_t *new_hashtable(int size) {
    hashtable_t *hashtable = NULL;
    int i;

    if (size < 1) {
        return NULL;
    }

    /* Allocate the table itself. */
    if ((hashtable = calloc(1, sizeof(hashtable_t))) == NULL) {
        return NULL;
    }

    /* Allocate pointers to the head nodes. */
    if ((hashtable->table = calloc(size, sizeof(hash_entry_t*)) ) == NULL) {
        return NULL;
    }
    for (i = 0; i < size; i++) {
        hashtable->table[i] = NULL;
    }

    hashtable->size = size;
    return hashtable;
}

/**
 * Hash a string for a particular hash table.
 */
static int _hash( hashtable_t *hashtable, str_t key ) {
    unsigned long int hashval = 0;
    int i = 0;

    /* Convert our string to an integer */
    const char *data = key.data;
    while (hashval < ULONG_MAX && i < key.length) {
        hashval = hashval << 8;
        hashval += data[i];
        i++;
    }
    return hashval % hashtable->size;
}

/**
 * Create a key-value pair.
 */
static hash_entry_t *ht_newpair(str_t key, void *value) {
    hash_entry_t *newpair;

    if ((newpair = malloc(sizeof(hash_entry_t))) == NULL) {
        return NULL;
    }

    newpair->key = str_copy(key);
    newpair->value = value;

    newpair->next = NULL;

    return newpair;
}

void ht_set(hashtable_t *hashtable, const str_t key, void *value) {
    int bin = 0;
    hash_entry_t *newpair = NULL;
    hash_entry_t *next = NULL;
    hash_entry_t *last = NULL;

    bin = _hash(hashtable, key);

    next = hashtable->table[bin];

    while (next != NULL && next->key.data != NULL && !str_eq(key, next->key)) {
        last = next;
        next = next->next;
    }

    /* There's already a pair.  Let's replace that string. */
    if (next != NULL && next->key.data != NULL && str_eq(key, next->key)) {
        free( next->value );
        next->value = strdup( value );
    } else {
        newpair = ht_newpair(key, value);

        /* We're at the start of the linked list in this bin. */
        if( next == hashtable->table[bin] ) {
            newpair->next = next;
            hashtable->table[ bin ] = newpair;

            /* We're at the end of the linked list in this bin. */
        } else if ( next == NULL ) {
            last->next = newpair;

            /* We're in the middle of the list. */
        } else  {
            newpair->next = next;
            last->next = newpair;
        }
    }
}

/**
 * Retrieve a key-value pair from a hash table.
 */
void *ht_get(hashtable_t *hashtable, const str_t key) {
    int bin = 0;
    hash_entry_t *pair;

    bin = _hash(hashtable, key);

    /* Step through the bin, looking for our value. */
    pair = hashtable->table[ bin ];
    while (pair != NULL && pair->key.data != NULL && !str_eq(key, pair->key)) {
        pair = pair->next;
    }

    /* Did we actually find anything? */
    if (pair == NULL || pair->key.data == NULL || !str_eq(key, pair->key)) {
        return NULL;
    } else {
        return pair->value;
    }
}
