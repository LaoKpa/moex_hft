#pragma once
#include "Managers/WinSockManager.h"
#include "Fast/FastProtocolManager.h"
#include "Fix/FixProtocolManager.h"
#include "Settings.h"
#include <sys/time.h>
#include "Stopwatch.h"
#include "Lib/AutoAllocatePointerList.h"
#include "Lib/StringIdComparer.h"
#include "MarketData/MarketDataTable.h"
#include "MarketData/OrderInfo.h"
#include "MarketData/TradeInfo.h"
#include "MarketData/StatisticInfo.h"
#include "MarketData/SymbolManager.h"
#include "ConnectionParameters.h"
#include "FeedTypes.h"
#include "Managers/DebugInfoManager.h"
#include "../ProgramStatistics.h"

class OrderTesterFond;
class OrderTesterCurr;
class TradeTesterFond;
class TradeTesterCurr;
class TestMessagesHelper;
class StatisticsTesterFond;
class StatisticsTesterCurr;
class SecurityDefinitionTester;
class SecurityStatusTester;
class DebugInfoManager;
class HistoricalReplayTester;

class FeedConnection {
    friend class OrderTesterFond;
    friend class OrderTesterCurr;
	friend class TradeTesterFond;
    friend class TradeTesterCurr;
	friend class FeedConnectionTester;
    friend class TestMessagesHelper;
    friend class StatisticsTesterFond;
    friend class StatisticsTesterCurr;
    friend class SecurityDefinitionTester;
    friend class SecurityStatusTester;
    friend class DebugInfoManager;
    friend class HistoricalReplayTester;

public:
	const int MaxReceiveBufferSize 				        = 1500;
    const int WaitAnyPacketMaxTimeMs                    = 4000;
    const int MaxHrUnsuccessfulConnectCount             = 100;
    const int WaitSecurityDefinitionPacketMaxTimeMs     = 20000;
protected:
	char										m_idName[16];
    char                                        m_channelName[16];
	char										feedTypeName[64];

#ifdef TEST
    TestMessagesHelper                          *m_testHelper;
#endif

    FeedConnectionType                          m_type;
    FeedConnectionId                            m_id;

    FeedConnection                              *m_incremental;
    FeedConnection                              *m_snapshot;
    FeedConnection                              *m_historicalReplay;
    FeedConnection                              *m_securityDefinition;
    bool                                        m_securityStatusSnapshotActive;
    int                                         m_isfStartSnapshotCount;

    FeedConnection                              *m_connectionsToRecvSymbols[32];
    int                                         m_connectionsToRecvSymbolsCount;

    int                                         m_snapshotRouteFirst;
    int                                         m_snapshotLastFragment;
    int                                         m_lastMsgSeqNumProcessed;
	int											m_rptSeq;

    int                                         m_waitIncrementalMaxTimeMs;
    int                                         m_snapshotMaxTimeMs;
    int                                         m_maxLostPacketCountForStartSnapshot;
    bool                                        m_isLastIncrementalRecv;

    bool                                        m_doNotCheckIncrementalActuality;
    bool                                        m_skipApplyMessages;

    FeedConnectionSecurityDefinitionMode        m_idfMode;
    FeedConnectionSecurityDefinitionState       m_idfState;
    int                                         m_idfMaxMsgSeqNo;
    int                                         m_idfStartMsgSeqNo;

    bool                                        m_idfDataCollected;
    bool                                        m_idfAllowUpdateData;
    bool                                        m_idfStopAfterUpdateAllMessages;
    bool                                        m_allowGenerateSecurityDefinitions;
    SymbolManager                               *m_symbolManager;

    FeedConnectionHistoricalReplayState             m_hsState;
    PointerList<FeedConnectionRequestMessageInfo>  *m_hsRequestList;
    int                                             m_hrMessageSize;
    int                                             m_hrSizeRemain;
    int                                             m_hrUnsuccessfulConnectCount;

    FeedConnectionMessageInfo                       **m_packets;
    int                                         m_packetsCount;

	int     									m_idLogIndex;
	int 										m_feedTypeNameLogIndex;

	char										feedTypeValue;

	FeedConnectionProtocol 						protocol;

	char										feedASourceIp[64];
	char										feedAIp[64];
	int											feedAPort;

	char										feedBSourceIp[64];
	char										feedBIp[64];
	int											feedBPort;

	int                                         m_windowMsgSeqNum;
    int											m_startMsgSeqNum;
    int                                         m_endMsgSeqNum;
    int                                         m_requestMessageStartIndex;

    const char                                  *m_senderCompId;
    int                                         m_senderCompIdLength;
    const char                                  *m_password;
    int                                         m_passwordLength;

	WinSockManager								*socketAManager;
	WinSockManager								*socketBManager;
	FastProtocolManager 						*m_fastProtocolManager;
    FastLogonInfo                               *m_fastLogonInfo;

    FixProtocolManager                          *m_fixProtocolManager;
    FixLogonInfo                                *m_hsLogonInfo;
    FixRejectInfo                               *m_hsRejectInfo;
    int                                          m_hsMsgSeqNo;

	ISocketBufferProvider						*m_socketABufferProvider;
	SocketBuffer								*m_sendABuffer;
	SocketBuffer								*m_recvABuffer;

	FeedConnectionState							m_state;
	FeedConnectionState							m_nextState;

    bool										m_shouldUseNextState;
    int                                         m_reconnectCount;
    int                                         m_maxReconnectCount;

    struct timeval                              *m_tval;
    Stopwatch                                   *m_stopwatch;
    Stopwatch                                   *m_waitTimer;
    bool                                        m_shouldReceiveAnswer;

	MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo>			*m_orderTableFond;
	MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo>			*m_orderTableCurr;
	MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>			*m_tradeTableFond;
	MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo>			*m_tradeTableCurr;
    MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>       *m_statTableFond;
    MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo>       *m_statTableCurr;
    LinkedPointer<FastSecurityDefinitionInfo>                                   **m_symbols;
    int                                                                         m_symbolsCount;

    void InitializeHistoricalReplay() {
        this->m_hsRequestList = new PointerList<FeedConnectionRequestMessageInfo>(RobotSettings::Default->HistoricalReplayMaxMessageRequestCount);
        this->m_hsRequestList->AllocData();
        this->m_fixProtocolManager = new FixProtocolManager(this->m_socketABufferProvider, FastProtocolVersion);
        this->m_fixProtocolManager->SetTargetComputerId(HistoricalReplayTargetComputerId);
        this->m_hsLogonInfo = new FixLogonInfo();
        this->m_hsRejectInfo = new FixRejectInfo();
        this->m_hsMsgSeqNo = 1;
    }
    void DisposeHistoricalReplay() {
        this->m_hsRequestList->FreeData();
        delete this->m_hsRequestList;
        delete this->m_hsLogonInfo;
        delete this->m_hsRejectInfo;
    }
    int GetPacketsCount() { return RobotSettings::Default->DefaultFeedConnectionPacketCount; }
    void InitializePackets(int count) {
        this->m_packetsCount = count;
        this->m_packets = new FeedConnectionMessageInfo*[ this->m_packetsCount ];
        for(int i = 0; i < this->m_packetsCount; i++)
            this->m_packets[i] = new FeedConnectionMessageInfo();
        DebugInfoManager::Default->PrintMemoryInfo("FeedConnectionInfo::InitializePackets");
    }
    void InitializeSecurityDefinition() {
        this->m_symbols = new LinkedPointer<FastSecurityDefinitionInfo>*[RobotSettings::Default->MaxSecurityDefinitionCount];
        for(int i = 0; i < RobotSettings::Default->MaxSecurityDefinitionCount; i++)
            this->m_symbols[i] = new LinkedPointer<FastSecurityDefinitionInfo>();
        this->m_symbolsCount = 0;
        this->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmCollectData;
        this->m_symbolManager = new SymbolManager(RobotSettings::Default->MarketDataMaxSymbolsCount);
    }
    void DisposeSecurityDefinition() {
        for(int i = 0; i < RobotSettings::Default->MaxSecurityDefinitionCount; i++)
            delete this->m_symbols[i];
        delete this->m_symbols;
    }

    inline void GetCurrentTime(UINT64 *time) {
        gettimeofday(this->m_tval, NULL);
        *time = this->m_tval->tv_usec / 1000;
    }

    inline int TryGetSecurityDefinitionTotNumReports(unsigned char *buffer) {
        this->m_fastProtocolManager->SetNewBuffer(buffer + 4, 1500);
        this->m_fastProtocolManager->DecodeHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedConnectionMessage::fmcSecurityDefinition)
            return 0;
        return this->m_fastProtocolManager->GetTotalNumReports();
    }

	inline bool CanListen() { return this->socketAManager->ShouldRecv() || this->socketBManager->ShouldRecv(); }
    inline void ThreatFirstMessageIndexAsStart() {
        this->m_startMsgSeqNum = -1;
        this->m_endMsgSeqNum = 0;
    }

    inline bool ProcessServerA() { return this->ProcessServer(this->socketAManager, LogMessageCode::lmcsocketA); }
    inline bool ProcessServerB() { return this->ProcessServer(this->socketBManager, LogMessageCode::lmcsocketB); }
    inline bool UpdateMsgSeqStartEnd(int msgSeqNum) {
        if(this->m_type == FeedConnectionType::Incremental) {
            if(this->m_endMsgSeqNum < msgSeqNum)
                this->m_endMsgSeqNum = msgSeqNum;
//                    BinaryLogItem *item = DefaultLogManager::Default->WriteFast(this->m_idLogIndex,
//                                                                    LogMessageCode::lmcFeedConnection_ProcessMessage,
//                                                                    this->m_recvABuffer->BufferIndex(),
//                                                                    this->m_recvABuffer->CurrentItemIndex());
        }
        else if(this->m_type == FeedConnectionType::InstrumentDefinition) {
          //printf("%d %s %s -> %d size = %d\n", socketManager->Socket(), this->m_channelName, this->m_idName, msgSeqNum, size);
//        BinaryLogItem *item = DefaultLogManager::Default->WriteFast(this->m_idLogIndex,
//                                                                    LogMessageCode::lmcFeedConnection_ProcessMessage,
//                                                                    this->m_recvABuffer->BufferIndex(),
//                                                                    this->m_recvABuffer->CurrentItemIndex());
            if(this->m_idfStartMsgSeqNo == 0)
                this->m_idfStartMsgSeqNo = msgSeqNum;
            if(this->m_idfMaxMsgSeqNo == 0)
                this->m_idfMaxMsgSeqNo = TryGetSecurityDefinitionTotNumReports(this->m_recvABuffer->CurrentPos());
        }
        else if(this->m_type == FeedConnectionType::InstrumentStatus) {
            if(this->m_endMsgSeqNum < msgSeqNum)
                this->m_endMsgSeqNum = msgSeqNum;
            if(this->m_startMsgSeqNum == -1)
                this->m_startMsgSeqNum = msgSeqNum;
        }
        else {
            //printf("%d  %s -> %d size = %d\n", socketManager->Socket(), this->m_idName, msgSeqNum, size);
//            BinaryLogItem *item = DefaultLogManager::Default->WriteFast(this->m_idLogIndex,
//                                                                    LogMessageCode::lmcFeedConnection_ProcessMessage,
//                                                                    this->m_recvABuffer->BufferIndex(),
//                                                                    this->m_recvABuffer->CurrentItemIndex());
            if(this->m_startMsgSeqNum == -1)
                this->m_startMsgSeqNum = msgSeqNum;
            if(this->m_endMsgSeqNum < msgSeqNum)
                this->m_endMsgSeqNum = msgSeqNum;
            if(this->m_endMsgSeqNum - msgSeqNum > 100) {
                if(this->m_snapshotRouteFirst != -1)
                    this->ClearPackets(this->m_snapshotRouteFirst, this->m_startMsgSeqNum);
                this->ClearPackets(this->m_startMsgSeqNum, this->m_endMsgSeqNum);
                this->m_startMsgSeqNum = msgSeqNum;
                this->m_endMsgSeqNum = msgSeqNum;
            }
            if(msgSeqNum < this->m_startMsgSeqNum)
                return false;
        }
        return true;
    }
    inline FeedConnectionMessageInfo* Packet(int index) { return this->m_packets[index - this->m_windowMsgSeqNum]; }
    inline bool ProcessServerCore_FromHistoricalReplay(SocketBuffer *buffer, int size, int msgSeqNum) {
        if(this->m_type == FeedConnectionType::InstrumentDefinition)
            this->m_endMsgSeqNum = msgSeqNum;

        if(msgSeqNum < this->m_windowMsgSeqNum)
            return false;

        FeedConnectionMessageInfo *info = this->Packet(msgSeqNum);
        if(info->m_address != 0)
            return true;

        buffer->SetCurrentItemSize(size);

//        BinaryLogItem *item = DefaultLogManager::Default->WriteFast(this->m_idLogIndex,
//                                                                    LogMessageCode::lmcFeedConnection_ProcessMessage,
//                                                                    buffer->BufferIndex(),
//                                                                    buffer->CurrentItemIndex());
        if(!this->UpdateMsgSeqStartEnd(msgSeqNum))
            return true;
        info->m_address = buffer->CurrentPos();
        info->m_size = size;
        info->m_requested = true;
        return true;
    }
    inline bool ProcessServerCore(WinSockManager *socketManager, int size) {
        int msgSeqNum = *((UINT*)this->m_recvABuffer->CurrentPos());
        if(this->m_type == FeedConnectionType::InstrumentDefinition)
            this->m_endMsgSeqNum = msgSeqNum;

        if(msgSeqNum < this->m_windowMsgSeqNum)
            return false;

        FeedConnectionMessageInfo *info = this->Packet(msgSeqNum);
        if(info->m_address != 0)
            return true;

        this->m_recvABuffer->SetCurrentItemSize(size);

        if(!this->UpdateMsgSeqStartEnd(msgSeqNum))
            return true;
        info->m_address = this->m_recvABuffer->CurrentPos();
        info->m_size = size;
        info->m_requested = false;
        this->m_recvABuffer->Next(size);
        return true;
    }
    inline bool ProcessServer(WinSockManager *socketManager, LogMessageCode socketName) {
        if(!socketManager->ShouldRecv())
            return false;
        if(!socketManager->Recv(this->m_recvABuffer->CurrentPos())) {
            DefaultLogManager::Default->WriteSuccess(socketName,
                                                     LogMessageCode::lmcFeedConnection_Listen_Atom,
                                                     false)->m_errno = errno;
            socketManager->Reconnect();
            return false;
        }
        int size = socketManager->RecvSize();
        if(size == 0)
            return false;
        return this->ProcessServerCore(socketManager, size);
    }

    inline bool HasQueueEntries() {
        if(this->m_orderTableFond != 0)
            return this->m_orderTableFond->HasQueueEntries();
        else if(this->m_orderTableCurr != 0)
            return this->m_orderTableCurr->HasQueueEntries();
        else if(this->m_tradeTableFond != 0)
            return this->m_tradeTableFond->HasQueueEntries();
        else if(this->m_tradeTableCurr != 0)
            return this->m_tradeTableCurr->HasQueueEntries();
        return false;
    }

    inline bool ShouldRestoreIncrementalMessages() {
        if(this->m_doNotCheckIncrementalActuality)
            return false;
        return this->HasPotentiallyLostPackets() || this->HasQueueEntries();
    }

    inline bool CanStopListeningSnapshot() {
        return this->SymbolsToRecvSnapshotCount() == 0 && !this->HasQueueEntries();
    }
