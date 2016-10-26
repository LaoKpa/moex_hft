#pragma once
#include "WinSockManager.h"
#include "FastProtocolManager.h"
#include "Types.h"
#include <sys/time.h>
#include "Stopwatch.h"
#include "Lib/AutoAllocatePointerList.h"
#include "Lib/HashTable.h"
#include "MarketData/MarketDataTable.h"

typedef enum _FeedConnectionMessage {
	fcmHeartBeat = 2108,
	fmcFullRefresh_OBS_FOND = 2412,
	fmcIncrementalRefresh_OBR_FOND = 2422,
	fmcFullRefresh_OBS_CURR = 3502,
	fmcIncrementalRefresh_OBR_CURR = 3512,
	fmcFullRefresh_OLS_FOND = 2410,
	fmcIncrementalRefresh_OLR_FOND = 2420,
	fmcFullRefresh_OLS_CURR = 3500,
	fmcIncrementalRefresh_OLR_CURR = 3510,
	fmcFullRefresh_TLS_FOND = 2411,
	fmcIncrementalRefresh_TLR_FOND = 2421,
	fmcFullRefresh_TLS_CURR = 3501,
	fmcIncrementalRefresh_TLR_CURR = 3511
}FeedConnectionMessage;

typedef enum _FeedConnectionProtocol {
	TCP_IP,
	UDP_IP
}FeedConnectionProtocol;

typedef enum _FeedConnectionState {
	fcsSuspend,
	fcsListen,
    fcsSendLogon,
    fcsResendLastMessage,
    fcsConnect
} FeedConnectionState;

typedef enum _FeedConnectionProcessMessageResultValue {
	fcMsgResProcessed,
	fcMsgResFailed,
	fcMsgResProcessedExit
}FeedConnectionProcessMessageResultValue;

class FeedConnection;
typedef bool (FeedConnection::*FeedConnectionWorkAtomPtr)();

typedef enum _FeedConnectionType {
    Incremental,
    Snapshot
}FeedConnectionType;

class OrderBookTester;
class OrderTester;
class FeedConnection {
	friend class OrderBookTester;
    friend class OrderTester;

	const int MaxReceiveBufferSize 				= 1500;
    const int WaitIncrementalMaxTimeSec         = 5;
    const int WaitAnyPacketMaxTimeSec           = 10;
protected:
	char										id[16];
	char										feedTypeName[64];

    FeedConnectionType                          m_type;
    FeedConnection                              *m_incremental;
    FeedConnection                              *m_snapshot;
	int 										m_snapshotStartMsgSeqNum;
	int											m_snapshotEndMsgSeqNum;
    int                                         m_snapshotRouteFirst;
    int                                         m_snapshotLastFragment;
    int                                         m_lastMsgSeqNumProcessed;
	int											m_rptSeq;
    int                                         m_snapshotAvailable;

    BinaryLogItem                               **m_packets;

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

	int											m_currentMsgSeqNum;
    int                                         m_maxRecvMsgSeqNum;

    const char                                  *m_senderCompId;
    int                                         m_senderCompIdLength;
    const char                                  *m_password;
    int                                         m_passwordLength;

    bool                                        m_waitingSnapshot;

	WinSockManager								*socketAManager;
	WinSockManager								*socketBManager;
	FastProtocolManager 						*m_fastProtocolManager;
    FastLogonInfo                               *m_fastLogonInfo;


	ISocketBufferProvider						*m_socketABufferProvider;
	SocketBuffer								*m_sendABuffer;
	SocketBuffer								*m_recvABuffer;

	FeedConnectionState							m_state;
	FeedConnectionWorkAtomPtr					m_workAtomPtr;

	FeedConnectionState							m_nextState;
	FeedConnectionWorkAtomPtr					m_nextWorkAtomPtr;
	bool										m_shouldUseNextState;

	FeedConnectionWorkAtomPtr					m_listenPtr;

