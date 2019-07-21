#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 262144

typedef struct entry_t {
    char *key;
    char *value;
    struct entry_t *next;
} entry_t;

typedef struct {
    entry_t **entries;
} ht_t;

ht_t *ht_create(void);
void ht_set(ht_t *, const char *, const char *);
char *ht_get(ht_t *, const char *);
void ht_destroy(ht_t *);
void ht_dump(ht_t *);

#endif
