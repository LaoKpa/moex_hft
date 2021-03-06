//
// Created by root on 27.10.16.
//

#ifndef HFT_ROBOT_TRADETESTER_H
#define HFT_ROBOT_TRADETESTER_H
#include "../Settings.h"

#ifdef TEST

#include "../Feeds/FeedConnection.h"
#include "TestMessagesHelper.h"
#include <stdio.h>

class TradeTesterFond {
    FeedConnection_FOND_TLR *incFond;
    FeedConnection_FOND_TLS *snapFond;
    TestMessagesHelper      *m_helper;
    MarketDataTable<TradeInfo, AstsTLSFONDInfo, AstsTLSFONDItemInfo> *m_table;

public:
    TradeTesterFond() {
        this->m_helper = new TestMessagesHelper();
        this->m_table = new MarketDataTable<TradeInfo, AstsTLSFONDInfo, AstsTLSFONDItemInfo>();
        this->incFond = new FeedConnection_FOND_TLR("TLR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->snapFond = new FeedConnection_FOND_TLS("TLS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);
        this->m_table->InitSymbols(10, 10);
        this->incFond->SetSymbolManager(new SymbolManager(10));
        this->snapFond->SetSymbolManager(this->incFond->GetSymbolManager());
        this->incFond->TradeFond()->InitSymbols(10, 10);
        this->incFond->SetMaxLostPacketCountForStartSnapshot(1);
    }
    ~TradeTesterFond() {
        delete this->incFond;
        delete this->snapFond;
        delete this->m_helper;
        delete this->m_table;
    }

    void TestItem(TradeInfo<AstsTLSFONDItemInfo> *tableItem) {
        for(int i = 0; i < tableItem->Trades()->Count(); i++)
            if(tableItem->Trades()->Item(i)->Allocator == 0)
                throw;
        if(tableItem->EntriesQueue() != 0) {
            if(tableItem->EntriesQueue()->Pointer->Data() != tableItem->EntriesQueue())
                throw;
            if(tableItem->EntriesQueue()->Allocator == 0)
                throw;
        }
    }

    void TestTableItemsAllocator(MarketDataTable<TradeInfo, AstsTLSFONDInfo, AstsTLSFONDItemInfo> *table) {
        for(int i = 0; i < table->SymbolsCount(); i++) {
            for(int j = 0; j < table->Symbol(i)->Count(); j++) {
                TradeInfo<AstsTLSFONDItemInfo> *item = table->Item(i, j);
                TestItem(item);
            }
        }
        TradeInfo<AstsTLSFONDItemInfo> *tb = new TradeInfo<AstsTLSFONDItemInfo>();
        tb->ObtainEntriesQueue();
        LinkedPointer<MDEntryQueue> *ptr = tb->EntriesQueue()->Allocator->Start();
        while(ptr != 0) {
            if(ptr->Data() == 0)
                throw;
            if(ptr == tb->EntriesQueue()->Allocator->End())
                break;
            ptr = ptr->Next();
        }
        tb->ReleaseEntryQue();
    }

    void Clear() {
        incFond->SetSnapshot(this->snapFond);
        incFond->TradeFond()->Clear();
        incFond->GetSymbolManager()->Clear();
        incFond->ClearMessages();
        incFond->WaitLostIncrementalMessageMaxTimeMcs(50000);
        incFond->m_waitTimer->Stop();
        incFond->m_waitTimer->Stop(1);
        snapFond->ClearMessages();
        snapFond->WaitSnapshotMaxTimeMcs(50000);
        incFond->StartListenSnapshot();
        snapFond->m_waitTimer->Stop();
        snapFond->Stop();
        incFond->Stop();

        this->m_helper->Clear();
        this->m_table->Clear();
        incFond->Start();
    }

    void Test_OnIncrementalRefresh_TLR_FOND_Add() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", "ses1");

        AstsIncrementalTLRFONDInfo *info = this->m_helper->CreateAstsIncrementalTLRFONDInfo();

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsTLSFONDItemInfo *item3 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsTLSFONDItemInfo *item4 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->incFond->OnIncrementalRefresh_TLR_FOND(info);

