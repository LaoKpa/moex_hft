//
// Created by root on 02.04.17.
//

#ifndef HFT_ROBOT_HRPOINTERLIST_H
#define HFT_ROBOT_HRPOINTERLIST_H

#include <stdio.h>

template <typename T> class HrPointerList;

template <typename T> class HrLinkedPointer {
    HrPointerList<T>  *m_owner;
    HrLinkedPointer   *m_next;
    HrLinkedPointer   *m_prev;
    HrLinkedPointer   *m_next2;
    HrLinkedPointer   *m_prev2;
    HrLinkedPointer   *m_next3;
    HrLinkedPointer   *m_prev3;
    HrLinkedPointer   *m_next4;
    HrLinkedPointer   *m_prev4;
    HrLinkedPointer   *m_next5;
    HrLinkedPointer   *m_prev5;

    T               *m_data;
    bool             m_released;

public:
    HrLinkedPointer() {
        this->m_next = 0;
        this->m_prev = 0;
        this->m_next2 = 0;
        this->m_prev2 = 0;
        this->m_next3 = 0;
        this->m_prev3 = 0;
        this->m_next4 = 0;
        this->m_prev4 = 0;
        this->m_next5 = 0;
        this->m_prev5 = 0;

        this->m_data = 0;
        this->m_released = true;
    }

    inline bool HasNext() { return this->m_next != 0; }
    inline HrLinkedPointer* Next() { return this->m_next; }
    inline void Next(HrLinkedPointer *node) { this->m_next = node; }
    inline HrLinkedPointer* Prev() { return this->m_prev; }
    inline void Prev(HrLinkedPointer *node) { this->m_prev = node; }

    inline bool HasNext2() { return this->m_next2 != 0; }
    inline HrLinkedPointer* Next2() { return this->m_next2; }
    inline void Next2(HrLinkedPointer *node) { this->m_next2 = node; }
    inline HrLinkedPointer* Prev2() { return this->m_prev2; }
    inline void Prev2(HrLinkedPointer *node) { this->m_prev2 = node; }

    inline bool HasNext3() { return this->m_next3 != 0; }
    inline HrLinkedPointer* Next3() { return this->m_next3; }
    inline void Next3(HrLinkedPointer *node) { this->m_next3 = node; }
    inline HrLinkedPointer* Prev3() { return this->m_prev3; }
    inline void Prev3(HrLinkedPointer *node) { this->m_prev3 = node; }

    inline bool HasNext4() { return this->m_next4 != 0; }
    inline HrLinkedPointer* Next4() { return this->m_next4; }
    inline void Next4(HrLinkedPointer *node) { this->m_next4 = node; }
    inline HrLinkedPointer* Prev4() { return this->m_prev4; }
    inline void Prev4(HrLinkedPointer *node) { this->m_prev4 = node; }

    inline bool HasNext5() { return this->m_next5 != 0; }
    inline HrLinkedPointer* Next5() { return this->m_next5; }
    inline void Next5(HrLinkedPointer *node) { this->m_next5 = node; }
    inline HrLinkedPointer* Prev5() { return this->m_prev5; }
    inline void Prev5(HrLinkedPointer *node) { this->m_prev5 = node; }

    inline T* Data() { return this->m_data; }
    inline void Data(T *data) { this->m_data = data; }
    inline HrPointerList<T>* Owner() { return this->m_owner; }
    inline void Owner(HrPointerList<T> *owner) { this->m_owner = owner; }
    inline bool Released() { return this->m_released; }
    inline void Released(bool released) {
        this->m_released = released;

        if(!released)
            return;
        if(this->m_next2 != 0) {
            this->m_next2 = 0;
            if(this->m_next3 != 0) {
                this->m_next3 = 0;
                if(this->m_next4 != 0) {
                    this->m_next4 = 0;
                    this->m_next5 = 0;
                }
            }
        }

        if(this->m_prev2 != 0) {
            this->m_prev2 = 0;
            if(this->m_prev3 != 0) {
                this->m_prev3 = 0;
                if(this->m_prev4 != 0) {
                    this->m_prev4 = 0;
                    this->m_prev5 = 0;
                }
            }
        }
    }
};


template <typename T> class HrPointerListLite;
class HrPointerListTester;

