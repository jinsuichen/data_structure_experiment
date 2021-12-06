#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 100
#define MAX_NAME_LENGTH 20
#define MAX_CHARACTOR_NUM 52
#define INF 0x3f3f3f3f

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
        if (node->child[(*p >= 'a') ? (*p - 'a') : (*p - 'A')] == NULL) { /* 对应的节点不存在，则申请一个节点 */
            node->child[(*p >= 'a') ? (*p - 'a') : (*p - 'A')] = create_trie_node();
        }
        node = node->child[(*p >= 'a') ? (*p - 'a') : (*p - 'A')]; /* 指向子节点 */
        p++;
    }
    node->id = top++;
}

int trie_search(Trie *obj, char *word) {
    Trie *node = obj;
    char *p = word;

    while (*p && node != NULL) {
        node = node->child[(*p >= 'a') ? (*p - 'a') : (*p - 'A')]; /* 循环在树中查找所有节点 */
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

typedef struct arc_node {
    int id;
    int price;
    int distance;
    struct arc_node *nxt;
} ArcNode;

typedef struct vertex {

    int id;
    ArcNode *head;

} Vertex;


typedef struct graph {

    Vertex *vertices[MAX_VERTEX_NUM];

} Graph;


Graph *create_graph() {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->vertices[i] = (Vertex *) malloc(sizeof(Vertex));
        graph->vertices[i]->head = (ArcNode *) malloc(sizeof(ArcNode));
        graph->vertices[i]->head->nxt = NULL;
        graph->vertices[i]->id = i;
    }
    return graph;
}

void dispose_list(ArcNode *head) {
    if (head->nxt) dispose_list(head->nxt);
    free(head);
}

void dispose_graph(Graph *graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        dispose_list((ArcNode *) graph->vertices[i]->head);
        free(graph->vertices[i]);
    }
    free(graph);
}

void add_edge(Graph *graph, int u, int v, int price, int distance) {

    ArcNode *new_node = (ArcNode *) malloc(sizeof(ArcNode));
    new_node->id = v;
    new_node->price = price;
    new_node->distance = distance;

    ArcNode *head = graph->vertices[u]->head;
    new_node->nxt = head->nxt;
    head->nxt = new_node;

}

int visited[MAX_VERTEX_NUM];
int weight[MAX_VERTEX_NUM];

int prim(Graph *graph, int n) {

    memset(visited, 0, sizeof(visited));
    memset(weight, 0x3f, sizeof(weight));
    weight[0] = 0;
    int v, cnt = 0;
    for (int i = 0; i < n; i++) {
        int min = INF;
        for (int j = 0; j < n; j++)
            if (!visited[j] && min > weight[j]) {
                min = weight[j];
                v = j;
            }
        if (min == INF)
            return cnt;
        cnt += min;
        visited[v] = 1;

        ArcNode *p_move = graph->vertices[v]->head->nxt;
        while (p_move) {
            if (!visited[p_move->id] && weight[p_move->id] > p_move->distance) {
                weight[p_move->id] = p_move->distance;
            }
            p_move = p_move->nxt;
        }
    }
    return cnt;
}


int main() {
    freopen("services.txt", "r", stdin);
    Graph *graph = create_graph();
    trie = create_trie();

    char u_name[MAX_NAME_LENGTH];
    char v_name[MAX_NAME_LENGTH];
    int price;
    int distance;
    int tot = 0;
    while (scanf("%s%s%d%d", u_name, v_name, &price, &distance) != EOF) {
        int u_id = get_id(u_name);
        int v_id = get_id(v_name);
        add_edge(graph, u_id, v_id, price, distance);
    }

    printf("%d\n", prim(graph, top));

    dispose_trie(trie);
    dispose_graph(graph);
    freopen("CON", "r", stdin);
    return 0;
}
