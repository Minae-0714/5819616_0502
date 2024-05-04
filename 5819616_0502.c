#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

typedef char element;  // 데이터 타입을 int에서 char로 변경하여 문자 처리 가능하게 함

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);  // 오류 시 프로그램 종료
}

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_full_queue(QueueType* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

int is_empty_queue(QueueType* q) {
    return q->front == q->rear;
}

void enqueue(QueueType* q, element item) {
    if (is_full_queue(q)) {
        error("큐가 가득 찼습니다.");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty_queue(q)) {
        error("큐가 비어 있습니다.");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

void init_stack(StackType* s) {
    s->top = -1;
}

int is_full_stack(StackType* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

int is_empty_stack(StackType* s) {
    return s->top == -1;
}

void push(StackType* s, element item) {
    if (is_full_stack(s)) {
        error("스택이 가득 찼습니다.");
    }
    s->data[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty_stack(s)) {
        error("스택이 비어 있습니다.");
    }
    return s->data[(s->top)--];
}

int check_palindrome(char* str) {
    QueueType q;
    StackType s;

    init_queue(&q);
    init_stack(&s);

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalnum(str[i])) {  
            char ch = tolower(str[i]);  
            enqueue(&q, ch);
            push(&s, ch);
        }
    }

    while (!is_empty_queue(&q)) {
        char ch1 = dequeue(&q);
        char ch2 = pop(&s);
        if (ch1 != ch2) {
            return 0;  // 회문이 아님
        }
    }
    return 1;  // 회문임
}

int main() {
    int choice;
    char str[MAX_QUEUE_SIZE];  

    while (1) {
        printf("1. 회문 입력\n");
        printf("2. 회문 검사\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        while (getchar() != '\n');  

        switch (choice) {
        case 1:
            printf("회문을 입력하세요: ");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = 0;  
            break;

        case 2:
            if (check_palindrome(str)) {
                printf("회문입니다.\n");
            }
            else {
                printf("회문이 아닙니다.\n");
            }
            break;
        case 3:
            return 0; 

        default:
            printf("잘못된 메뉴 선택입니다.\n");
            break;
        }
    }
    return 0;
}
