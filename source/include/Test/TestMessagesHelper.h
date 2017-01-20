//
// Created by root on 15.12.16.
//

#ifndef HFT_ROBOT_TESTMESSAGESHELPER_H
#define HFT_ROBOT_TESTMESSAGESHELPER_H

#include "Managers/WinSockManager.h"
#include "TestTemplateInfo.h"
#include "../FeedConnection.h"
#include <stdio.h>
#include <memory.h>

class SocketMessageInfo {
public:
    WinSockManager      *m_manager;
    bool                m_canRecv;
    unsigned char       m_buffer[512];
    int                 m_bufferLength;
};

class TestMessagesHelper {
public:
    static PointerList<SocketMessageInfo> *m_sockMessages;
    static bool SkipTimeOutCheck;

    char            **m_keys;
    int               m_keysCount;
private:

    const char *symbols[100];
    int rptSeq[100];
    int symbolsCount = 0;
    bool m_curr = false;

    int CalcMsgCount(const char *msg) {
        int len = strlen(msg);
        if(len == 0)
            return 0;
        int res = 0;
        for(int i = 0; i < len; i++) {
            if(msg[i] == ',')
                res++;
        }
        return res + 1;
    }

    int CalcWordLength(const char *msg, int startIndex) {
        int res = 0;
        for(int i = startIndex; msg[i] != ',' && msg[i] != '\0'; i++)
            res++;
        return res;
    }

    void TrimWord(const char *msg, int startIndex, int len, int *start, int *end) {
        *start = startIndex;
        *end = startIndex + len - 1;

        while(msg[*start] == ' ')
            (*start)++;
        while(msg[*end] == ' ')
            (*end)--;
        return ;
    }

    int SkipToNextWord(const char *msg, int start) {
        while(msg[start] == ' ')
            start++;
        return start;
    }

    void Split(const char *msg, int start, int end) {
        this->m_keys = new char*[100];
        this->m_keysCount = 0;
        for(int i = start; i <= end; i++) {
            if(msg[i] == ' ' || i == end) {
                if(i == end) i++;
                this->m_keys[this->m_keysCount] = new char[i - start + 1];
                memcpy(this->m_keys[this->m_keysCount], &msg[start], i - start);
                this->m_keys[this->m_keysCount][i-start] = '\0';
                if(i == end)
                    break;
                this->m_keysCount++;
                start = SkipToNextWord(msg, i);
                i = start - 1;
            }
        }
    }

    int KeyIndex(const char *key) {
        for(int i = 0; i < this->m_keysCount; i++) {
            if(StringIdComparer::Equal(this->m_keys[i], key))
                return i;
        }
        return -1;
    }

    int KeyIndex(const char *key, int startIndex) {
        for(int i = startIndex; i < this->m_keysCount; i++) {
            if(StringIdComparer::Equal(this->m_keys[i], key))
                return i;
        }
        return -1;
    }

    bool HasKey(const char *key) {
        return KeyIndex(key) != -1;
    }
    bool StartKey(const char *key) {
        return KeyIndex(key) == 0;
    }

