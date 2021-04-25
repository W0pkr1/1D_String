#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>


const int x01 = 20;
//const int x02 = 7;
const int L = 50;
const float ccsq = 0.8;


float gen()
{
    static float x;
    float res1 = x < x01 || x == x01 ? x / x01 : (L - x) / (L - x01);
    //float res2 = x < x02 || x == x02 ? x / x02 : (L - x) / (L - x02);
    x++;
    return res1;//+res2;
    
}

std::vector<float> new_S(std::vector<float> const& old_S, std::vector<float>const& older_s)
{
    std::vector<float> new_string(L);
    int i = 0;
    auto f = [&i, &old_S, &older_s](float& e)
    {   
        float lside = i == 0 ? 0 : old_S[i - 1];
        float rside = i == L - 1 ? 0 : old_S[i + 1];
        float res = 2 * old_S[i] - older_s[i] + ccsq *ccsq* (rside + lside - 2 * old_S[i]);
        i+=1;

        e = res;
    };
    std::for_each(new_string.begin(), new_string.end(), f);
    return new_string;
}

void save_data(std::ofstream & h, std::vector<float> const &s)
{
    for (float e : s) { h << e << ' '; }
    h << std::endl;

}

auto stepping(std::vector<float>& os, int const& steps)
{
    auto ns = new_S(os, os);
    std::ofstream handler("data/d1.txt");

    save_data(handler, os);
    save_data(handler, ns);

    for (int i = 0; i < steps; i++)
    {
        
        auto res = new_S(ns, os);
        os = ns;
        ns = res;
        save_data(handler, os);
    }
    handler.close();
}

int main()
{
    std::vector<float> oneDstring(L);
    std::generate(oneDstring.begin(), oneDstring.end(), gen);
    stepping(oneDstring, 1000);
    //for (float e : oneDstring) { std::cout << e << ' '; }
    //std::cout << std::endl;

}