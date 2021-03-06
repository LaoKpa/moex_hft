//
// Created by root on 23.12.16.
//

#ifndef HFT_ROBOT_QUOTEINFO_H
#define HFT_ROBOT_QUOTEINFO_H

#include "../Fast/FastTypes.h"

class QuoteInfo {
    Decimal     *m_pricePtr;
    Decimal     m_price;
    int         m_size;
    int         m_paddingBytes;
public:
    QuoteInfo() :
            m_price(0, 0),
            m_size(0),
            m_paddingBytes(0) {
        this->m_pricePtr = &(this->m_price);
    }
    QuoteInfo(Decimal *price, int size) :
            QuoteInfo() {
        this->m_pricePtr->Set(price);
        this->m_size = size;
    }

    inline void Clear() { }

    inline void AddSize(int size) {
        this->m_size += size;
    }
    inline void SubSize(int size) {
        this->m_size -= size;
    }
    inline void Price(Decimal *price) {
        this->m_pricePtr->Set(price);
        this->m_pricePtr->Calculate();
    }
    inline void Price(INT64 mantissa, INT32 exponent) {
        this->m_pricePtr->Mantissa = mantissa;
        this->m_pricePtr->Exponent = exponent;
        this->m_pricePtr->Calculate();
    }
    inline Decimal *Price() { return this->m_pricePtr; }
    inline void Size(int size) {
        this->m_size = size;
    }
    inline int Size() { return this->m_size; }
    inline void Size(Decimal *size) {
        this->m_size = (int)(size->Calculate());
    }
};

#endif //HFT_ROBOT_QUOTEINFO_H