    TestTemplateInfo *CreateTemplate() {
        TestTemplateInfo *info = new TestTemplateInfo();
        if(this->m_keysCount == 0)
            return info;

        info->m_msgSeqNo = 0;
        info->m_lost = HasKey("lost");
        info->m_skip = HasKey("skip_if_suspend");
        if(HasKey("msgSeqNo")) {
            info->m_msgSeqNo = atoi(this->m_keys[KeyIndex("msgSeqNo") + 1]);
        }
        if(HasKey("logout")) {
            info->m_templateId = FeedConnectionMessage::fmcLogout;
            return info;
        }
        else if(HasKey("logon")) {
            info->m_templateId = FeedConnectionMessage::fmcLogon;
            if(HasKey("sender"))
                info->m_senderId = this->m_keys[KeyIndex("sender") + 1];
            else
                info->m_senderId = 0;
            if(HasKey("pass"))
                info->m_pass = this->m_keys[KeyIndex("pass") + 1];
            else
                info->m_pass = 0;
            return info;
        }
        else if(HasKey("obr")) {
            info->m_templateId = FeedConnectionMessage::fmcIncrementalRefresh_Generic;
        }
        else if(HasKey("olr")) {
            info->m_templateId = this->m_curr? FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR:
                                 FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND;
        }
        else if(HasKey("tlr")) {
            info->m_templateId = this->m_curr? FeedConnectionMessage::fmcIncrementalRefresh_TLR_CURR:
                                 FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND;
        }
        else if(HasKey("obs")) {
            info->m_templateId = FeedConnectionMessage::fmcFullRefresh_Generic;
            int snapIndex = KeyIndex("obs");
            if(KeyIndex("begin") == snapIndex + 1)
                snapIndex++;
            info->m_symbol = this->m_keys[snapIndex + 1];
        }
        else if(HasKey("ols")) {
            info->m_templateId = this->m_curr? FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
                                 FeedConnectionMessage::fmcFullRefresh_OLS_FOND;
            int snapIndex = KeyIndex("ols");
            if(KeyIndex("begin") == snapIndex + 1)
                snapIndex++;
            info->m_symbol = this->m_keys[snapIndex + 1];
        }
        else if(HasKey("tls")) {
            info->m_templateId = this->m_curr ? FeedConnectionMessage::fmcFullRefresh_TLS_CURR :
                                 FeedConnectionMessage::fmcFullRefresh_TLS_FOND;
            int snapIndex = KeyIndex("tls");
            if (KeyIndex("begin") == snapIndex + 1)
                snapIndex++;
            info->m_symbol = this->m_keys[snapIndex + 1];
        }
        else if(HasKey("idf")) {
            info->m_templateId = FeedConnectionMessage::fmcSecurityDefinition;
            int idfIndex = KeyIndex("idf");
            if (HasKey("totNumReports"))
                info->m_totNumReports = atoi(this->m_keys[KeyIndex("totNumReports") + 1]);
            info->m_symbol = this->m_keys[idfIndex + 1];
        }
        else if(HasKey("isf")) {
            info->m_templateId = FeedConnectionMessage::fmcSecurityStatus;
            int isfIndex = KeyIndex("isf");
            info->m_symbol = this->m_keys[isfIndex + 1];
            info->m_session = this->m_keys[isfIndex + 2];
            info->m_sessionSubId = this->m_keys[isfIndex + 3];
            info->m_sessionStatus = (SecurityStatus)atoi(this->m_keys[isfIndex + 4]);
            info->m_auctionIndicator = atoi(this->m_keys[isfIndex + 5]);

            return info;
        }
        else if(HasKey("wait_snap")) {
            info->m_templateId = FeedConnectionMessage::fcmHeartBeat;
            info->m_wait = true;
            return info;
        }
        else if(HasKey("hbeat")) {
            info->m_templateId = FeedConnectionMessage::fcmHeartBeat;
            return info;
        }

        bool isSnap = HasKey("obs") || HasKey("ols") || HasKey("tls");
        bool isIdf = HasKey("idf");
        if(isSnap) {
            info->m_session = "session1";
            if(HasKey("begin")) {
                info->m_routeFirst = true;
            }
            if(HasKey("rpt")) {
                info->m_rptSec = atoi((const char *)(this->m_keys[KeyIndex("rpt") + 1]));
            }
            if(HasKey("lastmsg")) {
                info->m_lastMsgSeqNoProcessed = atoi((const char *)(this->m_keys[KeyIndex("lastmsg") + 1]));
            }
            else info->m_lastMsgSeqNoProcessed = 1;
            if(HasKey("end"))
                info->m_lastFragment = true;
        }

        if(isIdf) {
            int entryIndex = -1;
            int itemIndex = 0;

            while((entryIndex = KeyIndex("session", entryIndex + 1)) != -1) {
                TestTemplateItemInfo *item = new TestTemplateItemInfo();
                item->m_tradingSession = this->m_keys[entryIndex + 1];
                entryIndex++;

                info->m_items[itemIndex] = item;
                info->m_itemsCount++;

                itemIndex++;
            }
            return info;
        }

        int entryIndex = -1;
        int itemIndex = 0;
        while((entryIndex = KeyIndex("entry", entryIndex + 1)) != -1) {
            TestTemplateItemInfo *item = new TestTemplateItemInfo();
            item->m_tradingSession = "session1";
            item->m_action = MDUpdateAction::mduaAdd;
            if(StringIdComparer::Equal("del", this->m_keys[entryIndex + 1])) {
                item->m_action = MDUpdateAction::mduaDelete;
                entryIndex++;
            }
            else if(StringIdComparer::Equal("change", this->m_keys[entryIndex + 1])) {
                item->m_action = MDUpdateAction::mduaChange;
                entryIndex++;
            }
            item->m_symbol = this->m_keys[entryIndex + 1];
            item->m_entryId = this->m_keys[entryIndex + 2];
            item->m_entryType = MDEntryType::mdetBuyQuote;
            item->m_entryPx.Set(1, 1);
            item->m_entrySize.Set(1, 1);
            info->m_items[itemIndex] = item;
            info->m_itemsCount++;

            itemIndex++;
        }

        return info;
    }

    void FillMsg(TestTemplateInfo **temp, int count, const char *msg) {
        int startIndex = 0;
        for(int i = 0; i < count; i++) {
            int len = CalcWordLength(msg, startIndex);
            int start = 0, end = 0;
            TrimWord(msg, startIndex, len, &start, &end);
            Split(msg, start, end);
            temp[i] = CreateTemplate();
            startIndex += len + 1;
        }
    }

    int GetRptSeqFor(const char *symbol) {
        for(int i = 0; i < this->symbolsCount; i++) {
            if(StringIdComparer::Equal(this->symbols[i], symbol)) {
                rptSeq[i]++;
                return rptSeq[i];
            }
        }
        rptSeq[symbolsCount] = 1;
        symbols[symbolsCount] = symbol;
        symbolsCount++;
        return 1;
    }

    void FillRptSeq(TestTemplateInfo **msg, int count) {
        for(int i = 0; i < count; i++) {
            for(int j = 0; j < msg[i]->m_itemsCount; j++) {
                msg[i]->m_items[j]->m_rptSeq = GetRptSeqFor(msg[i]->m_items[j]->m_symbol);
            }
        }
    }

public:

