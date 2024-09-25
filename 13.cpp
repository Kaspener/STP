#include <iostream>
#include <cmath>
#include <vector>

int I(int eta)
{
    return static_cast<int>(log2(eta) / 3 + 1);
}

int K(int eta, int i)
{
    int total = 1;
    for (int j = 1; j < i; ++j)
    {
        total += eta / std::pow(8, j);
    }
    return total;
}

double N(int k, double nk)
{
    return k * nk;
}

double Nk(double eta2k)
{
    return 2 * eta2k * log2(eta2k);
}

double Eta2k(int eta)
{
    return eta * log2(eta);
}

double V(int k, double nk, double eta2k)
{
    return k * nk * log2(2 * eta2k);
}

double P(double n)
{
    return 3 * n / 8;
}

double Tk(double p)
{
    return p / (5 * 20);
}

double T(double tk)
{
    return tk / 2;
}

double B0(double v)
{
    return v / 3000;
}

double Tn(double b0, double t)
{
    return t / log(b0);
}

int main()
{
    std::vector<int> etas = {300, 400, 512};
    for (auto eta : etas)
    {
        int i = I(eta);
        int k = K(eta, i);
        double eta2k = Eta2k(eta);
        double nk = Nk(eta2k);
        double n = N(k, nk);
        double v = V(k, nk, eta2k);
        double p = P(n);
        double tk = Tk(n);
        double t = T(tk);
        double b0 = B0(v);
        double tn = Tn(b0, t);
        std::cout << "eta = " << eta << std::endl;
        std::cout << "i = " << i << std::endl;
        std::cout << "K = " << k << std::endl;
        std::cout << "Eta2k = " << eta2k << std::endl;
        std::cout << "Nk = " << nk << std::endl;
        std::cout << "N = " << n << std::endl;
        std::cout << "V = " << v << std::endl;
        std::cout << "P = " << p << std::endl;
        std::cout << "Tk = " << tk << std::endl;
        std::cout << "t = " << t << std::endl;
        std::cout << "B0 = " << b0 << std::endl;
        std::cout << "tn = " << tn << std::endl;
        std::cout << "------------------------------------------" << std::endl << std::endl;
    }
    return 0;
}