template <typename T> class HrPointerList {
    friend  class HrPointerListLite<T>;
    friend  class PointerListTester;
    int             m_capacity;

    HrLinkedPointer<T> *m_poolHead;
    HrLinkedPointer<T> *m_poolTail;

    HrLinkedPointer<T> *m_head;
    HrLinkedPointer<T> *m_tail;
    int              m_count;
    bool             m_autoAllocate;
    const char      *m_name;

public:
    inline HrLinkedPointer<T>* Pop(const char *name) {
        if(this->m_poolHead == this->m_poolTail) {
            this->Append(this->m_capacity, name);
        }
        HrLinkedPointer<T> *node = this->m_poolHead;
        this->m_poolHead = this->m_poolHead->Next();
        this->m_count++;
        node->Released(false);
        return node;
    }
    inline HrLinkedPointer<T>* Pop() {
        if(this->m_poolHead == this->m_poolTail) {
            this->Append(this->m_capacity);
        }
        HrLinkedPointer<T> *node = this->m_poolHead;
        this->m_poolHead = this->m_poolHead->Next();
        this->m_count++;
        node->Released(false);
        return node;
    }

    inline void Push(HrLinkedPointer<T> *node) {
        if(node->Released())
            return;
        node->Released(true);
        this->m_poolTail->Next(node);
        this->m_poolTail = node;
        this->m_count--;
    }
    HrPointerList(int capacity, bool autoAllocate) {
        this->m_name = "";
        this->m_capacity = capacity;
        this->m_count = 0;
        this->m_autoAllocate = autoAllocate;

        this->m_poolHead = new HrLinkedPointer<T>;
        this->m_poolTail = this->m_poolHead;

        for(int i = 0; i < this->m_capacity + 1; i++) {
            HrLinkedPointer<T> *ptr = new HrLinkedPointer<T>;
            ptr->Owner(this);

            this->m_poolTail->Next(ptr);
            this->m_poolTail = ptr;
        }

        this->m_tail = this->m_head = this->Pop();
        this->m_head->Next(0);
        this->m_head->Prev(0);
        this->m_head->Data(0);
        this->m_count = 0;

        if(this->m_autoAllocate)
            AllocData();
    }
    HrPointerList(int capacity, bool autoAllocate, const char *name) : HrPointerList(capacity, autoAllocate) {
        this->m_name = name;
    }
    HrPointerList(int capacity) : HrPointerList(capacity, false) { }
    HrPointerList(int capacity, const char *name) : HrPointerList(capacity, false, name) {
        this->m_name = name;
    }
    inline void FreeData() {
        HrLinkedPointer<T> *s = this->m_poolHead;
        while(true) {
            delete s->Data();
            if(s == this->m_poolTail)
                break;
            s = s->Next();
        }
    }
    inline void AllocData() {
        HrLinkedPointer<T> *s = this->m_poolHead;
        while(true) {
            s->Data(new T());
            if(s == this->m_poolTail)
                break;
            s = s->Next();
        }
    }
    ~HrPointerList() {
        this->Clear();

        HrLinkedPointer<T> *node = this->m_poolHead;
        do {
            if(this->m_autoAllocate)
                delete node->Data();
            delete node;
            node = node->Next();
        }
        while(node != this->m_poolTail);
    }

    inline HrLinkedPointer<T>* Add(T *data) {
        HrLinkedPointer<T> *node = this->Pop();
        node->Data(data);
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        this->m_tail->Next(0);
        return node;
    }

    inline HrLinkedPointer<T>* Add(HrLinkedPointer<T> *node) {
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        this->m_tail->Next(0);
        return node;
    }

    inline HrLinkedPointer<T>* Insert(HrLinkedPointer<T> *before, T *data) {
        HrLinkedPointer<T> *node = this->Pop();
        HrLinkedPointer<T> *prev = before->Prev();
        prev->Next(node);
        node->Prev(prev);
        node->Next(before);
        before->Prev(node);
        return node;
    }

    inline void Insert(HrLinkedPointer<T> *before, HrLinkedPointer<T> *node) {
        HrLinkedPointer<T> *prev = before->Prev();
        prev->Next(node);
        node->Prev(prev);
        node->Next(before);
        before->Prev(node);
    }

    inline HrLinkedPointer<T> *Pointer(int index) {
        HrLinkedPointer<T> *node = this->Start();
        while(index > 0) {
            if(node == this->End())
                return 0;
            node = node->Next();
            index--;
        }
        return node;
    }

    inline HrLinkedPointer<T> *PoolPointer(int index) {
        HrLinkedPointer<T> *node = this->PoolStart();
        while(index > 0) {
            if(node == this->PoolEnd())
                return 0;
            node = node->Next();
            index--;
        }
        return node;
    }

    inline T* Item(int index) {
        HrLinkedPointer<T> *node = this->Start();
        while(index > 0) {
            if(node == this->End())
                return 0;
            node = node->Next();
            index--;
        }
        return node->Data();
    }

    inline HrLinkedPointer<T>* Get(T *data) {
        HrLinkedPointer<T> *node = this->m_head;
        while(true) {
            if(node->Data() == data)
                return node;
            if(node == this->m_tail)
                break;
            node = node->Next();
        }
        return 0;
    }

    inline void Remove(HrLinkedPointer<T> *node) {
        HrLinkedPointer<T> *prev = node->Prev();
        HrLinkedPointer<T> *next = node->Next();
        if(node == this->m_tail) {
            prev->Next(0);
            this->m_tail = prev;
        }
        else {
            prev->Next(next);
            next->Prev(prev);
        }
        this->Push(node);
    }

    inline void Remove(T *data) {
        HrLinkedPointer<T> *node = this->Get(data);
        this->Remove(node);
    }

    inline bool IsFull() { return this->m_poolHead == this->m_poolTail; }

    inline HrLinkedPointer<T>* Append(int capacity, const char *name) {
        printf("!!!unexpected append %s count = %d, additional capacity = %d!!!\n", name, this->m_count, capacity); //TODO remove debug info
        this->m_capacity += capacity;
        HrLinkedPointer<T> *start = new HrLinkedPointer<T>();
        HrLinkedPointer<T> *node = start;
        for(int i = 0; i < capacity; i++) {
            HrLinkedPointer<T> *ptr = new HrLinkedPointer<T>;
            ptr->Owner(this);
            node->Next(ptr);
            node = node->Next();
        }
        HrLinkedPointer<T> *curr = start;
        if(this->m_autoAllocate) {
            for(int i = 0; i < capacity; i++) {
                curr->Data(new T());
                curr = curr->Next();
            }
        }
        this->m_poolTail->Next(start);
        this->m_poolTail = node;
        return start;
    }

    inline HrLinkedPointer<T>* Append(int capacity) {
        printf("!!!unexpected append %s count = %d, additional capacity = %d!!!\n", this->m_name, this->m_count, capacity); //TODO remove debug info
        this->m_capacity += capacity;
        HrLinkedPointer<T> *start = new HrLinkedPointer<T>();
        start->Owner(this);
        HrLinkedPointer<T> *node = start;
        for(int i = 0; i < capacity - 1; i++) {
            HrLinkedPointer<T> *next = new HrLinkedPointer<T>();
            next->Owner(this);
            node->Next(next);
            node = next;
        }

        HrLinkedPointer<T> *curr = start;
        if(this->m_autoAllocate) {
            for(int i = 0; i < capacity; i++) {
                curr->Data(new T());
                curr = curr->Next();
            }
        }
        this->m_poolTail->Next(start);
        this->m_poolTail = node;
        this->m_poolTail->Next(0);
#ifdef  TEST
        if(this->m_autoAllocate) {
            HrLinkedPointer<T> *ptr = this->m_poolHead;
            while (ptr != 0) {
                if (ptr->Data() == 0)
                    throw;
                ptr = ptr->Next();
            }
        }
#endif
        return start;
    }
    inline HrLinkedPointer<T>* Start() { return this->m_head->Next(); }
    inline HrLinkedPointer<T>* End() { return this->m_tail; }
    inline HrLinkedPointer<T>* Next(HrLinkedPointer<T> *node) { return node->Next(); }
    inline HrLinkedPointer<T>* PoolStart() { return this->m_poolHead; }
    inline HrLinkedPointer<T>* PoolEnd() { return this->m_poolTail; }
    inline int Count() { return this->m_count; }
    inline int Capacity() { return this->m_capacity; }

    inline void Clear() {
        if(this->m_head == this->m_tail)
            return;
        HrLinkedPointer<T> *st = this->Start();
        HrLinkedPointer<T> *end = this->End();
        HrLinkedPointer<T> *node = st;
        while(true) {
            node->Released(true);
            if(node == end)
                break;
            node = node->Next();
        }
        this->m_poolTail->Next(st);
        this->m_poolTail = end;
        this->m_tail = this->m_head;
        this->m_head->Next(0);
        this->m_head->Prev(0);
        this->m_count = 0;
    }

    int CopyToArray(T *array) {
        HrLinkedPointer<T> *node = this->Start();
        if(node == 0)
            return 0;
        int index = 0;
        while(true) {
            array[index] = node->Data();
            index++;
            if(node == this->End())
                return index;
            node = node->Next();
        }
    }
    inline int CalcPoolCount() {
        int sum = 0;
        HrLinkedPointer<T> *ptr = this->m_poolHead;
        while(true) {
            sum++;
            if(ptr == this->m_poolTail)
                break;
            ptr = ptr->Next();
        }
        // why - 1? becasue capacity = + 1 see constructor
        return sum - 1;
    }
};

