#ifndef HASHMAP_H
#define HASHMAP_H

#define TABLE_SIZE 262144

typedef struct entry_t {
    char *key;
    char *value;
    struct entry_t *next;
} entry_t;

typedef struct {
    entry_t **entries;
} hashtable_t;

hashtable_t *hashtable_create(void);
void hashtable_set(hashtable_t *, const char *, const char *);
char *hashtable_get(hashtable_t *, const char *);
void hashtable_destroy(hashtable_t *);
void hashtable_dump(hashtable_t *);

#endif