#pragma region snapshot
    inline bool PrepareDecodeSnapshotMessage(int packetIndex) {
        FeedConnectionMessageInfo *info = this->m_packets[packetIndex];
        unsigned char *buffer = info->m_address;
        if(this->ShouldSkipMessage(buffer, !info->m_requested))
            return false;
        this->m_fastProtocolManager->SetNewBuffer(buffer, info->m_size);
        this->m_fastProtocolManager->ReadMsgSeqNumber();
        this->m_fastProtocolManager->DecodeHeader();
        return true;
    }

    inline bool StartApplySnapshot_OLS_FOND() {
        this->m_incremental->OrderFond()->ObtainSnapshotItem(this->m_lastSnapshotInfo);
        if(this->m_incremental->OrderFond()->ApplyQuickSnapshot(this->m_lastSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->IncFondOlsProcessedCount();
            ProgramStatistics::Total->IncFondOlsProcessedCount();
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->OrderFond()->StartProcessSnapshot();
        this->ApplySnapshotPart_OLS_FOND(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_OLS_FOND(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncFondOlsProcessedCount();
        ProgramStatistics::Total->IncFondOlsProcessedCount();
#endif
        FastOLSFONDInfo *info = (FastOLSFONDInfo *) this->m_fastProtocolManager->DecodeOLSFOND();
        this->m_incremental->OrderFond()->ProcessSnapshot(info);
        info->ReleaseUnused();
        return true;
    }

    inline bool EndApplySnapshot_OLS_FOND() {
        this->m_incremental->OrderFond()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_OLS_FOND() {
        this->m_incremental->OrderFond()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_OLS_CURR() {
        this->m_incremental->OrderCurr()->ObtainSnapshotItem(this->m_lastSnapshotInfo);
        if(this->m_incremental->OrderCurr()->ApplyQuickSnapshot(this->m_lastSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->IncCurrOlsProcessedCount();
            ProgramStatistics::Total->IncCurrOlsProcessedCount();
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->OrderCurr()->StartProcessSnapshot();
        this->ApplySnapshotPart_OLS_CURR(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_OLS_CURR(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncCurrOlsProcessedCount();
        ProgramStatistics::Total->IncCurrOlsProcessedCount();
#endif
        FastOLSCURRInfo *info = (FastOLSCURRInfo *) this->m_fastProtocolManager->DecodeOLSCURR();
        this->m_incremental->OrderCurr()->ProcessSnapshot(info);
        info->ReleaseUnused();
        return true;
    }

    inline bool EndApplySnapshot_OLS_CURR() {
        this->m_incremental->OrderCurr()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_OLS_CURR() {
        this->m_incremental->OrderCurr()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_TLS_FOND() {
        this->m_incremental->TradeFond()->ObtainSnapshotItem(this->m_lastSnapshotInfo);
        if(this->m_incremental->TradeFond()->ApplyQuickSnapshot(this->m_lastSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->IncFondTlsProcessedCount();
            ProgramStatistics::Total->IncFondTlsProcessedCount();
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->TradeFond()->StartProcessSnapshot();
        this->ApplySnapshotPart_TLS_FOND(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_TLS_FOND(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncFondTlsProcessedCount();
        ProgramStatistics::Total->IncFondTlsProcessedCount();
#endif
        FastTLSFONDInfo *info = (FastTLSFONDInfo *) this->m_fastProtocolManager->DecodeTLSFOND();
        this->m_incremental->TradeFond()->ProcessSnapshot(info);
        info->ReleaseUnused();
        return true;
    }

    inline bool EndApplySnapshot_TLS_FOND() {
        this->m_incremental->TradeFond()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_TLS_FOND() {
        this->m_incremental->TradeFond()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_TLS_CURR() {
        this->m_incremental->TradeCurr()->ObtainSnapshotItem(this->m_lastSnapshotInfo);
        if(this->m_incremental->TradeCurr()->ApplyQuickSnapshot(this->m_lastSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->IncCurrTlsProcessedCount();
            ProgramStatistics::Total->IncCurrTlsProcessedCount();
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->TradeCurr()->StartProcessSnapshot();
        this->ApplySnapshotPart_TLS_CURR(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_TLS_CURR(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncCurrTlsProcessedCount();
        ProgramStatistics::Total->IncCurrTlsProcessedCount();
#endif
        FastTLSCURRInfo *info = (FastTLSCURRInfo *) this->m_fastProtocolManager->DecodeTLSCURR();
        this->m_incremental->TradeCurr()->ProcessSnapshot(info);
        info->ReleaseUnused();
        return true;
    }

    inline bool EndApplySnapshot_TLS_CURR() {
        this->m_incremental->TradeCurr()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_TLS_CURR() {
        this->m_incremental->TradeCurr()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_MSS_FOND() {
        this->m_incremental->StatisticFond()->ObtainSnapshotItem(this->m_lastSnapshotInfo);
        if(this->m_incremental->StatisticFond()->ApplyQuickSnapshot(this->m_lastSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->IncFondMssProcessedCount();
            ProgramStatistics::Total->IncFondMssProcessedCount();
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->StatisticFond()->StartProcessSnapshot();
        this->ApplySnapshotPart_MSS_FOND(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_MSS_FOND(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncFondMssProcessedCount();
        ProgramStatistics::Total->IncFondMssProcessedCount();
#endif
        FastGenericInfo *info = (FastGenericInfo *) this->m_fastProtocolManager->DecodeGeneric();
        this->m_incremental->StatisticFond()->ProcessSnapshot(info);
        info->ReleaseUnused();
        return true;
    }

    inline bool EndApplySnapshot_MSS_FOND() {
        this->m_incremental->StatisticFond()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_MSS_FOND() {
        this->m_incremental->StatisticFond()->CancelSnapshot();
        return true;
    }

    inline bool StartApplySnapshot_MSS_CURR() {
        this->m_incremental->StatisticCurr()->ObtainSnapshotItem(this->m_lastSnapshotInfo);
        if(this->m_incremental->StatisticCurr()->ApplyQuickSnapshot(this->m_lastSnapshotInfo)) {
#ifdef COLLECT_STATISTICS
            ProgramStatistics::Current->IncCurrMssProcessedCount();
            ProgramStatistics::Total->IncCurrMssProcessedCount();
#endif
            return false; // skip all the snapshot
        }
        this->m_incremental->StatisticCurr()->StartProcessSnapshot();
        this->ApplySnapshotPart_MSS_CURR(this->m_snapshotRouteFirst);
        return true;
    }

    inline bool ApplySnapshotPart_MSS_CURR(int index) {
        this->PrepareDecodeSnapshotMessage(index);
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncCurrMssProcessedCount();
        ProgramStatistics::Total->IncCurrMssProcessedCount();
#endif
        FastGenericInfo *info = (FastGenericInfo *) this->m_fastProtocolManager->DecodeGeneric();
        this->m_incremental->StatisticCurr()->ProcessSnapshot(info);
        info->ReleaseUnused();
        return true;
    }

    inline bool EndApplySnapshot_MSS_CURR() {
        this->m_incremental->StatisticCurr()->EndProcessSnapshot();
        return true;
    }

    inline bool CancelApplySnapshot_MSS_CURR() {
        this->m_incremental->StatisticCurr()->CancelSnapshot();
        return true;
    }
    
#pragma endregion

    inline int GetRequestMessageEndIndex(int start) {
        int end = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;
        for(int i = start - this->m_windowMsgSeqNum; i <= end; i++) {
            if(this->m_packets[i]->m_address != 0)
                return i + this->m_windowMsgSeqNum - 1;
        }
        return start;
    }

    inline int GetRequestMessageStartIndex(int start) {
        int end = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;
        for(int i = start - this->m_windowMsgSeqNum; i <= end; i++) {
            if(this->m_packets[i]->m_address == 0 && !this->m_packets[i]->m_requested)
                return i + this->m_windowMsgSeqNum;
        }
        return this->m_endMsgSeqNum + 1;
    }

    inline void RequestMessages(int start, int end) {
        FeedConnectionMessageInfo **info = this->m_packets + start - this->m_windowMsgSeqNum;
        for(int i = start; i <= end; i++, info++)
            (*info)->m_requested = true;
        printf("request messages from %d to %d\n", start, end);
        this->m_historicalReplay->HrRequestMessage(this, start, end);
    }

    inline void StartSecurityStatusSnapshot() {
        this->m_securityDefinition->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmUpdateData;
        this->m_securityDefinition->IdfStopAfterUpdateMessages(true);
        this->m_securityDefinition->Start();
        this->m_securityStatusSnapshotActive = true;
        this->m_isfStartSnapshotCount++;
    }

    inline void FinishSecurityStatusSnapshot() {
        this->m_securityDefinition->Stop();
        this->m_securityStatusSnapshotActive = false;
    }

    inline bool IsSecurityStatusSnapshotActive() { return this->m_securityStatusSnapshotActive; }

    inline bool ShouldStartSecurityStatusSnapshot(int endIndex) {
        if(this->m_securityStatusSnapshotActive)
            return false;
        if(this->m_securityDefinition->m_state != FeedConnectionState::fcsSuspend)
            return false;
        if(endIndex - this->m_requestMessageStartIndex < this->m_maxLostPacketCountForStartSnapshot)
            return false;
        return true;
    }

    inline bool ShouldStartIncrementalSnapshot(int endIndex) {
        return (endIndex - this->m_requestMessageStartIndex + 1) >= this->m_maxLostPacketCountForStartSnapshot;
    }

    inline bool CheckRequestLostIncrementalMessages() {
        if(this->m_requestMessageStartIndex == -1)
            return false;
        if(this->m_snapshot->State() != FeedConnectionState::fcsSuspend)
            return true;
        //printf("start request %d, end %d\n", this->m_requestMessageStartIndex, this->m_endMsgSeqNum);
        while(this->m_requestMessageStartIndex <= this->m_endMsgSeqNum) {
            this->m_requestMessageStartIndex = GetRequestMessageStartIndex(this->m_requestMessageStartIndex);
            if(this->m_requestMessageStartIndex > this->m_endMsgSeqNum)
                return true;
            printf("request start = %d\n", this->m_requestMessageStartIndex);
            int endIndex = GetRequestMessageEndIndex(this->m_requestMessageStartIndex);
            printf("request end = %d\n", this->m_requestMessageStartIndex);
            if(ShouldStartIncrementalSnapshot(endIndex)) {
                this->m_requestMessageStartIndex = -1;
                return this->StartListenSnapshot();
            }
            this->RequestMessages(this->m_requestMessageStartIndex, endIndex);
            this->m_requestMessageStartIndex = endIndex + 1;
        }
        return true;
    }

    inline void CheckRequestLostSecurityStatusMessages() {
        if(this->m_securityStatusSnapshotActive)
            return;
        if(this->m_requestMessageStartIndex == -1)
            return;
        while(this->m_requestMessageStartIndex <= this->m_endMsgSeqNum) {
            this->m_requestMessageStartIndex = GetRequestMessageStartIndex(this->m_requestMessageStartIndex);
            if(this->m_requestMessageStartIndex > this->m_endMsgSeqNum)
                break;
            int endIndex = GetRequestMessageEndIndex(this->m_requestMessageStartIndex);
            printf("security status: request %d-%d\n", this->m_requestMessageStartIndex, endIndex);
            printf("start %d end %d \n", this->m_startMsgSeqNum, this->m_endMsgSeqNum);
            if(ShouldStartSecurityStatusSnapshot(endIndex))
                this->StartSecurityStatusSnapshot();
            else if(!IsSecurityStatusSnapshotActive())
                this->RequestMessages(this->m_requestMessageStartIndex, endIndex);
            this->m_requestMessageStartIndex = endIndex + 1;
        }
    }

    inline bool ProcessSecurityStatusMessages() {


        if(this->m_securityStatusSnapshotActive) {
            if(this->m_securityDefinition->IsIdfDataCollected()) {
                this->FinishSecurityStatusSnapshot();
            }
        }

        int end = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;
        int i = this->m_startMsgSeqNum - this->m_windowMsgSeqNum;

        while(i <= end) {
            if(this->m_packets[i]->m_processed) {
                i++; continue;
            }
            if(this->m_packets[i]->m_address == 0) {
                if(this->m_securityStatusSnapshotActive) {
                    i++; continue;
                }
                if(this->m_requestMessageStartIndex < i + this->m_windowMsgSeqNum)
                    this->m_requestMessageStartIndex = i + this->m_windowMsgSeqNum;
                break;
            }
            if(!this->ProcessSecurityStatus(this->m_packets[i]))
                return false;
            i++;
        }

        // there is messages that needs to be requested
        this->CheckRequestLostSecurityStatusMessages();

        this->m_startMsgSeqNum = i + this->m_windowMsgSeqNum;
        return true;
    }

    inline bool ProcessIncrementalMessages() {
		int localStart = this->m_startMsgSeqNum - this->m_windowMsgSeqNum;
        int localEnd = this->m_endMsgSeqNum - this->m_windowMsgSeqNum;
        int i = localStart;

        int newStartMsgSeqNum = -1;

        while(i <= localEnd) {
            if(this->m_packets[i]->m_processed) {
                i++; continue;
            }
            if(this->m_packets[i]->m_address == 0) {
                if(this->m_requestMessageStartIndex < i + this->m_windowMsgSeqNum)
                    this->m_requestMessageStartIndex = i + this->m_windowMsgSeqNum;
                newStartMsgSeqNum = i + this->m_windowMsgSeqNum;
                break;
            }
            if(!this->ProcessIncremental(this->m_packets[i]))
                return false;
            i++;
        }

        while(i <= localEnd) {
            if(this->m_packets[i]->m_processed || this->m_packets[i]->m_address == 0) {
                i++; continue;
            }
            if(!this->ProcessIncremental(this->m_packets[i]))
                return false;
            i++;
        }
        if(newStartMsgSeqNum != -1) {
            this->m_startMsgSeqNum = newStartMsgSeqNum;
        }
        else {
            this->ClearLocalPackets(0, localEnd);
            this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
            this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
        }
        return true;
    }
    inline void MarketTableEnterSnapshotMode() {
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->EnterSnapshotMode();
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->EnterSnapshotMode();
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_tradeTableFond->EnterSnapshotMode();
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_tradeTableCurr->EnterSnapshotMode();
            return;
        }
        if(this->m_statTableFond != 0) {
            this->m_statTableFond->EnterSnapshotMode();
            return;
        }
        if(this->m_statTableCurr != 0) {
            this->m_statTableCurr->EnterSnapshotMode();
            return;
        }
    }
    inline int SymbolsToRecvSnapshotCount() {
        if(this->m_orderTableFond != 0)
            return this->m_orderTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_orderTableCurr != 0)
            return this->m_orderTableCurr->SymbolsToRecvSnapshotCount();
        if(this->m_tradeTableFond != 0)
            return this->m_tradeTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_tradeTableCurr != 0)
            return this->m_tradeTableCurr->SymbolsToRecvSnapshotCount();
        if(this->m_statTableFond != 0)
            return this->m_statTableFond->SymbolsToRecvSnapshotCount();
        if(this->m_statTableCurr != 0)
            return this->m_statTableCurr->SymbolsToRecvSnapshotCount();
        return 0;
    }
    inline bool IsMarketTableInSnapshotMode() {
        if(this->m_orderTableFond != 0)
            return this->m_orderTableFond->SnapshotMode();
        if(this->m_orderTableCurr != 0)
            return this->m_orderTableCurr->SnapshotMode();
        if(this->m_tradeTableFond != 0)
            return this->m_tradeTableFond->SnapshotMode();
        if(this->m_tradeTableCurr != 0)
            return this->m_tradeTableCurr->SnapshotMode();
        if(this->m_statTableFond != 0)
            return this->m_statTableFond->SnapshotMode();
        if(this->m_statTableCurr != 0)
            return this->m_statTableCurr->SnapshotMode();
        return false;
    }
    inline void MarketTableExitSnapshotMode() {
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->ExitSnapshotMode();
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_tradeTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_tradeTableCurr->ExitSnapshotMode();
            return;
        }
        if(this->m_statTableFond != 0) {
            this->m_statTableFond->ExitSnapshotMode();
            return;
        }
        if(this->m_statTableCurr != 0) {
            this->m_statTableCurr->ExitSnapshotMode();
            return;
        }
    }
    inline bool StartListenSnapshot() {
		if(this->m_snapshot->State() == FeedConnectionState::fcsListenSnapshot && this->IsMarketTableInSnapshotMode())
            return true;
        if(!this->m_snapshot->Start()) {
			DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, false);
			return false;
		}
        this->MarketTableEnterSnapshotMode();
        this->m_snapshot->StartNewSnapshot();
		DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, true);
        return true;
	}
    inline void UpdateMessageSeqNoAfterSnapshot() {
        this->ClearLocalPackets(0, GetLocalIndex(this->m_endMsgSeqNum));
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        this->m_windowMsgSeqNum = this->m_startMsgSeqNum;
    }
	inline bool StopListenSnapshot() {
        if(!this->m_snapshot->Stop()) {
			DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, false);
			return false;
		}
        this->MarketTableExitSnapshotMode();
		this->UpdateMessageSeqNoAfterSnapshot();
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, true);
		return true;
	}
	inline FastSnapshotInfo* GetSnapshotInfo(int msgSeqNo) {
		FeedConnectionMessageInfo *item = this->m_packets[msgSeqNo];
		unsigned char *buffer = item->m_address;
		if(this->ShouldSkipMessage(buffer, !item->m_requested))
            return 0;
        this->m_fastProtocolManager->SetNewBuffer(buffer, item->m_size);
		this->m_fastProtocolManager->ReadMsgSeqNumber();
		return this->m_fastProtocolManager->GetSnapshotInfo();
	}

    inline void ResetWaitTime() { this->m_waitTimer->Start(); }
    inline bool ActualMsgSeqNum() { return this->m_startMsgSeqNum == this->m_endMsgSeqNum; }

	inline void IncrementMsgSeqNo() { this->m_startMsgSeqNum++; }
	virtual ISocketBufferProvider* CreateSocketBufferProvider() {
			return new SocketBufferProvider(DefaultSocketBufferManager::Default,
											RobotSettings::Default->DefaultFeedConnectionSendBufferSize,
											RobotSettings::Default->DefaultFeedConnectionSendItemsCount,
											RobotSettings::Default->DefaultFeedConnectionRecvBufferSize,
											RobotSettings::Default->DefaultFeedConnectionRecvItemsCount);
	}
	virtual void ClearSocketBufferProvider() {

	}
    void SetMaxReconnectCount(int value) { this->m_maxReconnectCount = value; }
    void SetMaxLostPacketCountForStartSnapshot(int count) { this->m_maxLostPacketCountForStartSnapshot = count; }
    int MaxLostPacketCountForStartSnapshot() { return this->m_maxLostPacketCountForStartSnapshot; }
	inline void SetState(FeedConnectionState state) { this->m_state = state; }
    inline void SetId(FeedConnectionId id) { this->m_id = id; }
    inline void SetHsState(FeedConnectionHistoricalReplayState state) { this->m_hsState = state; }
	inline void SetNextState(FeedConnectionState state) {
		this->m_nextState = state;
		this->m_shouldUseNextState = true;
	}

    FastSnapshotInfo *m_lastSnapshotInfo;
    inline int GetLocalIndex(int msgSeqNo) { return msgSeqNo - this->m_windowMsgSeqNum; }
    inline int LocalIndexToMsgSeqNo(int index) { return index + this->m_windowMsgSeqNum; }
    inline bool FindRouteFirst() {
        for(int i = this->m_startMsgSeqNum; i <= this->m_endMsgSeqNum; i++) {
            if (this->m_packets[i]->m_address == 0) {
                this->m_startMsgSeqNum = i;
                return false;
            }
            this->m_lastSnapshotInfo = this->GetSnapshotInfo(i);
            if (this->m_lastSnapshotInfo != 0 && this->m_lastSnapshotInfo->RouteFirst == 1) {
                this->m_startMsgSeqNum = i;
                this->m_snapshotRouteFirst = i;
                return true;
            }
            this->m_packets[i]->Clear();
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
        return false;
    }

    inline bool StartApplySnapshot() {
        switch(this->m_lastSnapshotInfo->TemplateId) {
            case FeedConnectionMessage::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->StartApplySnapshot_MSS_FOND();
                    case FeedConnectionId::fcidMssCurr:
                        return this->StartApplySnapshot_MSS_CURR();
                    default:
                        return false;
                }
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
                return this->StartApplySnapshot_OLS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
                return this->StartApplySnapshot_OLS_CURR();
            case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
                return this->StartApplySnapshot_TLS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_TLS_CURR:
                return this->StartApplySnapshot_TLS_CURR();
            default:
                return false;
        }
    }

    inline bool EndApplySnapshot() {
        switch(this->m_lastSnapshotInfo->TemplateId) {
            case FeedConnectionMessage::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->EndApplySnapshot_MSS_FOND();
                    case FeedConnectionId::fcidMssCurr:
                        return this->EndApplySnapshot_MSS_CURR();
                    default:
                        return false;
                }
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
                return this->EndApplySnapshot_OLS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
                return this->EndApplySnapshot_OLS_CURR();
            case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
                return this->EndApplySnapshot_TLS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_TLS_CURR:
                return this->EndApplySnapshot_TLS_CURR();
            default:
                return false;
        }
    }

    inline bool CancelSnapshot() {
        switch(this->m_lastSnapshotInfo->TemplateId) {
            case FeedConnectionMessage::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->CancelApplySnapshot_MSS_FOND();
                    case FeedConnectionId::fcidMssCurr:
                        return this->CancelApplySnapshot_MSS_CURR();
                    default:
                        return false;
                }
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
                return this->CancelApplySnapshot_OLS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
                return this->CancelApplySnapshot_OLS_CURR();
            case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
                return this->CancelApplySnapshot_TLS_FOND();
            case FeedConnectionMessage::fmcFullRefresh_TLS_CURR:
                return this->CancelApplySnapshot_TLS_CURR();
            default:
                return false;
        }
    }

    inline bool ApplySnapshotPart(int index) {
        switch(this->m_lastSnapshotInfo->TemplateId) {
            case FeedConnectionMessage::fmcFullRefresh_Generic:
                switch(this->m_id) {
                    case FeedConnectionId::fcidMssFond:
                        return this->ApplySnapshotPart_MSS_FOND(index);
                    case FeedConnectionId::fcidMssCurr:
                        return this->ApplySnapshotPart_MSS_CURR(index);
                    default:
                        return false;
                }
                break;
            case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
                return this->ApplySnapshotPart_OLS_FOND(index);
            case FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
                return this->ApplySnapshotPart_OLS_CURR(index);
            case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
                return this->ApplySnapshotPart_TLS_FOND(index);
            case FeedConnectionMessage::fmcFullRefresh_TLS_CURR:
                return this->ApplySnapshotPart_TLS_CURR(index);
            default:
                return false;
        }
    }

    inline bool TryFindAndApplySnapshotContinuously() {
        if(this->m_snapshotRouteFirst == -1) {
            if(!FindRouteFirst())
                return false;
            if(!StartApplySnapshot()) {
                this->m_packets[this->m_snapshotRouteFirst]->Clear();
                this->m_snapshotRouteFirst = -1;
                this->m_startMsgSeqNum++;
                return true;
            }
            this->m_packets[this->m_snapshotRouteFirst]->Clear();
            if(this->m_lastSnapshotInfo->LastFragment) {
                EndApplySnapshot();
                this->m_snapshotRouteFirst = -1;
            }
            this->m_startMsgSeqNum++;
            return true;
        }
        if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
            return false;
        while(this->m_startMsgSeqNum <= this->m_endMsgSeqNum) {
            if (this->m_packets[this->m_startMsgSeqNum]->m_address == 0)
                return false;
            this->m_lastSnapshotInfo = this->GetSnapshotInfo(this->m_startMsgSeqNum);
            if(this->m_lastSnapshotInfo == 0)
                return false;
            this->ApplySnapshotPart(this->m_startMsgSeqNum);
            this->m_packets[this->m_startMsgSeqNum]->Clear();
            if(this->m_lastSnapshotInfo->LastFragment) {
                EndApplySnapshot();
                this->m_snapshotRouteFirst = -1;
                this->m_startMsgSeqNum++;
                return true;
            }
            this->m_startMsgSeqNum++;
        }
        return true;
    }

    inline bool HasPotentiallyLostPackets() {
        if(this->m_startMsgSeqNum > this->m_endMsgSeqNum)
            return false;
        return this->m_packets[GetLocalIndex(this->m_startMsgSeqNum)]->m_address == 0;
    }

    inline void UpdateLostPacketsStatistic(int count) {
        if(this->m_id == FeedConnectionId::fcidIdfCurr) {
            ProgramStatistics::Current->CurrIdfLostCount(count);
            ProgramStatistics::Total->CurrIdfLostCount(ProgramStatistics::Total->CurrIdfLostCount() + count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidIdfFond) {
            ProgramStatistics::Current->FondIdfLostCount(count);
            ProgramStatistics::Total->FondIdfLostCount(ProgramStatistics::Total->FondIdfLostCount() + count);
            return;
        }
        
        if(this->m_id == FeedConnectionId::fcidOlrCurr) {
            ProgramStatistics::Current->CurrOlrLostCount(count);
            ProgramStatistics::Total->CurrOlrLostCount(ProgramStatistics::Total->CurrOlrLostCount() + count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidOlrFond) {
            ProgramStatistics::Current->FondOlrLostCount(count);
            ProgramStatistics::Total->FondOlrLostCount(ProgramStatistics::Total->FondOlrLostCount() + count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidOlsCurr) {
            ProgramStatistics::Current->CurrOlsLostCount(count);
            ProgramStatistics::Total->CurrOlsLostCount(ProgramStatistics::Total->CurrOlsLostCount() + count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidOlsFond) {
            ProgramStatistics::Current->FondOlsLostCount(count);
            ProgramStatistics::Total->FondOlsLostCount(ProgramStatistics::Total->FondOlsLostCount() + count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidTlrCurr) {
            ProgramStatistics::Current->CurrTlrLostCount(count);
            ProgramStatistics::Total->CurrTlrLostCount(ProgramStatistics::Total->CurrTlrLostCount() + count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidTlrFond) {
            ProgramStatistics::Current->FondTlrLostCount(count);
            ProgramStatistics::Total->FondTlrLostCount(ProgramStatistics::Total->FondTlrLostCount() + count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidTlsCurr) {
            ProgramStatistics::Current->CurrTlsLostCount(count);
            ProgramStatistics::Total->CurrTlsLostCount(ProgramStatistics::Total->CurrTlsLostCount() + count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidTlsFond) {
            ProgramStatistics::Current->FondTlsLostCount(count);
            ProgramStatistics::Total->FondTlsLostCount(ProgramStatistics::Total->FondTlsLostCount() + count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidMsrCurr) {
            ProgramStatistics::Current->CurrMsrLostCount(count);
            ProgramStatistics::Total->CurrMsrLostCount(ProgramStatistics::Total->CurrMsrLostCount() + count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidMsrFond) {
            ProgramStatistics::Current->FondMsrLostCount(count);
            ProgramStatistics::Total->FondMsrLostCount(ProgramStatistics::Total->FondMsrLostCount() + count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidMssCurr) {
            ProgramStatistics::Current->CurrMssLostCount(count);
            ProgramStatistics::Total->CurrMssLostCount(ProgramStatistics::Total->CurrMssLostCount() + count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidMssFond) {
            ProgramStatistics::Current->FondMssLostCount(count);
            ProgramStatistics::Total->FondMssLostCount(ProgramStatistics::Total->FondMssLostCount() + count);
            return;
        }

        if(this->m_id == FeedConnectionId::fcidIsfCurr) {
            ProgramStatistics::Current->CurrIssLostCount(count);
            ProgramStatistics::Total->CurrIssLostCount(ProgramStatistics::Total->CurrIssLostCount() + count);
            return;
        }
        if(this->m_id == FeedConnectionId::fcidIsfFond) {
            ProgramStatistics::Current->FondIssLostCount(count);
            ProgramStatistics::Total->FondIssLostCount(ProgramStatistics::Total->FondIssLostCount() + count);
            return;
        }
    }

    inline void SkipLostPackets() {
        int localStart = GetLocalIndex(this->m_startMsgSeqNum);
        int localEnd = GetLocalIndex(this->m_endMsgSeqNum);
        for(int i = localStart; i <= localEnd; i++) {
            if(this->m_packets[i]->m_address != 0) {
#ifdef COLLECT_STATISTICS
                this->UpdateLostPacketsStatistic(i - localStart);
#endif
                this->m_startMsgSeqNum = LocalIndexToMsgSeqNo(i);
                return;
            }
        }
        this->m_startMsgSeqNum = this->m_endMsgSeqNum + 1;
    }

    inline void ClearPackets(int start, int end) {
        FeedConnectionMessageInfo **info = (this->m_packets + start - this->m_windowMsgSeqNum);
        for(int i = start; i <= end; i++, info++) {
            (*info)->Clear();
        }
    }

    inline void ClearLocalPackets(int start, int end) {
        FeedConnectionMessageInfo **info = (this->m_packets + start);
        for(int i = start; i <= end; i++, info++) {
            (*info)->Clear();
        }
    }

    inline bool ProcessSecurityDefinitionCore(unsigned char *buffer, int length) {
        this->m_fastProtocolManager->SetNewBuffer(buffer, length);
        this->m_fastProtocolManager->ReadMsgSeqNumber();

        this->m_fastProtocolManager->DecodeHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedConnectionMessage::fmcSecurityDefinition) {
            printf("not an security definition template: %d\n", this->m_fastProtocolManager->TemplateId());
            return true;
        }
        return this->ProcessSecurityDefinition((FastSecurityDefinitionInfo*)this->m_fastProtocolManager->DecodeSecurityDefinition());
    }

    inline bool ProcessSecurityDefinition(unsigned char *buffer, int length) {
        //DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
        bool res = this->ProcessSecurityDefinitionCore(buffer, length);
        //DefaultLogManager::Default->EndLog(res);
        return res;
    }

    inline bool ProcessSecurityDefinition(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = info->m_address;
        if(this->ShouldSkipMessage(buffer, !info->m_requested)) {
            info->m_processed = true;
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }

        //DefaultLogManager::Default->WriteFast(this->m_idLogIndex, this->m_recvABuffer->BufferIndex(), info->m_item->m_itemIndex);
        info->m_processed = true;
        return this->ProcessSecurityDefinition(buffer, info->m_size);
    }

    inline bool IdfAllowGenerateSecurityDefinitions() { return this->m_allowGenerateSecurityDefinitions; }
    inline void IdfAllowGenerateSecurityDefinitions(bool value) { this->m_allowGenerateSecurityDefinitions = value; }

    inline void OnCollectAllSecurityDefinitions() {
        this->m_idfDataCollected = true;
    };

    inline bool ProcessSecurityDefinitionMessagesFromStart() {
        if(this->m_idfMode == FeedConnectionSecurityDefinitionMode::sdmUpdateData) {
            FeedConnectionMessageInfo *info = this->Packet(this->m_endMsgSeqNum);
            this->UpdateSecurityDefinition(info);
            info->Clear();
            if(this->m_endMsgSeqNum == this->m_idfStartMsgSeqNo) {
                this->OnSecurityDefinitionUpdateAllMessages();
            }
        }
        else {
            if (this->m_endMsgSeqNum == this->m_idfStartMsgSeqNo) {
                if (this->HasLostPackets(1, this->m_idfMaxMsgSeqNo)) {
                    int lostPacketCount = CalcLostPacketCount(1, this->m_idfMaxMsgSeqNo);
#ifdef COLLECT_STATISTICS
                    if(this->m_id == FeedConnectionId::fcidIdfFond)
                        ProgramStatistics::Total->FondIdfProcessedCount(this->m_idfMaxMsgSeqNo - lostPacketCount);
                    else
                        ProgramStatistics::Total->CurrIdfProcessedCount(this->m_idfMaxMsgSeqNo - lostPacketCount);
#endif
                    printf("\t\t%s %s lost packet count = %d\n", this->m_channelName, this->m_idName, lostPacketCount); // TODOO remove debug
                    this->m_idfState = FeedConnectionSecurityDefinitionState::sdsProcessToEnd;
                    return true;
                }
#ifdef COLLECT_STATISTICS
                if(this->m_id == FeedConnectionId::fcidIdfFond)
                    ProgramStatistics::Total->FondIdfProcessedCount(this->m_idfMaxMsgSeqNo);
                else
                    ProgramStatistics::Total->CurrIdfProcessedCount(this->m_idfMaxMsgSeqNo);
#endif
                if(this->IdfAllowGenerateSecurityDefinitions())
                    this->GenerateSecurityDefinitions();
                else
                    this->OnCollectAllSecurityDefinitions();
            }
        }
        return true;
    }

    inline bool ProcessSecurityDefinitionMessagesToEnd() {
        if(this->m_endMsgSeqNum == this->m_idfMaxMsgSeqNo)
            this->m_idfState = FeedConnectionSecurityDefinitionState::sdsProcessFromStart;
        if(this->m_idfMode == FeedConnectionSecurityDefinitionMode::sdmUpdateData) {
            FeedConnectionMessageInfo *info = this->Packet(this->m_endMsgSeqNum);
            this->UpdateSecurityDefinition(info);
            info->Clear();
        }
        return true;
    }

    inline bool Listen_Atom_SecurityDefinition_Core() {
#ifdef COLLECT_STATISTICS
        if(this->m_id == FeedConnectionId::fcidIdfFond)
            ProgramStatistics::Current->FondIdfProcessedCount(this->m_endMsgSeqNum);
        else
            ProgramStatistics::Current->CurrIdfProcessedCount(this->m_endMsgSeqNum);
#endif
        if(this->m_idfState == FeedConnectionSecurityDefinitionState::sdsProcessToEnd)
            return this->ProcessSecurityDefinitionMessagesToEnd();
        return this->ProcessSecurityDefinitionMessagesFromStart();
    }

    inline bool Listen_Atom_Snapshot_Core() {
        if(this->m_startMsgSeqNum == -1)
            return true;

        if(this->HasPotentiallyLostPackets()) {
            this->m_waitTimer->Activate(1);
        }
        else
            this->m_waitTimer->Stop(1);
        if(this->m_waitTimer->IsElapsedMilliseconds(1, this->WaitSnapshotMaxTimeMs()) ||
                this->m_endMsgSeqNum - this->m_startMsgSeqNum > 5) {
            if(this->m_snapshotRouteFirst != -1) {
                this->CancelSnapshot();
                //this->ClearPackets(this->m_snapshotRouteFirst, this->m_startMsgSeqNum);
            }
            this->SkipLostPackets();
            this->m_waitTimer->Stop(1);
            this->m_snapshotRouteFirst = -1;
            this->m_snapshotLastFragment = -1;
        }

        int snapshotCount = 0;
        while(TryFindAndApplySnapshotContinuously())
            snapshotCount++;

        return true;
    }

    inline bool Listen_Atom_Incremental_Core() {

#ifndef TEST
        // TODO remove hack. just skip 30 messages and then try to restore
        // Skip this hack when testing :)
        if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend &&
                (this->m_endMsgSeqNum % 500) < 40) {
            this->Packet(this->m_endMsgSeqNum)->m_address = 0; // force historical replay
            printf("packet %d is lost, requestIndexd = %d\n", this->m_endMsgSeqNum, this->m_requestMessageStartIndex);
            return true;
        }
#endif

        if(!this->ProcessIncrementalMessages())
            return false;
        if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend) {
            if(!this->ShouldRestoreIncrementalMessages()) {
                this->m_waitTimer->Stop();
                return true;
            }
            this->m_waitTimer->Activate();
            if(this->m_waitTimer->ElapsedMilliseconds() >= this->m_waitIncrementalMaxTimeMs) {
                if(!this->CheckRequestLostIncrementalMessages())
                    return false;
                this->m_waitTimer->Stop();
            }
        }
        else {
            //printf("%d que entries and %d symbols to go\n", this->OrderCurr()->QueueEntriesCount(), this->OrderCurr()->SymbolsToRecvSnapshotCount());
            if(this->CanStopListeningSnapshot()) {
                this->StopListenSnapshot();
                this->m_waitTimer->Activate();
            }
        }
        return true;
    }

    inline bool Listen_Atom_SecurityStatus_Core() {
        if(!this->ProcessSecurityStatusMessages())
            return false;
        return true;
    }

    inline bool InitializeSockets() {
        if(this->socketAManager != NULL)
            return true;
        //DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_InitializeSockets);

        this->socketAManager = new WinSockManager();
        if(this->m_id != FeedConnectionId::fcidHFond &&
                this->m_id != FeedConnectionId::fcidHCurr)
            this->socketBManager = new WinSockManager();

        //DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline bool Suspend_Atom() {
        return true;
    }

    inline bool Reconnect_Atom() {
        DefaultLogManager::Default->StartLog(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Reconnect_Atom);

#ifndef  TEST
        if(!this->socketAManager->Reconnect()) {
            DefaultLogManager::Default->EndLog(false);
            this->m_reconnectCount++;
            if(this->m_reconnectCount > this->m_maxReconnectCount)
                return false;
            return true;
        }
        if(this->protocol == FeedConnectionProtocol::UDP_IP) {
            if (!this->socketBManager->Reconnect()) {
                DefaultLogManager::Default->EndLog(false);
                this->m_reconnectCount++;
                if (this->m_reconnectCount > this->m_maxReconnectCount)
                    return false;
                return true;
            }
        }
#endif
        this->m_reconnectCount = 0;
        this->SetState(this->m_nextState);
        this->m_waitTimer->Start();
        this->m_waitTimer->Stop(1);
        this->m_startMsgSeqNum = -1;
        this->m_endMsgSeqNum = -1;
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    inline void PrepareLogonInfo() {
        this->m_hsLogonInfo->HearthBtInt = 60;
        this->m_hsLogonInfo->ShouldResetSeqNum = false;

        strcpy(this->m_hsLogonInfo->Password, HistoricalReplayPassword);
        this->m_hsLogonInfo->PassLength = HistoricalReplayPasswordLength;

        strcpy(this->m_hsLogonInfo->SenderCompID, this->m_fixProtocolManager->SenderCompId());
        this->m_hsLogonInfo->SenderCompIDLength = this->m_fixProtocolManager->SenderCompIdLength();

        strcpy(this->m_hsLogonInfo->UserName, HistoricalReplayUserName);
        this->m_hsLogonInfo->UserNameLength = HistoricalReplayUserNameLength;
    }

    //TODO Socket buffer provider
    inline bool HistoricalReplay_SendLogon() {
        this->m_fixProtocolManager->PrepareSendBuffer();
        this->m_hsLogonInfo->MsgStartSeqNo = this->m_hsMsgSeqNo;
        this->m_fixProtocolManager->CreateFastLogonMessage(this->m_hsLogonInfo);

        if(!this->Connect())
            return false;
#ifdef TEST
        WinSockManager::m_testHelper = this->m_testHelper;
#endif
        if(!this->m_fixProtocolManager->SendFix(this->socketAManager)) {
            this->Disconnect();
            return true;
        }
        this->m_fixProtocolManager->IncSendMsgSeqNo();
        this->m_hsState = FeedConnectionHistoricalReplayState::hsWaitLogon;
        this->m_hrMessageSize = 0;
        this->m_waitTimer->Stop(2);
        return true;
    }

    inline bool CanRecv() { return this->socketAManager->ShouldRecv(); }

    inline void OnProcessHistoricalReplayExpectedLogoutMessage(FastLogoutInfo *info) {
        info->Text[info->TextLength] = 0;
        printf("\t\tHistorical Replay - Logout: %s\n", info->Text);
        info->Clear();
    }

    inline void OnProcessHistoricalReplayUnexpectedLogoutMessage(const char *methodName, FastLogoutInfo *info) {
        info->Text[info->TextLength] = 0;
        printf("\t\tHistorical Replay - %s - UNEXPECTED Logout: %s\n", methodName, info->Text);
        info->Clear();
    }

    inline bool IsHrReceiveFailedProcessed() {
        bool res;
        if(this->m_hrMessageSize != 0)
            res = this->socketAManager->Recv(this->m_recvABuffer->CurrentPos() + 4);
        else
            res = this->socketAManager->Recv(this->m_recvABuffer->CurrentPos());
        if(!res) {
            this->Disconnect();
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            return true;
        }
        return false;
    }

    inline void OnHistricalReplayExceedUnsuccessfullConnectCount() {
        printf("ERROR: HistoricalReplay not working....\n");
        LinkedPointer<FeedConnectionRequestMessageInfo> *ptr = this->m_hsRequestList->Start();
        while(ptr != 0) {
            ptr->Data()->m_conn->StartListenSnapshot();
            ptr = ptr->Next();
        }
        this->m_hsRequestList->Clear();
    }

    inline void CheckReconnectHistoricalReplay() {
        this->m_waitTimer->Activate(2);
        if(this->m_waitTimer->ElapsedSeconds(2) > 9) {
            this->Disconnect();
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            this->m_waitTimer->Stop();
            printf("historical replay timeout - reconnnect.\n");
            this->m_hrUnsuccessfulConnectCount++;
            if(this->m_hrUnsuccessfulConnectCount > FeedConnection::MaxHrUnsuccessfulConnectCount) {
                this->OnHistricalReplayExceedUnsuccessfullConnectCount();
            }
        }
    }

    inline bool HistoricalReplay_WaitLogon() {
        if(!this->CanRecv()) {
            this->CheckReconnectHistoricalReplay();
            return true;
        }
        this->m_hrUnsuccessfulConnectCount = 0;
        this->m_waitTimer->Stop(2);
        if(this->IsHrReceiveFailedProcessed())
            return true;
        int size = this->socketAManager->RecvSize();
        if(size == 4) {
            this->m_hrMessageSize = *(int*)this->socketAManager->RecvBytes();
            //printf("\t\t\trecv 4 byte. value in 4 byte = %d\n", this->m_hrMessageSize); //TODO remove debug
            return true;
        }
        else {
            //printf("\t\t\tpacket size = %d\n", size); //TODO remove debug
        }
        unsigned char *buffer = this->socketAManager->RecvBytes();
        this->m_recvABuffer->Next(size);
        if(this->m_hrMessageSize == 0) {
            buffer += 4; size -= 4;
        }
        this->m_fastProtocolManager->SetNewBuffer(buffer, size);
        this->m_fastProtocolManager->DecodeHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedConnectionMessage::fmcLogon) {
            this->Disconnect();
            if(this->m_fastProtocolManager->TemplateId() == FeedConnectionMessage::fmcLogout) {
                this->OnProcessHistoricalReplayUnexpectedLogoutMessage("OnWaitLogon", (FastLogoutInfo*)this->m_fastProtocolManager->DecodeLogout());
            }
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            return true;
        }
        return this->HistoricalReplay_SendMarketDataRequest();
    }

    inline bool HistoricalReplay_SendMarketDataRequest() {
        FeedConnectionRequestMessageInfo *info = this->m_hsRequestList->Start()->Data();
        this->m_fixProtocolManager->PrepareSendBuffer();
        this->m_fixProtocolManager->CreateMarketDataRequest(info->m_conn->m_idName, 3, info->StartMsgSeqNo(), info->EndMsgSeqNo());

        if(!this->m_fixProtocolManager->SendFix(this->socketAManager)) {
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
            this->Disconnect();
            return true;
        }
        this->m_fixProtocolManager->IncSendMsgSeqNo();
        this->m_hsState = FeedConnectionHistoricalReplayState::hsRecvMessage;
        this->m_hrSizeRemain = 0;
        this->m_hrMessageSize = 0;
        this->m_waitTimer->Stop(2);
        return true;
    }

    inline bool HistoricalReplay_RecvMessage() {
        if(!this->CanRecv()) {
            this->CheckReconnectHistoricalReplay();
            return true;
        }
        this->m_hrUnsuccessfulConnectCount = 0;
        this->m_waitTimer->Stop(2);

        unsigned char *buffer = this->m_recvABuffer->CurrentPos();
        this->socketAManager->Recv(buffer + this->m_hrSizeRemain);
        this->m_hrSizeRemain += this->socketAManager->RecvSize();

        LinkedPointer<FeedConnectionRequestMessageInfo> *ptr = this->m_hsRequestList->Start();
        FeedConnectionRequestMessageInfo *msg = ptr->Data();

        while(true) {
            if(this->m_hrMessageSize == 0) {
                if(this->m_hrSizeRemain < 4)
                    break;
                this->m_hrMessageSize = *(int*)buffer;
                buffer += 4; this->m_hrSizeRemain -= 4;
                this->m_recvABuffer->NextExact(4);
            }
            if(this->m_hrSizeRemain < this->m_hrMessageSize) {
                break;
            }
            this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_hrMessageSize);
            this->m_fastProtocolManager->DecodeHeader();

            if(this->m_fastProtocolManager->TemplateId() == FeedConnectionMessage::fmcLogout) {
                if(msg->IsAllMessagesReceived()) {
                    this->OnProcessHistoricalReplayExpectedLogoutMessage((FastLogoutInfo*)this->m_fastProtocolManager->DecodeLogout());
                    this->m_hsRequestList->Remove(ptr);
                    this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
                    return this->HistoricalReplay_SendLogout();
                }
                this->OnProcessHistoricalReplayUnexpectedLogoutMessage("OnRecvMessage", (FastLogoutInfo*)this->m_fastProtocolManager->DecodeLogout());
                this->Disconnect();
                this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
                return true;
            }

            msg->IncMsgSeqNo();
            msg->m_conn->ProcessServerCore_FromHistoricalReplay(this->m_recvABuffer, this->m_hrMessageSize, msg->LastRecvMsgSeqNo());

            this->m_recvABuffer->NextExact(this->m_hrMessageSize);
            this->m_hrSizeRemain -= this->m_hrMessageSize;
            buffer += this->m_hrMessageSize;
            this->m_hrMessageSize = 0;
        }

        return true;
    }

    inline bool HistoricalReplay_SendLogout() {
        this->m_fixProtocolManager->PrepareSendBuffer();
        this->m_fixProtocolManager->CreateFastLogoutMessage("Hasta la vista baby!", 20);

        this->m_fixProtocolManager->SendFix(this->socketAManager);
        this->m_fixProtocolManager->IncSendMsgSeqNo();
        this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
        this->Disconnect();
        return true;
    }

    inline bool HistoricalReplay_Suspend() {
        if(this->m_hsRequestList->Count() == 0)
            return true;
        FeedConnectionRequestMessageInfo *info = this->m_hsRequestList->Start()->Data();
        printf("Request message [%d, %d]. Try %d. Count = %d\n", info->StartMsgSeqNo(), info->EndMsgSeqNo(), info->m_requestCount, this->m_hsRequestList->Count());
//        if(info->m_requestCount >= 5) {
//            this->m_hsRequestList->Remove(this->m_hsRequestList->Start());
//            return true;
//        }
        info->m_requestCount++;

        return this->HistoricalReplay_SendLogon();
    }

    inline bool HistoricalReplay_Atom() {
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsSuspend)
            return this->HistoricalReplay_Suspend();
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsWaitLogon)
            return this->HistoricalReplay_WaitLogon();
        if(this->m_hsState == FeedConnectionHistoricalReplayState::hsRecvMessage)
            return this->HistoricalReplay_RecvMessage();
        return true;
    }
public:
    inline SocketBuffer* SendBuffer() { return this->m_sendABuffer; }
    inline SocketBuffer* RecvBuffer() { return this->m_recvABuffer; }

    inline void HrRequestMessage(FeedConnection *conn, int start, int end) {
        if(this->m_hsRequestList->IsFull()) {
            printf("error request msg: list is full.\n");
            return;
        }
        LinkedPointer<FeedConnectionRequestMessageInfo> *ptr = this->m_hsRequestList->Pop();
        FeedConnectionRequestMessageInfo *info = ptr->Data();
        info->m_conn = conn;
        info->SetMsgSeq(start, end);
        info->m_requestCount = 0;

        this->UpdateLostPacketsStatistic(end - start + 1);
        this->m_hsRequestList->Add(ptr);
    }
    inline void HrRequestMessage(FeedConnection *conn, int msgSeqNo) {
        HrRequestMessage(conn, msgSeqNo, msgSeqNo);
    }
    inline bool GenerateSecurityDefinitions() {
        printf("\t\t%s %s generating security definitions count = %d\n", this->m_channelName, this->m_idName, this->m_idfMaxMsgSeqNo); // TODOO remove debug
        FeedConnectionMessageInfo **info = (this->m_packets + 1); // skip zero messsage
        this->m_waitTimer->Start(3); // TODOO remove debug
        this->BeforeProcessSecurityDefinitions();
        for (int i = 1; i <= this->m_idfMaxMsgSeqNo; i++, info++) {
            if (!this->ProcessSecurityDefinition(*info))
                return false;
        }
        this->AfterProcessSecurityDefinitions();
        this->OnSecurityDefinitionRecvAllMessages();
        printf("\t\t%s %s done in %ld ms.\n", this->m_channelName, this->m_idName, this->m_waitTimer->ElapsedMilliseconds(3)); // TODOO remove debug
        this->m_waitTimer->Stop(3);
        return true;
    }
protected:
    inline bool Listen_Atom_Incremental() {

        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();
        this->m_isLastIncrementalRecv = recv;

        if(!this->m_isLastIncrementalRecv) {
            this->m_waitTimer->Activate(1);
            if(this->m_waitTimer->ElapsedMilliseconds(1) > this->WaitAnyPacketMaxTimeMs) {
                //TODO remove debug
                if(this->m_snapshot->State() == FeedConnectionState::fcsSuspend)
                    printf("%s listen atom incremental timeout... start snapshot\n", this->m_idName);
                this->StartListenSnapshot();
                return true;
            }
        }
        else {
            this->m_waitTimer->Stop(1);
        }

        return this->Listen_Atom_Incremental_Core();
    }

    inline bool Listen_Atom_SecurityStatus() {
        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();

        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->Start(1);
            }
            else {
                if(this->m_waitTimer->ElapsedMilliseconds(1) > this->WaitAnyPacketMaxTimeMs) {
                    printf("%s %s Timeout 10 sec... Reconnect...\n", this->m_channelName, this->m_idName);
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_SecurityStatus, false);
                    this->ReconnectSetNextState(FeedConnectionState::fcsListenSecurityStatus);
                }
            }
            return true;
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        return this->Listen_Atom_SecurityStatus_Core();
    }

    inline bool Listen_Atom_SecurityDefinition() {
        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();

        if(!recv) {
            if(!this->m_waitTimer->Active(1)) {
                this->m_waitTimer->Start(1);
            }
            else {
                if(this->m_waitTimer->ElapsedMilliseconds(1) > this->WaitAnyPacketMaxTimeMs) {
                    printf("%s %s Timeout 10 sec... Reconnect...\n", this->m_channelName, this->m_idName);
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_SecurityDefinition, false);
                    this->ReconnectSetNextState(FeedConnectionState::fcsListenSecurityDefinition);
                }
            }
            return true;
        }
        else {
            this->m_waitTimer->Stop(1);
        }
        return this->Listen_Atom_SecurityDefinition_Core();
    }

    inline bool Listen_Atom_Snapshot() {
        bool recv = this->ProcessServerA();
        recv |= this->ProcessServerB();

        if(!recv) {
            if(!this->m_waitTimer->Active(2)) {
                this->m_waitTimer->Start(2);
            }
            else {
                if(this->m_waitTimer->ElapsedMilliseconds(2) > this->WaitAnyPacketMaxTimeMs) {
                    this->m_waitTimer->Stop(2);
                    //printf("%d entries and %d symbols to go.\n", this->m_incremental->OrderCurr()->QueueEntriesCount(), this->m_incremental->OrderCurr()->SymbolsToRecvSnapshotCount());
                    DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_Listen_Atom_Snapshot, false);
                    ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
                    return true;
                }
            }
        }
        else {
            this->m_waitTimer->Stop(2);
        }

        return this->Listen_Atom_Snapshot_Core();
    }

    inline void ReconnectSetNextState(FeedConnectionState state) {
        this->m_waitTimer->Stop();
        this->SetNextState(state);
        this->SetState(FeedConnectionState::fcsConnect);
    }

    inline void JumpNextState() {
        this->SetState(this->m_nextState);
    }

	FILE *obrLogFile;

	inline bool OnIncrementalRefresh_OLR_FOND(FastOLSFONDItemInfo *info) {
		if(info->MDEntryType[0] == mdetEmptyBook) { // fatal!!!!!
			return true; // TODO!!!!!
		}
		return this->m_orderTableFond->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_OLR_CURR(FastOLSCURRItemInfo *info) {
		if(info->MDEntryType[0] == mdetEmptyBook) { // fatal!!!!!
			return true; // TODO!!!!!
		}
		return this->m_orderTableCurr->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_TLR_FOND(FastTLSFONDItemInfo *info) {
		return this->m_tradeTableFond->ProcessIncremental(info);
	}

	inline bool OnIncrementalRefresh_TLR_CURR(FastTLSCURRItemInfo *info) {
        return this->m_tradeTableCurr->ProcessIncremental(info);
	}

    inline bool OnIncrementalRefresh_MSR_FOND(FastGenericItemInfo *info) {
        return this->m_statTableFond->ProcessIncremental(info);
    }

    inline bool OnIncrementalRefresh_MSR_CURR(FastGenericItemInfo *info) {
        return this->m_statTableCurr->ProcessIncremental(info);
    }

    inline bool OnIncrementalRefresh_OLR_FOND(FastIncrementalOLRFONDInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncFondOlrProcessedCount();
        ProgramStatistics::Total->IncFondOlrProcessedCount();
#endif
        if(this->m_skipApplyMessages) { //TODO remove this
            this->m_fastProtocolManager->Print();
            info->Clear();
            return true;
        }

        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_OLR_FOND(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnIncrementalRefresh_OLR_CURR(FastIncrementalOLRCURRInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncCurrOlrProcessedCount();
        ProgramStatistics::Total->IncCurrOlrProcessedCount();
#endif
        if(this->m_skipApplyMessages) { //TODO remove this
            this->m_fastProtocolManager->Print();
            info->Clear();
            return true;
        }
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_OLR_CURR(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnIncrementalRefresh_TLR_FOND(FastIncrementalTLRFONDInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncFondTlrProcessedCount();
        ProgramStatistics::Total->IncFondTlrProcessedCount();
#endif
        if(this->m_skipApplyMessages) { //TODO remove this
            this->m_fastProtocolManager->Print();
            info->Clear();
            return true;
        }
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_TLR_FOND(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnIncrementalRefresh_TLR_CURR(FastIncrementalTLRCURRInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncCurrTlrProcessedCount();
        ProgramStatistics::Total->IncCurrTlrProcessedCount();
#endif
        if(this->m_skipApplyMessages) { //TODO remove this
            this->m_fastProtocolManager->Print();
            info->Clear();
            return true;
        }
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_TLR_CURR(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnIncrementalRefresh_MSR_FOND(FastIncrementalMSRFONDInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncFondMsrProcessedCount();
        ProgramStatistics::Total->IncFondMsrProcessedCount();
#endif
        if(this->m_skipApplyMessages) { //TODO remove this
            DebugInfoManager::Default->PrintStatisticsOnce<FastIncrementalMSRFONDInfo>(this->m_fastProtocolManager, info);
            info->Clear();
            return true;
        }
        return true;
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_MSR_FOND(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }



    inline bool OnIncrementalRefresh_MSR_CURR(FastIncrementalMSRCURRInfo *info) {
#ifdef COLLECT_STATISTICS
        ProgramStatistics::Current->IncCurrMsrProcessedCount();
        ProgramStatistics::Total->IncCurrMsrProcessedCount();
#endif
        if(this->m_skipApplyMessages) { //TODO remove this
            DebugInfoManager::Default->PrintStatisticsOnce<FastIncrementalMSRCURRInfo>(this->m_fastProtocolManager, info);
            info->Clear();
            return true;
        }
        bool res = true;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            res |= this->OnIncrementalRefresh_MSR_CURR(info->GroupMDEntries[i]);
        }
        info->ReleaseUnused();
        return res;
    }

    inline bool OnHearthBeatMessage(FastHeartbeatInfo *info) {
        throw; // there is no need to apply message just check
    }

    inline bool ApplyIncrementalCore() {
		switch(this->m_fastProtocolManager->TemplateId()) {
			case FeedConnectionMessage::fcmHeartBeat:
                return this->OnHearthBeatMessage((FastHeartbeatInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND:
				return this->OnIncrementalRefresh_OLR_FOND((FastIncrementalOLRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR:
				return this->OnIncrementalRefresh_OLR_CURR((FastIncrementalOLRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND:
				return this->OnIncrementalRefresh_TLR_FOND((FastIncrementalTLRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_TLR_CURR:
				return this->OnIncrementalRefresh_TLR_CURR((FastIncrementalTLRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
            case FeedConnectionMessage::fmcIncrementalRefresh_MSR_FOND:
                return this->OnIncrementalRefresh_MSR_FOND((FastIncrementalMSRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
            case FeedConnectionMessage::fmcIncrementalRefresh_MSR_CURR:
                return this->OnIncrementalRefresh_MSR_CURR((FastIncrementalMSRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
		}
		return true;
	}

	inline bool ProcessIncrementalCore(unsigned char *buffer, int length, bool shouldProcessMsgSeqNumber) {
		this->m_fastProtocolManager->SetNewBuffer(buffer, length);
		if(shouldProcessMsgSeqNumber)
            this->m_fastProtocolManager->ReadMsgSeqNumber();

		if(this->m_fastProtocolManager->Decode() == 0) {
            printf("unknown template: %d\n", this->m_fastProtocolManager->TemplateId());
            return true;
        }
        this->ApplyIncrementalCore();
		return true;
	}

    inline bool ProcessSecurityStatus(FastSecurityStatusInfo *info) {
        if(!this->m_securityDefinition->IsIdfDataCollected())
            return true; // TODO just skip? Should we do something else?
        return this->m_securityDefinition->UpdateSecurityDefinition(info);
    }

    inline bool ProcessSecurityStatus(unsigned char *buffer, int length, bool processMsgSeqNumber) {
        this->m_fastProtocolManager->SetNewBuffer(buffer, length);
        if(processMsgSeqNumber)
            this->m_fastProtocolManager->ReadMsgSeqNumber();

        if(this->m_fastProtocolManager->Decode() == 0) {
            printf("unknown template: %d\n", this->m_fastProtocolManager->TemplateId());
            return true;
        }

#ifdef TEST
        if(this->m_fastProtocolManager->MessageLength() != length)
            throw;
#endif

        if(this->m_fastProtocolManager->TemplateId() == FeedConnectionMessage::fmcSecurityStatus) {
            return this->ProcessSecurityStatus((FastSecurityStatusInfo *)this->m_fastProtocolManager->LastDecodeInfo());
        }

        return true;
    }

	inline bool ShouldSkipMessage(unsigned char *buffer, bool shouldProcessMsgSeqNumber) {
		if(shouldProcessMsgSeqNumber) {
            unsigned short *templateId = (unsigned short*)(buffer + 5);
            return (*templateId) == 0xbc10;
        }
        return *((unsigned short*)(buffer + 1)) == 0xbc10;
	}

	inline bool ProcessIncremental(FeedConnectionMessageInfo *info) {
        unsigned char *buffer = info->m_address;
		if(this->ShouldSkipMessage(buffer, !info->m_requested)) {
            info->m_processed = true;
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }

        //DefaultLogManager::Default->WriteFast(this->m_idLogIndex, this->m_recvABuffer->BufferIndex(), info->m_item->m_itemIndex);
        info->m_processed = true;
		return this->ProcessIncrementalCore(buffer, info->m_size, !info->m_requested);
	}

    inline bool ProcessSecurityStatus(FeedConnectionMessageInfo *info) {
#ifdef COLLECT_STATISTICS
        if(this->m_id == FeedConnectionId::fcidIsfFond) {
            ProgramStatistics::Current->IncFondIssProcessedCount();
            ProgramStatistics::Total->IncFondIssProcessedCount();
        }
        else {
            ProgramStatistics::Current->IncCurrIssProcessedCount();
            ProgramStatistics::Total->IncCurrIssProcessedCount();
        }
#endif
        unsigned char *buffer = info->m_address;
        if(this->ShouldSkipMessage(buffer, !info->m_requested)) {
            info->m_processed = true;
            return true;  // TODO - take this message into account, becasue it determines feed alive
        }

        //DefaultLogManager::Default->WriteFast(this->m_idLogIndex, this->m_recvABuffer->BufferIndex(), info->m_item->m_itemIndex);
        info->m_processed = true;
        return this->ProcessSecurityStatus(buffer, info->m_size, !info->m_requested);
    }

public:
	FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
	~FeedConnection();

    inline int LastMsgSeqNumProcessed() { return this->m_lastMsgSeqNumProcessed; }
    inline MarketDataTable<OrderInfo, FastOLSFONDInfo, FastOLSFONDItemInfo> *OrderFond() { return this->m_orderTableFond; }
	inline MarketDataTable<OrderInfo, FastOLSCURRInfo, FastOLSCURRItemInfo> *OrderCurr() { return this->m_orderTableCurr; }
	inline MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo> *TradeFond() { return this->m_tradeTableFond; }
	inline MarketDataTable<TradeInfo, FastTLSCURRInfo, FastTLSCURRItemInfo> *TradeCurr() { return this->m_tradeTableCurr; }
    inline MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo> *StatisticFond() { return this->m_statTableFond; }
    inline MarketDataTable<StatisticsInfo, FastGenericInfo, FastGenericItemInfo> *StatisticCurr() { return this->m_statTableCurr; }
    inline LinkedPointer<FastSecurityDefinitionInfo>** Symbols() { return this->m_symbols; }
    inline FastSecurityDefinitionInfo* Symbol(int index) { return this->m_symbols[index]->Data(); }
    inline int SymbolCount() { return this->m_symbolsCount; }
    inline FeedConnectionSecurityDefinitionMode SecurityDefinitionMode() { return this->m_idfMode; }
    inline void WaitIncrementalMaxTimeMs(int timeMs) { this->m_waitIncrementalMaxTimeMs = timeMs; }
    inline int WaitIncrementalMaxTimeMs() { return this->m_waitIncrementalMaxTimeMs; }
    inline void WaitSnapshotMaxTimeMs(int timeMs) { this->m_snapshotMaxTimeMs = timeMs; }
    inline int WaitSnapshotMaxTimeMs() { return this->m_snapshotMaxTimeMs; }

    inline void ClearMessages() {
        for(int i = 0;i < RobotSettings::Default->DefaultFeedConnectionPacketCount; i++)
            this->m_packets[i]->Clear();
        this->m_windowMsgSeqNum = 0;
        this->m_startMsgSeqNum = 1;
        this->m_endMsgSeqNum = 0;
    }

    inline void StartNewSnapshot() {
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartNewSnapshot, true);
        this->m_endMsgSeqNum = -1;
        this->m_startMsgSeqNum = -1;
        this->m_windowMsgSeqNum = 0;
        this->m_snapshotRouteFirst = -1;
        this->m_snapshotLastFragment = -1;
    }

    inline void SetType(FeedConnectionType type) {
        this->m_type = type;
		if(this->m_state == FeedConnectionState::fcsListenIncremental ||
                this->m_state == FeedConnectionState::fcsListenSnapshot)
			this->SetState(this->m_state);
		else if(this->m_nextState == FeedConnectionState::fcsListenIncremental ||
                this->m_nextState == FeedConnectionState::fcsListenSnapshot)
			this->SetNextState(this->m_state);
    }
    inline FeedConnectionType Type() { return this->m_type; }

    inline void SetIncremental(FeedConnection *conn) {
		if(this->m_incremental == conn)
			return;
		this->m_incremental = conn;
		if(this->m_incremental != 0)
			this->m_incremental->SetSnapshot(this);
	}
    inline FeedConnection *Incremental() { return this->m_incremental; }

    inline void SetSnapshot(FeedConnection *conn) {
		if(this->m_snapshot == conn)
			return;
		this->m_snapshot = conn;
		if(this->m_snapshot != 0)
			this->m_snapshot->SetIncremental(this);
	}
    inline FeedConnection* Snapshot() { return this->m_snapshot; }
    inline void SetHistoricalReplay(FeedConnection *historicalReplay) { this->m_historicalReplay = historicalReplay; }
    inline FeedConnection* HistoricalReplay() { return this->m_historicalReplay; }

    inline void SetSecurityDefinition(FeedConnection *securityDefinition) { this->m_securityDefinition = securityDefinition; }
    inline FeedConnection* SecurityDefinition() { return this->m_securityDefinition; }

    inline FeedConnection** ConnectionsToRecvSymbols() { return this->m_connectionsToRecvSymbols; }
    inline int ConnectionsToRecvSymbolsCount() { return this->m_connectionsToRecvSymbolsCount; }
    inline void AddConnectionToRecvSymbol(FeedConnection *conn) {
        if(conn == 0)
            return;
        this->m_connectionsToRecvSymbols[this->m_connectionsToRecvSymbolsCount] = conn;
        this->m_connectionsToRecvSymbolsCount++;
    }

    inline int CalcSessionsCount(FastSecurityDefinitionInfo *info) {
        int res = 0;
        FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
            res += info->MarketSegmentGrp[i]->TradingSessionRulesGrpCount;
        }
        return res;
    }

    inline void AddSymbol(LinkedPointer<FastSecurityDefinitionInfo> *ptr) {
        FastSecurityDefinitionInfo *info = ptr->Data();
        if(this->m_orderTableFond != 0) {
            MarketSymbolInfo<OrderInfo<FastOLSFONDItemInfo>> *symbol = this->m_orderTableFond->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_orderTableCurr != 0) {
            MarketSymbolInfo<OrderInfo<FastOLSCURRItemInfo>> *symbol = this->m_orderTableCurr->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_tradeTableFond != 0) {
            MarketSymbolInfo<TradeInfo<FastTLSFONDItemInfo>> *symbol = this->m_tradeTableFond->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            MarketSymbolInfo<TradeInfo<FastTLSCURRItemInfo>> *symbol = this->m_tradeTableCurr->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_statTableFond != 0) {
            MarketSymbolInfo<StatisticsInfo<FastGenericItemInfo>> *symbol = this->m_statTableFond->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
        if(this->m_statTableCurr != 0) {
            MarketSymbolInfo<StatisticsInfo<FastGenericItemInfo>> *symbol = this->m_statTableCurr->AddSymbol(info->Symbol, info->SymbolLength);

            symbol->SecurityDefinitionPtr(ptr);
            symbol->InitSessions(CalcSessionsCount(info));

            FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
            for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++) {
                FastSecurityDefinitionMarketSegmentGrpItemInfo *m = *market;
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
                for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
                    symbol->AddSession((*trading)->TradingSessionID, (*trading)->TradingSessionIDLength);
                }
            }
            return;
        }
    }

    inline void AddSecurityDefinitionToList(FastSecurityDefinitionInfo *info, int index) {
        info->Used = true;
        this->m_symbols[index]->Data(info);
        this->m_symbolsCount = index + 1;
    }

    inline void MakeUsed(FastSecurityDefinitionMarketSegmentGrpItemInfo *m, bool used) {
        m->Used = used;
        FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **trading = m->TradingSessionRulesGrp;
        for(int j = 0; j < m->TradingSessionRulesGrpCount; j++, trading++) {
            (*trading)->Used = used;
        }
    }

    inline void MakeUsed(FastSecurityDefinitionInfo *info, bool used) {
        info->Used = used;

        FastSecurityDefinitionMarketSegmentGrpItemInfo **market = info->MarketSegmentGrp;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++, market++)
            MakeUsed(*market, used);
    }

    inline void MergeSecurityDefinition(FastSecurityDefinitionInfo *parent, FastSecurityDefinitionInfo *child) {
        int freeIndex = parent->MarketSegmentGrpCount;
        FastSecurityDefinitionMarketSegmentGrpItemInfo **market = child->MarketSegmentGrp;
        for(int i = 0; i < child->MarketSegmentGrpCount; i++, market++, freeIndex++) {
            MakeUsed(*market, true);
            parent->MarketSegmentGrp[freeIndex] = *market;
        }
        parent->MarketSegmentGrpCount += child->MarketSegmentGrpCount;
        child->MarketSegmentGrpCount = 0;
    }

    inline void PrintSymbolManagerDebug() {
//        printf("Collected %d symbols\n", this->m_symbolsCount);
//        for(int i = 0; i < this->m_symbolManager->BucketListCount(); i++) {
//            int count = this->m_symbolManager->CalcBucketCollisitonCount(i);
//            if(count != 0)
//                printf("Collision %d = %d\n", i, count);
//        }
        printf("Collected %d symbols\n", this->m_symbolsCount);
    }

    inline void CheckAllSymbols() {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            bool isNewlyAdded = false;
            SymbolInfo *info = this->m_symbolManager->GetSymbol(
                    this->m_symbols[i]->Data()->Symbol,
                    this->m_symbols[i]->Data()->SymbolLength, &isNewlyAdded);
            if(!StringIdComparer::Equal(info->m_text, info->m_length,
                                        this->m_symbols[i]->Data()->Symbol,
                                        this->m_symbols[i]->Data()->SymbolLength)) {
                printf("Error: symbol collision\n");
            }
        }
    }

    inline void OnSecurityDefinitionUpdateAllMessages() {
        this->m_idfDataCollected = true;
        if(!this->m_idfStopAfterUpdateAllMessages)
            return;
        this->m_idfStartMsgSeqNo = 0;
        this->Stop();
    }

    inline void OnSecurityDefinitionRecvAllMessages() {
        this->m_idfDataCollected = true;
        this->m_idfStartMsgSeqNo = 0;
        this->ClearPackets(1, this->m_idfMaxMsgSeqNo);
        if(!this->m_idfAllowUpdateData) {
            this->Stop();
        }
        else {
            this->m_idfMode = FeedConnectionSecurityDefinitionMode::sdmUpdateData;
            this->m_waitTimer->Reset(0);
            this->m_waitTimer->Reset(1);
        }
    }

    inline bool ProcessSecurityDefinition(FastSecurityDefinitionInfo *info) {
        bool wasNewlyAdded = false;

        SymbolInfo *smb = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength, &wasNewlyAdded);

        MakeUsed(info, true);
        if(wasNewlyAdded) {
            this->AddSecurityDefinitionToList(info, smb->m_index);
            //printf("add sd to list index = %d\n", smb->m_index);
            //printf("new sec_def %d. sc = %d\n", info->MsgSeqNum, info->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->Allocator->Count()); // TODO
        }
        else {
            LinkedPointer<FastSecurityDefinitionInfo> *ptr = this->m_symbols[smb->m_index];
            if(!StringIdComparer::Equal(ptr->Data()->Symbol, ptr->Data()->SymbolLength, info->Symbol, info->SymbolLength)) {
                printf("merge symbols are not equal\n");
            }
            this->MergeSecurityDefinition(ptr->Data(), info);
            //printf("merge sec_def %d. sc = %d\n", info->MsgSeqNum, info->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->Allocator->Count()); // TODO
        }
        info->ReleaseUnused();

        return true;
    }

    inline void InitSymbols(int count) {
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->InitSymbols(count);
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->InitSymbols(count);
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_tradeTableFond->InitSymbols(count);
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_tradeTableCurr->InitSymbols(count);
            return;
        }
        if(this->m_statTableFond != 0) {
            this->m_statTableFond->InitSymbols(count);
            return;
        }
        if(this->m_statTableCurr != 0) {
            this->m_statTableCurr->InitSymbols(count);
            return;
        }
    }

    inline void ClearMarketData() {
        if(this->m_orderTableFond != 0) {
            this->m_orderTableFond->Release();
            return;
        }
        if(this->m_orderTableCurr != 0) {
            this->m_orderTableCurr->Release();
            return;
        }
        if(this->m_tradeTableFond != 0) {
            this->m_tradeTableFond->Release();
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_tradeTableCurr->Release();
            return;
        }
        if(this->m_statTableFond != 0) {
            this->m_statTableFond->Release();
            return;
        }
        if(this->m_tradeTableCurr != 0) {
            this->m_statTableCurr->Release();
            return;
        }
    }

    inline void ClearSecurityDefinitions() {
        for(int i = 0; i < this->m_symbolsCount; i++) {
            this->m_symbols[i]->Data()->Clear();
            this->m_symbols[i]->Data(0);
        }
        this->m_symbolsCount = 0;
    }

    inline void BeforeProcessSecurityDefinitions() {
        this->ClearSecurityDefinitions();
        for(int c = 0; c < this->m_connectionsToRecvSymbolsCount; c++) {
            this->m_connectionsToRecvSymbols[c]->ClearMarketData();
        }
    }

    inline void AddSecurityDefinition(LinkedPointer<FastSecurityDefinitionInfo> *ptr) {
        for(int c = 0; c < this->m_connectionsToRecvSymbolsCount; c++)
            this->m_connectionsToRecvSymbols[c]->AddSymbol(ptr);
    }

    inline FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* FindTradingSession(FastSecurityDefinitionInfo *info, const char *tradingSession, int tradingSessionLength) {
        for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
            FastSecurityDefinitionMarketSegmentGrpItemInfo *m = info->MarketSegmentGrp[i];
            for(int j = 0; j < m->TradingSessionRulesGrpCount; j++) {
                FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *t = m->TradingSessionRulesGrp[j];
                if(StringIdComparer::Equal(t->TradingSessionID, t->TradingSessionIDLength, tradingSession, tradingSessionLength))
                    return t;
                /*char smb = *(t->TradingSessionSubID);
                if(smb == *tradingSession) {
                    if(smb != 'N') // ONLY N subId can have 2 symbol length - 'NA' - other symbols - only one
                        return t;
                    if(t->TradingSessionSubIDLength == tradingSessionLength) // if both has 1 symbol 'N' or 2 symbols 'NA'
                        return t;
                }*/
            }
        }
        return 0;
    }

    inline void UpdateTradingSession(FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *trading, FastSecurityStatusInfo *info) {
        trading->NullMap = info->NullMap;
        StringIdComparer::CopyString(trading->TradingSessionSubID, info->TradingSessionSubID, info->TradingSessionSubIDLength);
        trading->TradingSessionSubIDLength = info->TradingSessionSubIDLength;
        trading->SecurityTradingStatus = info->SecurityTradingStatus;
        //Skip AuctionIndicator because there is no data in feed streams for them
    }

    inline bool UpdateSecurityDefinition(FastSecurityStatusInfo *info) {
        info->Clear(); // just free object before. Data will not be corrupt
        int index = this->IdfFindBySymbol(info->Symbol, info->SymbolLength);
        if(index == -1) // TODO should we do something for unknown symbol? or just skip?
            return true;
        FastSecurityDefinitionInfo *sd = this->Symbol(index);
        FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *trading = FindTradingSession(sd, info->TradingSessionID, info->TradingSessionIDLength);
        if(trading == 0) // TODO should we do something for unknow session? or just skip?
            return true;
        UpdateTradingSession(trading, info);
        return true;
    }

    inline void UpdateSecurityDefinition(FeedConnectionMessageInfo *info) {
        this->m_fastProtocolManager->SetNewBuffer(info->m_address + 4, info->m_size - 4); // skip msg seq num
        this->m_fastProtocolManager->DecodeHeader();
        if(this->m_fastProtocolManager->TemplateId() != FeedConnectionMessage::fmcSecurityDefinition)
            return;
        FastSecurityDefinitionInfo *fi = (FastSecurityDefinitionInfo *)this->m_fastProtocolManager->DecodeSecurityDefinition();
        this->UpdateSecurityDefinition(fi);
        fi->ReleaseUnused();
    }

    inline void ReplaceMarketSegmentGroupById(FastSecurityDefinitionInfo *info, FastSecurityDefinitionMarketSegmentGrpItemInfo *m) {
        FastSecurityDefinitionMarketSegmentGrpItemInfo **im = info->MarketSegmentGrp;
        int sCount = m->TradingSessionRulesGrpCount;
        bool found;
        for(int i = 0; i < info->MarketSegmentGrpCount; i++, im++) {
            if((*im)->TradingSessionRulesGrpCount != m->TradingSessionRulesGrpCount)
                continue;
            FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **is = (*im)->TradingSessionRulesGrp;
            FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **s = m->TradingSessionRulesGrp;
            found = true;
            for(int i = 0; i < sCount; i++, is++, s++) {
                if(!StringIdComparer::Equal((*is)->TradingSessionID, (*is)->TradingSessionIDLength, (*s)->TradingSessionID, (*s)->TradingSessionIDLength)) {
                    found = false;
                    break;
                }
            }
            if(found) {
                info->MarketSegmentGrp[i]->Clear();
                info->MarketSegmentGrp[i] = m;
                return;
            }
        }
    }

    inline void UpdateSecurityDefinition(LinkedPointer<FastSecurityDefinitionInfo> *ptr, FastSecurityDefinitionInfo *curr) {
        int sc1 = ptr->Data()->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->Allocator->Count();
        FastSecurityDefinitionInfo *prev = ptr->Data();
        int mcPrev = prev->MarketSegmentGrpCount;
        int mcCurr = curr->MarketSegmentGrpCount;
        for(int i = 0; i < mcCurr; i++) {
            prev->MarketSegmentGrp[mcPrev + i] = curr->MarketSegmentGrp[i];
            curr->MarketSegmentGrp[i]->Used = true;
        }
        for(int i = 0; i < mcPrev; i++) {
            curr->MarketSegmentGrp[i] = prev->MarketSegmentGrp[i];
        }
        int count = mcPrev + mcCurr;
        curr->MarketSegmentGrpCount = mcPrev;
        for(int i = mcPrev; i < count; i++) {
            ReplaceMarketSegmentGroupById(curr, prev->MarketSegmentGrp[i]);
        }
        curr->Used = true;

        prev->Used = false;
        prev->ReleaseUnused();
        ptr->Data(curr);
        int sc2 = curr->MarketSegmentGrp[0]->TradingSessionRulesGrp[0]->Allocator->Count();
        printf("update sc before %d after %d\n", sc1, sc2);
    }

    inline int IdfFindBySymbol(const char *symbol, int symbolLength) {
        bool newlyAdded = false;
        SymbolInfo *s = this->m_symbolManager->GetSymbol(symbol, symbolLength, &newlyAdded);
        if(newlyAdded)
            return -1;
        return s->m_index;
    }

    inline void UpdateSecurityDefinition(FastSecurityDefinitionInfo *info) {
        bool wasNewlyAdded;

        SymbolInfo *sm = this->m_symbolManager->GetSymbol(info->Symbol, info->SymbolLength, &wasNewlyAdded);
        LinkedPointer<FastSecurityDefinitionInfo> *orig = this->m_symbols[sm->m_index];
        if(!StringIdComparer::Equal(orig->Data()->Symbol, orig->Data()->SymbolLength, info->Symbol, info->SymbolLength)) {
            int symbolIndex = IdfFindBySymbol(info->Symbol, info->SymbolLength);
            printf("symbols are not equal\n");
        }
        this->UpdateSecurityDefinition(orig, info);
    }

    inline void AfterProcessSecurityDefinitions() {
        //TODO remove debug
        printf("%s %s SymbolsCount = %d\n", this->m_channelName, this->m_idName, this->m_symbolsCount);
        int sessionCount = 0;
        for(int i = 0; i < this->m_symbolsCount; i++) {
            for (int j = 0; j < this->m_symbols[i]->Data()->MarketSegmentGrpCount; j++) {
                sessionCount += this->m_symbols[i]->Data()->MarketSegmentGrp[j]->TradingSessionRulesGrpCount;
            }
        }
        printf("%s %s Total SessionsCount = %d\n", this->m_channelName, this->m_idName, sessionCount);

        for(int i = 0; i < this->m_connectionsToRecvSymbolsCount; i++)
            this->m_connectionsToRecvSymbols[i]->InitSymbols(this->m_symbolsCount);

        LinkedPointer<FastSecurityDefinitionInfo> **ptr = this->m_symbols;
        for(int i = 0; i < this->m_symbolsCount; i++, ptr++)
            this->AddSecurityDefinition(*ptr);
    }

    inline bool HasLostPackets(int msgStart, int msgEnd) {
        FeedConnectionMessageInfo **msg = (this->m_packets + msgStart - this->m_windowMsgSeqNum);
        for(int i = msgStart; i <= msgEnd; i++, msg++) {
            if((*msg)->m_address == 0)
                return true;
        }
        return false;
    }

    inline int CalcLostPacketCount(int msgStart, int msgEnd) {
        int sum = 0;
        FeedConnectionMessageInfo **msg = (this->m_packets + msgStart - this->m_windowMsgSeqNum);
        for(int i = msgStart; i <= msgEnd; i++, msg++) {
            if((*msg)->m_address == 0)
                sum++;
        }
        return sum;
    }

    inline bool IsIdfDataCollected() { return this->m_idfDataCollected; }
    inline bool IdfAllowUpdateData() { return this->m_idfAllowUpdateData; }
    inline bool IdfStopAfterUpdateMessages() { return this->m_idfStopAfterUpdateAllMessages; }
    inline void IdfStopAfterUpdateMessages(bool value) { this->m_idfStopAfterUpdateAllMessages = value; }
    inline void IdfAllowUpdateData(bool value) { this->m_idfAllowUpdateData = value; }
    inline FeedConnectionSecurityDefinitionMode IdfMode() { return this->m_idfMode; }
    inline FeedConnectionSecurityDefinitionState IdfState() { return this->m_idfState; }

	inline bool Connect() {
        if(this->socketAManager != NULL && this->socketAManager->IsConnected())
			return true;
		if(this->socketAManager == NULL && !this->InitializeSockets())
			return false;
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Connect);
		if(this->protocol == FeedConnectionProtocol::UDP_IP) {
			if (!this->socketAManager->ConnectMulticast(this->feedASourceIp, this->feedAIp, this->feedAPort)) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}
			if (!this->socketBManager->ConnectMulticast(this->feedBSourceIp, this->feedBIp, this->feedBPort)) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}
		}
		else {
			if(!this->socketAManager->Connect(this->feedAIp, this->feedAPort)) {
				DefaultLogManager::Default->EndLog(false);
				return false;
			}
		}
		DefaultLogManager::Default->EndLog(true);
		return true;
	}

	inline bool Disconnect() {
        if((this->socketAManager == NULL || !this->socketAManager->IsConnected()) &&
                (this->socketBManager == NULL || !this->socketBManager->IsConnected()))
            return true;
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Disconnect);

		bool result = true;
		if(this->socketAManager != NULL)
			result &= this->socketAManager->Disconnect();
		if(this->socketBManager != NULL)
			result &= this->socketBManager->Disconnect();

		DefaultLogManager::Default->EndLog(result);
		return result;
	}

    void SetSenderCompId(const char *senderCompId) {
        this->m_senderCompId = senderCompId;
        if(this->m_senderCompId == NULL)
            this->m_senderCompIdLength = 0;
        else
            this->m_senderCompIdLength = strlen(this->m_senderCompId);
        if(this->m_type == FeedConnectionType::HistoricalReplay && this->m_senderCompId != 0) {
            strcpy(this->m_hsLogonInfo->SenderCompID, this->m_senderCompId);
            this->m_hsLogonInfo->SenderCompIDLength = this->m_senderCompIdLength;
        }
    }
    void SetPassword(const char *password) {
        if(this->m_type == FeedConnectionType::HistoricalReplay) {
            this->m_password = HistoricalReplayPassword;
            this->m_passwordLength = HistoricalReplayPasswordLength;
        }
        else {
            this->m_password = password;
            this->m_passwordLength = strlen(this->m_password);
        }
    }

    inline char* ChannelName() { return this->m_channelName; }
    inline void ChannelName(const char *channelName) {
        strcpy(this->m_channelName, channelName);
    }
    inline char* IdName() { return this->m_idName; }
    inline FeedConnectionId Id() { return this->m_id; }

	inline virtual void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);

		DefaultLogManager::Default->EndLog(true);
	}

	inline int MsgSeqNo() { return this->m_startMsgSeqNum; }
    inline int LastRecvMsgSeqNo() { return this->m_endMsgSeqNum; }
	inline int ExpectedMsgSeqNo() { return this->m_startMsgSeqNum + 1; }

	inline bool DoWorkAtom() {
		FeedConnectionState st = this->m_state;
        if(st == FeedConnectionState::fcsListenIncremental)
            return this->Listen_Atom_Incremental();
        if(st == FeedConnectionState::fcsHistoricalReplay)
            return this->HistoricalReplay_Atom();
        if(st == FeedConnectionState::fcsListenSecurityDefinition)
            return this->Listen_Atom_SecurityDefinition();
        if(st == FeedConnectionState::fcsListenSecurityStatus)
            return this->Listen_Atom_SecurityStatus();
        if(st == FeedConnectionState::fcsListenSnapshot)
            return this->Listen_Atom_Snapshot();
        if(st == FeedConnectionState::fcsSuspend)
            return true;
        if(st == FeedConnectionState::fcsConnect)
            return this->Reconnect_Atom();
        return true;

	}
    inline FeedConnectionState CalcListenStateByType() {
        if(m_type == FeedConnectionType::InstrumentDefinition)
            return FeedConnectionState::fcsListenSecurityDefinition;
        else if(m_type == FeedConnectionType::Snapshot)
            return FeedConnectionState::fcsListenSnapshot;
        else if(m_type == FeedConnectionType::HistoricalReplay)
            return FeedConnectionState::fcsHistoricalReplay;
        else if(m_type == FeedConnectionType::InstrumentStatus)
            return FeedConnectionState::fcsListenSecurityStatus;
        return FeedConnectionState::fcsListenIncremental;
    }
	inline void Listen() {
        FeedConnectionState st = CalcListenStateByType();
		if(this->m_state == FeedConnectionState::fcsSuspend)
			this->SetState(st);
		else
			this->SetNextState(st);
	}
    inline void BeforeListenSecurityDefinition() {
        this->ClearPackets(1, this->m_idfMaxMsgSeqNo);
        if(this->m_idfMode == FeedConnectionSecurityDefinitionMode::sdmCollectData)
            this->ClearSecurityDefinitions();

        this->m_idfState = FeedConnectionSecurityDefinitionState::sdsProcessToEnd;
        this->m_idfStartMsgSeqNo = 0;
        this->m_idfMaxMsgSeqNo = 0;
        this->m_startMsgSeqNum = 0;
        this->m_endMsgSeqNum = 0;
        this->m_idfDataCollected = false;
        if(this->m_idfMode == FeedConnectionSecurityDefinitionMode::sdmCollectData)
            this->m_symbolManager->Clear();
    }
    inline void BeforeListenSecurityStatus() {
        this->m_securityStatusSnapshotActive = false;
    }
    inline void BeforeListen() {
        if(this->m_type == FeedConnectionType::InstrumentDefinition) {
            BeforeListenSecurityDefinition();
        }
        if(this->m_type == FeedConnectionType::InstrumentStatus) {
            BeforeListenSecurityStatus();
        }
        if(this->m_type == FeedConnectionType::HistoricalReplay) {
            this->m_hsState = FeedConnectionHistoricalReplayState::hsSuspend;
        }
        if(this->m_type == FeedConnectionType::Incremental) {
            this->m_requestMessageStartIndex = -1;
        }
    }
    inline bool Start() {
        if(this->m_state == FeedConnectionState::fcsHistoricalReplay)
            return true;
        if(!this->Connect())
			return false;
		if(this->m_state != FeedConnectionState::fcsSuspend)
            return true;
        this->m_waitTimer->Start();
        this->m_waitTimer->Stop(1);
        this->m_waitTimer->Stop(2); //for snapshot
        this->BeforeListen();
        this->Listen();
		return true;
    }
	inline bool Stop() {
		if(this->m_state == FeedConnectionState::fcsHistoricalReplay)
            return true;
        this->SetState(FeedConnectionState::fcsSuspend);
		if(!this->Disconnect())
			return false;
		return true;
	}
    inline FeedConnectionState State() { return this->m_state; }
    inline void DoNotCheckIncrementalActuality(bool value) {
        this->m_doNotCheckIncrementalActuality = value;
    }
    inline void SkipApplyMessages(bool value) { this->m_skipApplyMessages = value; }

#ifdef TEST
    inline void SetTestMessagesHelper(TestMessagesHelper *helper) { this->m_testHelper = helper; }
#endif
};


