#include "Vec3d.h"
#include<vector>  


//  Point A with Line BC
bool isRight(Point a, Point b, Point c) {
    return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]) < 0;
}
double dist(Point a, Point b) {
    return sqrt((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}



std::vector<Point> DumbConvexHull(std::vector<Point> S) {
    using namespace std;
    vector<pair<Point, Point>> E;
    for (Point p : S) {
        for (Point q : S) {
            if (p != q) {
                bool valid = true;
                for (Point r : S) {
                    if (!isRight(r, p, q) || (dist(p, r) + dist(r, q) != dist(p, q))) {
                        valid = false;
                    }
                }
                if (valid) {
                    E.push_back({ p,q });
                }
            }
        }
    }

    Point last = E[0].second;
    vector<Point> L;

    L.push_back(E[0].first);
    Point prev = last;
    Point now = L[0];

    do // omg koristam do while prv pat posle 7 godini
    {
        for (int i = 1; i < E.size(); i++) {
            Point a = E[i].first;
            Point b = E[i].second;
            if (b == now)swap(a, b);

            if (a == now && b != prev) {
                L.push_back(b);
                now = b;
                prev = a;
            }
        }
    } while (last != prev);

    return L;
}

 