#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    char* maze;
} maze_t;

void maze_init(maze_t* maze, int n, char floor, char wall) {
    maze->n = n;
    maze->maze = (char*) malloc(n * n);
    for (int i = 0; i < n; ++i) {
        int wall_len = i % 2 ? 0 : 1 + rand() % (n - 2);
        for (int j = 0; j < n; ++j, --wall_len) {
            maze->maze[j + i * n] = floor;
            if (((i % 2 == 0) && (j % 2 == 0)) || i == 0 || i == n - 1 || j == 0 || j == n - 1 || wall_len > 0) {
                maze->maze[j + i * n] = wall;
            }
        }
    }
}

void maze_set(maze_t* maze, int i, int j, char c) {
    maze->maze[j + i * maze->n] = c;
}

char maze_get(maze_t* maze, int i, int j) {
    return maze->maze[j + i * maze->n];
}

int main(int argc, char** argv) {
    int n = 13;
    int seed = 42;
    char floor = '*';
    char wall = '#';
    maze_t maze;

    srand(seed);
    maze_init(&maze, n, floor, wall);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            putc(maze_get(&maze, i, j), stdout);
        }
        putc('\n', stdout);
    }

    return 0;
}