    TestMessagesHelper() {
        if(TestMessagesHelper::m_sockMessages->PoolStart()->Data() == 0)
            TestMessagesHelper::m_sockMessages->AllocData();
    }
    ~TestMessagesHelper() {
    }

    FastLogonInfo* CreateLogonMessage(TestTemplateInfo *tmp) {
        FastLogonInfo *info = new FastLogonInfo();

        int sidLen = strlen(tmp->m_senderId);
        char *sid = new char[sidLen + 1];

        strcpy(sid, tmp->m_senderId);

        int pLen = strlen(tmp->m_pass);
        char *p = new char[pLen + 1];
        strcpy(p, tmp->m_pass);

        info->SenderCompID = sid;
        info->SenderCompIDLength = sidLen;

        info->AllowPassword = true;
        info->Password = p;
        info->PasswordLength = pLen;

        info->MsgSeqNum = tmp->m_msgSeqNo;

        return info;
    }

    FastOLSFONDInfo* CreateOLSFondInfo(const char *symbol, const char *trading) {
        FastOLSFONDInfo *info = new FastOLSFONDInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastOLSFONDItemInfo* CreateOLSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastOLSFONDItemInfo> *list = new AutoAllocatePointerList<FastOLSFONDItemInfo>(1, 1);
        FastOLSFONDItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastIncrementalOLRFONDInfo* CreateFastIncrementalOLRFONDInfo() {
        AutoAllocatePointerList<FastIncrementalOLRFONDInfo> *list = new AutoAllocatePointerList<FastIncrementalOLRFONDInfo>(1, 1);
        return list->NewItem();
    }

    FastIncrementalOLRCURRInfo* CreateFastIncrementalOLRCURRInfo() {
        AutoAllocatePointerList<FastIncrementalOLRCURRInfo> *list = new AutoAllocatePointerList<FastIncrementalOLRCURRInfo>(1, 1);
        return list->NewItem();
    }

    FastIncrementalTLRFONDInfo* CreateFastIncrementalTLRFONDInfo() {
        AutoAllocatePointerList<FastIncrementalTLRFONDInfo> *list = new AutoAllocatePointerList<FastIncrementalTLRFONDInfo>(1, 1);
        return list->NewItem();
    }

    FastIncrementalTLRCURRInfo* CreateFastIncrementalTLRCURRInfo() {
        AutoAllocatePointerList<FastIncrementalTLRCURRInfo> *list = new AutoAllocatePointerList<FastIncrementalTLRCURRInfo>(1, 1);
        return list->NewItem();
    }

    FastOLSFONDItemInfo* CreateOLRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        FastOLSFONDItemInfo *info = CreateOLSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastOLSFONDItemInfo* CreateOLRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }
    
    FastOLSCURRInfo* CreateOLSCurrInfo(const char *symbol, const char *trading) {
        FastOLSCURRInfo *info = new FastOLSCURRInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastOLSCURRItemInfo* CreateOLSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastOLSCURRItemInfo> *list = new AutoAllocatePointerList<FastOLSCURRItemInfo>(1, 1);
        FastOLSCURRItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastOLSCURRItemInfo* CreateOLRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        FastOLSCURRItemInfo *info = CreateOLSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastOLSCURRItemInfo* CreateOLRCurrItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOLRCurrItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }
    
    FastGenericInfo* CreateOBSFondInfo(const char *symbol, const char *trading) {
        FastGenericInfo *info = new FastGenericInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastGenericItemInfo* CreateOBSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastGenericItemInfo> *list = new AutoAllocatePointerList<FastGenericItemInfo>(1, 1);
        FastGenericItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastGenericItemInfo* CreateOBRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        FastGenericItemInfo *info = CreateOBSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastGenericItemInfo* CreateOBRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOBRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    FastGenericInfo* CreateOBSCurrInfo(const char *symbol, const char *trading) {
        FastGenericInfo *info = new FastGenericInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastGenericItemInfo* CreateOBSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastGenericItemInfo> *list = new AutoAllocatePointerList<FastGenericItemInfo>(1, 1);
        FastGenericItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastGenericItemInfo* CreateOBRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa,
                                               INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta,
                                               MDUpdateAction updateAction, MDEntryType entryType, const char *entryId,
                                               int rptSeq) {
        FastGenericItemInfo *info = CreateOBSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastGenericItemInfo* CreateOBRCurrItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateOBRCurrItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    FastTLSFONDInfo* CreateTLSFondInfo(const char *symbol, const char *trading) {
        FastTLSFONDInfo *info = new FastTLSFONDInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastTLSFONDItemInfo* CreateTLSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastTLSFONDItemInfo> *list = new AutoAllocatePointerList<FastTLSFONDItemInfo>(1, 1);
        FastTLSFONDItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastTLSFONDItemInfo *info = CreateTLSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateTLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    FastTLSFONDItemInfo* CreateTLRFondItemInfo(const char *symbol, const char *trading, const char *entryId, int rptSec) {
        return CreateTLRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, rptSec);
    }

    FastTLSCURRInfo* CreateTLSCurrInfo(const char *symbol, const char *trading) {
        FastTLSCURRInfo *info = new FastTLSCURRInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastTLSCURRItemInfo* CreateTLSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastTLSCURRItemInfo> *list = new AutoAllocatePointerList<FastTLSCURRItemInfo>(1, 1);
        FastTLSCURRItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastTLSCURRItemInfo* CreateTLSCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastTLSCURRItemInfo *info = CreateTLSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastTLSCURRItemInfo* CreateTLSCurrItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateTLSCurrItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    FastTLSCURRItemInfo* CreateTLSCurrItemInfo(const char *symbol, const char *trading, const char *entryId, int rptSec) {
        return CreateTLSCurrItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, rptSec);
    }

    FastGenericInfo* CreateMSSFondInfo(const char *symbol, const char *trading) {
        FastGenericInfo *info = new FastGenericInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastGenericItemInfo* CreateGenericItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastGenericItemInfo> *list = new AutoAllocatePointerList<FastGenericItemInfo>(1, 1);
        FastGenericItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastGenericItemInfo* CreateGenericItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastGenericItemInfo *info = CreateGenericItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastGenericItemInfo* CreateGenericItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateGenericItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, 1);
    }

    FastGenericItemInfo* CreateGenericItemInfo(const char *symbol, const char *trading, const char *entryId, int rptSec) {
        return CreateGenericItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote,
                                     entryId, rptSec);
    }

