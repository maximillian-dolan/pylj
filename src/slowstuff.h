void compute_accelerations(int len_particles, const double *xpos, const double *ypos, double *xacc, double *yacc,
                           double *distances, double box_length);

void debye(int len_distances, const double *cdistances, int len_qs, const double *cqs, double *inten);
