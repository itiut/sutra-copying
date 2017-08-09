#include <glib.h>
#include <stdlib.h>
#include "../c09/string_utilities.h"
#include "process_dir.h"
#include "unictr.h"

typedef struct {
    int count;
} count_s;

void hash_a_character(gunichar uc, GHashTable *hash) {
    count_s *ct = g_hash_table_lookup(hash, &uc);
    if (!ct) {
        ct = calloc(1, sizeof(count_s));
        gunichar *newchar = malloc(sizeof(gunichar));
        *newchar = uc;
        g_hash_table_insert(hash, newchar, ct);
    }
    ct->count++;
}

void printone(void *key_in, void *val_in, void *ignored) {
    gunichar const *key = key_in;
    count_s const *val = val_in;
    char utf8[7];
    utf8[g_unichar_to_utf8(*key, utf8)] = '\0';
    printf("%s\t%i\n", utf8, val->count);
}

static gboolean equal_chars(void const * a_in, void const * b_in) {
    gunichar const *a = a_in;
    gunichar const *b = b_in;
    return (*a == *b);
}

GHashTable *new_unicode_couting_hash() {
    return g_hash_table_new(g_str_hash, equal_chars);
}
