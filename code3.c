#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20
#define MAX_NAME_LENGTH 25

#define MAX_CHARACTOR_NUM 27

typedef struct tire_node {
    int id; /* 该节点的单次数量 */
    struct tire_node *child[MAX_CHARACTOR_NUM];
} Trie;

Trie *create_trie_node() {
    Trie *obj = (Trie *) malloc(sizeof(Trie));
    if (obj == NULL) {
        return NULL;
    }
    obj->id = -1;
    for (int i = 0; i < MAX_CHARACTOR_NUM; i++) {
        obj->child[i] = NULL;
    }
    return obj;
}

Trie *create_trie() {
    return create_trie_node();
}

int top = 0;

void trie_insert(Trie *obj, char *word) {
    char *p = word;
    Trie *node = obj;
    while (*p) {
        if (node->child[(*p == '_') ? 26 : (*p - 'a')] == NULL) { /* 对应的节点不存在，则申请一个节点 */
            node->child[(*p == '_') ? 26 : (*p - 'a')] = create_trie_node();
        }
        node = node->child[(*p == '_') ? 26 : (*p - 'a')]; /* 指向子节点 */
        p++;
    }
    node->id = top++;
}

int trie_search(Trie *obj, char *word) {
    Trie *node = obj;
    char *p = word;

    while (*p && node != NULL) {
        node = node->child[(*p == '_') ? 26 : (*p - 'a')]; /* 循环在树中查找所有节点 */
        p++;
    }

    if (node == NULL) {
        return -1;
    } else {
        return node->id;
    }
}

void dispose_trie(Trie *obj) {
    if (obj != NULL) {
        free(obj);
    }
}

Trie *trie;

int get_id(char *s) {
    int id = trie_search(trie, s);
    if (id == -1) {
        trie_insert(trie, s);
        int new_id = trie_search(trie, s);
        return new_id;
    } else {
        return id;
    }
}

typedef struct children_node {
    int child_id;
    struct children_node *next;
} ChildPtr;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int val;
    ChildPtr *head;
} Node;

typedef struct {
    Node nodes[MAX_SIZE];
} Tree;

Tree tree;

void init_tree() {
    freopen("definitions.txt", "r", stdin);
    for (int i = 0; i < MAX_SIZE; i++) {
        tree.nodes[i].head = (ChildPtr *) malloc(sizeof(Node));
        tree.nodes[i].head->next = NULL;
    }

    char name[MAX_NAME_LENGTH];
    char son_name[MAX_NAME_LENGTH];
    int val;
    while (scanf("%s%d%s", name, &val, son_name) != EOF) {
        int id = get_id(name);
        int son_id = get_id(son_name);
        ChildPtr *first = tree.nodes[id].head;
        ChildPtr *new_children = (ChildPtr *) malloc(sizeof(ChildPtr));
        new_children->child_id = son_id;
        tree.nodes[son_id].val = val;
        strcpy(tree.nodes[son_id].name, son_name);
        new_children->next = first->next;
        first->next = new_children;
    }

    freopen("CON", "r", stdin);

}


void dispose_tree_list(ChildPtr *p) {
    if (p->next) dispose_tree_list(p->next);
    free(p);
}

void dispose_tree(Tree tree) {
    for (int i = 0; i < MAX_SIZE; i++) {
        dispose_tree_list(tree.nodes[i].head);
    }
}

void display_what_is(char *name) {
    printf("Part %s subparts are:\n", name);
    int id = get_id(name);
    Node node = tree.nodes[id];
    ChildPtr *p_move = node.head->next;
    while (p_move) {
        printf("\t%d %s\n", tree.nodes[p_move->child_id].val, tree.nodes[p_move->child_id].name);
        p_move = p_move->next;
    }
}

void display_how_many(char *son_name, char *fa_name) {
    int son_id = get_id(son_name);
    int fa_id = get_id(fa_name);
    Node node = tree.nodes[fa_id];
    ChildPtr *p_move = node.head->next;
    while (p_move) {
        if (p_move->child_id == son_id) {
            int cnt = tree.nodes[p_move->child_id].val;
            printf("%s has %d %s\n", fa_name, cnt, son_name);
            return;
        }
        p_move = p_move->next;
    }
    printf("%s has 0 %s\n", fa_name, son_name);
}

int main() {
    trie = create_trie();
    init_tree();

    //for test
    //freopen("op.txt", "r", stdin);

    char line[1000];
    while (fgets(line, 1000, stdin) != NULL) {
        char op[10];
        sscanf(line, "%s", op);
        if (!strcmp(op, "what")) {
            char name[MAX_NAME_LENGTH];
            sscanf(line, "%s%s%s", op, op, name);
            display_what_is(name);
        } else {
            char son_name[MAX_NAME_LENGTH];
            char fa_name[MAX_NAME_LENGTH];
            sscanf(line, "%s%s%s%s", op, op, son_name, fa_name);
            display_how_many(son_name, fa_name);
        }
    }
    dispose_trie(trie);
    dispose_tree(tree);
    return 0;
}