    struct timeval                              *m_tval;
    Stopwatch                                   *m_stopwatch;
    Stopwatch                                   *m_waitTimer;
    bool                                        m_shouldReceiveAnswer;

protected:
	MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo>		*m_orderBookTableFond;
	MarketDataTable<OrderBookTableItem,FastOBSCURRInfo, FastOBSCURRItemInfo>        *m_orderBookTableCurr;
	MarketDataTable<OrderTableItem, FastOLSFONDInfo, FastOLSFONDItemInfo>			*m_orderTableFond;
	MarketDataTable<OrderTableItem, FastOLSCURRInfo, FastOLSCURRItemInfo>			*m_orderTableCurr;
	MarketDataTable<TradeTableItem, FastTLSFONDInfo, FastTLSFONDItemInfo>			*m_tradeTableFond;
	MarketDataTable<TradeTableItem, FastTLSCURRInfo, FastTLSCURRItemInfo>			*m_tradeTableCurr;
private:

    inline void GetCurrentTime(UINT64 *time) {
        gettimeofday(this->m_tval, NULL);
        *time = this->m_tval->tv_usec / 1000;
    }

	inline bool CanListen() { return this->socketAManager->ShouldRecv() || this->socketBManager->ShouldRecv(); }

    inline bool ProcessServerA() { return this->ProcessServer(this->socketAManager, LogMessageCode::lmcsocketA); }
    inline bool ProcessServerB() { return this->ProcessServer(this->socketBManager, LogMessageCode::lmcsocketB); }
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
        int msgSeqNum = *((UINT*)socketManager->RecvBytes());
        if(this->m_packets[msgSeqNum] != 0)
            return false;

