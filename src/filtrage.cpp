#include "filtrage.h"
#include "debug.h"


Filtrage::Filtrage(unsigned size)
{
    m_last.resize(size);
    m_cumul.resize(size);
    for(unsigned short i = 0; i < size; ++i)
    {
        m_cumul[i] = 0.;
        m_last[i] = 0.;
    }
}


void Filtrage::passeBasRecur(std::vector<float> &values)
{
    for(unsigned short i = 0; i < values.size(); ++i){
        DEBUG("Value before : " + QString::number(values[i]));
        values[i] = m_last[i] + m_K * (values[i] - m_last[i]);
        m_last[i] = values[i];
        DEBUG("Value after : " + QString::number(values[i]));
    }

}

void Filtrage::passeBasDirect(std::vector<float> &values)
{
    static unsigned count = 0;


   for(unsigned short i = 0; i < values.size(); ++i){
        m_cumul[i] += values[i];
    }
    ++count;


    if(count == m_N){
        for(unsigned short i = 0; i < values.size(); ++i){
            values[i] = m_cumul[i] / (float)m_N;
            m_cumul[i] += 0.;
        }
        count = 0;
    }
}


