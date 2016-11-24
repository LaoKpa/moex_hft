//
// Created by root on 13.10.16.
//

#ifndef HFT_ROBOT_ORDERBOOKTABLE_H
#define HFT_ROBOT_ORDERBOOKTABLE_H

#include "../Lib/HashTable.h"
#include "../FastTypes.h"

#define MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH 2000

template <typename T> class MDEntrQueue {
    T           **m_incEntries;
    int         m_incEntriesCount;
    int         m_incEntriesMaxIndex;
    int         m_incStartRptSeq;

public:
    MDEntrQueue() {
        this->m_incEntries = new T*[MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH];
        this->m_incEntriesCount = MDENTRYINFO_INCREMENTAL_ENTRIES_BUFFER_LENGTH;
        bzero(this->m_incEntries, sizeof(T*) * this->m_incEntriesCount);
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
    }
    ~MDEntrQueue() {
        delete this->m_incEntries;
    }

    inline void StartRptSeq(int rptSeq) {
        this->m_incStartRptSeq = rptSeq;
    }

    inline int StartRptSeq() { return this->m_incStartRptSeq; }

    inline void AddEntry(T *entry) {
        int index = entry->RptSeq - this->m_incStartRptSeq;
        this->m_incEntries[index] = entry;
        if(index > this->m_incEntriesMaxIndex)
            this->m_incEntriesMaxIndex = index;
    }

    inline void Reset() {
        bzero(this->m_incEntries, sizeof(T*) * this->m_incEntriesCount);
        this->m_incEntriesMaxIndex = -1;
        this->m_incStartRptSeq = 0;
    }

    inline void Clear() {
        T **ptr = this->m_incEntries;
        T *item = 0;
        for(int i = 0; i < this->m_incEntriesCount; i++) {
            item = *ptr;
            if(item != 0) item->Clear();
        }
        this->Reset();
    }

    inline int MaxIndex() { return this->m_incEntriesMaxIndex; }
    inline bool HasEntries() { return this->m_incEntriesMaxIndex != -1; };
    inline T** Entries() { return this->m_incEntries; }
    inline int RptSeq() { return this->m_incStartRptSeq; }
};

