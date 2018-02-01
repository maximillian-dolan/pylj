#include "slowstuff.h"
#include <math.h>

void compute_accelerations(int len_particles, const double *xpos, const double *ypos, double *xacc, double *yacc,
                           double *distances, double box_length)
{
    int i = 0;
    double dx, dy, dr, f;
    for (i = 0; i < len_particles; i++)
    {
        xacc[i] = 0.;
        yacc[i] = 0.;
    }
    int k = 0;
    for (i = 0; i < len_particles - 1; i++)
    {
        int j = 0;
        for (j = i + 1; j < len_particles; j++)
        {
            dx = xpos[i] - xpos[j];
            dy = ypos[i] - ypos[j];
            if (fabs(dx) > 0.5 * box_length)
            {
                dx *= 1 - box_length / fabs(dx);
            }
            if (fabs(dy) > 0.5 * box_length)
            {
                dy *= 1 - box_length / fabs(dy);
            }
            dr = sqrt(dx * dx + dy * dy);
            distances[k] = dr;
            k++;
            f = 48. * pow(dr, -13.) - 24. * pow(dr, -7.);
            xacc[i] += f * dx / dr;
            yacc[i] += f * dy / dr;
            xacc[j] -= f * dx / dr;
            yacc[j] -= f * dy / dr;
        }
    }
}

void debye(int len_distances, const double *cdistances, int len_qs, const double *cqs, double *inten)
{
    int i = 0;
    for (i = 0; i < len_qs; i++)
    {
        double in = 0, a = 0, b = 0;
        int j = 0;
        for (j = 0; j < len_distances; j++)
        {
            b = cqs[i] * cdistances[j];
            a = sin(b);
            in += a / b;
        }
        inten[i] = in;
    }
}