        if(this->incFond->TradeFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->TradeFond()->Symbol(0)->Count() != 1)
            throw;
        TradeInfo<AstsTLSFONDItemInfo> *obi = this->incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 1)
            throw;
        AstsTLSFONDItemInfo *quote = obi->Trades()->Item(0);
        Decimal price(3, -2);
        Decimal size(1, 2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->incFond->OnIncrementalRefresh_TLR_FOND(info);

        if(this->incFond->TradeFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->TradeFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 2)
            throw;
        quote = obi->Trades()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->incFond->OnIncrementalRefresh_TLR_FOND(info);

        if(this->incFond->TradeFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->TradeFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 3)
            throw;

        quote = obi->Trades()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        quote = obi->Trades()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->Trades()->Last()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "333333", 6))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->incFond->OnIncrementalRefresh_TLR_FOND(info);

        if(this->incFond->TradeFond()->UsedItemCount() != 1)
            throw;
        if(this->incFond->TradeFond()->SymbolsCount() != 1)
            throw;
        if(this->incFond->TradeFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(obi == 0)
            throw;
        if(obi->Trades()->Count() != 4)
            throw;

        quote = obi->Trades()->Item(0);
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "111111", 6))
            throw;

        quote = obi->Trades()->Item(1);
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "222222", 6))
            throw;

        quote = obi->Trades()->Start()->Next()->Next()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "333333", 6))
            throw;

        quote = obi->Trades()->Last()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "444444", 6))
            throw;
    }

    void Test_Clear() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", "ses1");

        AstsIncrementalTLRFONDInfo *info = this->m_helper->CreateAstsIncrementalTLRFONDInfo();
        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsTLSFONDItemInfo *item3 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsTLSFONDItemInfo *item4 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_TLR_FOND(info);

        this->incFond->TradeFond()->Clear();
        if(item1->Allocator->Count() != 0 ||
           item2->Allocator->Count() != 0 ||
           item3->Allocator->Count() != 0 ||
           item4->Allocator->Count() != 0)
            throw;
        if(this->incFond->TradeFond()->UsedItemCount() != 0)
            throw;

        TradeInfo<AstsTLSFONDItemInfo> *obi = this->incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(obi->Trades()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_TLS_FOND() {
        this->Clear();
        this->TestDefaults();
        this->AddSymbol("symbol1", "ses1");

        AstsIncrementalTLRFONDInfo *info = this->m_helper->CreateAstsIncrementalTLRFONDInfo();
        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "111111", 1);
        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "222222", 2);
        AstsTLSFONDItemInfo *item3 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "333333", 3);
        AstsTLSFONDItemInfo *item4 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "444444", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->incFond->OnIncrementalRefresh_TLR_FOND(info);

        TradeInfo<AstsTLSFONDItemInfo> *obi2 = this->incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(obi2->Trades()->Count() != 4)
            throw;

        AstsTLSFONDInfo *info2 = this->m_helper->CreateTLSFondInfo("t1s2", "ses1");
        AstsTLSFONDItemInfo *newItem1 = this->m_helper->CreateTLSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "777777");
        AstsTLSFONDItemInfo *newItem2 = this->m_helper->CreateTLSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "888888");
        info2->RptSeq = 5;

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->incFond->TradeFond()->ObtainSnapshotItem(info2);
        this->incFond->TradeFond()->ProcessSnapshot(info2);

        if(this->incFond->TradeFond()->UsedItemCount() != 2)
            throw;

        TradeInfo<AstsTLSFONDItemInfo> *obi3 = this->incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(obi3->Trades()->Count() != 4)
            throw;

        TradeInfo<AstsTLSFONDItemInfo> *obi = this->incFond->TradeFond()->GetItem("t1s2", "ses1");
        if(obi->Trades()->Count() != 2)
            throw;

        AstsTLSFONDItemInfo *qt1 = obi->Trades()->Item(0);
        AstsTLSFONDItemInfo *qt2 = obi->Trades()->Item(1);

        if(!StringIdComparer::Equal(qt1->MDEntryID, 2, "777777", 2))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 2, "888888", 2))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_TLR_FOND() {
        printf("TLR FOND Test_OnIncrementalRefresh_TLR_FOND_Add\n");
        Test_OnIncrementalRefresh_TLR_FOND_Add();
        printf("TLR FOND Test_Clear\n");
        Test_Clear();
    }

    void Test_TLR_FOND() {
        printf("TLR FOND Test_OnIncrementalRefresh_TLR_FOND\n");
        Test_OnIncrementalRefresh_TLR_FOND();
        printf("TLR FOND Test_OnFullRefresh_TLS_FOND\n");
        Test_OnFullRefresh_TLS_FOND();
    }

    void TestDefaults() {
        if(this->incFond->TradeFond()->SymbolsCount() != 0)
            throw;
        this->TestTableItemsAllocator(incFond->TradeFond());
        TradeInfo<AstsTLSFONDItemInfo> *tb = new TradeInfo<AstsTLSFONDItemInfo>();
        tb->ObtainEntriesQueue();
        LinkedPointer<MDEntryQueue> *ptr = tb->EntriesQueue()->Allocator->Start();
        while(ptr != 0) {
            if(ptr->Data() == 0)
                throw;
            if(ptr == tb->EntriesQueue()->Allocator->End())
                break;
            ptr = ptr->Next();
        }
        tb->ReleaseEntryQue();
    }

    void TestTableItem_CorrectBegin() {
        TradeInfo<AstsTLSFONDItemInfo> *tb = new TradeInfo<AstsTLSFONDItemInfo>();

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        if(!tb->ProcessIncrementalMessage(item1))
            throw;
        if(tb->EntriesQueue() != 0)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        delete tb;
    }

    void TestTableItem_IncorrectBegin() {
        TradeInfo<AstsTLSFONDItemInfo> *tb = new TradeInfo<AstsTLSFONDItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<TradeInfo<AstsTLSFONDItemInfo>>("symbol1"));

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
        item1->RptSeq = 2;
        item1->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item1))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(tb->EntriesQueue()->StartRptSeq() != 1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 1)
            throw;
        if(tb->RptSeq() != 0)
            throw;

        delete tb;
    }

    void TestTableItem_SkipMessage() {
        TradeInfo<AstsTLSFONDItemInfo> *tb = new TradeInfo<AstsTLSFONDItemInfo>();
        tb->SymbolInfo(this->m_helper->CreateSymbol<TradeInfo<AstsTLSFONDItemInfo>>("symbol1"));

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "111111");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");
        item2->RptSeq = 3;
        item2->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item2))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 2)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        AstsTLSFONDItemInfo *item3 = this->m_helper->CreateTLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "333333");
        item3->RptSeq = 4;
        item3->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item3))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 2)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        delete tb;
    }

    void TestTable_Default() {
        this->ClearSymbols();

        TestTableItemsAllocator(this->m_table);
    }

    void AddSymbol(const char *symbol, const char *session) {
        this->incFond->GetSymbolManager()->AddSymbol(symbol);
        this->incFond->TradeFond()->Add(symbol, session);
        this->m_table->Add(symbol, session);
    }

    void AddSymbol(const char *symbol) {
        AddSymbol(symbol, "ses1");
    }

    void ClearSymbols() {
        this->m_table->Clear();
        this->incFond->TradeFond()->Clear();
        this->incFond->GetSymbolManager()->Clear();
    }

    void TestTable_AfterClear() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsTLSFONDItemInfo *item = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", "111111", 1);
        item->RptSeq = 1;

        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", "111111", 2);
        item2->RptSeq = 2;

        AstsTLSFONDItemInfo *item3 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", "111111", 4);
        item3->RptSeq = 4;

        this->m_table->ProcessIncremental(item, 0, item->TradingSessionIDUint);
        this->m_table->ProcessIncremental(item2, 0, item->TradingSessionIDUint);
        this->m_table->ProcessIncremental(item3, 0, item->TradingSessionIDUint);

        if(this->m_table->UsedItemCount() != 1)
            throw;
        TradeInfo<AstsTLSFONDItemInfo> *tableItem = this->m_table->GetItem("symbol1", "ses1");
        if(tableItem->EntriesQueue()->MaxIndex() != 1) // 3 is empty and 4 has value
            throw;
        this->m_table->Clear();
        if(this->m_table->UsedItemCount() != 0)
            throw;
        if(tableItem->RptSeq() != 0)
            throw;
        if(tableItem->Trades()->Count() != 0)
            throw;
        if(tableItem->EntriesQueue() != 0)
            throw;


    }

    void TestTable_CorrectBegin() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint))
            throw;
    }

    void TestTable_IncorrectBegin() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 2;

        if(this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint))
            throw;
    }

    void TestTable_SkipMessages() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionIDUint))
            throw;


    }

    void Test_2UsedItemsAfter2IncrementalMessages() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol2", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item2->RptSeq = 1;

        if(!this->m_table->ProcessIncremental(item2, 1, item2->TradingSessionIDUint))
            throw;

        if(this->m_table->UsedItemCount() != 2)
            throw;


    }

    void TestTable_CorrectApplySnapshot() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint);

        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "222222", 3);
        item2->RptSeq = 3;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item3 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "333333", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item4 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "444444", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item5 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "555555", 3);
        item5->RptSeq = 3;

        AstsTLSFONDInfo *info = this->m_helper->CreateTLSFondInfo("symbol1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 3;

        TradeInfo<AstsTLSFONDItemInfo> *tb = this->m_table->GetItem("symbol1", "ses1");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->Trades()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->Trades()->Count() != 1)
            throw;
        if(tb->RptSeq() == 3)
            throw;
        if(!this->m_table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 5)
            throw;
        if(tb->Trades()->Count() != 3)
            throw;
        if(tb->EntriesQueue() != 0)
            throw;
    }

    void TestTable_CorrectApplySnapshot_2() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint);

        AstsTLSFONDItemInfo *item3 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "333333", 4);
        item3->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item4 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "444444", 5);
        item4->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionIDUint))
            throw;

        AstsTLSFONDInfo *info1 = this->m_helper->CreateTLSFondInfo("symbol1", "ses1");
        info1->GroupMDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->RouteFirst = true;
        info1->GroupMDEntries[0] = this->m_helper->CreateTLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");

        AstsTLSFONDInfo *info2 = this->m_helper->CreateTLSFondInfo("symbol1", "ses1");
        info2->GroupMDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->RouteFirst = true;
        info2->GroupMDEntries[0] = this->m_helper->CreateTLSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "222222");

        TradeInfo<AstsTLSFONDItemInfo> *tb = this->m_table->GetItem("symbol1", "ses1");

        this->m_table->ObtainSnapshotItem(info1);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->Trades()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info1);
        this->m_table->ProcessSnapshot(info2);
        if(!this->m_table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 5)
            throw;
        if(tb->Trades()->Count() != 4)
            throw;
    }

    void TestTable_IncorrectApplySnapshot() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint);

        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "222222", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item3 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "333333", 5);
        item3->RptSeq = 5;

        if(this->m_table->ProcessIncremental(item3, 0, item3->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item4 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "444444", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item5 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "555555", 2);
        item5->RptSeq = 2;

        AstsTLSFONDInfo *info = this->m_helper->CreateTLSFondInfo("symbol1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 2;

        TradeInfo<AstsTLSFONDItemInfo> *tb = this->m_table->GetItem("symbol1", "ses1");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->Trades()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 2);
        if(tb->Trades()->Count() != 1)
            throw;
        if(tb->RptSeq() == 2)
            throw;
        if(this->m_table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 2)
            throw;
    }

    void TestTable_IncorrectApplySnapshot_WhenMessageSkipped() {
        this->ClearSymbols();
        this->AddSymbol("symbol1");

        AstsTLSFONDItemInfo *item1 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "111111", 1);
        item1->RptSeq = 1;

        this->m_table->ProcessIncremental(item1, 0, item1->TradingSessionIDUint);

        AstsTLSFONDItemInfo *item2 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "222222", 4);
        item2->RptSeq = 4;

        if(this->m_table->ProcessIncremental(item2, 0, item2->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item4 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "444444", 6);
        item4->RptSeq = 6;

        if(this->m_table->ProcessIncremental(item4, 0, item4->TradingSessionIDUint))
            throw;

        AstsTLSFONDItemInfo *item5 = this->m_helper->CreateTLRFondItemInfo("symbol1", "ses1", 8, 1, 8, 1, MDUpdateAction::mduaAdd,
                                                                           MDEntryType::mdetBuyQuote, "555555", 3);
        item5->RptSeq = 3;

        AstsTLSFONDInfo *info = this->m_helper->CreateTLSFondInfo("symbol1", "ses1");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        info->RptSeq = 3;

        TradeInfo<AstsTLSFONDItemInfo> *tb = this->m_table->GetItem("symbol1", "ses1");

        this->m_table->ObtainSnapshotItem(info);
        this->m_table->StartProcessSnapshot();
        if(tb != this->m_table->SnapshotItem())
            throw;
        if(tb->Trades()->Count() != 0)
            throw;

        this->m_table->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->Trades()->Count() != 1)
            throw;
        if(tb->RptSeq() == 3)
            throw;
        if(this->m_table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 4)
            throw;
        this->m_table->ObtainSnapshotItem(info);
        if(this->m_table->EndProcessSnapshot())
            throw;
    }

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay, bool testSnapshotPackets) {
        this->m_helper->SendMessages(fci, fcs, inc, snap, delay);
        if(testSnapshotPackets)
            this->TestSnapshotPacketsCleared();
    }

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay) {
        SendMessages(fci, fcs, inc, snap, delay, true);
    }

    void SendMessages(FeedConnection *c, TestTemplateInfo **items, int count) {
        this->m_helper->SendMessages(c, items, count);
    }

    void TestConnection_EmptyTest() {
        this->Clear();

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedTemplateId::fcmHeartBeat, 3)}, 3);

    }

    void TestConnection_TestCorrectIncMessages() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 3, 3, 1, 3, 1),
                                     }, 1),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "444444", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 3);


        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(incFond->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 4)
            throw;
    }

    /*
     * Incremental message num 2 is lost. This means that for item s1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * */
    void TestConnection_TestIncMessagesLost_AndWhenAppeared() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        TradeInfo<AstsTLSFONDItemInfo> *item = incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(item->Trades()->Count() != 2)
            throw;
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 1) // cell for rptseq 3 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(((AstsTLSFONDItemInfo*)(item->EntriesQueue()->Entries()[1]))->RptSeq != 4)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "444444", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(incFond->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->Trades()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        TradeInfo<AstsTLSFONDItemInfo> *item = incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(item->Trades()->Count() != 2)
            throw;
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(((AstsTLSFONDItemInfo*)(item->EntriesQueue()->Entries()[2]))->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "444444", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(incFond->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->Trades()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue() != 0) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        TradeInfo<AstsTLSFONDItemInfo> *item = incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(item->Trades()->Count() != 2)
            throw;
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(((AstsTLSFONDItemInfo*)(item->EntriesQueue()->Entries()[2]))->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(!incFond->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->Trades()->Count() != 3) // at least one message is applied
            throw;
        if(!item->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // should be reset
            throw;
        if(item->RptSeq() != 3) // now rpt seq should be 3
            throw;

        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->Trades()->Count() != 5) // all messages applied
            throw;
        if(item->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1() {
        this->Clear();
        this->AddSymbol("symbol1");

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        TradeInfo<AstsTLSFONDItemInfo> *item = incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(item->Trades()->Count() != 2)
            throw;
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(((AstsTLSFONDItemInfo*)(item->EntriesQueue()->Entries()[2]))->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(!incFond->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->Trades()->Count() != 2) // nothing encreased because first message skipped
            throw;
        if(!item->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(item->RptSeq() != 2) // because nothing was applied
            throw;

        SendMessages(incFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "333333", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(incFond->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->Trades()->Count() != 5) // applied two messages
            throw;
        if(item->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestIncMessageLost_AndWaitTimerElapsed() {
        this->Clear();
        this->AddSymbol("symbol1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(incFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "111111", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "222222", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "ses1", "555555", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        TradeInfo<AstsTLSFONDItemInfo> *item = incFond->TradeFond()->GetItem("symbol1", "ses1");
        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMicrosecondsFast() < incFond->WaitLostIncrementalMessageMaxTimeMcs()) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        }
        if(!incFond->ListenIncremental_Core())
            throw;
        //entering snapshot mode
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        // timer should be stopped
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_startMsgSeqNum != -1)
            throw;
        if(snapFond->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnection_TestSnapshotNoMessagesAtAll() {
        this->Clear();

        incFond->StartListenSnapshot();
        if(!snapFond->m_waitTimer->Active()) // start wait timer immediately
            throw;

        snapFond->ListenSnapshot(); // activate timer 2 when first time no messages recv
        //no messages
        while(snapFond->m_waitTimer->ElapsedMicrosecondsFast(2) <= snapFond->WaitAnyPacketMaxTimeMcs - 50000) {
            if(!snapFond->m_waitTimer->Active())
                throw;
            if(!snapFond->ListenSnapshot())
                throw; // nothing should be happens
            if(!snapFond->m_waitTimer->Active(2))
                throw;
            if(snapFond->m_endMsgSeqNum != -1)
                throw;
            if(snapFond->m_startMsgSeqNum != -1)
                throw;
        }
        while(snapFond->m_waitTimer->ElapsedMicrosecondsFast(2) <= snapFond->WaitAnyPacketMaxTimeMcs) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
            // just wait
        }
        if(!snapFond->m_waitTimer->Active(2))
            throw;

        if(!snapFond->ListenSnapshot()) // reconnect
            throw;
        if(snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsConnect)
            throw;
        if(snapFond->m_nextState != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_waitTimer->Active(2))
            throw;

        // now we should restart?
        if(!snapFond->Reconnect_Atom())
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_startMsgSeqNum != -1)
            throw;
        if(snapFond->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnection_OneMessageReceived() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();
        if(!snapFond->m_waitTimer->Active())
            throw;
        //no messages first half time
        while(snapFond->m_waitTimer->ElapsedMicrosecondsFast() < snapFond->WaitSnapshotMaxTimeMcs() / 2) {
            if(!snapFond->m_waitTimer->Active())
                throw;
            if(!snapFond->ListenSnapshot())
                throw; // nothing should be happens
            if(snapFond->m_endMsgSeqNum != -1)
                throw;
            if(snapFond->m_startMsgSeqNum != -1)
                throw;
        }

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 2, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        //timer should be active but reset
        if(snapFond->m_waitTimer->ElapsedMicrosecondsFast() >= snapFond->WaitAnyPacketMaxTimeMcs / 2)
            throw;

        if(!snapFond->ListenSnapshot())
            throw; // nothing should be happens
    }

    void TestConnection_RouteFirstReceived_Empty() {

        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 2, "symbol1", "ses1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(snapFond->m_snapshotRouteFirst != 2)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(!snapFond->ListenSnapshot_Core())
            throw;

        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;

        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(snapFond->m_snapshotRouteFirst != 2)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
    }

    void TestConnection_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
        this->AddSymbol("symbol1");

        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 1, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 1)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 2, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 3, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 4, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 2);

        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 5)
            throw;
        if(snapFond->m_endMsgSeqNum != 4)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 5, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 6, "symbol1", "ses1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 2);

        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 7)
            throw;
        if(snapFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_snapshotRouteFirst != 6)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(!snapFond->ListenSnapshot_Core())
            throw;

        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 7)
            throw;
        if(snapFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_snapshotRouteFirst != 6)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
    }

    void TestConnection_LastFragmentReceivedBeforeRouteFirst() {
        this->Clear();
        this->AddSymbol("symbol1");

        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 1, "symbol1", "ses1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 1)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
    }

    void TestConnection_SnapshotSomeMessagesNotReceived() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 1, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapFond->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 3, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapFond->ListenSnapshot_Core();

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        if(!snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        snapFond->m_waitTimer->Stop(); // reset timer 0 to avoid simulate situation when no packet received
        // now wait some time and after that we have to skip lost message to get other snapshot
        while(!snapFond->m_waitTimer->IsTimeOutFast(1, snapFond->WaitSnapshotMaxTimeMcs())) {
            snapFond->ListenSnapshot_Core();
            if(!snapFond->m_waitTimer->Active(1))
                break;
        }

        snapFond->ListenSnapshot_Core();
        if(snapFond->m_startMsgSeqNum != 4)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
    }

    void TestConnection_SnapshotSomeMessagesReceivedLater() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 1, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        snapFond->ListenSnapshot_Core();

        // message seq 2 lost
        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 3, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
            throw;

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!snapFond->m_waitTimer->Active())
            throw;
        if(!snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        // wait some time and then receive lost packet
        while(!snapFond->m_waitTimer->IsTimeOutFast(1, snapFond->WaitSnapshotMaxTimeMcs() / 2)) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
            snapFond->m_waitTimer->StartFast(); // reset timer 0 to avoid simulate situation when no packet received
            if(!snapFond->ListenSnapshot_Core())
                throw;
        }

        if(!snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 2, "symbol1", "ses1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(!snapFond->ListenSnapshot_Core())
            throw;
        if(snapFond->m_startMsgSeqNum != 4)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;
    }

    void TestConnection_StopTimersAfterReconnect() {
        this->Clear();
        incFond->StartListenSnapshot();

        // manually activate timer 1
        snapFond->m_waitTimer->Activate(1);
        snapFond->ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
        snapFond->DoWorkAtomSnapshot();

        if(!snapFond->m_waitTimer->Active())
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
    }

    void TestConnection_TestSnapshotCollect() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        SendMessages(snapFond, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 2, "symbol1", "ses1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4)
        }, 1);

        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;

        snapFond->ListenSnapshot_Core();
        //snapshot received and should be applied
        TradeInfo<AstsTLSFONDItemInfo> *tableItem = incFond->TradeFond()->GetItem("symbol1", "ses1");

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(incFond->TradeFond()->UsedItemCount() != 1)
            throw;

        if(tableItem->Trades()->Count() != 2)
            throw;
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
    }

    void TestConnection_TestSnapshotMessageLostAndTimeExpired() {
        this->Clear();
        this->AddSymbol("symbol1");
        incFond->StartListenSnapshot();

        snapFond->WaitSnapshotMaxTimeMcs(100);
        if(!snapFond->m_waitTimer->Active())
            throw;

        SendMessages(snapFond, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 2, "symbol1", "ses1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 4, "symbol1", "ses1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("222222"),
                                     }, 2, 6),
        }, 2);

        if(snapFond->Packet(3)->m_address != 0)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 4)
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;

        snapFond->ListenSnapshot_Core();
        if(snapFond->m_waitTimer->Active(1))
            throw;

        snapFond->ListenSnapshot_Core();

        if(!snapFond->m_waitTimer->Active(1))
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_snapshotRouteFirst != 2)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;

        snapFond->ListenSnapshot_Core();
        if(!snapFond->m_waitTimer->Active(1))
            throw;
        while(snapFond->m_waitTimer->ElapsedMicrosecondsFast(1) <= snapFond->WaitSnapshotMaxTimeMcs())
            snapFond->ListenSnapshot_Core();

        snapFond->ListenSnapshot_Core();
        // reset
        if(snapFond->m_snapshotRouteFirst != -1)
            throw;
        if(snapFond->m_snapshotLastFragment != -1)
            throw;
        if(snapFond->m_waitTimer->Active(1))
            throw;
    }
    /*
     * Snapshot received for only one item, this means that snapshot connection should not be stopped
     * */
    void TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->TradeFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 1),
                                             new TestTemplateItemInfo("symbol2", "111111", 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 4),
                                             new TestTemplateItemInfo("symbol2", "111111", 4),
                                     }, 2)
        }, 2);

        if(!incFond->ListenIncremental_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        if(incFond->TradeFond()->UsedItemCount() != 2)
            throw;

        if(!incFond->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(incFond->m_waitTimer->ElapsedMicrosecondsFast() < incFond->WaitLostIncrementalMessageMaxTimeMcs()) {
            Stopwatch::Default->GetElapsedMicrosecondsGlobal();
        }

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(snapFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcFullRefresh_TLS_FOND, 2, "symbol1", "ses1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("111111"),
                                             new TestTemplateItemInfo("111111"),
                                     }, 2, 4)
        }, 1);
        if(!snapFond->ListenSnapshot_Core())
            throw;

        this->TestTableItemsAllocator(incFond->TradeFond());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        TradeInfo<AstsTLSFONDItemInfo> *item1 = incFond->TradeFond()->GetItem("symbol1", "ses1");
        TradeInfo<AstsTLSFONDItemInfo> *item2 = incFond->TradeFond()->GetItem("symbol2", "ses1");
        if(item1->HasEntries())
            throw;
        if(!item2->HasEntries())
            throw;

        for(int i = 0; i < item1->Trades()->Count(); i++)
            if(item1->Trades()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < item2->Trades()->Count(); i++)
            if(item2->Trades()->Item(i)->Allocator == 0)
                throw;
    }

    void TestConnection_SkipHearthBeatMessages_Incremental() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->incFond->StartListenSnapshot();
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol1 e2, wait_snap, hbeat, hbeat, hbeat",
                     "                                                  hbeat, hbeat, hbeat",
                     30);
        if(incFond->Packet(4)->m_address == 0 || incFond->Packet(5)->m_address == 0 || incFond->Packet(6)->m_address == 0)
            throw;
        if(!incFond->Packet(4)->m_processed || !incFond->Packet(5)->m_processed || !incFond->Packet(6)->m_processed)
            throw;
        // do not check Snapshot Feed Connection because it immediately cleares packets after processing,
        // because it can receive packet with the same message number again and again (cycle)
        //if(snapFond->Packet(1)->m_address == 0 || snapFond->Packet(2)->m_address == 0 || snapFond->Packet(3)->m_address == 0)
        //    throw;
        //if(!snapFond->Packet(1)->m_processed || !snapFond->Packet(2)->m_processed || !snapFond->Packet(3)->m_processed)
        //    throw;
    }

    void TestConnection_AllSymbolsAreOk() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol1 e2, tlr entry symbol1 e3, tlr entry symbol2 e1, tlr entry symbol2 e2",
                     "",
                     30);
        if(incFond->TradeFond()->UsedItemCount() != 2)
            throw;
        if(incFond->TradeFond()->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->TradeFond()->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_NotAllSymbolsAreOk() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol1 e2, tlr entry symbol1 e3, tlr entry symbol2 e1, tlr entry symbol2 e2",
                     "",
                     30);
        if(incFond->TradeFond()->UsedItemCount() != 2)
            throw;
        if(!incFond->TradeFond()->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->TradeFond()->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_AllSymbolsAreOkButOneMessageLost() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        this->AddSymbol("symbol3");

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e2, tlr entry symbol1 e3, tlr entry symbol2 e1, tlr entry symbol2 e2",
                     "",
                     30);

        if(incFond->TradeFond()->UsedItemCount() != 3)
            throw;
        if(incFond->TradeFond()->Symbol(0)->Session(0)->HasEntries())
            throw;
        if(incFond->TradeFond()->Symbol(1)->Session(0)->HasEntries())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol3");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1",
                     "",
                     30);
        if(incFond->HasPotentiallyLostPackets())
            throw;
        if(incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2() {
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol3");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1, hbeat",
                     "",
                     30);
        if(!incFond->HasPotentiallyLostPackets())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(!incFond->m_waitTimer->Active())
            throw;
        if(incFond->m_waitTimer->IsTimeOutFast(incFond->m_waitLostIncrementalMessageMaxTimeMcs))
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1, hbeat, hbeat",
                     "",
                     30);
        if(incFond->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incFond->HasPotentiallyLostPackets())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->TradeFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->TradeFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // snapshot should not be stopped
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(incFond->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!incFond->HasPotentiallyLostPackets())
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->m_waitTimer->Active())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->TradeFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->TradeFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1() {
//        this->Clear();
//
//        this->AddSymbol("s1", "ses1");
//        this->AddSymbol("symbol3", "ses1");
//
//        if(snapFond->State() != FeedConnectionState::fcsSuspend)
//            throw;
//        SendMessages(incFond, snapFond,
//                     "tlr entry s1 e1, lost tlr entry symbol3 e1, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat",
//                     "",
//                     30);
//        if(incFond->SymbolsToRecvSnapshotCount() != 2)
//            throw;
//        if(!incFond->HasPotentiallyLostPackets())
//            throw;
//        if(!incFond->ShouldRestoreIncrementalMessages())
//            throw;
//        if(incFond->m_waitTimer->Active())
//            throw;
//        if(snapFond->State() != FeedConnectionState::fcsConnect)
//            throw;
//        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 2)
//            throw;
//        if(incFond->TradeFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
//            throw;
//        if(incFond->TradeFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
//            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1, wait_snap",
                     "",
                     30);
        if(incFond->m_waitTimer->Active())
            throw;
        if(incFond->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incFond->ShouldRestoreIncrementalMessages())
            throw;
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(incFond->TradeFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->TradeFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // we should receive at least one snapshot for all items
    // we received snapshot for one item
    // and we did not receive incremental messages for symbol 2 after snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1, wait_snap, tlr entry symbol1 e3,    hbeat,                              hbeat",
                     "                                                            tls symbol3 begin rpt 1, tls symbol3 rpt 1 entry symbol3 e1, tls symbol3 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->CanStopListeningSnapshot()) // because we did not receive all snapshots for all m_symbols
            throw;
        if(snapFond->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->UsedItemCount() != 3)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 2)
            throw;
        if(incFond->TradeFond()->GetItem("symbol2", "ses1")->Trades()->Count() != 0)
            throw;
        if(incFond->TradeFond()->GetItem("symbol3", "ses1")->Trades()->Count() != 1)
            throw;
        if(incFond->m_startMsgSeqNum != 2)
            throw;
        if(incFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_startMsgSeqNum != 4)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(incFond, snapFond,
                     "lost tlr entry symbol1 e1, lost hbeat, wait_snap",
                     "tls symbol1 begin rpt 1, tls symbol1 rpt 1 entry symbol1 e1, tls symbol1 rpt 1 end",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->UsedItemCount() != 1)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 1)
            throw;
        if(incFond->m_startMsgSeqNum != 4)
            throw;
        if(incFond->m_endMsgSeqNum != 3)
            throw;
        if(snapFond->m_startMsgSeqNum != 4)
            throw;
        if(snapFond->m_endMsgSeqNum != 3)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1, wait_snap, tlr entry symbol1 e3,                         hbeat,                                        hbeat",
                     "                                                            tls symbol3 begin rpt 1 end entry symbol3 e1, tls symbol1 begin rpt 2 end entry symbol1 e1, hbeat, tls symbol2 begin rpt 2 end entry symbol2 e1",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->RptSeq() != 2)
            throw;
        if(incFond->TradeFond()->GetItem("symbol3", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->TradeFond()->GetItem("symbol2", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->UsedItemCount() != 3)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->TradeFond()->GetItem("symbol2", "ses1")->Trades()->Count() != 1)
            throw;
        if(incFond->TradeFond()->GetItem("symbol3", "ses1")->Trades()->Count() != 1)
            throw;
        if(incFond->m_startMsgSeqNum != 7)
            throw;
        if(incFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_startMsgSeqNum != 5)
            throw;
        if(snapFond->m_endMsgSeqNum != 4)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    // almost the same as TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2
    // however there is no heartbeat msg in snap channel so symbol 2 receives snapshot earlier than his second message so it buyquotes count == 1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        this->AddSymbol("symbol3", "ses1");

        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->UsedItemCount() != 3)
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1, wait_snap, tlr entry symbol1 e3,                              tlr entry symbol2 e1,                    tlr entry symbol2 e2",
                     "                                                       tls symbol3 begin rpt 1 end entry symbol3 e1, tls symbol1 begin rpt 2 end entry symbol1 e1, tls symbol2 begin rpt 2 end entry symbol2 e1 skip_if_suspend",
                     30);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->RptSeq() != 2)
            throw;
        if(incFond->TradeFond()->GetItem("symbol3", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->TradeFond()->GetItem("symbol2", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->UsedItemCount() != 3)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(incFond->TradeFond()->GetItem("symbol2", "ses1")->Trades()->Count() != 2)
            throw;
        if(incFond->TradeFond()->GetItem("symbol3", "ses1")->Trades()->Count() != 1)
            throw;
        if(incFond->m_startMsgSeqNum != 7)
            throw;
        if(incFond->m_endMsgSeqNum != 6)
            throw;
        if(snapFond->m_startMsgSeqNum != 3)
            throw;
        if(snapFond->m_endMsgSeqNum != 2)
            throw;
    }
    // we receive snapshot which rpt seq is less than incremental actual rpt seq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");

        if(!incFond->m_waitTimer->Active())
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol1 e2, tlr entry symbol1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          tls symbol1 begin rpt 1 entry symbol1 e1 end",
                     50);
        if(incFond->HasQueueEntries())
            throw;
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->RptSeq() != 3)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 3)
            throw;
        if(snapFond->m_startMsgSeqNum != 2)
            throw;
        if(snapFond->m_endMsgSeqNum != 1)
            throw;
        if(snapFond->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(snapFond->m_startMsgSeqNum != 2) // detect that
            throw;
    }
    // we received snapshot for item but item has 2 gaps and snapshot is partially actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol1 e2, lost tlr entry symbol1 e3, tlr entry symbol1 e4, lost tlr entry symbol1 e5, tlr entry symbol1 e6, wait_snap, ",
                     "                                                                                                                           tls symbol1 begin rpt 4 entry symbol1 e4 end",
                     30);
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!incFond->TradeFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->RptSeq() != 4)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol1 e2, lost tlr entry symbol1 e3, tlr entry symbol1 e4, lost tlr entry symbol1 e5, tlr entry symbol1 e6, wait_snap, ",
                     "                                                                                                                           tls symbol1 begin rpt 5 entry symbol1 e5 end",
                     30);
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->RptSeq() != 6)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol1 e2, lost tlr entry symbol1 e3, tlr entry symbol1 e4, lost tlr entry symbol1 e5, tlr entry symbol1 e6, wait_snap, ",
                     "                                                                                                                           tls symbol1 begin rpt 6 entry symbol1 e6 end",
                     30);
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(incFond->HasQueueEntries())
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->RptSeq() != 6)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->Trades()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        incFond->WaitLostIncrementalMessageMaxTimeMcs(500000);
        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol2 e1, lost tlr entry symbol1 e2, wait_snap, hbeat                               lost tlr entry symbol1 e3,               tlr entry symbol1 e4",
                     "                                                                   tls symbol1 begin rpt 2 entry symbol1 e2 end, tls symbol2 begin rpt 1 entry symbol2 e1 end, hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->RptSeq() != 2)
            throw;
        if(!incFond->TradeFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->EntriesQueue()->StartRptSeq() != 3)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(incFond->TradeFond()->GetItem("symbol2", "ses1")->RptSeq() != 1)
            throw;
        if(incFond->TradeFond()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        if(incFond->TradeFond()->Symbol(0)->Session(0)->ShouldProcessSnapshot())
            throw;
        if(incFond->TradeFond()->Symbol(1)->Session(0)->ShouldProcessSnapshot())
            throw;
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol2 e1, lost tlr entry symbol1 e2, wait_snap, hbeat                               lost tlr entry symbol1 e3,               tlr entry symbol1 e4, hbeat ",
                     "                                                                   tls symbol1 begin rpt 2 entry symbol1 e2 end, tls symbol2 begin rpt 1 entry symbol2 e1 end, hbeat          , tls symbol1 begin rpt 3 entry symbol1 e3 end",
                     30);
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->RptSeq() != 4)
            throw;
        if(incFond->TradeFond()->GetItem("symbol1", "ses1")->HasEntries())
            throw;
        if(incFond->TradeFond()->QueueEntriesCount() != 0)
            throw;
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        incFond->Start();

        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol2 e1, lost tlr entry symbol1 e2, wait_snap, tlr entry symbol2 e2, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(incFond->TradeFond()->GetItem("symbol2", "ses1")->ShouldProcessSnapshot())
            throw;
    }
    // we have received twice the same snapshot (rpt seq num = the same value) which means that item did not receive incremental message so item state is actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7() {
        // do nothing. lets consider that after receiving snapshot item will be in actual state if there is no queue entries
    }
    // we can receive null snapshot i.e. snapshot with LastMsgSeqNumProcessed = 0 RptSeq = 0
    // this means that item has NO DATA
    // so just clear queue entries and decrease session to recv snapshot value
    void TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived() {
        this->Clear();

        /*
        unsigned char *msg = new unsigned char[52] {
                0x65, 0x23, 0x00, 0x00, 0xe0, 0x12, 0xec, 0x46, 0xe5, 0x23,
                0x68, 0x08, 0x12, 0x7f, 0x4c, 0x74, 0xc0, 0x81, 0x80, 0x00,
                0xe5, 0x52, 0x50, 0x4d, 0xcf, 0x52, 0x55, 0x30, 0x30, 0x30,
                0x41, 0x30, 0x4a, 0x54, 0x5a, 0x46, 0xb1, 0x82, 0x82, 0x93,
                0x80, 0x81, 0xca, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                0x80, 0x80
        };
        incFond->m_fastProtocolManager->SetNewBuffer(msg, 52);
        incFond->m_fastProtocolManager->ReadMsgSeqNumber();
        incFond->m_fastProtocolManager->Decode();
        incFond->m_fastProtocolManager->Print();
        */

        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        if(!incFond->m_waitTimer->Active())
            throw;
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol1 e2, tlr entry symbol1 e2, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     tls symbol1 begin rpt 0 lastmsg 0 entry symbol1 e1 end",
                     30);
        if(incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
    }
    void TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate() {

    }
    void TestConnection_EnterSnapshotMode() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        incFond->TradeFond()->EnterSnapshotMode();
        if(!incFond->TradeFond()->GetItem("symbol1", "ses1")->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnection_ClearSnapshotMessages_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol1 e2, wait_snap, hbeat",
                     "                                                  tls symbol1 begin rpt 2 entry symbol1 e2 end",
                     30);
        if(snapFond->Packet(1)->m_address != 0)
            throw;
        if(snapFond->Packet(1)->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnection_ClearSnapshotMessages_2() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol1 e2, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, tls symbol1 begin rpt 2 entry symbol1 e2 end",
                     30);
        if(snapFond->Packet(1)->m_address != 0 ||
           snapFond->Packet(2)->m_address != 0 ||
           snapFond->Packet(3)->m_address != 0)
            throw;
        if(snapFond->Packet(1)->m_processed != false ||
           snapFond->Packet(2)->m_processed != false ||
           snapFond->Packet(3)->m_processed != false)
            throw;
    }
    // clear if skip lost packets in snapshot
    void TestConnection_ClearSnapshotMessages_3() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        snapFond->WaitSnapshotMaxTimeMcs(50000);
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol1 e2, wait_snap, hbeat",
                     "                                                  tls symbol1 begin rpt 2 entry symbol1 e2, lost tls symbol1 rpt 2 entry symbol1 e2, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(snapFond->m_packets[i]->m_address != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnection_ClearSnapshotMessages_4() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        snapFond->WaitSnapshotMaxTimeMcs(50000);
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol1 e2, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  tls symbol1 begin rpt 2 entry symbol1 e2, lost tls symbol1 rpt 2 entry symbol1 e2, hbeat, hbeat, hbeat, hbeat, hbeat, tls symbol1 rpt 2 entry symbol1 e2, tls symbol1 begin rpt 2 entry symbol1 e2 end",
                     30);
        if(incFond->TradeFond()->UsedItemCount() != 1)
            throw;
        if(snapFond->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!incFond->CanStopListeningSnapshot())
            throw;
        TestSnapshotPacketsCleared();
    }
    void TestSnapshotPacketsCleared() {
        for(int i = 1; i < 100; i++) {
            if(snapFond->m_packets[i]->m_address != 0 || snapFond->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // messages should be clear in snapshot connection because the are repeat
    void TestConnection_ClearSnapshotMessages() {
        printf("TLR FOND TestConnection_ClearSnapshotMessages_1\n");
        TestConnection_ClearSnapshotMessages_1();
        printf("TLR FOND TestConnection_ClearSnapshotMessages_2\n");
        TestConnection_ClearSnapshotMessages_2();
        printf("TLR FOND TestConnection_ClearSnapshotMessages_3\n");
        TestConnection_ClearSnapshotMessages_3();
        printf("TLR FOND TestConnection_ClearSnapshotMessages_4\n");
        TestConnection_ClearSnapshotMessages_4();
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot() {
        printf("TLR FOND TestConnection_EnterSnapshotMode\n");
        TestConnection_EnterSnapshotMode();
        printf("TLR FOND TestConnection_ClearSnapshotMessages\n");
        TestConnection_ClearSnapshotMessages();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_1();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_4();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7();
    }

    void TestConnection_Clear_AfterIncremental() {
        this->TestTableItemsAllocator(incFond->TradeFond());
        this->Clear();
        this->AddSymbol("symbol1");
        this->AddSymbol("symbol2");
        incFond->StartListenSnapshot();

        this->TestTableItemsAllocator(incFond->TradeFond());

        SendMessages(incFond, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 1),
                                             new TestTemplateItemInfo("symbol2", "111111", 1),
                                     }, 2),
                new TestTemplateInfo(FeedTemplateId::fmcIncrementalRefresh_TLR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "111111", 4),
                                             new TestTemplateItemInfo("symbol2", "111111", 4),
                                     }, 2)
        }, 2);

        if(!incFond->ListenIncremental_Core())
            throw;

        MDEntryQueue *que1 = incFond->TradeFond()->Symbol(0)->Session(0)->EntriesQueue();
        MDEntryQueue *que2 = incFond->TradeFond()->Symbol(1)->Session(0)->EntriesQueue();

        this->TestTableItemsAllocator(incFond->TradeFond());

        incFond->TradeFond()->Clear();
    }

    void TestConnection() {
        printf("TLR FOND TestConnection_AllSymbolsAreOk\n");
        TestConnection_AllSymbolsAreOk();
        printf("TLR FOND TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("TLR FOND TestConnection_AllSymbolsAreOkButOneMessageLost\n");
        TestConnection_AllSymbolsAreOkButOneMessageLost();
        printf("TLR FOND TestConnection_SkipHearthBeatMessages_Incremental\n");
        TestConnection_SkipHearthBeatMessages_Incremental();
        printf("TLR FOND TestConnection_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot();
        printf("TLR FOND TestConnection_NotAllSymbolsAreOk\n");
        TestConnection_NotAllSymbolsAreOk();
        printf("TLR FOND TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("TLR FOND TestConnection_StopTimersAfterReconnect\n");
        TestConnection_StopTimersAfterReconnect();
        printf("TLR FOND TestConnection_SnapshotSomeMessagesReceivedLater\n");
        TestConnection_SnapshotSomeMessagesReceivedLater();
        printf("TLR FOND TestConnection_SnapshotSomeMessagesNotReceived\n");
        TestConnection_SnapshotSomeMessagesNotReceived();
        printf("TLR FOND TestConnection_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnection_LastFragmentReceivedBeforeRouteFirst();
        printf("TLR FOND TestConnection_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnection_RouteFirstReceived_AfterSomeDummyMessages();
        printf("TLR FOND TestConnection_RouteFirstReceived_Empty\n");
        TestConnection_RouteFirstReceived_Empty();
        printf("TLR FOND TestConnection_TestSnapshotNoMessagesAtAll\n");
        TestConnection_TestSnapshotNoMessagesAtAll();
        printf("TLR FOND TestConnection_OneMessageReceived\n");
        TestConnection_OneMessageReceived();
        printf("TLR FOND TestConnection_Clear_AfterIncremental\n");
        TestConnection_Clear_AfterIncremental();
        printf("TLR FOND TestConnection_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnection_TestIncMessageLost_AndWaitTimerElapsed();
        printf("TLR FOND TestConnection_TestSnapshotCollect\n");
        TestConnection_TestSnapshotCollect();
        printf("TLR FOND TestConnection_TestSnapshotNotCollect\n");
        TestConnection_TestSnapshotMessageLostAndTimeExpired();
        printf("TLR FOND TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("TLR FOND TestConnection_EmptyTest\n");
        TestConnection_EmptyTest();
        printf("TLR FOND TestConnection_TestCorrectIncMessages\n");
        TestConnection_TestCorrectIncMessages();
        printf("TLR FOND TestConnection_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnection_TestIncMessagesLost_AndWhenAppeared();
        printf("TLR FOND TestConnection_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnection_TestInc2MessagesLost_AppearedThen2Messages();
        printf("TLR FOND TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("TLR FOND TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1();
    }

    void TestTradeTableItem() {
        printf("TLR FOND TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("TLR FOND TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("TLR FOND TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("TLR FOND TestTable_Default\n");
        TestTable_Default();
        printf("TLR FOND TestTable_AfterClear\n");
        TestTable_AfterClear();
        printf("TLR FOND TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("TLR FOND TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("TLR FOND TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("TLR FOND Test_2UsedItemsAfter2IncrementalMessages\n");
        Test_2UsedItemsAfter2IncrementalMessages();
        printf("TLR FOND TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("TLR FOND TestTable_CorrectApplySnapshot_2\n");
        TestTable_CorrectApplySnapshot_2();
        printf("TLR FOND TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("TLR FOND TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
        TestTable_IncorrectApplySnapshot_WhenMessageSkipped();
    }

    void TestStringIdComparer() {
        char buf[128];
        for(int i = 1; i < 128; i++) {
            buf[i] = (char)(0x30 + i);
        }
        for(int i = 1; i < 128; i++) {
            if(!StringIdComparer::Equal(buf, i, buf, i))
                throw;
        }
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "tlr entry symbol1 e1",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_2() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->incFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "tlr entry symbol1 e1, tlr entry symbol1 e2",
                           "",
                           30);

        int newCount = this->incFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
        this->incFond->TradeFond()->Clear();
        newCount = this->incFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_3() {
        // there is no delete update action in trades
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_4() {
        AstsTLSFONDItemInfo *info = this->m_helper->CreateTLSFondItemInfo(1, 1, 1, 1, MDEntryType::mdetBuyQuote, "111111");
        if(info->Allocator->Count() != 1)
            throw;
        //info->Used = false;
        //info->ReleaseUnused();
        //if(info->Allocator->Count() != 0)
        //    throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Inc_5() {
        // there is no change action in trades incremental
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "tlr entry symbol1 e1, lost tlr entry symbol1 e2, wait_snap, hbeat",
                           "                                                  tls begin symbol1 entry symbol1 e2 rpt 2 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount + 1)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_1() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "tlr entry symbol1 e1, lost tlr entry symbol1 e2 entry symbol1 e3, wait_snap",
                           "                                                            ",
                           30);
        if(this->incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(!this->incFond->HasPotentiallyLostPackets())
            throw;
        if(this->incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(this->snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_2() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "tlr entry symbol1 e1, lost tlr entry symbol1 e2 entry symbol1 e3, wait_snap, hbeat",
                           "                                                                   ",
                           30);
        if(this->incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(!this->incFond->HasPotentiallyLostPackets())
            throw;
        if(this->incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(this->snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_3() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "tlr entry symbol1 e1, lost tlr entry symbol1 e2 entry symbol1 e3, wait_snap, hbeat",
                           "                                                              tls begin symbol1 entry symbol1 e2 rpt 2",
                           30, false);
        if(this->incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(!this->incFond->HasPotentiallyLostPackets())
            throw;
        if(this->incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(this->snapFond->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_4() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "tlr entry symbol1 e1, lost tlr entry symbol1 e2 entry symbol1 e3, wait_snap, hbeat,                        hbeat",
                           "                                                              tls begin symbol1 entry symbol1 e2 rpt 2",
                           30, false);
        if(this->incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(!this->incFond->HasPotentiallyLostPackets())
            throw;
        if(this->incFond->TradeFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(this->snapFond->State() == FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_5() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessages(this->incFond, this->snapFond,
                           "tlr entry symbol1 e1, lost tlr entry symbol1 e2 entry symbol1 e3, wait_snap, hbeat,                          hbeat",
                           "                                                              tls begin symbol1 entry symbol1 e2 rpt 2, tls symbol1 entry symbol1 e3 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount + 2)
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_2() {
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_1();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_2();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_3();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_4();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2_5();
    }

    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_3() {
        // there is no UpdateAction in snap messages so we don't have to check these cases
        /*this->Clear();

        this->AddSymbol("s1", "ses1");
        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        this->SendMessagesIdf(this->incFond, this->snapFond,
                           "tlr entry s1 e1, tlr entry s1 e2, lost tlr entry s1 e4 entry s1 e4, wait_snap, hbeat",
                           "                                                   tls begin s1 entry s1 e1 rpt 2, tls s1 entry s1 e2, tls s1 entry s1 e3, tls s1 entry del s1 e2 end",
                           30);

        int newCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount + 3)
            throw;*/
    }

    // check in case CheckProcessIfSessionInActualState returns true
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_4() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");
        this->AddSymbol("symbol2", "ses1");
        this->AddSymbol("symbol3", "ses1");

        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol3 e1, wait_snap, tlr entry symbol1 e3,                              hbeat,                              hbeat",
                     "                                                       tls symbol3 begin rpt 1 end entry symbol3 e1, tls symbol1 begin rpt 2 end entry symbol1 e1, hbeat, tls symbol2 begin rpt 2 end entry symbol2 e1",
                     30);
        int newCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount + 4) // was 2 and it seems that it is wrong
            throw;
    }
    // check in case CheckProcessNullSnapshot
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_5() {
        this->Clear();
        this->AddSymbol("symbol1", "ses1");
        incFond->Start();

        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, lost tlr entry symbol1 e2, tlr entry symbol1 e2, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     tls symbol1 begin rpt 0 lastmsg 0 entry symbol1 e1 end",
                     30);
        int newCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount)
            throw;
    }

    // check in case ShouldProcessSnapshot
    void TestInfoAndItemInfoUsageAndAllocationFond_Snap_6() {
        this->Clear();

        this->AddSymbol("symbol1", "ses1");

        int prevCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        SendMessages(incFond, snapFond,
                     "tlr entry symbol1 e1, tlr entry symbol1 e2, tlr entry symbol1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          tls symbol1 begin rpt 1 entry symbol1 e1 end",
                     50);
        int newCount = this->snapFond->m_fastProtocolManager->m_astsTLSFONDItems->Count();
        if(newCount != prevCount + 3) // should not process snapshot
            throw;
    }

    void TestInfoAndItemInfoUsageAndAllocationFond() {
        this->m_helper->SetFondMode();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_1();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_2();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_3();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_4();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Inc_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Inc_5();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_1\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_1();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_2\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_2();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_3\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_3();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_4\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_4();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_5\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_5();
        printf("TLR FOND TestInfoAndItemInfoUsageAndAllocationFond_Snap_6\n");
        TestInfoAndItemInfoUsageAndAllocationFond_Snap_6();
    }

    void Test() {
        TestDefaults();
        TestStringIdComparer();
        TestConnection();
        TestInfoAndItemInfoUsageAndAllocationFond();
        Test_TLR_FOND();
        TestTradeTableItem();
    }
};

#endif //TEST
#endif //HFT_ROBOT_TRADETESTER_H
