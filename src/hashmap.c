#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

unsigned int hash(const char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // hash method 1 (expo)
    //for (; i < key_len; ++i) {
    //    value += 97 ^ (key_len - i + 1) * key[i];
    //    value = value % TABLE_SIZE;
    //}

    // hash method 2 (multiplication)
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }
    value = value % TABLE_SIZE;

    return value;
}

entry_t *ht_pair(const char *key, const char *value) {
    // allocate the entry
    entry_t *entry = malloc(sizeof(entry) * 1);
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    // copy the key and value in place
    strcpy(entry->key, key);
    strcpy(entry->value, value);

    // next starts out null but may be set later on
    entry->next = NULL;

    return entry;
}

ht_t *ht_create(void) {
    // allocate table
    ht_t *hashtable = malloc(sizeof(ht_t) * 1);

    // allocate table entries
    hashtable->entries = malloc(sizeof(entry_t*) * TABLE_SIZE);

    // set each to null (needed for proper operation)
    int i = 0;
    for (; i < TABLE_SIZE; ++i) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set(ht_t *hashtable, const char *key, const char *value) {
    unsigned int bucket = hash(key);

    // try to look up an entry set
    entry_t *entry = hashtable->entries[bucket];

    // no entry means bucket empty, insert immediately
    if (entry == NULL) {
        hashtable->entries[bucket] = ht_pair(key, value);
        return;
    }

    entry_t *prev;

    // walk through each entry until either the end is reached or a matching key is found
    while (entry != NULL) {
        // check key
        if (strcmp(entry->key, key) == 0) {
            // match found, replace value
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;
    }

    // end of chain reached without a match, add new
    prev->next = ht_pair(key, value);
}

char *ht_get(ht_t *hashtable, const char *key) {
    unsigned int bucket = hash(key);

    // try to find a valid bucket
    entry_t *entry = hashtable->entries[bucket];

    // no bucket means no entry
    if (entry == NULL) {
        return NULL;
    }

    // walk through each entry in the bucket, which could just be a single thing
    while (entry != NULL) {
        // return value if found
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }

        // proceed to next key if available
        entry = entry->next;
    }

    // reaching here means there were >= 1 entries but no key match
    return NULL;
}

void ht_destroy(ht_t *hashtable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        // lookup first entry in the bucket
        entry_t *entry = hashtable->entries[i];

        // no entries, move on
        if (entry == NULL) {
            continue;
        }

        entry_t *next = entry->next;

        for (;;) {
            free(entry->key);
            free(entry->value);
            free(entry);

            // a null next means all entries in the chain have been free'd
            if (next == NULL) {
                break;
            }

            // replace entry with next entry, and next with the next entry's next
            entry = next;
            next = entry->next;
        }
    }

    free(hashtable->entries);
    free(hashtable);
}

void ht_dump(ht_t *hashtable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        entry_t *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("bucket[%d]: ", i);

        for(;;) {
            printf("%s=%s ", entry->key, entry->value);

            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}
