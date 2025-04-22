#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "func.h"

inline void acceleration(const Point &p_next, Point &p_mid, const Point &p_prev, const double dx) {
    p_mid.a = (p_next.y - 2*p_mid.y + p_prev.y) / (dx * dx);
}

inline void euler_mid(Point &p, const double dt) {
    const double v_mid = p.v + 0.5 * dt * p.a;
    p.y += v_mid * dt;
    p.v += p.a * dt;
}

inline double kinetic_energy(const Point* const points, const double dx, const unsigned n) {
    double ek = 0.0;
    for (auto i = 0; i < n; ++i) {
        const auto v = points[i].v;
        ek += v * v;
    }
    return ek * dx/2;
}

inline double potential_energy(const Point* const points, const double dx, const unsigned n) {
    double ep = 0.0;
    for (auto i = 0; i < n - 1; ++i) {
        const auto y_curr = points[i].y;
        const auto y_next = points[i+1].y;
        ep += pow(y_next - y_curr, 2);
    }
    return ep / (2 * dx);
}

void run(const char *en_file_name, const char *pos_file_name, const double dt, const unsigned t_max, const unsigned n) {
    std::fstream energy_file(en_file_name, std::ios::out | std::ios::trunc);
    if (!energy_file.is_open())
        throw std::runtime_error(std::format("Could not open file: '{}'", en_file_name));

    std::fstream position_file(pos_file_name, std::ios::out | std::ios::trunc);
    if (!position_file.is_open()) {
        energy_file.close();
        throw std::runtime_error(std::format("Could not open file: {}", pos_file_name));
    }

    energy_file << "t,Ek,Ep,Ec\n";

    std::ostringstream header;
    header << "t";

    for (auto i = 0; i <= n; ++i)
        header << ",i" << i << ",x" << i << ",y" << i << ",v" << i << ",a" << i;
    header << "\n";
    position_file << header.str();

    auto dx = L / n;
    const auto points = new Point[n+1];
    points[n].x = L;

    for (auto i = 1; i < n; ++i) {
        double x = i * dx;
        double y = std::sin(x) / 1e4;
        points[i].x = x;
        points[i].y = y;
        points[i].v = 0;
    }

    std::ostringstream first_line;
    first_line << 0.0 << "," << 0 << "," << points[0];
    for (auto i = 1; i < n; ++i) {
        acceleration(points[i-1], points[i], points[i+1], dx);
        first_line << "," << i << "," << points[i];
    }
    first_line << "," << n << "," << points[n] << "\n";
    position_file << first_line.str();

    double ek = kinetic_energy(points, dx, n);
    double ep = potential_energy(points, dx, n);
    double ec = ek + ep;
    energy_file << 0.0 << "," << ek << "," << ep << "," << ec << "\n";

    const auto steps = static_cast<unsigned>(t_max / dt) + 1;

    for (auto step = 1; step < steps; ++step) {
        auto t = step * dt;
        for (auto i = 1; i < n; ++i)
            acceleration(points[i+1], points[i], points[i-1], dx);
        position_file << t;
        for (auto i = 0; i < n; ++i) {
            euler_mid(points[i], dt);
            position_file << "," << i << "," << points[i];
        }
        position_file << "," << n << "," << points[n] << "\n";
        ek = kinetic_energy(points, dx, n);
        ep = potential_energy(points, dx, n);
        ec = ek + ep;
        energy_file << t << "," << ek << "," << ep << "," << ec << "\n";
    }
    energy_file.close();
    position_file.close();
    delete[] points;
}

