#ifndef STRUCT_H
#define STRUCT_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 10

typedef enum {
    EMPTY = ' ',
    WALL = '#',
    PLAYER = 'o',
    BOX = 'X',
    GOAL = '.'
} Element;

typedef struct {
    int x;
    int y;
    char mouvement;
} PositionJoueur;

typedef struct {
    int x;
    int y;
} PositionBoite;

typedef struct {
    int x;
    int y;
} PositionEmplacement;

#endif

