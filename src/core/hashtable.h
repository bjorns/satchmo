#pragma once
#include "core/str.h"

struct hash_entry {
	str_t key;
	void *value;
	struct hash_entry *next;
};
typedef struct hash_entry hash_entry_t;

typedef struct {
	int size;
	hash_entry_t **table;
} hashtable_t;


/**
 * Create new hashtable
 */
hashtable_t *new_hashtable(int size);

/**
 * Insert a key-value pair into a hash table.
 */
void ht_set(hashtable_t *hashtable, const str_t key, void *value);


/**
 * Retrieve value
 */
void *ht_get(hashtable_t *hashtable, const str_t key);