template <typename T> class HrPointerListLite {
    HrPointerList<T>      *m_pool;

    HrLinkedPointer<T>    *m_head;
    HrLinkedPointer<T>    *m_tail;
    int                 m_count;
public:
    HrPointerListLite(HrPointerList<T> *globalPool) {
        this->m_pool = globalPool;
        this->m_head = this->m_tail = this->m_pool->Pop();
        this->m_tail->Next(0);
        this->m_head->Prev(0);
        this->m_count = 0;
    }
    ~HrPointerListLite() {
        Clear();
    }
    inline void Clear() {
        if(this->m_count == 0)
            return;
        this->m_pool->m_poolTail->Next(this->m_head->Next());
        this->m_head->Prev(this->m_pool->m_poolTail);
        this->m_pool->m_poolTail = this->m_tail;
        this->m_pool->m_count -= this->m_count;
        this->m_count = 0;
        this->m_tail = this->m_head;
        this->m_head->Next(0);
    }
    inline HrLinkedPointer<T>* Start() { return this->m_head->Next(); }
    inline HrLinkedPointer<T>* End() { return this->m_tail; }
    inline HrLinkedPointer<T>* Next(HrLinkedPointer<T> *node) { return node->Next(); }
    inline int Count() { return this->m_count; }

    inline HrLinkedPointer<T>* Add(const char *name) {
        HrLinkedPointer<T> *node = this->m_pool->Pop(name);
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        node->Next(0);
        this->m_count++;
        return node;
    }
    inline HrLinkedPointer<T>* Add(T *data, const char *name) {
        HrLinkedPointer<T> *node = this->Add(name);
        node->Data(data);
        return node;
    }

    inline HrLinkedPointer<T>* Add() {
        HrLinkedPointer<T> *node = this->m_pool->Pop();
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
        node->Next(0);
        this->m_count++;
        return node;
    }
    inline HrLinkedPointer<T>* Add(T *data) {
        HrLinkedPointer<T> *node = this->Add();
        node->Data(data);
        return node;
    }

    inline HrLinkedPointer<T>* Insert(HrLinkedPointer<T> *insertBefore, const char *name) {
        HrLinkedPointer<T> *node = this->m_pool->Pop(name);
        HrLinkedPointer<T> *prev = insertBefore->Prev();
        node->Prev(prev);
        prev->Next(node);
        node->Next(insertBefore);
        insertBefore->Prev(node);
        this->m_count++;
        return node;
    }
    inline HrLinkedPointer<T>* Insert(HrLinkedPointer<T> *insertBefore, T *data, const char *name) {
        HrLinkedPointer<T> *node = this->Insert(insertBefore, name);
        node->Data(data);
        return node;
    }

    inline HrLinkedPointer<T>* Insert(HrLinkedPointer<T> *insertBefore) {
        HrLinkedPointer<T> *node = this->m_pool->Pop();
        HrLinkedPointer<T> *prev = insertBefore->Prev();
        node->Prev(prev);
        prev->Next(node);
        node->Next(insertBefore);
        insertBefore->Prev(node);
        this->m_count++;
        return node;
    }
    inline HrLinkedPointer<T>* Insert(HrLinkedPointer<T> *insertBefore, T *data) {
        HrLinkedPointer<T> *node = this->Insert(insertBefore);
        node->Data(data);
        return node;
    }
    inline void Remove(HrLinkedPointer<T> *node) {
        HrLinkedPointer<T> *prev = node->Prev();
        HrLinkedPointer<T> *next = node->Next();
        prev->Next(next);
        if(next != 0) {
            next->Prev(prev);
        }
        else {
            this->m_tail = prev;
        }
        this->m_count--;
        this->m_pool->Push(node);
    }
    inline T* Item(int index) {
        HrLinkedPointer<T> *node = this->Start();
        while(index > 0) {
            if(node == this->End())
                return 0;
            node = node->Next();
            index--;
        }
        return node->Data();
    }

    inline HrLinkedPointer<T>* Get(T *data) {
        HrLinkedPointer<T> *node = this->m_head;
        while(true) {
            if(node->Data() == data)
                return node;
            if(node == this->m_tail)
                break;
            node = node->Next();
        }
        return 0;
    }

    inline int IndexOf(HrLinkedPointer<T> *item) {
        HrLinkedPointer<T> *node = this->m_head;
        int index = 0;
        while(true) {
            if(node == item)
                return index;
            if(node == this->m_tail)
                break;
            node = node->Next();
            index++;
        }
        return -1;
    }
};

#endif //HFT_ROBOT_HRPOINTERLIST_H