    FastGenericInfo* CreateMSSCurrInfo(const char *symbol, const char *trading) {
        FastGenericInfo *info = new FastGenericInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastGenericItemInfo* CreateGenericItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId, int rptSeq) {

        AutoAllocatePointerList<FastGenericItemInfo> *list = new AutoAllocatePointerList<FastGenericItemInfo>(1, 1);
        FastGenericItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);
        info->RptSeq = rptSeq;

        return info;
    }

    void AddTradingSession(FastSecurityDefinitionInfo *info, int marketIndex, const char *tradingSession) {
        int newIndex = info->MarketSegmentGrp[marketIndex]->TradingSessionRulesGrpCount;
        info->MarketSegmentGrp[marketIndex]->TradingSessionRulesGrpCount++;
        AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo> *list = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>(1, 1);
        FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *item = list->NewItem();
        info->MarketSegmentGrp[marketIndex]->TradingSessionRulesGrp[newIndex] = item;

        char *trd = new char[strlen(tradingSession) + 1];
        strcpy(trd, tradingSession);

        item->TradingSessionID = trd;
        item->TradingSessionIDLength = strlen(trd);
    }

    void AddMarketSegemntGroup(FastSecurityDefinitionInfo *info) {
        AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo> *list = new AutoAllocatePointerList<FastSecurityDefinitionMarketSegmentGrpItemInfo>(1, 1);
        info->MarketSegmentGrp[info->MarketSegmentGrpCount] = list->NewItem();
        info->MarketSegmentGrpCount++;
    }

    FastSecurityDefinitionInfo* CreateSecurityDefinitionInfo(const char *symbol) {
        AutoAllocatePointerList<FastSecurityDefinitionInfo> *list = new AutoAllocatePointerList<FastSecurityDefinitionInfo>(1, 1);
        FastSecurityDefinitionInfo *info = list->NewItem();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        info->Symbol = smb;
        info->SymbolLength = strlen(symbol);
        info->AllowSymbol = true;

        return info;
    }

    FastSecurityStatusInfo* CreateSecurityStatusInfo(const char *symbol, const char *session, const char *sessionSubId) {
        AutoAllocatePointerList<FastSecurityStatusInfo> *list = new AutoAllocatePointerList<FastSecurityStatusInfo>(1, 1);
        FastSecurityStatusInfo *info = list->NewItem();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *ss = new char[strlen(session) + 1];
        strcpy(ss, session);

        char *sub = new char[strlen(sessionSubId) + 1];
        strcpy(sub, sessionSubId);

        info->Symbol = smb;
        info->SymbolLength = strlen(symbol);

        info->AllowTradingSessionID = true;
        info->TradingSessionID = ss;
        info->TradingSessionIDLength = strlen(session);

        info->AllowTradingSessionSubID = true;
        info->TradingSessionSubID = sub;
        info->TradingSessionSubIDLength = strlen(sessionSubId);

        return info;
    }

    FastSecurityDefinitionInfo* CreateSecurityDefinitionInfo(TestTemplateInfo *tmp) {
        FastSecurityDefinitionInfo *info = CreateSecurityDefinitionInfo(tmp->m_symbol);

        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->AllowMarketSegmentGrp = true;
        this->AddMarketSegemntGroup(info);
        info->MarketSegmentGrp[0]->AllowTradingSessionRulesGrp = true;
        if(tmp->m_totNumReports != 0) {
            info->AllowTotNumReports = true;
            info->TotNumReports = tmp->m_totNumReports;
        }

        for(int i = 0; i < tmp->m_itemsCount; i++) {
            this->AddTradingSession(info, 0, tmp->m_items[i]->m_tradingSession);
        }
        return info;
    }

    FastSecurityStatusInfo* CreateSecurityStatusInfo(TestTemplateInfo *tmp) {
        FastSecurityStatusInfo *info = CreateSecurityStatusInfo(tmp->m_symbol, tmp->m_session, tmp->m_sessionSubId);

        info->AllowSecurityTradingStatus = true;
        info->SecurityTradingStatus = tmp->m_sessionStatus;

        info->AllowAuctionIndicator = true;
        info->AuctionIndicator = tmp->m_auctionIndicator;

        info->MsgSeqNum = tmp->m_msgSeqNo;

        return info;
    }

    FastOLSFONDItemInfo* CreateOLRFondItemInfo(TestTemplateItemInfo *tmp) {
        FastOLSFONDItemInfo *info = new FastOLSFONDItemInfo();

        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;

        info->AllowMDEntryType = true;
        info->PresenceMap |= info->MDEntryTypePresenceIndex;
        info->MDEntryType = new char[1];
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;

        info->AllowMDEntryPx = true;
        info->PresenceMap |= info->MDEntryPxPresenceIndex;
        info->MDEntryPx.Assign(&tmp->m_entryPx);

        info->AllowMDEntrySize = true;
        info->PresenceMap |= info->MDEntrySizePresenceIndex;
        info->MDEntrySize.Assign(&tmp->m_entrySize);

        info->AllowRptSeq = true;
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->AllowSymbol = true;
            info->PresenceMap |= info->SymbolPresenceIndex;
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->AllowTradingSessionID = true;
            info->PresenceMap |= info->TradingSessionIDPresenceIndex;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->AllowMDEntryID = true;
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            info->MDEntryID = new char[info->MDEntryIDLength + 1];
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    FastGenericItemInfo* CreateObrFondItemInfo(TestTemplateItemInfo *tmp) {
        FastGenericItemInfo *info = new FastGenericItemInfo();
        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;
        info->AllowMDEntryType = true;
        info->MDEntryType = new char[1];
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;
        info->AllowMDEntryPx = true;
        info->MDEntryPx.Assign(&tmp->m_entryPx);
        info->AllowMDEntrySize = true;
        info->MDEntrySize.Assign(&tmp->m_entrySize);
        info->AllowRptSeq = true;
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->AllowSymbol = true;
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->AllowMDEntryID = true;
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            info->MDEntryID = new char[info->MDEntryIDLength + 1];
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    FastTLSFONDItemInfo* CreateTLRFondItemInfo(TestTemplateItemInfo *tmp) {
        FastTLSFONDItemInfo *info = new FastTLSFONDItemInfo();
        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;

        info->MDEntryType = new char[1];
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;

        info->AllowMDEntryPx = true;
        info->PresenceMap |= info->MDEntryPxPresenceIndex;
        info->MDEntryPx.Assign(&tmp->m_entryPx);

        info->AllowMDEntrySize = true;
        info->PresenceMap |= info->MDEntrySizePresenceIndex;
        info->MDEntrySize.Assign(&tmp->m_entrySize);

        info->AllowRptSeq = true;
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->AllowSymbol = true;
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->AllowMDEntryID = true;
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            info->MDEntryID = new char[info->MDEntryIDLength + 1];
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    FastOLSCURRItemInfo* CreateOLRCurrItemInfo(TestTemplateItemInfo *tmp) {
        FastOLSCURRItemInfo *info = new FastOLSCURRItemInfo();
        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;

        info->AllowMDEntryType = true;
        info->PresenceMap |= info->MDEntryTypePresenceIndex;
        info->MDEntryType = new char[1];
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;

        info->AllowMDEntryPx = true;
        info->PresenceMap |= info->MDEntryPxPresenceIndex;
        info->MDEntryPx.Assign(&tmp->m_entryPx);

        info->AllowMDEntrySize = true;
        info->PresenceMap |= info->MDEntrySizePresenceIndex;
        info->MDEntrySize.Assign(&tmp->m_entrySize);

        info->AllowRptSeq = true;
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->AllowSymbol = true;
            info->PresenceMap |= info->SymbolPresenceIndex;
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->AllowTradingSessionID = true;
            info->PresenceMap |= info->TradingSessionIDPresenceIndex;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->AllowMDEntryID = true;
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            info->MDEntryID = new char[info->MDEntryIDLength + 1];
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    FastGenericItemInfo* CreateObrCurrItemInfo(TestTemplateItemInfo *tmp) {
        FastGenericItemInfo *info = new FastGenericItemInfo();
        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;
        info->AllowMDEntryType = true;
        info->MDEntryType = new char[1];
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;
        info->AllowMDEntryPx = true;
        info->MDEntryPx.Assign(&tmp->m_entryPx);
        info->AllowMDEntrySize = true;
        info->MDEntrySize.Assign(&tmp->m_entrySize);
        info->AllowRptSeq = true;
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->AllowSymbol = true;
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->AllowMDEntryID = true;
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            info->MDEntryID = new char[info->MDEntryIDLength + 1];
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    FastTLSCURRItemInfo* CreateTLRCurrItemInfo(TestTemplateItemInfo *tmp) {
        FastTLSCURRItemInfo *info = new FastTLSCURRItemInfo();
        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;

        info->MDEntryType = new char[1];
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;

        info->AllowMDEntryPx = true;
        info->PresenceMap |= info->MDEntryPxPresenceIndex;
        info->MDEntryPx.Assign(&tmp->m_entryPx);

        info->AllowMDEntrySize = true;
        info->PresenceMap |= info->MDEntrySizePresenceIndex;
        info->MDEntrySize.Assign(&tmp->m_entrySize);

        info->AllowRptSeq = true;
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->AllowSymbol = true;
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->AllowMDEntryID = true;
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            info->MDEntryID = new char[info->MDEntryIDLength + 1];
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    void EncodeHearthBeatMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastHeartbeatInfo *info = new FastHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeHeartbeatInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendHearthBeatMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastHeartbeatInfo *info = new FastHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeHeartbeatInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeLogoutMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastLogoutInfo *info = new FastLogoutInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeLogoutInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendLogoutMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastLogoutInfo *info = new FastLogoutInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeLogoutInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeLogonMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastLogonInfo *info = CreateLogonMessage(tmp);
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeLogonInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendLogonMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastLogonInfo *info = CreateLogonMessage(tmp);
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeLogonInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastIncrementalGenericInfo* CreateIncrementalGenericMessageCore(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalGenericInfo *info = new FastIncrementalGenericInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeIncrementalGenericMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalGenericInfo *info = CreateIncrementalGenericMessageCore(conn, tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalGenericInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendIncrementalGenericMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalGenericInfo *info = CreateIncrementalGenericMessageCore(conn, tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalGenericInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastGenericInfo* CreateSnapshotGenericMessageCore(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastGenericInfo *info = new FastGenericInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeSnapshotGenericMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastGenericInfo *info = CreateSnapshotGenericMessageCore(conn, tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeGenericInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendSnapshotGenericMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastGenericInfo *info = CreateSnapshotGenericMessageCore(conn, tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeGenericInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastIncrementalOLRFONDInfo* CreateOLRFondMessageCore(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalOLRFONDInfo *info = new FastIncrementalOLRFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeOLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalOLRFONDInfo *info = CreateOLRFondMessageCore(conn, tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalOLRFONDInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendOLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalOLRFONDInfo *info = CreateOLRFondMessageCore(conn, tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalOLRFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeSecurityDefinitionMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastSecurityDefinitionInfo *info = CreateSecurityDefinitionInfo(tmp);
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeSecurityDefinitionInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendSecurityDefinitionMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastSecurityDefinitionInfo *info = CreateSecurityDefinitionInfo(tmp);
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeSecurityDefinitionInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void EncodeSecurityStatusMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastSecurityStatusInfo *info = CreateSecurityStatusInfo(tmp);
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeSecurityStatusInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendSecurityStatusMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastSecurityStatusInfo *info = CreateSecurityStatusInfo(tmp);
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeSecurityStatusInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastOLSFONDInfo* CreateOLSFondMessage(TestTemplateInfo *tmp) {
        FastOLSFONDInfo *info = new FastOLSFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeOLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastOLSFONDInfo *info = CreateOLSFondMessage(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeOLSFONDInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendOLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastOLSFONDInfo *info = CreateOLSFondMessage(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeOLSFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastIncrementalTLRFONDInfo* CreateTLRFondMessageCore(TestTemplateInfo *tmp) {
        FastIncrementalTLRFONDInfo *info = new FastIncrementalTLRFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeTLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalTLRFONDInfo *info = CreateTLRFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalTLRFONDInfo(info);
        conn->m_sendABuffer->Next (conn->m_fastProtocolManager->MessageLength());
    }

    void SendTLRFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalTLRFONDInfo *info = CreateTLRFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalTLRFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastTLSFONDInfo* CreateTLSFondMessageCore(TestTemplateInfo *tmp) {
        FastTLSFONDInfo *info = new FastTLSFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRFondItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeTLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastTLSFONDInfo *info = CreateTLSFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeTLSFONDInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendTLSFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastTLSFONDInfo *info = CreateTLSFondMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeTLSFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastIncrementalOLRCURRInfo* CreateOLRCurrMessageCore(TestTemplateInfo *tmp) {
        FastIncrementalOLRCURRInfo *info = new FastIncrementalOLRCURRInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRCurrItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeOLRCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalOLRCURRInfo* info = CreateOLRCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalOLRCURRInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendOLRCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalOLRCURRInfo* info = CreateOLRCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalOLRCURRInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastOLSCURRInfo* CreateOLSCurrMessageCore(TestTemplateInfo *tmp) {
        FastOLSCURRInfo *info = new FastOLSCURRInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateOLRCurrItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeOLSCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastOLSCURRInfo *info = CreateOLSCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeOLSCURRInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendOLSCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastOLSCURRInfo *info = CreateOLSCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeOLSCURRInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastIncrementalTLRCURRInfo* CreateTLRCurrMessageCore(TestTemplateInfo *tmp) {
        FastIncrementalTLRCURRInfo *info = new FastIncrementalTLRCURRInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRCurrItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeTLRCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalTLRCURRInfo *info = CreateTLRCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalTLRCURRInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendTLRCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalTLRCURRInfo *info = CreateTLRCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalTLRCURRInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastTLSCURRInfo* CreateTLSCurrMessageCore(TestTemplateInfo *tmp) {
        FastTLSCURRInfo *info = new FastTLSCURRInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateTLRCurrItemInfo(tmp->m_items[i]);
        }
        return info;
    }

    void EncodeTLSCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastTLSCURRInfo *info = CreateTLSCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_sendABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeTLSCURRInfo(info);
        conn->m_sendABuffer->Next(conn->m_fastProtocolManager->MessageLength());
    }

    void SendTLSCurrMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastTLSCURRInfo *info = CreateTLSCurrMessageCore(tmp);

        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeTLSCURRInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void SendMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        switch(tmp->m_templateId) {
            case FeedConnectionMessage::fcmHeartBeat:
                SendHearthBeatMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_Generic:
                SendIncrementalGenericMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_Generic:
                SendSnapshotGenericMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND:
                SendOLRFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
                SendOLSFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND:
                SendTLRFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
                SendTLSFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR:
                SendOLRCurrMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
                SendOLSCurrMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_TLR_CURR:
                SendTLRCurrMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_TLS_CURR:
                SendTLSCurrMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcSecurityDefinition:
                SendSecurityDefinitionMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcSecurityStatus:
                SendSecurityStatusMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcLogon:
                SendLogonMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcLogout:
                SendLogoutMessage(conn, tmp);
                break;
            default:
                break;
        }
    }

    void SendMessages(FeedConnection *conn, TestTemplateInfo **templates, int templatesCount) {
        for(int i = 0; i < templatesCount; i++)
            SendMessage(conn, templates[i]);
    }

    void SendMessagesIdf(FeedConnection *fif, const char *idf, int delay) {
        int idfMsgCount = CalcMsgCount(idf);
        TestTemplateInfo **idf_msg = new TestTemplateInfo*[idfMsgCount];
        FillMsg(idf_msg, idfMsgCount, idf);

        int idf_index = 0;
        Stopwatch w;
        w.Start(1);
        while(idf_index < idfMsgCount) {
            if(idf_msg[idf_index]->m_msgSeqNo == 0)
                idf_msg[idf_index]->m_msgSeqNo = idf_index + 1;
            if(!idf_msg[idf_index]->m_lost) {
                SendMessage(fif, idf_msg[idf_index]);
                if (!fif->Listen_Atom_SecurityDefinition_Core())
                    throw;
            }
            idf_index++;

            w.Start();
            while(!w.IsElapsedMilliseconds(delay));
            w.Stop();
            if(!TestMessagesHelper::SkipTimeOutCheck && w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
    }

    void SendMessagesIsf(FeedConnection *fif, const char *idf, int delay) {
        int idfMsgCount = CalcMsgCount(idf);
        TestTemplateInfo **idf_msg = new TestTemplateInfo*[idfMsgCount];
        FillMsg(idf_msg, idfMsgCount, idf);

        int idf_index = 0;
        Stopwatch w;
        w.Start(1);
        while(idf_index < idfMsgCount) {
            if(idf_msg[idf_index]->m_msgSeqNo == 0)
                idf_msg[idf_index]->m_msgSeqNo = idf_index + 1;
            if(!idf_msg[idf_index]->m_lost) {
                SendMessage(fif, idf_msg[idf_index]);
                if (!fif->Listen_Atom_SecurityStatus_Core())
                    throw;
            }
            idf_index++;

            w.Start();
            while(!w.IsElapsedMilliseconds(delay));
            w.Stop();
            if(!TestMessagesHelper::SkipTimeOutCheck && w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
    }

    void EncodeMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        switch(tmp->m_templateId) {
            case FeedConnectionMessage::fcmHeartBeat:
                EncodeHearthBeatMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_Generic:
                EncodeIncrementalGenericMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_Generic:
                EncodeSnapshotGenericMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND:
                EncodeOLRFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
                EncodeOLSFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND:
                EncodeTLRFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
                EncodeTLSFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR:
                EncodeOLRCurrMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
                EncodeOLSCurrMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_TLR_CURR:
                EncodeTLRCurrMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_TLS_CURR:
                EncodeTLSCurrMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcSecurityDefinition:
                EncodeSecurityDefinitionMessage(conn, tmp);
            case FeedConnectionMessage::fmcLogon:
                EncodeLogonMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcLogout:
                EncodeLogoutMessage(conn, tmp);
                break;
            default:
                break;
        }
    }

    void EncodeMessage(FeedConnection *fc, const char *msg) {
        int incMsgCount = CalcMsgCount(msg);
        TestTemplateInfo **inc_msg = new TestTemplateInfo*[incMsgCount];
        FillMsg(inc_msg, incMsgCount, msg);
        FillRptSeq(inc_msg, incMsgCount);

        this->EncodeMessage(fc, inc_msg[0]);
    }

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay) {
        int incMsgCount = CalcMsgCount(inc);
        int snapMsgCount = CalcMsgCount(snap);

        TestTemplateInfo **inc_msg = new TestTemplateInfo*[incMsgCount];
        TestTemplateInfo **snap_msg = new TestTemplateInfo*[snapMsgCount];

        FillMsg(inc_msg, incMsgCount, inc);
        FillMsg(snap_msg, snapMsgCount, snap);
        FillRptSeq(inc_msg, incMsgCount);

        int inc_index = 0;
        int snap_index = 0;

        Stopwatch w;
        w.Start(1);
        bool snapshotStarterd = false;
        while(inc_index < incMsgCount || snap_index < snapMsgCount) {
            if(inc_index < incMsgCount && !inc_msg[inc_index]->m_lost) {
                inc_msg[inc_index]->m_msgSeqNo = inc_index + 1;
                SendMessage(fci, inc_msg[inc_index]);
            }
            fci->Listen_Atom_Incremental_Core();
            if(snapshotStarterd && fcs->State() == FeedConnectionState::fcsSuspend && snap_index < snapMsgCount && !snap_msg[snap_index]->m_skip)
                throw;
            if(inc_index < incMsgCount && inc_msg[inc_index]->m_wait) {
                if(!fci->m_waitTimer->Active())
                    throw;
                if(fcs->State() != FeedConnectionState::fcsSuspend)
                    throw;
                while(!fci->m_waitTimer->IsElapsedMilliseconds(fci->WaitIncrementalMaxTimeMs()) && fcs->State() == FeedConnectionState::fcsSuspend)
                    fci->Listen_Atom_Incremental_Core();
                if(fcs->State() == FeedConnectionState::fcsSuspend)
                    fci->Listen_Atom_Incremental_Core();
                if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
                    throw;
                snapshotStarterd = true;
            }
            if(inc_index < incMsgCount)
                inc_index++;
            if(fcs->State() == FeedConnectionState::fcsListenSnapshot) {
                if (snap_index < snapMsgCount && !snap_msg[snap_index]->m_lost) {
                    snap_msg[snap_index]->m_msgSeqNo = snap_index + 1;
                    if(snap_msg[snap_index]->m_templateId != FeedConnectionMessage::fcmHeartBeat && (snap_msg[snap_index]->m_symbol == 0 || snap_msg[snap_index]->m_session == 0))
                        throw;
                    SendMessage(fcs, snap_msg[snap_index]);
                }
                if(snap_index < snapMsgCount)
                    snap_index++;
                fcs->Listen_Atom_Snapshot_Core();
            }
            else {
                if (snap_index < snapMsgCount && snap_msg[snap_index]->m_skip) {
                    snap_index++;
                }
            }
            w.Start();
            while(!w.IsElapsedMilliseconds(delay));
            w.Stop();
            if(!TestMessagesHelper::SkipTimeOutCheck && w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
        fci->Listen_Atom_Incremental_Core(); // emulate endless loop
    }

    void Clear() {
        this->symbolsCount = 0;
        for(int i = 0; i < 100; i++) {
            this->symbols[i] = 0;
            this->rptSeq[i] = 0;
        }
    }

    inline void SetCurrMode() { this->m_curr = true; }
    inline void SetFondMode() { this->m_curr = false; }

    void CreateFixLogonMessage(FeedConnection *fc, const char *senderId, const char *pass) {
        FixLogonInfo *lg = new FixLogonInfo;

        strcpy(lg->SenderCompID, senderId);
        lg->SenderCompIDLength = strlen(senderId);

        strcpy(lg->Password, pass);
        lg->PassLength = strlen(pass);

        fc->m_fixProtocolManager->CreateLogonMessage(lg);
    }

    void ClearPoll() {
        for(int i = 0; i < WinSockManager::m_registeredCount; i++) {
            WinSockManager::m_recvCount[i] = 0;
        }
    }

    void SetRecvFor(WinSockManager *m, unsigned char *buffer, int bufferLen) {
        LinkedPointer<SocketMessageInfo> *ptr = TestMessagesHelper::m_sockMessages->Pop();
        SocketMessageInfo *msg = ptr->Data();

        msg->m_manager = m;
        if(buffer != 0)
            memcpy(msg->m_buffer, buffer, bufferLen);
        msg->m_canRecv = buffer != 0;
        msg->m_bufferLength = bufferLen;

        this->m_sockMessages->Add(ptr);
        for(int i = 0; i < WinSockManager::m_registeredCount; i++) {
            if(WinSockManager::m_registeredManagers[i] == msg->m_manager) {
                WinSockManager::m_recvCount[i] = msg->m_canRecv? 1: 0;
            }
        }
    }
    void SetRecvFixFor(FeedConnection *fc) {
        this->SetRecvFor(fc->socketAManager, fc->m_fixProtocolManager->SendBuffer(), fc->m_fixProtocolManager->MessageLength());
    }

    void SetRecvFastFor(FeedConnection *fc) {
        this->SetRecvFor(fc->socketAManager, fc->m_fastProtocolManager->Buffer(), fc->m_fastProtocolManager->MessageLength());
    }

};

#endif //HFT_ROBOT_TESTMESSAGESHELPER_H
