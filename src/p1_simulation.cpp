#include "p1_simulation.h"

P1_simulation::P1_simulation(double beta, double sigma, double gamma,
                             double s0, double e0, double i0, double r0, double dt)
    : beta(beta), sigma(sigma), gamma(gamma), dt(dt),
      s(s0), e(e0), i(i0), r(r0), t(0.0) {}

void P1_simulation::euler_step() {
    double ds = -beta * i * s;
    double de = beta * i * s - sigma * e;
    double di = sigma * e - gamma * i;
    double dr = gamma * i;

    s += ds * dt;
    e += de * dt;
    i += di * dt;
    r += dr * dt;

    t += dt;
}