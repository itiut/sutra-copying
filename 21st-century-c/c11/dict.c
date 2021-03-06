#include <stdio.h>
#include <stdlib.h>
#include "dict.h"

void *dictionary_not_found;

dictionary_s *dictionary_new() {
    static int dnf;
    if (!dictionary_not_found) {
        dictionary_not_found = &dnf;
    }
    dictionary_s *out = malloc(sizeof(dictionary_s));
    *out = (dictionary_s){};
    return out;
}

static void dictionary_add_keyval(dictionary_s *in, keyval *kv) {
    in->length++;
    in->pairs = realloc(in->pairs, sizeof(keyval *) * in->length);
    in->pairs[in->length - 1] = kv;
}

void dictionary_add(dictionary_s *in, char *key, void *value) {
    if (!key) {
        fprintf(stderr, "NULL is not a valid key.\n");
        abort();
    }
    dictionary_add_keyval(in, keyval_new(key, value));
}

void *dictionary_find(dictionary_s const *in, char const *key) {
    for (int i = 0; i < in->length; i++) {
        if (keyval_matches(in->pairs[i], key)) {
            return in->pairs[i]->value;
        }
    }
    return dictionary_not_found;
}

dictionary_s *dictionary_copy(dictionary_s *in) {
    dictionary_s *out = dictionary_new();
    for (int i = 0; i < in->length; i++) {
        dictionary_add_keyval(out, keyval_copy(in->pairs[i]));
    }
    return out;
}

void dictionary_free(dictionary_s *in) {
    for (int i = 0; i < in->length; i++) {
        keyval_free(in->pairs[i]);
    }
    free(in);
}
