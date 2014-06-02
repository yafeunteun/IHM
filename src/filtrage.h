#ifndef FILTRAGE_H
#define FILTRAGE_H

#include <vector>

class Filtrage
{
public:
    Filtrage(unsigned size);
    void passeBasRecur(std::vector<float>& val);
    void passeBasDirect(std::vector<float>& val);
    inline void setK(float k){m_K = k;}
    inline void setN(float n){m_N = n;}

private:
    std::vector<float> m_last;
    std::vector<double> m_cumul;
    float m_K = 1.;
    unsigned m_N = 1;
};

#endif // FILTRAGE_H



