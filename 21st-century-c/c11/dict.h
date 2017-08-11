#include "keyval.h"

extern void *dictionary_not_found;

typedef struct dictionary_s {
    keyval **pairs;
    int length;
} dictionary_s;

dictionary_s *dictionary_new();
dictionary_s *dictionary_copy(dictionary_s *in);
void dictionary_free(dictionary_s *in);
void dictionary_add(dictionary_s *in, char *key, void *value);
void *dictionary_find(dictionary_s const *in, char const *key);