        this->m_recvABuffer->SetCurrentItemSize(size);
        BinaryLogItem *item = DefaultLogManager::Default->WriteFast(this->m_idLogIndex,
                                                                    LogMessageCode::lmcFeedConnection_ProcessMessage,
                                                                    this->m_recvABuffer->BufferIndex(),
                                                                    this->m_recvABuffer->CurrentItemIndex());
        if(this->m_type == FeedConnectionType::Incremental) {
            //if(this->m_currentMsgSeqNum == 1)
            //    this->m_currentMsgSeqNum = msgSeqNum;  // TODO - remove after debug end
            if (this->m_maxRecvMsgSeqNum < msgSeqNum)
                this->m_maxRecvMsgSeqNum = msgSeqNum;
        }
        else {
            if(this->m_snapshotStartMsgSeqNum == -1)
                this->m_snapshotStartMsgSeqNum = msgSeqNum;
            if(this->m_snapshotEndMsgSeqNum < msgSeqNum)
                this->m_snapshotEndMsgSeqNum = msgSeqNum;
			if(this->m_snapshotStartMsgSeqNum > this->m_snapshotEndMsgSeqNum)
				this->m_snapshotStartMsgSeqNum = this->m_snapshotEndMsgSeqNum; // TODO unbelievable - remove then
        }
        this->m_packets[msgSeqNum] = item;
        this->m_recvABuffer->Next(size);
        return true;
    }
    inline bool WaitingSnapshot() { return this->m_waitingSnapshot; }
    inline bool SnapshotAvailable() { return this->m_snapshotAvailable; }

	inline bool ApplyOrderBookSnapshot_FOND() {
        this->m_orderBookTableFond->Clear();
        for(int i = this->m_snapshotRouteFirst; i <= this->m_snapshotLastFragment; i++) {
            this->ProcessMessage(this->m_packets[i]);
        }
        //FastOBSFONDInfo *info = (FastOBSFONDInfo*)this->m_snapshot->m_fastProtocolManager->LastDecodeInfo();
		//this->m_orderBookTable->Add(info->Symbol, info->TradingSessionID, (void**)info->GroupMDEntries, info->GroupMDEntriesCount);
		return true;
	}

    inline bool ApplySnapshot() {
        switch(this->m_fastProtocolManager->TemplateId()) {
			case FeedConnectionMessage::fmcFullRefresh_OBS_FOND:
				return this->ApplyOrderBookSnapshot_FOND();
		}
		return true;
	}

    inline bool ApplyPacketSequence() {
        int i = this->m_currentMsgSeqNum;
        bool processed = false;
        while(i <= this->m_maxRecvMsgSeqNum) {
            if(this->m_packets[i] == 0) {
				i++; continue; // TODO remove this code
                //this->m_currentMsgSeqNum = i; // TODO uncomment this code
                //return processed;
            }
            this->ProcessMessage(this->m_packets[i]);
            processed = true;
            i++;
        }
        this->m_currentMsgSeqNum = i;
        return processed;
    }
    inline bool StartListenSnapshot() {
		if(!this->m_snapshot->Start()) {
			DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, false);
			return false;
		}
        this->m_waitingSnapshot = true;
		this->m_snapshot->StartNewSnapshot();
		DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartListenSnapshot, true);
		return true;
	}
	inline bool StopListenSnapshot() {
		if(!this->m_snapshot->Stop()) {
			DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, false);
			return false;
		}
		DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StopListenSnapshot, true);
		return true;
	}
	inline bool CheckForRouteFirst(BinaryLogItem *item) {
		unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);
		this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
		this->m_fastProtocolManager->ReadMsgSeqNumber();
		FastSnapshotInfo* info = this->m_fastProtocolManager->GetSnapshotInfo();
        return info == NULL? false: info->RouteFirst == 1;
    }
    inline bool CheckForLastFragment(BinaryLogItem *item, int *refMsgSeqNum) {
        unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);
        this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
		this->m_fastProtocolManager->ReadMsgSeqNumber();
        FastSnapshotInfo* info = this->m_fastProtocolManager->GetSnapshotInfo();
        if(info == NULL)
			return false;
		*refMsgSeqNum = info->LastMsgSeqNumProcessed;
        return info->LastFragment == 1;
    }
	inline int GetRouteFirst() {
		if(this->m_snapshotStartMsgSeqNum == -1)
			return -1;
		while(this->m_snapshotStartMsgSeqNum <= this->m_snapshotEndMsgSeqNum) {
			if(this->CheckForRouteFirst(this->m_packets[this->m_snapshotStartMsgSeqNum])) {
                DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_GetRouteFirst, true);
                return this->m_snapshotStartMsgSeqNum;
            }
            this->m_snapshotStartMsgSeqNum++;
		}
		return -1;
	}
	inline FastSnapshotInfo* GetSnapshotInfo(int index) {
		if(this->m_packets[index] == NULL)
			return NULL;
		BinaryLogItem *item = this->m_packets[index];
		unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);
		this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
		this->m_fastProtocolManager->ReadMsgSeqNumber();
		return this->m_fastProtocolManager->GetSnapshotInfo();
	}
    inline int GetLastFragment(int *refMsgSeqNum) {
		if(this->m_snapshotStartMsgSeqNum == -1)
			return -1;
        while(this->m_snapshotStartMsgSeqNum <= this->m_snapshotEndMsgSeqNum) {
            if (this->CheckForLastFragment(this->m_packets[this->m_snapshotStartMsgSeqNum], refMsgSeqNum)) {
                DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_GetLastFragment, false);
                return this->m_snapshotStartMsgSeqNum;
            }
            this->m_snapshotStartMsgSeqNum++;
        }
        return -1;
    }
    inline void ResetWaitTime() { this->m_waitTimer->Start(); }
    inline void StartWaitIncremental() { this->m_waitingSnapshot = false; }
    inline bool ActualMsgSeqNum() { return this->m_currentMsgSeqNum == this->m_maxRecvMsgSeqNum; }

	inline void IncrementMsgSeqNo() { this->m_currentMsgSeqNum++; }
	bool InitializeSockets();
	virtual ISocketBufferProvider* CreateSocketBufferProvider() {
			return new SocketBufferProvider(DefaultSocketBufferManager::Default,
											RobotSettings::DefaultFeedConnectionSendBufferSize,
											RobotSettings::DefaultFeedConnectionSendItemsCount,
											RobotSettings::DefaultFeedConnectionRecvBufferSize,
											RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
	virtual void ClearSocketBufferProvider() {
		//delete (SocketBufferProvider*)this->m_socketABufferProvider;
	}
	inline void SetState(FeedConnectionState state, FeedConnectionWorkAtomPtr funcPtr) {
		this->m_state = state;
		this->m_workAtomPtr = funcPtr;
	}
	inline void SetNextState(FeedConnectionState state, FeedConnectionWorkAtomPtr funcPtr) {
		this->m_nextState = state;
		this->m_nextWorkAtomPtr = funcPtr;
		this->m_shouldUseNextState = true;
	}

	bool Suspend_Atom();
	bool Listen_Atom();
    bool Listen_Atom_Incremental();
    bool Listen_Atom_Snapshot();
    bool SendLogon_Atom();
    bool ResendLastMessage_Atom();
    bool Reconnect_Atom();

    inline void ReconnectSetNextState(FeedConnectionState state, FeedConnectionWorkAtomPtr funcPtr) {
        this->SetNextState(state, funcPtr);
        this->SetState(FeedConnectionState::fcsConnect, &FeedConnection::Reconnect_Atom);
    }

    inline void JumpNextState() {
        this->SetState(this->m_nextState, this->m_nextWorkAtomPtr);
    }

    inline bool SendCore() {
        this->m_sendABuffer->SetCurrentItemSize(this->m_fastProtocolManager->MessageLength());
        DefaultLogManager::Default->WriteFast(LogMessageCode::lmcFeedConnection_SendCore, this->m_sendABuffer->BufferIndex(), this->m_sendABuffer->CurrentItemIndex());
        if(!this->socketAManager->Send(this->m_fastProtocolManager->Buffer(), this->m_fastProtocolManager->MessageLength())) {
            this->SetState(FeedConnectionState::fcsResendLastMessage, &FeedConnection::ResendLastMessage_Atom);
            DefaultLogManager::Default->EndLog(false);
            return true;
        }

        this->m_sendABuffer->Next(this->m_fastProtocolManager->MessageLength());
        this->SetState(FeedConnectionState::fcsListen, this->m_listenPtr);
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

	inline void AddOrderBookInfoFond(FastOBSFONDItemInfo *info) {
		this->m_orderBookTableFond->Add(info);
	}

	inline void ChangeOrderBookInfoFond(FastOBSFONDItemInfo *info) {
		this->m_orderBookTableFond->Change(info);
	}

	inline void RemoveOrderBookInfoFond(FastOBSFONDItemInfo *info) {
		this->m_orderBookTableFond->Remove(info);
	}

	inline void AddOrderBookInfoCurr(FastOBSCURRItemInfo *info) {
		this->m_orderBookTableCurr->Add(info);
	}

	inline void ChangeOrderBookInfoCurr(FastOBSCURRItemInfo *info) {
		this->m_orderBookTableCurr->Change(info);
	}

	inline void RemoveOrderBookInfoCurr(FastOBSCURRItemInfo *info) {
		this->m_orderBookTableCurr->Remove(info);
	}

	inline void AddOrderInfoFond(FastOLSFONDItemInfo *info) {
		this->m_orderTableFond->Add(info);
	}

	inline void ChangeOrderInfoFond(FastOLSFONDItemInfo *info) {
		this->m_orderTableFond->Change(info);
	}

	inline void RemoveOrderInfoFond(FastOLSFONDItemInfo *info) {
		this->m_orderTableFond->Remove(info);
	}

	inline void AddOrderInfoCurr(FastOLSCURRItemInfo *info) {
		this->m_orderTableCurr->Add(info);
	}

	inline void ChangeOrderInfoCurr(FastOLSCURRItemInfo *info) {
		this->m_orderTableCurr->Change(info);
	}

	inline void RemoveOrderInfoCurr(FastOLSCURRItemInfo *info) {
		this->m_orderTableCurr->Remove(info);
	}

	inline void AddTradeInfoCurr(FastTLSCURRItemInfo *info) {
		this->m_tradeTableCurr->Add(info);
	}

	inline void AddTradeInfoFond(FastTLSFONDItemInfo *info) {
		this->m_tradeTableFond->Add(info);
	}

	FILE *obrLogFile;
	inline bool OnIncrementalRefresh_OBR_FOND(FastOBSFONDItemInfo *info) {
		if(info->MDUpdateAction == MDUpdateAction::mduaAdd) {
			AddOrderBookInfoFond(info);
		}
		else if(info->MDUpdateAction == MDUpdateAction::mduaChange) {
			ChangeOrderBookInfoFond(info);
		}
		else if(info->MDUpdateAction == MDUpdateAction::mduaDelete) {
			RemoveOrderBookInfoFond(info);
		}

		return true;
	}

	inline bool OnIncrementalRefresh_OBR_CURR(FastOBSCURRItemInfo *info) {
		if(info->MDUpdateAction == MDUpdateAction::mduaAdd) {
			AddOrderBookInfoCurr(info);
		}
		else if(info->MDUpdateAction == MDUpdateAction::mduaChange) {
			ChangeOrderBookInfoCurr(info);
		}
		else if(info->MDUpdateAction == MDUpdateAction::mduaDelete) {
			RemoveOrderBookInfoCurr(info);
		}

		return true;
	}

	inline bool OnIncrementalRefresh_OLR_FOND(FastOLSFONDItemInfo *info) {
		if(info->MDEntryType[0] == mdetEmptyBook) { // fatal!!!!!
			return true; // TODO!!!!!
		}
		if(info->MDUpdateAction == MDUpdateAction::mduaAdd) {
			AddOrderInfoFond(info);
		}
		else if(info->MDUpdateAction == MDUpdateAction::mduaChange) {
			ChangeOrderInfoFond(info);
		}
		else if(info->MDUpdateAction == MDUpdateAction::mduaDelete) {
			RemoveOrderInfoFond(info);
		}

		return true;
	}

	inline bool OnIncrementalRefresh_OLR_CURR(FastOLSCURRItemInfo *info) {
		if(info->MDEntryType[0] == mdetEmptyBook) { // fatal!!!!!
			return true; // TODO!!!!!
		}
		if(info->MDUpdateAction == MDUpdateAction::mduaAdd) {
			AddOrderInfoCurr(info);
		}
		else if(info->MDUpdateAction == MDUpdateAction::mduaChange) {
			ChangeOrderInfoCurr(info);
		}
		else if(info->MDUpdateAction == MDUpdateAction::mduaDelete) {
			RemoveOrderInfoCurr(info);
		}

		return true;
	}

	inline bool OnIncrementalRefresh_TLR_FOND(FastTLSFONDItemInfo *info) {
		if(info->MDUpdateAction == MDUpdateAction::mduaAdd) {
			AddTradeInfoFond(info);
		}
		return true;
	}

	inline bool OnIncrementalRefresh_TLR_CURR(FastTLSCURRItemInfo *info) {
		if(info->MDUpdateAction == MDUpdateAction::mduaAdd) {
			AddTradeInfoCurr(info);
		}

		return true;
	}

	inline bool OnIncrementalRefresh_OBR_FOND(FastIncrementalOBRFONDInfo *info) {
		bool res = true;
		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			res |= this->OnIncrementalRefresh_OBR_FOND(info->GroupMDEntries[i]);
		}
		return res;
	}

    inline bool OnFullRefresh_OBS_FOND(FastOBSFONDInfo *info) {
        this->m_orderBookTableFond->Clear();
		this->m_orderBookTableFond->Add(info);
        return true;
    }

	inline bool OnIncrementalRefresh_OBR_CURR(FastIncrementalOBRCURRInfo *info) {
		bool res = true;
		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			res |= this->OnIncrementalRefresh_OBR_CURR(info->GroupMDEntries[i]);
		}
		return res;
	}

	inline bool OnFullRefresh_OBS_CURR(FastOBSCURRInfo *info) {
		this->m_orderBookTableCurr->Clear();
		this->m_orderBookTableCurr->Add(info);
		return true;
	}

	inline bool OnIncrementalRefresh_OLR_FOND(FastIncrementalOLRFONDInfo *info) {
		bool res = true;
		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			res |= this->OnIncrementalRefresh_OLR_FOND(info->GroupMDEntries[i]);
		}
		return res;
	}

	inline bool OnFullRefresh_OLS_FOND(FastOLSFONDInfo *info) {
		this->m_orderTableFond->Clear();
		this->m_orderTableFond->Add(info);
		return true;
	}

	inline bool OnIncrementalRefresh_OLR_CURR(FastIncrementalOLRCURRInfo *info) {
		bool res = true;
		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			res |= this->OnIncrementalRefresh_OLR_CURR(info->GroupMDEntries[i]);
		}
		return res;
	}

	inline bool OnFullRefresh_OLS_CURR(FastOLSCURRInfo *info) {
		this->m_orderTableCurr->Clear();
		this->m_orderTableCurr->Add(info);
		return true;
	}

	inline bool OnIncrementalRefresh_TLR_FOND(FastIncrementalTLRFONDInfo *info) {
		bool res = true;
		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			res |= this->OnIncrementalRefresh_TLR_FOND(info->GroupMDEntries[i]);
		}
		return res;
	}

	inline bool OnFullRefresh_TLS_FOND(FastTLSFONDInfo *info) {
		this->m_tradeTableFond->Clear();
		this->m_tradeTableFond->Add(info);
		return true;
	}

	inline bool OnIncrementalRefresh_TLR_CURR(FastIncrementalTLRCURRInfo *info) {
		bool res = true;
		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			res |= this->OnIncrementalRefresh_TLR_CURR(info->GroupMDEntries[i]);
		}
		return res;
	}

	inline bool OnFullRefresh_TLS_CURR(FastTLSCURRInfo *info) {
		this->m_tradeTableCurr->Clear();
		this->m_tradeTableCurr->Add(info);
		return true;
	}

	inline bool ApplyDecodedMessage() {
		switch(this->m_fastProtocolManager->TemplateId()) {
			case FeedConnectionMessage::fcmHeartBeat:
				break;
			case FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND:
				return this->OnIncrementalRefresh_OBR_FOND((FastIncrementalOBRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
            case FeedConnectionMessage::fmcFullRefresh_OBS_FOND:
                return this->OnFullRefresh_OBS_FOND((FastOBSFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OBR_CURR:
				return this->OnIncrementalRefresh_OBR_CURR((FastIncrementalOBRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcFullRefresh_OBS_CURR:
				return this->OnFullRefresh_OBS_CURR((FastOBSCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OLR_FOND:
				return this->OnIncrementalRefresh_OLR_FOND((FastIncrementalOLRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR:
				return this->OnIncrementalRefresh_OLR_CURR((FastIncrementalOLRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcFullRefresh_OLS_FOND:
				return this->OnFullRefresh_OLS_FOND((FastOLSFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcFullRefresh_OLS_CURR:
				return this->OnFullRefresh_OLS_CURR((FastOLSCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_TLR_FOND:
				return this->OnIncrementalRefresh_TLR_FOND((FastIncrementalTLRFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcFullRefresh_TLS_FOND:
				return this->OnFullRefresh_TLS_FOND((FastTLSFONDInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcIncrementalRefresh_TLR_CURR:
				return this->OnIncrementalRefresh_TLR_CURR((FastIncrementalTLRCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
			case FeedConnectionMessage::fmcFullRefresh_TLS_CURR:
				return this->OnFullRefresh_TLS_CURR((FastTLSCURRInfo*)this->m_fastProtocolManager->LastDecodeInfo());
		}
		return true;
	}

	inline bool ProcessMessage(BinaryLogItem *item) {
        unsigned char *buffer = this->m_recvABuffer->Item(item->m_itemIndex);

		//TODO remove unused logging
		int length = this->m_recvABuffer->ItemLength(item->m_itemIndex);
		fprintf(this->obrLogFile, "unsigned char *msg%d = new unsigned char [%d] { ", item->m_itemIndex, length);
		for(int i = 0; i < length; i++) {
			fprintf(this->obrLogFile, "0x%2.2x", buffer[i]);
			if(i < length - 1)
				fprintf(this->obrLogFile, ", ");
		}
		fprintf(this->obrLogFile, "};\n");
		fflush(this->obrLogFile);
		//till this

		this->m_fastProtocolManager->SetNewBuffer(buffer, this->m_recvABuffer->ItemLength(item->m_itemIndex));
        this->m_fastProtocolManager->ReadMsgSeqNumber();
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);
		this->m_fastProtocolManager->Decode();
		this->m_fastProtocolManager->Print();
		this->ApplyDecodedMessage();
		DefaultLogManager::Default->EndLog(true);
        return true;
	}
public:
	FeedConnection(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort);
	~FeedConnection();

    inline int LastMsgSeqNumProcessed() { return this->m_lastMsgSeqNumProcessed; }
	inline MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo> *OrderBookFond() { return this->m_orderBookTableFond; }
	inline MarketDataTable<OrderBookTableItem, FastOBSCURRInfo, FastOBSCURRItemInfo> *OrderBookCurr() { return this->m_orderBookTableCurr; }
	inline MarketDataTable<OrderTableItem, FastOLSFONDInfo, FastOLSFONDItemInfo> *OrderFond() { return this->m_orderTableFond; }
	inline MarketDataTable<OrderTableItem, FastOLSCURRInfo, FastOLSCURRItemInfo> *OrderCurr() { return this->m_orderTableCurr; }
	inline MarketDataTable<TradeTableItem, FastTLSFONDInfo, FastTLSFONDItemInfo> *TradeFond() { return this->m_tradeTableFond; }
	inline MarketDataTable<TradeTableItem, FastTLSCURRInfo, FastTLSCURRItemInfo> *TradeCurr() { return this->m_tradeTableCurr; }

    inline void StartNewSnapshot() {
        DefaultLogManager::Default->WriteSuccess(this->m_idLogIndex, LogMessageCode::lmcFeedConnection_StartNewSnapshot, true);
        this->m_snapshotAvailable = false;
        this->m_snapshotEndMsgSeqNum = -1;
        this->m_snapshotStartMsgSeqNum = -1;
        this->m_snapshotRouteFirst = -1;
        this->m_snapshotLastFragment = -1;
    }

    inline void SetType(FeedConnectionType type) {
        this->m_type = type;
        this->m_listenPtr = this->m_type == FeedConnectionType::Incremental? &FeedConnection::Listen_Atom_Incremental: &FeedConnection::Listen_Atom_Snapshot;
		if(this->m_state == FeedConnectionState::fcsListen)
			this->SetState(this->m_state, this->m_listenPtr);
		else if(this->m_nextState == FeedConnectionState::fcsListen)
			this->SetNextState(this->m_state, this->m_listenPtr);
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
    inline FeedConnection *Snapshot() { return this->m_snapshot; }

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
    }
    void SetPassword(const char *password) {
        this->m_password = password;
        this->m_passwordLength = strlen(this->m_password);
    }

    inline char* Id() { return this->id; }

	inline virtual void Decode() {
		DefaultLogManager::Default->StartLog(this->m_feedTypeNameLogIndex, LogMessageCode::lmcFeedConnection_Decode);

		DefaultLogManager::Default->EndLog(true);
	}

	inline int MsgSeqNo() { return this->m_currentMsgSeqNum; }
	inline int ExpectedMsgSeqNo() { return this->m_currentMsgSeqNum + 1; }

	inline bool DoWorkAtom() {
		return (this->*m_workAtomPtr)();
	}
	inline void Listen() {
		if(this->m_state == FeedConnectionState::fcsSuspend)
			this->SetState(FeedConnectionState::fcsListen, this->m_listenPtr);
		else
			this->SetNextState(FeedConnectionState::fcsListen, this->m_listenPtr);
	}
    inline bool Start() {
        if(!this->Connect())
			return false;
		if(this->m_state != FeedConnectionState::fcsSuspend)
            return true;
        this->m_waitTimer->Start();
        this->Listen();
		return true;
    }
	inline bool Stop() {
		this->SetState(FeedConnectionState::fcsSuspend, &FeedConnection::Suspend_Atom);
		if(!this->Disconnect())
			return false;
		return true;
	}
};

class FeedConnection_CURR_OBR : public FeedConnection {
public:
	FeedConnection_CURR_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {

		this->SetType(FeedConnectionType::Incremental);
		this->m_orderBookTableCurr = new MarketDataTable<OrderBookTableItem, FastOBSCURRInfo, FastOBSCURRItemInfo>();
    }
	~FeedConnection_CURR_OBR() {
		delete this->m_orderBookTableCurr;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OBS : public FeedConnection {
public:
	FeedConnection_CURR_OBS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {

		this->SetType(FeedConnectionType::Snapshot);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_MSR : public FeedConnection {
public:
	FeedConnection_CURR_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_MSS : public FeedConnection {
public:
	FeedConnection_CURR_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OLR : public FeedConnection {
public:
	FeedConnection_CURR_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_orderTableCurr = new MarketDataTable<OrderTableItem, FastOLSCURRInfo, FastOLSCURRItemInfo>();
    }
	~FeedConnection_CURR_OLR() {
		delete this->m_orderTableCurr;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_OLS : public FeedConnection {
public:
	FeedConnection_CURR_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_TLR : public FeedConnection {
public:
	FeedConnection_CURR_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_CURR_TLS : public FeedConnection {
public:
	FeedConnection_CURR_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
		this->m_tradeTableCurr = new MarketDataTable<TradeTableItem, FastTLSCURRInfo, FastTLSCURRItemInfo>();
    }
	~FeedConnection_CURR_TLS() {
		delete this->m_tradeTableCurr;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OBR : public FeedConnection {
public:
	FeedConnection_FOND_OBR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_orderBookTableFond = new MarketDataTable<OrderBookTableItem, FastOBSFONDInfo, FastOBSFONDItemInfo>();
    }
	~FeedConnection_FOND_OBR() {
		delete this->m_orderBookTableFond;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OBS : public FeedConnection {
public:
	FeedConnection_FOND_OBS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_MSR : public FeedConnection {
public:
	FeedConnection_FOND_MSR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_MSS : public FeedConnection {
public:
	FeedConnection_FOND_MSS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OLR : public FeedConnection {
public:
	FeedConnection_FOND_OLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_orderTableFond = new MarketDataTable<OrderTableItem, FastOLSFONDInfo, FastOLSFONDItemInfo>();
    }
	~FeedConnection_FOND_OLR() {
		delete this->m_orderTableFond;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_OLS : public FeedConnection {
public:
	FeedConnection_FOND_OLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_TLR : public FeedConnection {
public:
	FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Incremental);
		this->m_tradeTableFond = new MarketDataTable<TradeTableItem, FastTLSFONDInfo, FastTLSFONDItemInfo>();
    }
	~FeedConnection_FOND_TLR() {
		delete this->m_tradeTableFond;
	}
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

class FeedConnection_FOND_TLS : public FeedConnection {
public:
	FeedConnection_FOND_TLS(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
		FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
		this->SetType(FeedConnectionType::Snapshot);
    }
	ISocketBufferProvider* CreateSocketBufferProvider() {
		return new SocketBufferProvider(DefaultSocketBufferManager::Default,
										RobotSettings::DefaultFeedConnectionSendBufferSize,
										RobotSettings::DefaultFeedConnectionSendItemsCount,
										RobotSettings::DefaultFeedConnectionRecvBufferSize,
										RobotSettings::DefaultFeedConnectionRecvItemsCount);
	}
};

