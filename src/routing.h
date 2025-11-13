#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Enrutador usando un AVL tree.
// Realmente no se van a añadir tantas rutas como para que valga la pena, pero
// El BST podía quedar muy desvalanceado
// Puede que 

struct Route {
    char *key;
    char *value;
    int height;
    struct Route *left, *right;
};

struct Route *Search_route(struct Route *root, char *key);
struct Route *Insert_route(struct Route *root, char *key, char *value);
// No hace falta borrar
// struct Route *delete_route(struct Route *root, char *key, char *value);
struct Route *Init_route(char *key, char *value);
void Print_tree(struct Route *root);
