//
// Created by root on 31.12.16.
//

#ifndef HFT_ROBOT_SYMBOLMANAGER_H
#define HFT_ROBOT_SYMBOLMANAGER_H

#include "../Lib/StringHash.h"
#include "../Lib/PointerList.h"
#include "../Lib/StringIdComparer.h"
#include <memory.h>

typedef enum _SymbolHashType {
    Last4Chars,      // for FOND
    TwoAfterTwo,     // for CURR
}SymbolHashType;

class SymbolInfo {
    static const int m_textSize = 16;
public:
    union {
        char m_text[SymbolInfo::m_textSize] __attribute__((aligned(16)));
        struct {
            UINT64          m_symbol1;
            UINT32          m_symbol2;
            short           m_index;
            unsigned short  m_length;
        };
    };

    SymbolInfo() :
            m_index(-1),
            m_length(0) {
        memset(this->m_text, 0, sizeof(SymbolInfo));
    }
    void Set(const char *symbol, unsigned short length, unsigned short index) {
        memcpy(this->m_text, symbol, length);
        this->m_text[length] = '\0';
        this->m_length = length;
        this->m_index = index;
    }
};

class SymbolManagerTester;
class SecurityDefinitionTester;
class SymbolManager {
    friend class SymbolManagerTester;
    friend class SecurityDefinitionTester;

    static const int            BucketList2Count = 1000000;

    LinkedPointer<SymbolInfo>   **m_bucketList;
    SymbolInfo                  **m_bucketList2;
    PointerList<SymbolInfo>      *m_pool;
    SymbolHashType              m_hashType;

    int                         m_capacity;
    int                         m_paddingBytes;
    unsigned short              m_count;
    short                       m_freeIndex;

