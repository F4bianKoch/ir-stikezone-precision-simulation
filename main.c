#include <stdio.h>
#include <stdlib.h>
#include "baseball.c"
#include "est_pos.c"

#define ITERATIONS 1000000
#define THRESHOLD 0.5
#define WIDTH 200
#define HEIGHT 200
#define FREQ 3.25

struct est_pos estimate_position(struct baseball b);

int main() 
{
    double precision_x = 0.0;
    double precision_y = 0.0;
    double average_hits_x = 0.0;
    double average_hits_y = 0.0;

    for (int i = 0; i < ITERATIONS; i++) {
        struct baseball b;
        b.x = rand() % WIDTH + (double) (rand() % 10) / 10;
        b.y = rand() % HEIGHT + (double) (rand() % 10) / 10;
        b.bound_pos_x = b.x + BALL_RADIUS;
        b.bound_neg_x = b.x - BALL_RADIUS;
        b.bound_pos_y = b.y + BALL_RADIUS;
        b.bound_neg_y = b.y - BALL_RADIUS;
        struct est_pos p = estimate_position(b);
        printf("x: %0.1f, y: %.1f | est_pos: (%.2f, %.2f), hits_x: %d, hits_y: %d\n", b.x, b.y, p.x, p.y, p.hits_x, p.hits_y);

        if ( b.x - p.x < THRESHOLD) {
            precision_x++;
        }

        if ( b.y - p.y < THRESHOLD) {
            precision_y++;
        }

        average_hits_x += p.hits_x;
        average_hits_y += p.hits_y;
    }

    printf("Precision X: %.2f %%\n", (precision_x / ITERATIONS) * 100);
    printf("Precision Y: %.2f %%\n", (precision_y / ITERATIONS) * 100);

    printf("Average Hits X: %.2f\n", (average_hits_x / ITERATIONS));
    printf("Average Hits Y: %.2f\n", (average_hits_y / ITERATIONS));

    return 0;
}

struct est_pos estimate_position(struct baseball b) 
{
    double average_x = 0;
    double average_y = 0;
    int hits_x = 0;
    int hits_y = 0;
    double ir_x;
    double ir_y;

    for (int i = 0; i < (int) WIDTH / FREQ; i++) {
        ir_x = i * FREQ;
        if (ir_x > b.bound_neg_x && ir_x < b.bound_pos_x) {
            average_x = average_x + ir_x;
            hits_x++;
        }
    }

    for (int k = 0; k < (int) HEIGHT / FREQ; k++) {
        ir_y = k * FREQ;
        if (ir_y > b.bound_neg_y && ir_y < b.bound_pos_y) {
            average_y = average_y + ir_y;
            hits_y++;
        }
    }

    struct est_pos p;
    p.x = hits_x != 0 ? average_x / hits_x : 0.0;
    p.y = hits_y != 0 ? average_y / hits_y : 0.0;
    p.hits_x = hits_x;
    p.hits_y = hits_y;

    return p;
}