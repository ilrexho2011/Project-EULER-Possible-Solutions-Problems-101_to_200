#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef uint16_t u16;
typedef uint64_t u64;

typedef struct point { s8 x, y; } point;

#define MAX_POINTS (1<<16)
point points[MAX_POINTS];
int points_len;
int radius;

void
make_all_points(void)
{
    register point *p = points;
    points_len = 0;
    register int r = radius, rr = r*r, y, yy, x;
    for (y = r - 1; y > -r; --y) {
        yy = y * y;
        for (x = -r + 1; x < r; x++) {
            if ((x | y) && (yy + (x * x) < rr)) {
                p->x = (s8)x; p->y = (s8)y; p++;
                points_len++;
            }
        }
    }
}

int
main(int argc, char **argv)
{
    memset(points, 0, sizeof(point) * MAX_POINTS);

    radius = (argc > 1) ? atoi(argv[1]) : 105;
    assert(radius >= 2 && radius <= 105);

    make_all_points();

    register int len = points_len, mid = len / 2,
             i1, i2, i3;
    register float Am, Bm, Cm;
    register s8 a[8] = { 0 };
    register u64 *b = (u64*)a;

    #define Ax (a[0])
    #define Ay (a[1])
    #define Bx (a[2])
    #define By (a[3])
    #define Cx (a[4])
    #define Cy (a[5])
    
    #define A_X (255l<<0)
    #define A_Y (255l<<8)
    #define B_X (255l<<16)
    #define B_Y (255l<<24)
    #define C_X (255l<<32)
    #define C_Y (255l<<40)
    
    #define AB_X (A_X | B_X)
    #define BC_X (B_X | C_X)
    #define AC_X (A_X | C_X)
    #define AB_Y (A_Y | B_Y)
    #define BC_Y (B_Y | C_Y)
    #define AC_Y (A_Y | C_Y)

    register int i1_start = 0, i1_end = mid;
    register s16 x1, x2, x3;

    if (argc > 2) {
        i1_start = atoi(argv[2]);
        i1_end = i1_start + 1;
        assert(i1_start < mid);
    }

    if (argc > 3)
        i1_end = MIN(i1_start + atoi(argv[3]), mid);

    for (i1 = i1_start; i1 < i1_end; i1++) {

        #define GET(p, i) p##x = points[i].x; p##y = points[i].y;
        GET(A, i1) 
        
        #define GRAD(p) ((float)p##y / (float)p##x)
        Am = Ax ? GRAD(A) : 0.0;

        register long count = 0;

        for (i2 = i1 + 1; i2 < len; i2++) {
            GET(B, i2) 
                
            #define M0(mask) ((*b & mask) == 0)
            if (M0(AB_Y) || M0(AB_X))
                continue;

            Bm = Bx ? GRAD(B) : 0.0;
            if (Ax && Bx && Am == Bm)
                continue;
            
            #define CROSS(a, b) ((a##x * b##y) - (a##y * b##x))
            x1 = CROSS(B, A);

            for (i3 = MAX(mid, i2 + 1); i3 < len; i3++) {
                GET(C, i3)
                    
                x2 = CROSS(A, C);
                x3 = CROSS(C, B);

                #define DSIGN(a, b) (((a)^(b)) < 0)
                if (DSIGN(x1, x2) || DSIGN(x2, x3))
                    continue;

                if (M0(BC_Y) || M0(AC_Y) || M0(AC_X) || M0(BC_X))
                    continue;
                
                if (Cx) { 
                    Cm = GRAD(C);
                    if ((Ax && Am == Cm) || (Bx && Bm == Cm))
                        continue;
                }

                count++;
            }
        }
        printf("%ld\n", count);
    }
    return 0;
}