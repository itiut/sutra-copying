// clang charct.c ../c09/string_utilities.c process_dir.c unictr.c $(pkg-config --cflags --libs glib-2.0)
#include <glib.h>
#include <stdlib.h>
#include "../c09/string_utilities.h"
#include "process_dir.h"
#include "unictr.h"

void hash_a_file(filestruct path) {
    GHashTable *hash = path.data;
    char *sf = string_from_file(path.fullname);
    if (!sf) {
        return;
    }
    char *sf_copy = sf;
    if (g_utf8_validate(sf, -1, NULL)) {
        for (gunichar uc; (uc = g_utf8_get_char(sf)) != '\0'; sf = g_utf8_next_char(sf)) {
            hash_a_character(uc, hash);
        }
    }
    free(sf_copy);
}

int main(int argc, char **argv) {
    GHashTable *hash = new_unicode_couting_hash();
    char *start = NULL;
    if (argc > 1) {
        asprintf(&start, "%s", argv[1]);
    }
    printf("Hashing %s\n", start ? start : "the current directory");
    process_dir(.name = start, .file_action = hash_a_file, .data = hash);
    g_hash_table_foreach(hash, printone, NULL);
}
