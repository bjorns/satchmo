#pragma once

struct hash_entry {
	char *key;
	char *value;
	struct hash_entry *next;
};

typedef struct hash_entry hash_entry_t;

typedef struct {
	int size;
	hash_entry_t **table;
} hashtable_t;

hashtable_t *ht_create(int size);

void ht_set(hashtable_t *hashtable, char *key, char *value);
char *ht_get( hashtable_t *hashtable, char *key );
