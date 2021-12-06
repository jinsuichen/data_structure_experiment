#include <stdio.h>
#include <stdlib.h>


double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a > b ? b : a;
}

struct Student {
    char name[20];
    int chinese_score;
    int math_score;
};

typedef struct Student Data;

struct Node {
    Data data;
    struct Node *nxt;
};

struct Node *create_node(Data data) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->nxt = NULL;
    new_node->data = data;
    return new_node;
}

struct Node *create_list() {
    struct Node *list = (struct Node *) malloc(sizeof(struct Node));
    list->nxt = NULL;
    return list;
}

void print_list(struct Node *head_node) {

    if (!head_node->nxt) {
        printf("no data now\n");
        return;
    }


    int cnt = 0;
    Data max_score = head_node->nxt->data;
    Data min_score = head_node->nxt->data;
    Data average_score;
    average_score.chinese_score = 0;
    average_score.math_score = 0;
    struct Node *p_move = head_node->nxt;

    printf("id\tname\tchinese\t\tmath\ttotal\n");

    while (p_move) {
        max_score.chinese_score = max(max_score.chinese_score, p_move->data.chinese_score);
        max_score.math_score = max(max_score.math_score, p_move->data.math_score);
        min_score.chinese_score = min(min_score.chinese_score, p_move->data.chinese_score);
        min_score.math_score = min(min_score.math_score, p_move->data.math_score);
        average_score.chinese_score += p_move->data.chinese_score;
        average_score.math_score += p_move->data.math_score;

        printf("%02d\t%s\t\t%3d\t\t%3d\n",
               ++cnt,
               p_move->data.name,
               p_move->data.chinese_score,
               p_move->data.math_score);

        p_move = p_move->nxt;
    }

    printf("  \tmax\t\t%3d\t\t%3d\n", max_score.chinese_score, max_score.math_score);
    printf("  \tmin\t\t%3d\t\t%3d\n", min_score.chinese_score, min_score.math_score);
    printf("  \ttot\t\t%3d\t\t%3d\n", average_score.chinese_score, average_score.math_score);
    printf("  \tavg\t\t%3d\t\t%3d\n", average_score.chinese_score / cnt, average_score.math_score / cnt);

}

void insert(struct Node *headNode, Data data) {
    struct Node *new_node = create_node(data);
    new_node->nxt = headNode->nxt;
    headNode->nxt = new_node;
}

void delete_by_appoint_pos(struct Node *head_node, int pos) {
    struct Node *p_move = head_node;
    for (int i = 0; i < pos - 1; i++) {
        if (!p_move->nxt) {
            return;
        }
        p_move = p_move->nxt;
    }
    if (!p_move->nxt) {
        return;
    }
    struct Node *tmp = p_move->nxt;
    p_move->nxt = tmp->nxt;
    free(tmp);
}

void dispose_list(struct Node *s) {
    if (s != NULL) {
        free(s->nxt);
        free(s);
    }
}

int main() {

    struct Node *list = create_list();

    while (1) {

        printf("please select:\n");
        printf("\t0.exit\n");
        printf("\t1.show all infos\n");
        printf("\t2.add\n");
        printf("\t3.delete\n");

        int choice;
        scanf("%d", &choice);
        if (choice == 0) {
            dispose_list(list);
            break;
        } else if (choice == 1) {
            print_list(list);
        } else if (choice == 2) {
            Data data;
            printf("Please input your name: ");
            scanf("%s", data.name);
            printf("Please input your chinese score: ");
            scanf("%d", &data.chinese_score);
            printf("Please input your math score: ");
            scanf("%d", &data.math_score);

            insert(list, data);
        } else if (choice == 3) {
            printf("please input id you want to delete: ");
            int id;
            scanf("%d", &id);
            delete_by_appoint_pos(list, id);
        }

    }

    return 0;
}