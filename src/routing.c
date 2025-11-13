#include "routing.h"

struct Route *Search_route(struct Route *root, char *key){
    if(root == NULL){
        return NULL;
    }
    if(strcmp(key, root->key) == 0){
        return root;
    }
    if(strcmp(key, root->key) < 0){
        search_route(root->left, key);
    }
    if(strcmp(key, root->key) > 0){
        search_route(root->right, key);
    }
    // No debería llegar pero asi no me sale un warning en el editor
    return NULL;
}

struct Route *Init_route(char *key, char *value){
    struct Route *ruta = (struct Route *)malloc(sizeof(struct Route));
    ruta->key = key;
    ruta->value = value;
    ruta->height = 1;
    ruta->left = NULL;
    ruta->right = NULL;
    return ruta;
}

int height_route(struct Route *root){
    if(root == NULL){
        return 0;
    }else {
        return root->height;
    }
}

int max(int a, int b){
    if(a > b) return a;
    return b;
    // return (a > b)? a : b;
}

int check_balance(struct Route *left, struct Route *right){
    int balance = height_route(left) - height_route(right);
    return balance;
}

struct Route *r_rotate(struct Route *node){
    struct Route *new_root = node->left;
    
    node->left = new_root->right;
    new_root->right = node;

    node->height = 1 + max(height_route(node->left), height_route(node->right));
    new_root->height = 1 + max(height_route(new_root->left), height_route(new_root->right));

    return new_root;
}

struct Route *l_rotate(struct Route *node){
    struct Route *new_root = node->right;

    node->right = new_root->left;
    new_root->left = node;

    node->height = 1 + max(height_route(node->left), height_route(node->right));
    new_root->height = 1 + max(height_route(new_root->left), height_route(new_root->right));

    return new_root;
}

struct Route *Insert_route(struct Route *root, char *key, char *value){
    struct Route *node;
    if(root == NULL){
        root = init_route(key, value);
        return root;
    }else if(strcmp(key, root->key) == 0){
        printf("Ya existe esta ruta!!");
        exit(1);
    }else if(strcmp(key, root->key) < 0){
        root->left = insert_route(root->left, key, value);
    }else if(strcmp(key, root->key) > 0){
        root->right = insert_route(root->right, key, value);
    }

    root->height = 1 + max(height_route(root->left), height_route(root->right));
    int balance  = check_balance(root->left, root->right); 
    if(balance > 1){
        if(strcmp(key, root->left->key) < 0){
            // left left
            return r_rotate(root);
        }else{
            // left right
            root->left = l_rotate(root->left);
            return r_rotate(root);
        }
    }else if(balance < -1){
        if(strcmp(key, root->right->key) > 0){
            // right right
            return l_rotate(root);
        }else{
            // right left
            root->right = r_rotate(root->right);
            return l_rotate(root);
        }
    }
    return root;
}

void Print_tree(struct Route *root){
    if(root != NULL){
        printf("%s ", root->key);
        Print_tree(root->left);
        Print_tree(root->right);
    }
}
