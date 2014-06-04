#include "filtrage.h"
#include "debug.h"


/*!
*  \brief Constructor
*
*  Constructor of Filtrage class
*
*  \param size : The number of data sent to the filter each time. i.e the size of the vector
*   sent to the differents methods of filtering.
*/
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

/*!
*  \brief Recursive low pass filter.
*  \param values : A reference on the vector containing the values to filter.
*/
void Filtrage::passeBasRecur(std::vector<float> &values)
{
    for(unsigned short i = 0; i < values.size(); ++i){
        DEBUG("Value before : " + QString::number(values[i]));
        values[i] = m_last[i] + m_K * (values[i] - m_last[i]);
        m_last[i] = values[i];
        DEBUG("Value after : " + QString::number(values[i]));
    }

}


/*!
*  \brief Low pass filter.
*  \param values : A reference on the vector containing the values to filter.
*/
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


