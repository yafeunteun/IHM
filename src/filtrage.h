#ifndef FILTRAGE_H
#define FILTRAGE_H

/*!
 * \file filtrage.h
 * \author yann feunteun
 * \version 0.1
 * \date 06/03/2014
 */

#include <vector>


/*! \class Filtrage
   * \brief This class provides several methods of filtering.
   */

class Filtrage
{
public:
    Filtrage(unsigned size);
    void passeBasRecur(std::vector<float>& val);
    void passeBasDirect(std::vector<float>& val);

    /*!
    *  \brief Set the coefficient for the recursive method (method passeBasRecur).
    *  \param k : The coefficient between 0 and 1 (1 means no filtering).
    */
    inline void setK(float k){if(k > 0. && k < 1.)m_K = k;}

    /*!
    *  \brief Set the number of data to accumulate for the filtering (method passeBasDirect).
    *  \param n : The number of data to accumulate.
    */
    inline void setN(float n){if(n > 0.)m_N = n;}

private:
    std::vector<float> m_last;
    std::vector<double> m_cumul;
    float m_K = 1.;
    unsigned m_N = 1;
};

#endif // FILTRAGE_H



