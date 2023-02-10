#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_POS -1//空栈
#define MIN_STACK_SIZE 5//栈的最小值

typedef int element_type;//数据类型

typedef struct stack_record {
    int capacity;//容量
    int stackTop;//栈顶
    element_type *array;
} Stack;


int is_empty(Stack *s) {
    return (s->stackTop == EMPTY_POS);
}

int is_full(Stack *s) {
    return (s->stackTop == s->capacity - 1);
}

void make_empty(Stack *s) {
    if (s != NULL) {
        s->stackTop = EMPTY_POS;
    }
}

Stack *create_stack(int max_elements) {
    Stack *s;

    if (max_elements < MIN_STACK_SIZE) {
        printf("Stack size is too small\n");
        return NULL;
    }
    s = (Stack *) malloc(sizeof(struct stack_record));
    s->array = (element_type *) malloc(sizeof(element_type) * max_elements);
    s->capacity = max_elements;
    make_empty(s);

    return s;

}

void dispose_stack(Stack *s) {
    if (s != NULL) {
        free(s->array);
        free(s);
    }
}


void push(element_type element, Stack *s) {
    if (!is_full(s)) {
        s->stackTop++;
        s->array[s->stackTop] = element;
    } else {
        printf("full stack\n");
    }
}

element_type top(Stack *s) {
    if (!is_empty(s)) {
        return s->array[s->stackTop];
    } else {
        return 0;
    }
}

element_type pop(Stack *s) {
    if (!is_empty(s)) {
        return s->array[s->stackTop--];
    } else {
        return 0;
    }
}


char str[1000];

Stack *num;
Stack *op;

int get_priority(char ch) {
    if (ch == '+' || ch == '-') return 1;
    else if (ch == '*' || ch == '/') return 2;
    else return 0;
}


void eval() {

    int b = pop(num);
    int a = pop(num);
    int ch = pop(op);

    if (ch == '+') push(a + b, num);
    else if (ch == '-') push(a - b, num);
    else if (ch == '*') push(a * b, num);
    else if (ch == '/') push(a / b, num);

}

int main() {

    num = create_stack(1000);
    op = create_stack(1000);

    scanf("%s", str);
    for (int i = 0; str[i]; i++) {
        char ch = str[i];

        if (ch >= '0' && ch <= '9') {
            int j = i;
            int ret = 0;
            while (str[j] && str[j] >= '0' && str[j] <= '9') {
                ret = ret * 10 + str[j++] - '0';
            }
            i = j - 1;
            push(ret, num);
        } else if (ch == '(') {
            push('(', op);
        } else if (ch == ')') {
            while (top(op) != '(') {
                eval();
            }
            pop(op);
        } else {
            while (!is_empty(op) && get_priority(top(op)) >= get_priority(ch)) eval();
            push(ch, op);
        }

    }

    while (!is_empty(op)) eval();
    printf("The ans is: %d\n", top(num));


    dispose_stack(op);
    dispose_stack(num);

    return 0;
}