template <typename T> class OrderBookTableItem {
    PointerList<T>      *m_sellQuoteList;
    PointerList<T>      *m_buyQuoteList;

    MDEntrQueue<T>      *m_entryInfo;

    bool                 m_used;
    int                  m_rptSeq;

    SizedArray          *m_symbol;
    SizedArray          *m_tradingSession;
public:
    OrderBookTableItem() {
        this->m_entryInfo = new MDEntrQueue<T>();
        this->m_sellQuoteList = new PointerList<T>(128);
        this->m_buyQuoteList = new PointerList<T>(128);
        this->m_rptSeq = 0;
        this->m_used = false;
    }
    ~OrderBookTableItem() {
        delete this->m_entryInfo;
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline SizedArray* Symbol() { return this->m_symbol; }
    inline void Symbol(SizedArray *symbol) { this->m_symbol = symbol; }
    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline void TradingSession(SizedArray *session) { this->m_tradingSession = session; }

    inline MDEntrQueue<T>* QueueEntries() { return this->m_entryInfo; }

    inline PointerList<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline PointerList<T>* BuyQuotes() { return this->m_buyQuoteList; }
    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline int RptSeq() { return this->m_rptSeq; }
    inline void RptSeq(int rptSeq) { this->m_rptSeq = rptSeq; }
    inline void Clear(PointerList<T> *list) {
        this->m_rptSeq = 0;
        if(list->Count() == 0)
            return;
        LinkedPointer<T> *node = list->Start();
        while(true) {
            node->Data()->Clear();
            if(node == list->End())
                break;
            node = node->Next();
        }
        list->Clear();
    }
    inline void Clear() {
        Clear(this->m_sellQuoteList);
        Clear(this->m_buyQuoteList);
        this->m_entryInfo->Clear();
        this->m_rptSeq = 0;
    }

    inline LinkedPointer<T>* AddBuyQuote(Decimal *price) {
        LinkedPointer<T> *node = this->m_buyQuoteList->Start();
        double value = price->Calculate();

        if(node != null) {
            while (true) {
                if (node->Data()->MDEntryPx.Value < value) {
                    LinkedPointer<T> *curr = this->m_buyQuoteList->Pop();
                    this->m_buyQuoteList->Insert(node, curr);
                    return curr;
                }
                if (node == this->m_buyQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        LinkedPointer<T> *curr = this->m_buyQuoteList->Pop();
        this->m_buyQuoteList->Add(curr);
        return curr;
    }

    inline LinkedPointer<T>* AddSellQuote(Decimal *price) {
        LinkedPointer<T> *node = this->m_sellQuoteList->Start();
        double value = price->Calculate();

        if(node != null) {
            while (true) {
                if (node->Data()->MDEntryPx.Value > value) {
                    LinkedPointer<T> *curr = this->m_sellQuoteList->Pop();
                    this->m_sellQuoteList->Insert(node, curr);
                    return curr;
                }
                if (node == this->m_sellQuoteList->End())
                    break;
                node = node->Next();
            }
        }
        LinkedPointer<T> *curr = this->m_sellQuoteList->Pop();
        this->m_sellQuoteList->Add(curr);
        return curr;
    }

    inline LinkedPointer<T>* AddBuyQuote(T *item) {
        LinkedPointer<T> *res = AddBuyQuote(&(item->MDEntryPx));
        item->Used = true;
        res->Data(item);
        return res;
    }

    inline LinkedPointer<T>* AddSellQuote(T *item) {
        LinkedPointer<T> *res = AddSellQuote(&(item->MDEntryPx));
        item->Used = true;
        res->Data(item);
        return res;
    }

    inline LinkedPointer<T>* Add(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            return this->AddBuyQuote(info);
        return this->AddSellQuote(info);
    }

    inline LinkedPointer<T>* GetQuote(PointerList<T> *list, T *info) {
        LinkedPointer<T> *node = list->Start();
        if(node == 0)
            return 0;
        while(true) {
            if(node->Data()->Id->Equal(info->MDEntryID, info->MDEntryIDLength))
                return node;
            if(node == list->End())
                return 0;
            node = node->Next();
        }
    }

    inline LinkedPointer<T>* RemoveBuyQuote(T *info) {
        LinkedPointer<T> *node = this->m_buyQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(StringIdComparer::Equal(data->MDEntryID, data->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength)) {
                this->m_buyQuoteList->Remove(node);
                data->Clear();
                return node;
            }
            if(node == this->m_buyQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline LinkedPointer<T>* RemoveSellQuote(T *info) {
        LinkedPointer<T> *node = this->m_sellQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(StringIdComparer::Equal(data->MDEntryID, data->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength)) {
                this->m_sellQuoteList->Remove(node);
                data->Clear();
                return node;
            }
            if(node == this->m_sellQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline void ChangeBuyQuote(T *info) {
        this->RemoveBuyQuote(info);
        this->AddBuyQuote(info);
    }

    inline void ChangeSellQuote(T *info) {
        this->RemoveSellQuote(info);
        this->AddSellQuote(info);
    }

    inline void Remove(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->RemoveBuyQuote(info);
        else
            this->RemoveSellQuote(info);
    }

    inline void Change(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->ChangeBuyQuote(info);
        else
            this->ChangeSellQuote(info);
    }

    inline MDEntrQueue<T>* EntriesQueue() { return this->m_entryInfo; }

    inline bool IsNextMessage(T *info) {
        return info->RptSeq - this->m_rptSeq == 1;
    }

    inline void PushMessageToQueue(T *info) {
        this->m_entryInfo->StartRptSeq(this->m_rptSeq + 1);
        this->m_entryInfo->AddEntry(info);
    }

    inline void ForceProcessMessage(T *info) {
        if(info->MDUpdateAction == mduaAdd)
            this->Add(info);
        else if(info->MDUpdateAction == mduaChange)
            this->Change(info);
        else
            this->Remove(info);
    }

    inline bool ProcessIncrementalMessage(T *info) {
        if(!this->IsNextMessage(info)) {
            this->PushMessageToQueue(info);
            return false;
        }
        this->m_rptSeq = info->RptSeq;
        this->ForceProcessMessage(info);
        if(this->m_entryInfo->HasEntries())
            return this->ProcessQueueMessages();
        return true;
    }

    inline void StartProcessSnapshotMessages() {
        this->BuyQuotes()->Clear();
        this->SellQuotes()->Clear();
    }

    inline void ProcessSnapshotMessage(T *info) {
        this->ForceProcessMessage(info);
    }

    inline bool ProcessQueueMessages() {
        if(!this->m_entryInfo->HasEntries())
            return false;
        T **entry = this->m_entryInfo->Entries();
        int incRptSeq = this->m_entryInfo->RptSeq();
        int maxIndex = this->m_entryInfo->MaxIndex();
        if(this->m_rptSeq + 1 < incRptSeq)
            return false;
        int startIndex = this->m_rptSeq + 1 - incRptSeq;
        for(int i = 0; i < startIndex; i++, entry++) {
            if((*entry) != 0) (*entry)->Clear();
        }
        for(int index = startIndex; index <= maxIndex; index++) {
            if((*entry) == 0)
                return false;
            ForceProcessMessage(*entry);
            this->m_rptSeq = (*entry)->RptSeq;
            entry++;
        }
        this->m_entryInfo->Reset();
        return true;
    }

    inline bool EndProcessSnapshotMessages() {
        return this->ProcessQueueMessages();
    }
};


template <typename T> class OrderTableItem {
    PointerList<T>      *m_sellQuoteList;
    PointerList<T>      *m_buyQuoteList;

    bool                 m_used;
    SizedArray          *m_symbol;
    SizedArray          *m_tradingSession;
public:
    OrderTableItem() {
        this->m_sellQuoteList = new PointerList<T>(128);
        this->m_buyQuoteList = new PointerList<T>(128);
    }
    ~OrderTableItem() {
        delete this->m_sellQuoteList;
        delete this->m_buyQuoteList;
    }

    inline SizedArray* Symbol() { return this->m_symbol; }
    inline void Symbol(SizedArray *symbol) { this->m_symbol = symbol; }
    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline void TradingSession(SizedArray *session) { this->m_tradingSession = session; }

    inline PointerList<T>* SellQuotes() { return this->m_sellQuoteList; }
    inline PointerList<T>* BuyQuotes() { return this->m_buyQuoteList; }
    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(PointerList<T> *list) {
        if(list->Count() == 0)
            return;
        LinkedPointer<T> *node = list->Start();
        while(true) {
            node->Data()->Clear();
            if(node == list->End())
                break;
            node = node->Next();
        }
        list->Clear();
    }
    inline void Clear() {
        Clear(this->m_sellQuoteList);
        Clear(this->m_buyQuoteList);
    }

    inline LinkedPointer<T>* AddBuyQuote(T *item) {
        item->Used = true;
        return this->m_buyQuoteList->Add(item);
    }

    inline LinkedPointer<T>* AddSellQuote(T *item) {
        item->Used = true;
        return this->m_sellQuoteList->Add(item);
    }

    inline LinkedPointer<T>* Add(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            return this->AddBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            return this->AddSellQuote(info);
        return 0;
    }

    inline LinkedPointer<T>* GetQuote(PointerList<T> *list, T *info) {
        LinkedPointer<T> *node = list->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *info2 = node->Data();
            if(StringIdComparer::Equal(info2->MDEntryID, info2->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength))
                return node;
            if(node == list->End())
                return 0;
            node = node->Next();
        }
    }

    inline LinkedPointer<T>* RemoveBuyQuote(T *info) {
        LinkedPointer<T> *node = this->m_buyQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(StringIdComparer::Equal(data->MDEntryID, data->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength)) {
                this->m_buyQuoteList->Remove(node);
                data->Clear();
                return node;
            }
            if(node == this->m_buyQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline LinkedPointer<T>* RemoveSellQuote(T *info) {
        LinkedPointer<T> *node = this->m_sellQuoteList->Start();
        if(node == 0)
            return 0;
        while(true) {
            T *data = node->Data();
            if(StringIdComparer::Equal(data->MDEntryID, data->MDEntryIDLength, info->MDEntryID, info->MDEntryIDLength)) {
                this->m_sellQuoteList->Remove(node);
                data->Clear();
                return node;
            }
            if(node == this->m_sellQuoteList->End())
                break;
            node = node->Next();
        }
        return 0;
    }

    inline void ChangeBuyQuote(T *info) {
        LinkedPointer<T> *ptr = GetQuote(this->m_buyQuoteList, info);
        info->Used = true;
        ptr->Data()->Clear();
        ptr->Data(info);
    }

    inline void ChangeSellQuote(T *info) {
        LinkedPointer<T> *ptr = GetQuote(this->m_sellQuoteList, info);
        info->Used = true;
        ptr->Data()->Clear();
        ptr->Data(info);
    }

    inline void Remove(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->RemoveBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            this->RemoveSellQuote(info);
    }

    inline void Change(T *info) {
        if(info->MDEntryType[0] == mdetBuyQuote)
            this->ChangeBuyQuote(info);
        else if(info->MDEntryType[0] == mdetSellQuote)
            this->ChangeSellQuote(info);
    }
};


template <typename T> class TradeTableItem {
    PointerList<T>      *m_tradeList;

    bool                 m_used;
    SizedArray          *m_symbol;
    SizedArray          *m_tradingSession;
public:
    TradeTableItem() {
        this->m_tradeList = new PointerList<T>(128);
    }
    ~TradeTableItem() {
        delete this->m_tradeList;
    }

    inline SizedArray* Symbol() { return this->m_symbol; }
    inline void Symbol(SizedArray *symbol) { this->m_symbol = symbol; }
    inline SizedArray* TradingSession() { return this->m_tradingSession; }
    inline void TradingSession(SizedArray *session) { this->m_tradingSession = session; }

    inline PointerList<T>* Trades() { return this->m_tradeList; }
    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }
    inline void Clear(PointerList<T> *list) {
        if(list->Count() == 0)
            return;
        LinkedPointer<T> *node = list->Start();
        while(true) {
            node->Data()->Clear();
            if(node == list->End())
                break;
            node = node->Next();
        }
        list->Clear();
    }
    inline void Clear() {
        Clear(this->m_tradeList);
    }

    inline LinkedPointer<T>* Add(T *info) {
        return this->m_tradeList->Add(info);
    }
};

/*
template <typename T> class StatisticsTableItem {
    bool            m_used;
    Decimal         *m_buyQuote;
    Decimal         *m_sellQuote;

public:
    StatisticsTableItem() {
        this->m_used = false;
    }

    inline bool Used() { return this->m_used; }
    inline void Used(bool used) { this->m_used = used; }

    inline void SetProperty(MDEntryType entryType, T *item) {
        if(entryType <= MDEntryType::mdetOLSTradeAskAuctionOpenClose) {
            if(entryType <= MDEntryType::mdetDisbalance) {
                if(entryType <= MDEntryType::mdetPriceOpenFirst) {
                    if(entryType <= MDEntryType::mdetLastDealInfo) {
                        if(entryType <= MDEntryType::mdetSellQuote) {
                            if(entryType == MDEntryType::mdetBuyQuote) {
                                this->m_buyQuote->Assign(item->MDEntryPx);
                            }
                            else { // mdetSellQuote
                                this->m_sellQuote->Assign(item->MDEntryPx);
                            }
                        }
                        else {
                            // mdetLastDealInfo

                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetIndicesList) {
                        }
                        else { // mdetPriceOpenFirst
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetPriceMin) {
                        if(entryType <= MDEntryType::mdetPriceMax) {
                            if(entryType == MDEntryType::mdetPriceCloseLast) {
                            }
                            else { // mdetPriceMax
                            }
                        }
                        else {
                            // mdetPriceMin
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceAve) {
                        }
                        else { // mdetDisbalance
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAuctionPriceCalculated) {
                    if(entryType <= MDEntryType::mdetAskPriceMax) {
                        if(entryType <= MDEntryType::mdetEmptyBook) {
                            if(entryType == MDEntryType::mdetTransactionsMagnitude) {
                            }
                            else { // mdetEmptyBook
                            }
                        }
                        else {
                            // mdetAskPriceMax
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetBidPriceMin) {
                        }
                        else { // mdetAuctionPriceCalculated
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetMSSTradingDenyNotEnoughMoney) {
                        if(entryType <= MDEntryType::mdetAuctionMagnitudeClose) {
                            if(entryType == MDEntryType::mdetAuctionPriceClose) {
                            }
                            else { // mdetAuctionMagnitudeClose
                            }
                        }
                        else {
                            // mdetMSSTradingDenyNotEnoughMoney
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetMSSTradeAskAuctionMagnitudeOpenClose) {
                        }
                        else { // mdetOLSTradeAskAuctionOpenClose
                        }
                    }
                }
            }
        }
        else {
            if(entryType <= MDEntryType::mdetPriceCurrentOfficial) {
                if(entryType <= MDEntryType::mdetSessionBid) {
                    if(entryType <= MDEntryType::mdetPreTradePeriodPrice) {
                        if(entryType <= MDEntryType::mdetOLSTradeBidAuctionOpenClose) {
                            if(entryType == MDEntryType::mdetMSSTradeBidAuctionMagnitudeOpenClose) {
                            }
                            else { // mdetOLSTradeBidAuctionOpenClose
                            }
                        }
                        else {
                            // mdetPreTradePeriodPrice
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetSessionAsk) {
                        }
                        else { // mdetSessionBid
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetTradePrice) {
                        if(entryType <= MDEntryType::mdetTradePrice2) {
                            if(entryType == MDEntryType::mdetPostTradePeriodPrice) {
                            }
                            else { // mdetTradePrice2
                            }
                        }
                        else {
                            // mdetTradePrice
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetPriceOpenOfficial) {
                        }
                        else { // mdetPriceCurrentOfficial
                        }
                    }
                }
            }
            else {
                if(entryType <= MDEntryType::mdetAskTotal) {
                    if(entryType <= MDEntryType::mdetAuctionPriceBigPackets) {
                        if(entryType <= MDEntryType::mdetPriceCloseOfficial) {
                            if(entryType == MDEntryType::mdetLegitimQuote) {
                            }
                            else { // mdetPriceCloseOfficial
                            }
                        }
                        else {
                            // mdetAuctionPriceBigPackets
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetDuration) {
                        }
                        else { // mdetAskTotal
                        }
                    }
                }
                else {
                    if(entryType <= MDEntryType::mdetAuctionMagnitudeBigPackets) {
                        if(entryType == MDEntryType::mdetBidTotal) {
                        }
                        else { // mdetAuctionMagnitudeBigPackets
                        }
                    }
                    else {
                        if(entryType == MDEntryType::mdetCumulativeCouponDebit) {
                        }
                        else { // mdetAllDeals
                        }
                    }
                }
            }
        }
    }
    
    inline void Add(T *item) {
        SetProperty(item->MDentryType[0], item);
    }
    inline void Change(T *item) {
        SetProperty(item->MDentryType[0], item);
    }
    inline void Remove(T *item) {

    }
};
*/

template <template<typename ITEMINFO> class TABLEITEM, typename INFO, typename ITEMINFO> class MarketDataTable {
    HashTable<TABLEITEM<ITEMINFO>>              *m_table;
    TABLEITEM<ITEMINFO>                         *m_snapshotItem;
    int                                         m_queueItemsCount;
public:
    MarketDataTable() {
        this->m_table = new HashTable<TABLEITEM<ITEMINFO>>();
        this->m_queueItemsCount = 0;
    }
    ~MarketDataTable() {
        delete this->m_table;
    }
    inline bool ProcessIncremental(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_table->AddUsed(tableItem);
        bool prevHasEntries = tableItem->QueueEntries()->HasEntries();
        bool res = tableItem->ProcessIncrementalMessage(info);
        bool hasEntries = tableItem->QueueEntries()->HasEntries();
        if(!prevHasEntries && hasEntries)
            this->m_queueItemsCount++;
        else if(prevHasEntries && !hasEntries)
            this->m_queueItemsCount--;
        return res;
    }
    inline void StartProcessSnapshot(INFO *info) {
        this->m_snapshotItem = this->m_table->GetCachedItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        if(this->m_snapshotItem == 0)
            this->m_snapshotItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_table->AddUsed(this->m_snapshotItem);
        this->m_snapshotItem->StartProcessSnapshotMessages();
    }
    inline bool EndProcessSnapshot(){
        bool res = this->m_snapshotItem->EndProcessSnapshotMessages();
        if(!this->m_snapshotItem->EntriesQueue()->HasEntries())
            this->m_queueItemsCount--;
        return res;
    }
    inline void ProcessSnapshot(ITEMINFO **item, int count, int rptSeq) {
        for(int j = 0; j < count; j++) {
            this->m_snapshotItem->ProcessSnapshotMessage(*item);
            item++;
        }
        this->m_snapshotItem->RptSeq(rptSeq);
    }
    inline bool ProcessSnapshot(INFO *info) {
        this->StartProcessSnapshot(info);
        this->ProcessSnapshot(info->GroupMDEntries, info->GroupMDEntriesCount, info->RptSeq);
        return this->EndProcessSnapshot();
    }
    inline void Add(const char *symbol, int symbolLen, const char *tradingSession, int tradingLen, ITEMINFO *item) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingLen);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(item);
    }
    inline void Add(const char *symbol, int symbolLen, const char *tradingSession, int tradingLen, ITEMINFO **items) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingLen);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(items);
    }
    inline void Add(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_table->AddUsed(tableItem);
        tableItem->Add(info);
    }
    inline void Add(INFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        this->m_table->AddUsed(tableItem);
        ITEMINFO **item = info->GroupMDEntries;

        for(int i = 0; i < info->GroupMDEntriesCount; i++, item++) {
            tableItem->Add(*item);
        }
    }
    inline void Remove(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        tableItem->Remove(info);
    }
    inline void Change(ITEMINFO *info) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(info->Symbol, info->SymbolLength, info->TradingSessionID, info->TradingSessionIDLength);
        tableItem->Change(info);
    }
    inline void Clear() {
        this->m_table->Clear();
    }
    inline void ClearItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) {
        TABLEITEM<ITEMINFO> *tableItem = this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingSessionLen);
        this->m_table->RemoveUsed(tableItem);
        tableItem->Clear();
    }
    inline TABLEITEM<ITEMINFO>*** TableCore() { return this->m_table->TableCore(); }
    inline int SymbolsCount() { return this->m_table->SymbolsCount(); }
    inline int TradingSessionsCount() { return this->m_table->TradingSessionsCount(); }
    inline int UsedItemCount() { return this->m_table->UsedItemCount(); }
    inline TABLEITEM<ITEMINFO>* Item(int sindex, int tindex) { return this->m_table->Item(sindex, tindex); }
    inline TABLEITEM<ITEMINFO>* UsedItem(int index) { return this->m_table->UsedItems()->Item(index); }
    inline TABLEITEM<ITEMINFO>* GetItem(const char *symbol, int symbolLen, const char *tradingSession, int tradingSessionLen) { return this->m_table->GetItem(symbol, symbolLen, tradingSession, tradingSessionLen);  }
    inline TABLEITEM<ITEMINFO>* GetItem(const char *symbol, const char *tradingSession) { return this->m_table->GetItem(symbol, strlen(symbol), tradingSession, strlen(tradingSession));  }
    inline TABLEITEM<ITEMINFO>* SnapshotItem() { return this->m_snapshotItem; }
    inline bool HasQueueEntries() {
        return this->m_queueItemsCount > 0;
    }
    inline int QueueItemsCount() { return this->m_queueItemsCount; }
};

#endif //HFT_ROBOT_ORDERBOOKTABLE_H
