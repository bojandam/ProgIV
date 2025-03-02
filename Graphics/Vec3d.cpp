#include<iostream>
#include<cmath>

const double PI = 3.14159265358979323846;

struct Vec3d
{
    double v[4];
    Vec3d() : v{ 0,0,0,0 } {}
    Vec3d(double x, double y, double z, double w = 1) : v{ x, y, z, w } {}
    Vec3d(const Vec3d & vec) :v{ vec.v[0],vec.v[1],vec.v[2],vec.v[3] } {}
    double operator[](const int i) const { return v[i]; }
    double & operator[](const int i) { return v[i]; }
};

std::ostream & operator<<(std::ostream & out, const Vec3d & o) {
    out << "[";
    for (int i = 0; i < 4; i++)
        out << o[i] << " ";
    out << "]";
    return out;
}

struct Matrix
{
    double m[4][4];
    Matrix(int x = 0) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = 0;
        for (int i = 0; i < 4; i++)m[i][i] = x;
    }
    Matrix(const Matrix & o) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = o.m[i][j];
    }
    Matrix(const double M[4][4]) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = M[i][j];
    }

    Matrix operator*(const Matrix & o)
    {
        Matrix rez(0);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    rez.m[i][j] += m[i][k] * o.m[k][j];

        return rez;
    }

    Vec3d operator*(const Vec3d & second)
    {
        Vec3d rez;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rez[i] += m[i][j] * second[j];

        return rez;
    }
};
std::ostream & operator<<(std::ostream & out, const Matrix & o)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            out << o.m[i][j] << " ";
        out << std::endl;
    }
    return out;
}


Matrix translation_Matrix(double v[]) {
    Matrix rez(1);
    for (int i = 0; i < 3; i++) {
        rez.m[i][3] = v[i];
    }
    return rez;
}

Matrix translation_Matrix(double x, double y, double z) {
    double v[3] = { x,y,z };
    return translation_Matrix(v);
}

Matrix rotationX_Matrix(double rad) {
    double M[4][4] = { { 1,    0,        0,      0 },
                       { 0, cos(rad), -sin(rad), 0 },
                       { 0, sin(rad),  cos(rad), 0 },
                       { 0,    0,        0,      1 } };
    return Matrix(M);
}

Matrix rotationY_Matrix(double rad) {
    double M[4][4] = { {  cos(rad), 0, sin(rad), 0 },
                       {    0,      1,    0,     0 },
                       { -sin(rad), 0, cos(rad), 0 },
                       {    0,      0,    0,     1 } };
    return Matrix(M);
}

Matrix rotationZ_Matrix(double rad) {
    double M[4][4] = { { cos(rad), -sin(rad), 0, 0 },
                       { sin(rad),  cos(rad), 0, 0 },
                       {    0,        0,      1, 0 },
                       {    0,        0,      0, 1 } };
    return Matrix(M);
}


Matrix scale_Matrix(double v[]) {
    Matrix rez(1);
    for (int i = 0; i < 3; i++) {
        rez.m[i][i] = v[i];
    }
    return rez;
}
Matrix scale_Matrix(double x, double y, double z) {
    double v[] = { x,y,z };
    return scale_Matrix(v);

}


int main() {
    using namespace std;

    double x, y, z;
    cin >> x >> y >> z;
    Vec3d point(x, y, z);

    cout << point << endl;

    Matrix Trans(translation_Matrix(1, 1, 1));
    cout << endl;
    cout << Trans << endl;
    cout << (Trans * point) << endl;

    Matrix RotX(rotationX_Matrix(PI));
    cout << endl;
    cout << RotX << endl;
    cout << (RotX * point) << endl;

    Matrix RotY(rotationY_Matrix(PI));
    cout << endl;
    cout << RotY << endl;
    cout << (RotY * point) << endl;

    Matrix RotZ(rotationZ_Matrix(PI));
    cout << endl;
    cout << RotZ << endl;
    cout << (RotZ * point) << endl;

    Matrix Scal(scale_Matrix(0.5, 2, 3));
    cout << endl;
    cout << Scal << endl;
    cout << (Scal * point) << endl;

}