    inline short GetFreeIndex() {
        this->m_freeIndex++;
        return this->m_freeIndex;
    }
    inline void AddBucket(LinkedPointer<SymbolInfo> *ptr, int hash) {
        this->m_bucketList[hash] = ptr;
    }
    inline LinkedPointer<SymbolInfo>* AddFirstSymbol(const char *symbol, int length, int hash) {
        LinkedPointer<SymbolInfo> *ptr = GetPtrFromPool();
        ptr->Data()->Set(symbol, length, GetFreeIndex());
        AddBucket(ptr, hash);
        this->m_count++;
        return ptr;
    }
    inline void ClearBucketList() {
        if(this->m_bucketList != 0) {
            for (int i = 0; i < StringHash::HashArrayItemsCount; i++) {
                LinkedPointer<SymbolInfo> *ptr = this->m_bucketList[i];
                if(ptr == 0)
                    continue;
                while (ptr != 0) {
                    LinkedPointer<SymbolInfo> *prevPtr = ptr;
                    if(ptr == ptr->Next())
                        throw;
                    ptr = ptr->Next();
                    this->m_pool->Push(prevPtr);
                }
                this->m_bucketList[i] = 0;
            }
        }
        else if(this->m_bucketList2 != 0) {
            memset(this->m_bucketList2, 0, sizeof(SymbolInfo *) * BucketList2Count);
        }
        this->m_pool->Clear();
    }
    inline LinkedPointer<SymbolInfo>* GetBucket(int hash) {
        return this->m_bucketList[hash];
    }
    inline LinkedPointer<SymbolInfo>* GetPtrFromPool() {
        LinkedPointer<SymbolInfo> *res = this->m_pool->Pop();
        res->Next(0);
        return res;
    }
    inline bool FindSymbol(LinkedPointer<SymbolInfo> *start, const char *symbol, int length, LinkedPointer<SymbolInfo> **found) {
        while(true) {
            SymbolInfo *s = start->Data();
            if(StringIdComparer::EqualFast(s->m_text, s->m_length, symbol, length)) {
                *found = start;
                return true;
            }
            if(!start->HasNext()) {
                *found = start;
                return false;
            }
            start = start->Next();
        }
    }
    inline SymbolInfo* FindSymbol(LinkedPointer<SymbolInfo> *start, const char *symbol, int length) {
        int count = 0;
        while(true) {
            SymbolInfo *s = start->Data();
            if(StringIdComparer::EqualFast(s->m_text, s->m_length, symbol, length)) {
                return s;
            }
            if(!start->HasNext())
                return 0;
            start = start->Next();
            count++;
        }
    }
    inline void AppendSymbol(LinkedPointer<SymbolInfo> *current, LinkedPointer<SymbolInfo> *next) {
        current->Next(next);
        next->Next(0);
        this->m_count++;
    }
    void AssignPointersToSymbols() {
    }
public:
    SymbolManager(int capacity, SymbolHashType hashType) {
        this->m_capacity = capacity;
        this->m_count = 0;
        this->m_freeIndex = -1;
        this->m_hashType = hashType;

        this->m_pool = new PointerList<SymbolInfo>(capacity + 10);
        this->m_pool->AllocData();
        //this->AssignPointersToSymbols();
        this->m_bucketList = new LinkedPointer<SymbolInfo>*[StringHash::HashArrayItemsCount];
        for(int i = 0; i < StringHash::HashArrayItemsCount; i++)
            this->m_bucketList[i] = 0;
        this->m_bucketList2 = 0;
    }
    SymbolManager(int capacity) : SymbolManager(capacity, SymbolHashType::Last4Chars) {

    }
    SymbolManager(int capacity, bool useUint64Hash, SymbolHashType hashType) {
        this->m_capacity = capacity;
        this->m_count = 0;
        this->m_freeIndex = -1;
        this->m_hashType = hashType;

        this->m_pool = new PointerList<SymbolInfo>(capacity + 10);
        this->m_pool->AllocData();
        this->AssignPointersToSymbols();
        this->m_bucketList = 0;
        this->m_bucketList2 = new SymbolInfo*[BucketList2Count];
        memset(this->m_bucketList2, 0, sizeof(SymbolInfo*) * BucketList2Count);
    }
    SymbolManager(int capacity, bool useUint64Hash) : SymbolManager(capacity, useUint64Hash, SymbolHashType::Last4Chars) {

    }
    ~SymbolManager() {
        delete this->m_pool;
        if(this->m_bucketList2 != 0)
            delete this->m_bucketList2;
    }
    inline void Clear() {
        this->m_freeIndex = -1;
        this->m_count = 0;
        ClearBucketList();
    }
    inline int SymbolCount() {
        return this->m_count;
    }
    inline int BucketListCount() { return StringHash::HashArrayItemsCount; }
    int CalcBucketCollisitonCount(int index) {
        LinkedPointer<SymbolInfo> *ptr = this->m_bucketList[index];
        if(ptr == 0) return 0;
        int count = 1;
        while(ptr->HasNext()) {
            count++; ptr = ptr->Next();
        }
        return count;
    }
    int CalcMaxBucketCollisionCount() {
        int res = 0;
        for(int i = 0; i < StringHash::HashArrayItemsCount; i++) {
            int count = CalcBucketCollisitonCount(i);
            if(count > res) res = count;
        }
        return res;
    }
    inline int GetSymbolIndex(const char *symbol, bool *wasNewlyAdded) {
        return GetSymbolIndex(symbol, strlen(symbol), wasNewlyAdded);
    }
    inline int GetSymbolIndex(const char *symbol, int length, bool *wasNewlyAdded) {
        SymbolInfo *info = GetSymbol(symbol, length, wasNewlyAdded);
        return info->m_index;
    }
    static const char *AlignedString(const char *string) {
        SymbolInfo *info = new SymbolInfo();
        strcpy(info->m_text, string);
        return info->m_text;
    }
    inline SymbolInfo* GetSymbol(const char *symbol, bool *wasNewlyAdded) {
        return this->GetSymbol(AlignedString(symbol), strlen(symbol), wasNewlyAdded);
    }
    inline SymbolInfo* AddSymbol(const char *symbol) {
        bool wasNewlyAdded = false;
        SymbolInfo *res = this->GetSymbol(AlignedString(symbol), strlen(symbol), &wasNewlyAdded);
#ifdef TEST
        if(!wasNewlyAdded)
            throw;
#endif
        return res;
    }
    inline SymbolInfo* GetSymbol(UINT64 securityId, bool *wasNewlyAdded) {
        if(this->m_bucketList2[securityId] == 0) {
            *wasNewlyAdded = true;
            SymbolInfo *smb = GetPtrFromPool()->Data();
            smb->m_index = GetFreeIndex();
            this->m_bucketList2[securityId] = smb;
            this->m_count++;
            return smb;
        }
        *wasNewlyAdded = false;
        return this->m_bucketList2[securityId];
    }
    inline SymbolInfo* GetExistingSymbol(UINT64 securityId) {
        return this->m_bucketList2[securityId];
    }
    inline SymbolInfo* GetSymbol(UINT64 securityId) {
        bool wasNewlyAdded;
        SymbolInfo *info = this->GetSymbol(securityId, &wasNewlyAdded);
        if(wasNewlyAdded) { //TODO remove debug
            printf("!!!unexpected add %" PRIu64 "\n", securityId);
        }
        return info;
    }
    inline SymbolInfo* AddSymbol(UINT64 securityId) {
        bool wasNewlyAdded;
        SymbolInfo *info = this->GetSymbol(securityId, &wasNewlyAdded);
        if(!wasNewlyAdded) { //TODO remove debug
            printf("!!!already added %" PRIu64 "\n", securityId);
        }
        return info;
    }
    inline int GetHash(const char *symbol, int length) {
        if(this->m_hashType == SymbolHashType::Last4Chars)
            return StringHash::GetHash(symbol, length);
        return StringHash::GetHash2(symbol, length);
    }
    inline SymbolInfo* GetSymbol(const char *symbol, int length) {
        int hash = this->GetHash(symbol, length);
        LinkedPointer<SymbolInfo> *bucket = GetBucket(hash);
        return FindSymbol(bucket, symbol, length);
    }
    inline SymbolInfo* GetSymbol(const char *symbol, int length, bool *wasNewlyAdded) {
        int hash = this->GetHash(symbol, length);
        LinkedPointer<SymbolInfo> *bucket = GetBucket(hash);
        if(bucket == 0) {
            *wasNewlyAdded = true;
            return AddFirstSymbol(symbol, length, hash)->Data();
        }
        LinkedPointer<SymbolInfo> *sptr = 0;
        if(FindSymbol(bucket, symbol, length, &sptr)) {
            *wasNewlyAdded = false;
            return sptr->Data();
        }
        *wasNewlyAdded = true;
        LinkedPointer<SymbolInfo> *newPtr = GetPtrFromPool();
        newPtr->Data()->Set(symbol, length, GetFreeIndex());
        AppendSymbol(sptr, newPtr);
        return newPtr->Data();
    }
};

#endif //HFT_ROBOT_SYMBOLMANAGER_H
