#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10
typedef struct {
    short r;
    short c;
} element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
    s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
StackType* s;
// �����Լ�
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return;
    }
    else return s->data[(s->top)--];
}
//��ũ�Լ�
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return;
    }
    else return s->data[(s->top)];
}

element here = { 1,0 }, entry = { 1,0 };
char maze[MAZE_SIZE][MAZE_SIZE] = {

        {'1','1','1','1','1','1','1','1','1','1'},

        {'e','1','0','1','0','0','0','1','0','1'},

        {'0','0','0','1','0','0','0','1','0','1'},

        {'0','1','0','0','0','1','1','0','0','1'},

        {'1','0','0','0','1','0','0','0','0','1'},

        {'1','0','0','0','1','0','0','0','0','1'},

        {'1','0','0','0','0','0','1','0','1','1'},

        {'1','0','1','1','1','0','1','1','0','1'},

        {'1','1','0','0','0','0','0','0','0','x'},

        {'1','1','1','1','1','1','1','1','1','1'}

};
// ��ġ�� ���ÿ� ����
void push_loc(StackType* s, int r, int c)
{
    if (r < 0 || c < 0) return;
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("-------------\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void)
{
    int r, c;
    int count = 0;
    
    StackType s;
    StackType s1;
    StackType s2;
    StackType s3;
    StackType s4;

    init_stack(&s);
    init_stack(&s1);
    init_stack(&s2);
    init_stack(&s3);
    init_stack(&s4);

    push(&s2, here);
    push(&s4, here);
    while (maze[here.r][here.c] != 'x') {

        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);

        if (is_empty(&s)) {
            printf("������ ���� �����ϴ�.\n");
            return;
        }
        else {
            // ������ ��ǥ��  s1�� ����-------------------------------------------
            if ((maze[r - 1][c] != '1' && maze[r - 1][c] != '.') &&
                (maze[r + 1][c] != '1' && maze[r + 1][c] != '.')) {
                push(&s1, here);
            }
            else if ((maze[r - 1][c] != '1' && maze[r - 1][c] != '.') &&
                (maze[r][c - 1] != '1' && maze[r][c - 1] != '.')) {
                push(&s1, here);
            }
            else if ((maze[r - 1][c] != '1' && maze[r - 1][c] != '.') &&
                (maze[r][c + 1] != '1' && maze[r][c + 1] != '.')) {
                push(&s1, here);
            }
            else if ((maze[r + 1][c] != '1' && maze[r + 1][c] != '.') &&
                (maze[r][c - 1] != '1' && maze[r][c - 1] != '.')) {
                push(&s1, here);
            }
            else if ((maze[r + 1][c] != '1' && maze[r + 1][c] != '.') &&
                (maze[r][c + 1] != '1' && maze[r][c + 1] != '.')) {
                push(&s1, here);
            }
            else if ((maze[r][c - 1] != '1' && maze[r][c - 1] != '.') &&
                (maze[r][c + 1] != '1' && maze[r][c + 1] != '.')) {
                push(&s1, here);
            }
            //----------------------------------------------------------------------------
            here = pop(&s);
            
            //��� ������ ������ �� �̰ų� ���϶� 
            if ((maze[r - 1][c] == '.' || maze[r - 1][c] == '1')
                && (maze[r + 1][c] == '.' || maze[r + 1][c] == '1')
                && (maze[r][c - 1] == '.' || maze[r][c - 1] == '1')
                && (maze[r][c + 1] == '.' || maze[r][c + 1] == '1')) {

                pop(&s2);

                //s1.top�� s3.top�� ���������� s3�� poo�Ͽ� s2�� push
                while (!is_empty(&s3)&& !is_empty(&s1) && !(s3.top==s1.top)) {
                    element tmp = pop(&s3);
                    push(&s2, tmp);
                }
                while (!is_empty(&s4) && !is_empty(&s1) && !(s4.top-2 == s1.top)) {
                    element tmp = pop(&s4);
                    
                }

                pop(&s1);
                push(&s2, here);
                push(&s4, here);
            }
            else {
                push(&s2, here);
                push(&s3, here);
                push(&s4, here);
            }
           
            
        }
        
    }
    printf("-------------\n����\n");
    init_stack(&s3);

    printf("�̵� ���:");
    while (!is_empty(&s2)) {
        element tmp = pop(&s2);
        push(&s3, tmp);
    }

    while (!is_empty(&s3)) {
        element tmp = pop(&s3);
        printf("(%d,%d)", tmp.r, tmp.c);
    }
    printf("\n\n");

    init_stack(&s2);
    printf("�ǵ��ư��� ���� ������ ���: ");
    while (!is_empty(&s4)) {
        element tmp = pop(&s4);
        push(&s2, tmp);
    }

    while (!is_empty(&s2)) {
        element tmp = pop(&s2);
        printf("(%d,%d)", tmp.r, tmp.c);
    }
   
    printf("\n");
    system("pause");
    return 0;
}
