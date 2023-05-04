#define BALL_DIAMETER 7.5
#define BALL_RADIUS BALL_DIAMETER / 2

struct baseball
{
    double x;
    double y;
    double bound_neg_x;
    double bound_pos_x;
    double bound_neg_y;
    double bound_pos_y;
};
