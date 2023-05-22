#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define MAX_NAME_LEN 10

typedef struct {
    char name[MAX_NAME_LEN + 1];
    int size;
    char **primitives;
} Program;

typedef struct {
    int loop_iterator;
    int start_position;
} Loop;

void read_program(Program *program) {
    char buffer[1024];
    char *tokens[1024];

    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // remove trailing newline
    int num_tokens = 0;
    tokens[num_tokens] = strtok(buffer, " ");
    while (tokens[num_tokens] != NULL) {
        num_tokens++;
        tokens[num_tokens] = strtok(NULL, " ");
    }

    strcpy(program->name, tokens[0]);
    program->size = atoi(tokens[1]);

    program->primitives = malloc(sizeof(char*) * program->size);
    for (int i = 0; i < program->size; i++) {
        program->primitives[i] = malloc(sizeof(char) * 2);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0; // remove trailing newline
        num_tokens = 0;
        tokens[num_tokens] = strtok(buffer, " ");
        while (tokens[num_tokens] != NULL) {
            num_tokens++;
            tokens[num_tokens] = strtok(NULL, " ");
        }
        if (strcmp(tokens[0], "DOOP") == 0) {
            program->primitives[i][0] = 0;
            program->primitives[i][1] = atoi(tokens[1]);
        } else if (strcmp(tokens[0], "BLOCK") == 0) {
            program->primitives[i][0] = 1;
            program->primitives[i][1] = atoi(tokens[1]);
        } else if (strcmp(tokens[0], "LOOP") == 0) {
            program->primitives[i][0] = 2;
            program->primitives[i][1] = atoi(tokens[1]);
        } else if (strcmp(tokens[0], "END") == 0) {
            program->primitives[i][0] = 3;
            program->primitives[i][1] = 0;
        } else { // halt
            program->primitives[i][0] = 4;
            program->primitives[i][1] = 0;
        }
    }
}

void free_program(Program *program) {
    for (int i = 0; i < program->size; i++) {
        free(program->primitives[i]);
    }
    free(program->primitives);
}

void simulate_program(Program *program) {
    int time = 0, doopCount = 0, doopTime = 0, blockCount = 0, blockTime = 0;
    int curPrimitive = 0;
    Stack* stack = stack_initialize(sizeof(Loop), "Loop");

    while (curPrimitive < program->size) {
        if (program->primitives[curPrimitive][0] == 0) {
            int ticks = program->primitives[curPrimitive][1];
            printf("%05d: DOOP\n", time);
            time += ticks;
            doopCount++;
            doopTime += ticks;
            curPrimitive++;
        } else if (program->primitives[curPrimitive][0] == 1) {
            int ticks = program->primitives[curPrimitive][1];
            printf("%05d: BLOCK\n", time);
            time += ticks;
            blockCount++;
            blockTime += ticks;
            curPrimitive++;
        } else if (program->primitives[curPrimitive][0] == 2) {
            Loop *loop = malloc(sizeof(Loop));
            loop->loop_iterator = program->primitives[curPrimitive][1];
            loop->start_position = curPrimitive + 1;
            stack_push(stack, loop);
            curPrimitive++;
        } else if (program->primitives[curPrimitive][0] == 3) {
            Loop *loop = (Loop *)stack_peek(stack);
            if (loop->loop_iterator > 1) {
                loop->loop_iterator--;
                curPrimitive = loop->start_position;
            } else {
                stack_pop(stack);
                curPrimitive++;
                free(loop);
            }
        } else if (program->primitives[curPrimitive][0] == 4) {
            printf("%05d: HALT\n", time);
            break;
        } else {
            curPrimitive++;
        }
    }

    printf("\n");
    printf("DOOP count : %d\n", doopCount);
    printf("DOOP time  : %d\n", doopTime);
    printf("BLOCK count: %d\n", blockCount);
    printf("BLOCK time : %d\n", blockTime);
}

int main() {
    Program program;
    read_program(&program);
    simulate_program(&program);
    free_program(&program);
    return 0;
}
