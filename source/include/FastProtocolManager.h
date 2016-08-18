#pragma once
#include "FixTypes.h"
#include <stdio.h>

#define FAST_STOPBIT_FIRST_BYTE 		0x00000080L
#define FAST_STOPBIT_SECOND_BYTE		0x00008000L
#define FAST_STOPBIT_THIRD_BYTE			0x00800000L
#define FAST_STOPBIT_FORTH_BYTE			0x80000000L

#pragma region Message_Info_Structures_Definition_GeneratedCode
#define PRESENCE_MAP_INDEX0  0x00000040
#define PRESENCE_MAP_INDEX1  0x00000020
#define PRESENCE_MAP_INDEX2  0x00000010
#define PRESENCE_MAP_INDEX3  0x00000008
#define PRESENCE_MAP_INDEX4  0x00000004
#define PRESENCE_MAP_INDEX5  0x00000002
#define PRESENCE_MAP_INDEX6  0x00000001
#define PRESENCE_MAP_INDEX7  0x00004000
#define PRESENCE_MAP_INDEX8  0x00002000
#define PRESENCE_MAP_INDEX9  0x00001000
#define PRESENCE_MAP_INDEX10 0x00000800
#define PRESENCE_MAP_INDEX11 0x00000400
#define PRESENCE_MAP_INDEX12 0x00000200
#define PRESENCE_MAP_INDEX13 0x00000100
#define PRESENCE_MAP_INDEX14 0x00400000
#define PRESENCE_MAP_INDEX15 0x00200000
#define PRESENCE_MAP_INDEX16 0x00100000
#define PRESENCE_MAP_INDEX17 0x00080000
#define PRESENCE_MAP_INDEX18 0x00040000
#define PRESENCE_MAP_INDEX19 0x00020000
#define PRESENCE_MAP_INDEX20 0x00010000
#define PRESENCE_MAP_INDEX21 0x40000000
#define PRESENCE_MAP_INDEX22 0x20000000
#define PRESENCE_MAP_INDEX23 0x10000000
#define PRESENCE_MAP_INDEX24 0x08000000
#define PRESENCE_MAP_INDEX25 0x04000000
#define PRESENCE_MAP_INDEX26 0x02000000
#define PRESENCE_MAP_INDEX27 0x01000000

typedef struct _FastHeaderInfo {
	UINT							PresenceMap;
	char*							MessageType;			// id=35    constant has constant value = A
	int							MessageTypeLength;
}FastHeaderInfo;

typedef struct _FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							QuoteCondition;			// id=276  presence=optional  
	int							QuoteConditionLength;
	bool							AllowQuoteCondition;
	char*							TradeCondition;			// id=277  presence=optional  
	int							TradeConditionLength;
	bool							AllowTradeCondition;
	char*							OpenCloseSettlFlag;			// id=286  presence=optional  
	int							OpenCloseSettlFlagLength;
	bool							AllowOpenCloseSettlFlag;
	char*							OrdType;			// id=40  presence=optional  
	int							OrdTypeLength;
	bool							AllowOrdType;
	UINT32							EffectiveTime;			// id=5902  presence=optional  
	bool							AllowEffectiveTime;
	UINT32							StartTime;			// id=9820  presence=optional  
	bool							AllowStartTime;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	bool							AllowAccruedInterestAmt;
	Decimal							ChgFromWAPrice;			// id=5510  presence=optional  
	bool							AllowChgFromWAPrice;
	Decimal							ChgOpenInterest;			// id=5511  presence=optional  
	bool							AllowChgOpenInterest;
	Decimal							BidMarketSize;			// id=5292  presence=optional  
	bool							AllowBidMarketSize;
	Decimal							AskMarketSize;			// id=5293  presence=optional  
	bool							AllowAskMarketSize;
	INT32							TotalNumOfTrades;			// id=6139  presence=optional  
	bool							AllowTotalNumOfTrades;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	Decimal							TotalVolume;			// id=5791  presence=optional  
	bool							AllowTotalVolume;
	INT32							OfferNbOr;			// id=9168  presence=optional  
	bool							AllowOfferNbOr;
	INT32							BidNbOr;			// id=9169  presence=optional  
	bool							AllowBidNbOr;
	Decimal							ChgFromSettlmnt;			// id=9750  presence=optional  
	bool							AllowChgFromSettlmnt;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	INT32							SumQtyOfBest;			// id=10503  presence=optional  
	bool							AllowSumQtyOfBest;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	Decimal							MinCurrPx;			// id=10509  presence=optional  
	bool							AllowMinCurrPx;
	UINT32							MinCurrPxChgTime;			// id=10510  presence=optional  
	bool							AllowMinCurrPxChgTime;
	UINT32							VolumeIndicator;			// id=7017  presence=optional  
	bool							AllowVolumeIndicator;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							NominalValue;			// id=9280  presence=optional  
	bool							AllowNominalValue;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	char*							CXFlag;			// id=5154  presence=optional    copy
	int							CXFlagLength;
	char*							PrevCXFlag; // copy
	int							PrevCXFlagLength; // copy
	bool							AllowCXFlag;
	const UINT							CXFlagPresenceIndex = PRESENCE_MAP_INDEX1;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							EffectiveTime;			// id=5902  presence=optional  
	bool							AllowEffectiveTime;
	UINT32							StartTime;			// id=9820  presence=optional  
	bool							AllowStartTime;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							QuoteCondition;			// id=276  presence=optional  
	int							QuoteConditionLength;
	bool							AllowQuoteCondition;
	char*							TradeCondition;			// id=277  presence=optional  
	int							TradeConditionLength;
	bool							AllowTradeCondition;
	char*							OpenCloseSettlFlag;			// id=286  presence=optional  
	int							OpenCloseSettlFlagLength;
	bool							AllowOpenCloseSettlFlag;
	char*							OrdType;			// id=40  presence=optional  
	int							OrdTypeLength;
	bool							AllowOrdType;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	bool							AllowNetChgPrevDay;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	bool							AllowAccruedInterestAmt;
	Decimal							ChgFromWAPrice;			// id=5510  presence=optional  
	bool							AllowChgFromWAPrice;
	Decimal							ChgOpenInterest;			// id=5511  presence=optional  
	bool							AllowChgOpenInterest;
	Decimal							BidMarketSize;			// id=5292  presence=optional  
	bool							AllowBidMarketSize;
	Decimal							AskMarketSize;			// id=5293  presence=optional  
	bool							AllowAskMarketSize;
	INT32							TotalNumOfTrades;			// id=6139  presence=optional  
	bool							AllowTotalNumOfTrades;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	Decimal							TotalVolume;			// id=5791  presence=optional  
	bool							AllowTotalVolume;
	INT32							OfferNbOr;			// id=9168  presence=optional  
	bool							AllowOfferNbOr;
	INT32							BidNbOr;			// id=9169  presence=optional  
	bool							AllowBidNbOr;
	Decimal							ChgFromSettlmnt;			// id=9750  presence=optional  
	bool							AllowChgFromSettlmnt;
	INT32							SumQtyOfBest;			// id=10503  presence=optional  
	bool							AllowSumQtyOfBest;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	Decimal							MinCurrPx;			// id=10509  presence=optional  
	bool							AllowMinCurrPx;
	UINT32							MinCurrPxChgTime;			// id=10510  presence=optional  
	bool							AllowMinCurrPxChgTime;
	UINT32							VolumeIndicator;			// id=7017  presence=optional  
	bool							AllowVolumeIndicator;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							NominalValue;			// id=9280  presence=optional  
	bool							AllowNominalValue;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	char*							CXFlag;			// id=5154  presence=optional    copy
	int							CXFlagLength;
	char*							PrevCXFlag; // copy
	int							PrevCXFlagLength; // copy
	bool							AllowCXFlag;
	const UINT							CXFlagPresenceIndex = PRESENCE_MAP_INDEX1;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	char*							OrdType;			// id=40  presence=optional  
	int							OrdTypeLength;
	bool							AllowOrdType;
	Decimal							TotalVolume;			// id=5791  presence=optional  
	bool							AllowTotalVolume;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	char*							MDEntryType;			// id=269  
	int							MDEntryTypeLength;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	bool							AllowAccruedInterestAmt;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	char*							MDEntryType;			// id=269  
	int							MDEntryTypeLength;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	UINT32							EffectiveTime;			// id=5902  presence=optional  
	bool							AllowEffectiveTime;
	Decimal							NominalValue;			// id=9280  presence=optional  
	bool							AllowNominalValue;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							StartTime;			// id=9820  presence=optional  
	bool							AllowStartTime;
	char*							QuoteCondition;			// id=276  presence=optional  
	int							QuoteConditionLength;
	bool							AllowQuoteCondition;
	char*							TradeCondition;			// id=277  presence=optional  
	int							TradeConditionLength;
	bool							AllowTradeCondition;
	char*							OpenCloseSettlFlag;			// id=286  presence=optional  
	int							OpenCloseSettlFlagLength;
	bool							AllowOpenCloseSettlFlag;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	bool							AllowNetChgPrevDay;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	bool							AllowAccruedInterestAmt;
	Decimal							ChgFromWAPrice;			// id=5510  presence=optional  
	bool							AllowChgFromWAPrice;
	Decimal							ChgOpenInterest;			// id=5511  presence=optional  
	bool							AllowChgOpenInterest;
	Decimal							BidMarketSize;			// id=5292  presence=optional  
	bool							AllowBidMarketSize;
	Decimal							AskMarketSize;			// id=5293  presence=optional  
	bool							AllowAskMarketSize;
	INT32							TotalNumOfTrades;			// id=6139  presence=optional  
	bool							AllowTotalNumOfTrades;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	INT32							OfferNbOr;			// id=9168  presence=optional  
	bool							AllowOfferNbOr;
	INT32							BidNbOr;			// id=9169  presence=optional  
	bool							AllowBidNbOr;
	Decimal							ChgFromSettlmnt;			// id=9750  presence=optional  
	bool							AllowChgFromSettlmnt;
	Decimal							MinCurrPx;			// id=10509  presence=optional  
	bool							AllowMinCurrPx;
	UINT32							MinCurrPxChgTime;			// id=10510  presence=optional  
	bool							AllowMinCurrPxChgTime;
	UINT32							VolumeIndicator;			// id=7017  presence=optional  
	bool							AllowVolumeIndicator;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	char*							CXFlag;			// id=5154  presence=optional    copy
	int							CXFlagLength;
	char*							PrevCXFlag; // copy
	int							PrevCXFlagLength; // copy
	bool							AllowCXFlag;
	const UINT							CXFlagPresenceIndex = PRESENCE_MAP_INDEX0;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	char*							QuoteCondition;			// id=276  presence=optional  
	int							QuoteConditionLength;
	bool							AllowQuoteCondition;
	char*							TradeCondition;			// id=277  presence=optional  
	int							TradeConditionLength;
	bool							AllowTradeCondition;
	char*							OpenCloseSettlFlag;			// id=286  presence=optional  
	int							OpenCloseSettlFlagLength;
	bool							AllowOpenCloseSettlFlag;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	bool							AllowNetChgPrevDay;
	Decimal							ChgFromWAPrice;			// id=5510  presence=optional  
	bool							AllowChgFromWAPrice;
	Decimal							ChgOpenInterest;			// id=5511  presence=optional  
	bool							AllowChgOpenInterest;
	INT32							TotalNumOfTrades;			// id=6139  presence=optional  
	bool							AllowTotalNumOfTrades;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	INT32							OfferNbOr;			// id=9168  presence=optional  
	bool							AllowOfferNbOr;
	INT32							BidNbOr;			// id=9169  presence=optional  
	bool							AllowBidNbOr;
	Decimal							ChgFromSettlmnt;			// id=9750  presence=optional  
	bool							AllowChgFromSettlmnt;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	char*							CXFlag;			// id=5154  presence=optional    copy
	int							CXFlagLength;
	char*							PrevCXFlag; // copy
	int							PrevCXFlagLength; // copy
	bool							AllowCXFlag;
	const UINT							CXFlagPresenceIndex = PRESENCE_MAP_INDEX0;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	char*							OrdType;			// id=40  presence=optional  
	int							OrdTypeLength;
	bool							AllowOrdType;
	Decimal							TotalVolume;			// id=5791  presence=optional  
	bool							AllowTotalVolume;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	char*							DealNumber;			// id=9885  presence=optional    copy
	int							DealNumberLength;
	char*							PrevDealNumber; // copy
	int							PrevDealNumberLength; // copy
	bool							AllowDealNumber;
	const UINT							DealNumberPresenceIndex = PRESENCE_MAP_INDEX0;
	char*							OrderStatus;			// id=10505  presence=optional  
	int							OrderStatusLength;
	bool							AllowOrderStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	UINT32							EffectiveTime;			// id=5902  presence=optional  
	bool							AllowEffectiveTime;
	Decimal							NominalValue;			// id=9280  presence=optional  
	bool							AllowNominalValue;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  presence=optional  
	int							MDEntryTypeLength;
	bool							AllowMDEntryType;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  
	int							MDEntryTypeLength;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	Decimal							AccruedInterestAmt;			// id=5384  presence=optional  
	bool							AllowAccruedInterestAmt;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	Decimal							Yield;			// id=236  presence=optional  
	bool							AllowYield;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo;

typedef struct _FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo {
	UINT							PresenceMap;
	UINT32							MDUpdateAction;			// id=279  presence=optional  
	bool							AllowMDUpdateAction;
	char*							MDEntryType;			// id=269  
	int							MDEntryTypeLength;
	char*							MDEntryID;			// id=278  presence=optional  
	int							MDEntryIDLength;
	bool							AllowMDEntryID;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	INT32							RptSeq;			// id=83  presence=optional  
	bool							AllowRptSeq;
	UINT32							MDEntryDate;			// id=272  presence=optional  
	bool							AllowMDEntryDate;
	UINT32							MDEntryTime;			// id=273  presence=optional  
	bool							AllowMDEntryTime;
	UINT32							OrigTime;			// id=9412  presence=optional  
	bool							AllowOrigTime;
	char*							OrderSide;			// id=10504  presence=optional  
	int							OrderSideLength;
	bool							AllowOrderSide;
	Decimal							MDEntryPx;			// id=270  presence=optional  
	bool							AllowMDEntryPx;
	Decimal							MDEntrySize;			// id=271  presence=optional  
	bool							AllowMDEntrySize;
	Decimal							TradeValue;			// id=6143  presence=optional  
	bool							AllowTradeValue;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	Decimal							Price;			// id=44  presence=optional  
	bool							AllowPrice;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
}FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo;

typedef struct _FastSecurityDefinitionGroupInstrAttribItemInfo {
	UINT							PresenceMap;
	INT32							InstrAttribType;			// id=871  
	BYTE*							InstrAttribValue;			// id=872  presence=optional  
	int							InstrAttribValueLength;
	bool							AllowInstrAttribValue;
}FastSecurityDefinitionGroupInstrAttribItemInfo;

typedef struct _FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo {
	UINT							PresenceMap;
	char*							TradingSessionID;			// id=336  
	int							TradingSessionIDLength;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	bool							AllowSecurityTradingStatus;
	INT32							OrderNote;			// id=9680  presence=optional  
	bool							AllowOrderNote;
}FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo;

typedef struct _FastSecurityDefinitionMarketSegmentGrpItemInfo {
	UINT							PresenceMap;
	Decimal							RoundLot;			// id=561  presence=optional  
	bool							AllowRoundLot;
	int							TradingSessionRulesGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo** TradingSessionRulesGrp;			// presence=optional  
	bool							AllowTradingSessionRulesGrp;
}FastSecurityDefinitionMarketSegmentGrpItemInfo;

typedef struct _FastLogonInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	char*							TargetCompID;			// id=56  
	int							TargetCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	INT32							HeartBtInt;			// id=108  
	char*							Username;			// id=553  presence=optional  
	int							UsernameLength;
	bool							AllowUsername;
	char*							Password;			// id=554  presence=optional  
	int							PasswordLength;
	bool							AllowPassword;
	char*							DefaultApplVerID;			// id=1137  
	int							DefaultApplVerIDLength;
}FastLogonInfo;

typedef struct _FastLogoutInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	char*							TargetCompID;			// id=56  
	int							TargetCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char*							Text;			// id=58  presence=optional  
	int							TextLength;
	bool							AllowText;
}FastLogoutInfo;

typedef struct _FastMarketDataSnapshotFullRefreshGenericInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
	Decimal							NetChgPrevDay;			// id=451  presence=optional  
	bool							AllowNetChgPrevDay;
	int							GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshGenericInfo;

typedef struct _FastMarketDataIncrementalRefreshGenericInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshGenericInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOLSFONDInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
	int							GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshOLSFONDInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOLSCURRInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	int							GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshOLSCURRInfo;

typedef struct _FastMarketDataSnapshotFullRefreshTLSFONDInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
	int							GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshTLSFONDInfo;

typedef struct _FastMarketDataSnapshotFullRefreshTLSCURRInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	int							GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshTLSCURRInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOBSFONDInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
	int							GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshOBSFONDInfo;

typedef struct _FastMarketDataSnapshotFullRefreshOBSCURRInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	UINT32							LastMsgSeqNumProcessed;			// id=369  presence=optional  
	bool							AllowLastMsgSeqNumProcessed;
	INT32							RptSeq;			// id=83  
	INT32							TradSesStatus;			// id=340  presence=optional  
	bool							AllowTradSesStatus;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							Symbol;			// id=55  
	int							SymbolLength;
	UINT32							LastFragment;			// id=893  presence=optional  
	bool							AllowLastFragment;
	UINT32							RouteFirst;			// id=7944  presence=optional  
	bool							AllowRouteFirst;
	INT32							MDSecurityTradingStatus;			// id=1682  presence=optional  
	bool							AllowMDSecurityTradingStatus;
	int							GroupMDEntriesCount;
	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataSnapshotFullRefreshOBSCURRInfo;

typedef struct _FastMarketDataIncrementalRefreshMSRFONDInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshMSRFONDInfo;

typedef struct _FastMarketDataIncrementalRefreshMSRCURRInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshMSRCURRInfo;

typedef struct _FastMarketDataIncrementalRefreshOLRFONDInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshOLRFONDInfo;

typedef struct _FastMarketDataIncrementalRefreshOLRCURRInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshOLRCURRInfo;

typedef struct _FastMarketDataIncrementalRefreshOBRFONDInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshOBRFONDInfo;

typedef struct _FastMarketDataIncrementalRefreshOBRCURRInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshOBRCURRInfo;

typedef struct _FastMarketDataIncrementalRefreshTLRFONDInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshTLRFONDInfo;

typedef struct _FastMarketDataIncrementalRefreshTLRCURRInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	int							GroupMDEntriesCount;
	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo** GroupMDEntries;
}FastMarketDataIncrementalRefreshTLRCURRInfo;

typedef struct _FastSecurityDefinitionInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34    increment
	const UINT							MsgSeqNumPresenceIndex = PRESENCE_MAP_INDEX0;
	UINT64							SendingTime;			// id=52  
	char*							MessageEncoding;			// id=347    default
	int							MessageEncodingLength;
	const UINT							MessageEncodingPresenceIndex = PRESENCE_MAP_INDEX1;
	INT32							TotNumReports;			// id=911  presence=optional  
	bool							AllowTotNumReports;
	char*							Symbol;			// id=55  presence=optional  
	int							SymbolLength;
	bool							AllowSymbol;
	BYTE*							SecurityID;			// id=48  presence=optional  
	int							SecurityIDLength;
	bool							AllowSecurityID;
	BYTE*							SecurityIDSource;			// id=22  presence=optional  
	int							SecurityIDSourceLength;
	bool							AllowSecurityIDSource;
	INT32							Product;			// id=460  presence=optional  
	bool							AllowProduct;
	BYTE*							CFICode;			// id=461  presence=optional  
	int							CFICodeLength;
	bool							AllowCFICode;
	BYTE*							SecurityType;			// id=167  presence=optional  
	int							SecurityTypeLength;
	bool							AllowSecurityType;
	UINT32							MaturityDate;			// id=541  presence=optional  
	bool							AllowMaturityDate;
	UINT32							SettlDate;			// id=64  presence=optional  
	bool							AllowSettlDate;
	char*							SettleType;			// id=5459  presence=optional  
	int							SettleTypeLength;
	bool							AllowSettleType;
	Decimal							OrigIssueAmt;			// id=5850  presence=optional  
	bool							AllowOrigIssueAmt;
	UINT32							CouponPaymentDate;			// id=224  presence=optional  
	bool							AllowCouponPaymentDate;
	Decimal							CouponRate;			// id=223  presence=optional  
	bool							AllowCouponRate;
	UINT32							SettlFixingDate;			// id=9119  presence=optional  
	bool							AllowSettlFixingDate;
	Decimal							DividendNetPx;			// id=9982  presence=optional  
	bool							AllowDividendNetPx;
	BYTE*							SecurityDesc;			// id=107  presence=optional  
	int							SecurityDescLength;
	bool							AllowSecurityDesc;
	BYTE*							EncodedSecurityDesc;			// id=351  presence=optional  
	int							EncodedSecurityDescLength;
	bool							AllowEncodedSecurityDesc;
	BYTE*							QuoteText;			// id=9696  presence=optional  
	int							QuoteTextLength;
	bool							AllowQuoteText;
	int							GroupInstrAttribCount;			// presence=optional  
	FastSecurityDefinitionGroupInstrAttribItemInfo** GroupInstrAttrib;			// presence=optional  
	bool							AllowGroupInstrAttrib;
	char*							Currency;			// id=15  presence=optional  
	int							CurrencyLength;
	bool							AllowCurrency;
	int							MarketSegmentGrpCount;			// presence=optional  
	FastSecurityDefinitionMarketSegmentGrpItemInfo** MarketSegmentGrp;			// presence=optional  
	bool							AllowMarketSegmentGrp;
	char*							SettlCurrency;			// id=120  presence=optional  
	int							SettlCurrencyLength;
	bool							AllowSettlCurrency;
	INT32							PriceType;			// id=423  presence=optional  
	bool							AllowPriceType;
	char*							StateSecurityID;			// id=5217  presence=optional  
	int							StateSecurityIDLength;
	bool							AllowStateSecurityID;
	BYTE*							EncodedShortSecurityDesc;			// id=5383  presence=optional  
	int							EncodedShortSecurityDescLength;
	bool							AllowEncodedShortSecurityDesc;
	BYTE*							MarketCode;			// id=5385  presence=optional  
	int							MarketCodeLength;
	bool							AllowMarketCode;
	Decimal							MinPriceIncrement;			// id=969  presence=optional  
	bool							AllowMinPriceIncrement;
	Decimal							MktShareLimit;			// id=5387  presence=optional  
	bool							AllowMktShareLimit;
	Decimal							MktShareThreshold;			// id=5388  presence=optional  
	bool							AllowMktShareThreshold;
	Decimal							MaxOrdersVolume;			// id=5389  presence=optional  
	bool							AllowMaxOrdersVolume;
	Decimal							PriceMvmLimit;			// id=5470  presence=optional  
	bool							AllowPriceMvmLimit;
	Decimal							FaceValue;			// id=5508  presence=optional  
	bool							AllowFaceValue;
	Decimal							BaseSwapPx;			// id=5556  presence=optional  
	bool							AllowBaseSwapPx;
	Decimal							RepoToPx;			// id=5677  presence=optional  
	bool							AllowRepoToPx;
	Decimal							BuyBackPx;			// id=5558  presence=optional  
	bool							AllowBuyBackPx;
	UINT32							BuyBackDate;			// id=5559  presence=optional  
	bool							AllowBuyBackDate;
	Decimal							NoSharesIssued;			// id=7595  presence=optional  
	bool							AllowNoSharesIssued;
	Decimal							HighLimit;			// id=9199  presence=optional  
	bool							AllowHighLimit;
	Decimal							LowLimit;			// id=9200  presence=optional  
	bool							AllowLowLimit;
	INT32							NumOfDaysToMaturity;			// id=10508  presence=optional  
	bool							AllowNumOfDaysToMaturity;
}FastSecurityDefinitionInfo;

typedef struct _FastSecurityStatusInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	char*							Symbol;			// id=55  
	int							SymbolLength;
	char*							TradingSessionID;			// id=336  presence=optional  
	int							TradingSessionIDLength;
	bool							AllowTradingSessionID;
	char*							TradingSessionSubID;			// id=625  presence=optional  
	int							TradingSessionSubIDLength;
	bool							AllowTradingSessionSubID;
	INT32							SecurityTradingStatus;			// id=326  presence=optional  
	bool							AllowSecurityTradingStatus;
	UINT32							AuctionIndicator;			// id=5509  presence=optional  
	bool							AllowAuctionIndicator;
}FastSecurityStatusInfo;

typedef struct _FastTradingSessionStatusInfo {
	UINT							PresenceMap;
	char*							ApplVerID;			// id=1128    constant has constant value = 9
	int							ApplVerIDLength;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
	INT32							TradSesStatus;			// id=340  
	char*							Text;			// id=58  presence=optional  
	int							TextLength;
	bool							AllowText;
	char*							TradingSessionID;			// id=336  
	int							TradingSessionIDLength;
}FastTradingSessionStatusInfo;

typedef struct _FastHeartbeatInfo {
	UINT							PresenceMap;
	char*							BeginString;			// id=8    constant has constant value = FIXT.1.1
	int							BeginStringLength;
	char*							SenderCompID;			// id=49    constant has constant value = MOEX
	int							SenderCompIDLength;
	UINT32							MsgSeqNum;			// id=34  
	UINT64							SendingTime;			// id=52  
}FastHeartbeatInfo;

#pragma endregion

class FastProtocolManager;

#pragma region Decode_Method_Pointer_Definition_GeneratedCode
typedef void* (FastProtocolManager::*FastDecodeMethodPointer)();
#pragma endregion

#pragma region Checking_Presence_GeneratedCode
#define CheckMandatoryFieldPresence(map, field) ((map & field) != 0)
#define CheckOptionalFieldPresence(map, field) ((map & field) != 0)
#pragma endregion

class FastProtocolManager {
	const int maxBufferLength = 16000;
	BYTE	*buffer;
	BYTE	*currentPos;
	int		bufferLength;

    unsigned int     m_sendMsgSeqNo;
    unsigned int     m_recvMsgSeqNo;

#pragma region String_Constant_Declaration_GeneratedCode
public:
	char	MessageEncodingConstString[6];
	const UINT	MessageEncodingConstStringLength = 5;
private:

	void InitializeConstantStrings() {
		sprintf(MessageEncodingConstString, "UTF-8");
	}
#pragma endregion

#pragma region Structure_Objects_Declaration_GeneratedCode
	FastHeaderInfo*	m_header;
	FastLogonInfo*	m_logon;
	FastLogoutInfo*	m_logout;
	FastMarketDataSnapshotFullRefreshGenericInfo*	m_marketDataSnapshotFullRefreshGeneric;
	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshGenericInfo*	m_marketDataIncrementalRefreshGeneric;
	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshGenericGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOLSFONDInfo*	m_marketDataSnapshotFullRefreshOLSFOND;
	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOLSCURRInfo*	m_marketDataSnapshotFullRefreshOLSCURR;
	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshTLSFONDInfo*	m_marketDataSnapshotFullRefreshTLSFOND;
	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshTLSCURRInfo*	m_marketDataSnapshotFullRefreshTLSCURR;
	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOBSFONDInfo*	m_marketDataSnapshotFullRefreshOBSFOND;
	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems;
	FastMarketDataSnapshotFullRefreshOBSCURRInfo*	m_marketDataSnapshotFullRefreshOBSCURR;
	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo*	m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshMSRFONDInfo*	m_marketDataIncrementalRefreshMSRFOND;
	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshMSRCURRInfo*	m_marketDataIncrementalRefreshMSRCURR;
	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOLRFONDInfo*	m_marketDataIncrementalRefreshOLRFOND;
	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOLRCURRInfo*	m_marketDataIncrementalRefreshOLRCURR;
	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOBRFONDInfo*	m_marketDataIncrementalRefreshOBRFOND;
	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshOBRCURRInfo*	m_marketDataIncrementalRefreshOBRCURR;
	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshTLRFONDInfo*	m_marketDataIncrementalRefreshTLRFOND;
	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems;
	FastMarketDataIncrementalRefreshTLRCURRInfo*	m_marketDataIncrementalRefreshTLRCURR;
	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo*	m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems;
	FastSecurityDefinitionInfo*	m_securityDefinition;
	FastSecurityDefinitionGroupInstrAttribItemInfo*	m_securityDefinitionGroupInstrAttribItems;
	FastSecurityDefinitionMarketSegmentGrpItemInfo*	m_securityDefinitionMarketSegmentGrpItems;
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*	m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	FastSecurityStatusInfo*	m_securityStatus;
	FastTradingSessionStatusInfo*	m_tradingSessionStatus;
	FastHeartbeatInfo*	m_heartbeat;
	int		m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsMaxCount;
	int		m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsMaxCount;
	int		m_securityDefinitionGroupInstrAttribItemsMaxCount;
	int		m_securityDefinitionMarketSegmentGrpItemsMaxCount;
	int		m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsMaxCount;
	FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo*		m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo*		m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo*		m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo*		m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo*		m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo*		m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo*		m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem;
	FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo*		m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem;
	FastSecurityDefinitionGroupInstrAttribItemInfo*		m_securityDefinitionGroupInstrAttribItemsCurrentItem;
	FastSecurityDefinitionMarketSegmentGrpItemInfo*		m_securityDefinitionMarketSegmentGrpItemsCurrentItem;
	FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*		m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem;

	void InitializeMessageInfo() {
		this->m_header = new FastHeaderInfo();
		memset(this->m_header, 0, sizeof(FastHeaderInfo));

		this->m_logon = new FastLogonInfo();
		memset(this->m_logon, 0, sizeof(FastLogonInfo));

		this->m_logout = new FastLogoutInfo();
		memset(this->m_logout, 0, sizeof(FastLogoutInfo));

		this->m_marketDataSnapshotFullRefreshGeneric = new FastMarketDataSnapshotFullRefreshGenericInfo();
		memset(this->m_marketDataSnapshotFullRefreshGeneric, 0, sizeof(FastMarketDataSnapshotFullRefreshGenericInfo));

		this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshGeneric = new FastMarketDataIncrementalRefreshGenericInfo();
		memset(this->m_marketDataIncrementalRefreshGeneric, 0, sizeof(FastMarketDataIncrementalRefreshGenericInfo));

		this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItems = new FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataSnapshotFullRefreshOLSFOND = new FastMarketDataSnapshotFullRefreshOLSFONDInfo();
		memset(this->m_marketDataSnapshotFullRefreshOLSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshOLSFONDInfo));

		this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataSnapshotFullRefreshOLSCURR = new FastMarketDataSnapshotFullRefreshOLSCURRInfo();
		memset(this->m_marketDataSnapshotFullRefreshOLSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshOLSCURRInfo));

		this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataSnapshotFullRefreshTLSFOND = new FastMarketDataSnapshotFullRefreshTLSFONDInfo();
		memset(this->m_marketDataSnapshotFullRefreshTLSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshTLSFONDInfo));

		this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataSnapshotFullRefreshTLSCURR = new FastMarketDataSnapshotFullRefreshTLSCURRInfo();
		memset(this->m_marketDataSnapshotFullRefreshTLSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshTLSCURRInfo));

		this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataSnapshotFullRefreshOBSFOND = new FastMarketDataSnapshotFullRefreshOBSFONDInfo();
		memset(this->m_marketDataSnapshotFullRefreshOBSFOND, 0, sizeof(FastMarketDataSnapshotFullRefreshOBSFONDInfo));

		this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataSnapshotFullRefreshOBSCURR = new FastMarketDataSnapshotFullRefreshOBSCURRInfo();
		memset(this->m_marketDataSnapshotFullRefreshOBSCURR, 0, sizeof(FastMarketDataSnapshotFullRefreshOBSCURRInfo));

		this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems = new FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo));
		this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshMSRFOND = new FastMarketDataIncrementalRefreshMSRFONDInfo();
		memset(this->m_marketDataIncrementalRefreshMSRFOND, 0, sizeof(FastMarketDataIncrementalRefreshMSRFONDInfo));

		this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshMSRCURR = new FastMarketDataIncrementalRefreshMSRCURRInfo();
		memset(this->m_marketDataIncrementalRefreshMSRCURR, 0, sizeof(FastMarketDataIncrementalRefreshMSRCURRInfo));

		this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshOLRFOND = new FastMarketDataIncrementalRefreshOLRFONDInfo();
		memset(this->m_marketDataIncrementalRefreshOLRFOND, 0, sizeof(FastMarketDataIncrementalRefreshOLRFONDInfo));

		this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshOLRCURR = new FastMarketDataIncrementalRefreshOLRCURRInfo();
		memset(this->m_marketDataIncrementalRefreshOLRCURR, 0, sizeof(FastMarketDataIncrementalRefreshOLRCURRInfo));

		this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshOBRFOND = new FastMarketDataIncrementalRefreshOBRFONDInfo();
		memset(this->m_marketDataIncrementalRefreshOBRFOND, 0, sizeof(FastMarketDataIncrementalRefreshOBRFONDInfo));

		this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshOBRCURR = new FastMarketDataIncrementalRefreshOBRCURRInfo();
		memset(this->m_marketDataIncrementalRefreshOBRCURR, 0, sizeof(FastMarketDataIncrementalRefreshOBRCURRInfo));

		this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshTLRFOND = new FastMarketDataIncrementalRefreshTLRFONDInfo();
		memset(this->m_marketDataIncrementalRefreshTLRFOND, 0, sizeof(FastMarketDataIncrementalRefreshTLRFONDInfo));

		this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems = new FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsMaxCount = 1024;

		this->m_marketDataIncrementalRefreshTLRCURR = new FastMarketDataIncrementalRefreshTLRCURRInfo();
		memset(this->m_marketDataIncrementalRefreshTLRCURR, 0, sizeof(FastMarketDataIncrementalRefreshTLRCURRInfo));

		this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems = new FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo[1024];
		memset(this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems, 0, 1024 * sizeof(FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo));
		this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsMaxCount = 1024;

		this->m_securityDefinition = new FastSecurityDefinitionInfo();
		memset(this->m_securityDefinition, 0, sizeof(FastSecurityDefinitionInfo));

		this->m_securityDefinitionGroupInstrAttribItems = new FastSecurityDefinitionGroupInstrAttribItemInfo[1024];
		memset(this->m_securityDefinitionGroupInstrAttribItems, 0, 1024 * sizeof(FastSecurityDefinitionGroupInstrAttribItemInfo));
		this->m_securityDefinitionGroupInstrAttribItemsMaxCount = 1024;

		this->m_securityDefinitionMarketSegmentGrpItems = new FastSecurityDefinitionMarketSegmentGrpItemInfo[1024];
		memset(this->m_securityDefinitionMarketSegmentGrpItems, 0, 1024 * sizeof(FastSecurityDefinitionMarketSegmentGrpItemInfo));
		this->m_securityDefinitionMarketSegmentGrpItemsMaxCount = 1024;

		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = new FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo[1024];
		memset(this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems, 0, 1024 * sizeof(FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo));
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsMaxCount = 1024;

		this->m_securityStatus = new FastSecurityStatusInfo();
		memset(this->m_securityStatus, 0, sizeof(FastSecurityStatusInfo));

		this->m_tradingSessionStatus = new FastTradingSessionStatusInfo();
		memset(this->m_tradingSessionStatus, 0, sizeof(FastTradingSessionStatusInfo));

		this->m_heartbeat = new FastHeartbeatInfo();
		memset(this->m_heartbeat, 0, sizeof(FastHeartbeatInfo));

	}

	void ResetMessageInfoIndicies() {
		this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItems;
		this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItems;
		this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem = this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItems;
		this->m_securityDefinitionGroupInstrAttribItemsCurrentItem = this->m_securityDefinitionGroupInstrAttribItems;
		this->m_securityDefinitionMarketSegmentGrpItemsCurrentItem = this->m_securityDefinitionMarketSegmentGrpItems;
		this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem = this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}
#pragma endregion

#pragma region Decode_Method_Pointer_Arrays_GeneratedCode
	FastDecodeMethodPointer* DecodeMethods_Generic;
	FastDecodeMethodPointer* DecodeMethods_OLS_FOND;
	FastDecodeMethodPointer* DecodeMethods_OLS_CURR;
	FastDecodeMethodPointer* DecodeMethods_TLS_FOND;
	FastDecodeMethodPointer* DecodeMethods_TLS_CURR;
	FastDecodeMethodPointer* DecodeMethods_OBS_FOND;
	FastDecodeMethodPointer* DecodeMethods_OBS_CURR;
	FastDecodeMethodPointer* DecodeMethods_MSR_FOND;
	FastDecodeMethodPointer* DecodeMethods_MSR_CURR;
	FastDecodeMethodPointer* DecodeMethods_OLR_FOND;
	FastDecodeMethodPointer* DecodeMethods_OLR_CURR;
	FastDecodeMethodPointer* DecodeMethods_OBR_FOND;
	FastDecodeMethodPointer* DecodeMethods_OBR_CURR;
	FastDecodeMethodPointer* DecodeMethods_TLR_FOND;
	FastDecodeMethodPointer* DecodeMethods_TLR_CURR;

	void InitializeDecodeMethodPointers() {
		int ptCount = 256;
		this->DecodeMethods_Generic = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_Generic, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_Generic[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_Generic[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_Generic[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_Generic[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshGeneric;
		this->DecodeMethods_Generic[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshGeneric;
		this->DecodeMethods_Generic[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_Generic[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_Generic[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_Generic[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OLS_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OLS_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_OLS_FOND[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_OLS_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OLS_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OLS_FOND[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOLSFOND;
		this->DecodeMethods_OLS_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OLS_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OLS_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OLS_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OLS_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OLS_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_OLS_CURR[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_OLS_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OLS_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OLS_CURR[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOLSCURR;
		this->DecodeMethods_OLS_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OLS_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OLS_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OLS_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_TLS_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_TLS_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_TLS_FOND[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_TLS_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_TLS_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_TLS_FOND[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshTLSFOND;
		this->DecodeMethods_TLS_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_TLS_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_TLS_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_TLS_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_TLS_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_TLS_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_TLS_CURR[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_TLS_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_TLS_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_TLS_CURR[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshTLSCURR;
		this->DecodeMethods_TLS_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_TLS_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_TLS_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_TLS_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OBS_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OBS_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_OBS_FOND[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_OBS_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OBS_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OBS_FOND[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOBSFOND;
		this->DecodeMethods_OBS_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OBS_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OBS_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OBS_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OBS_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OBS_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_OBS_CURR[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_OBS_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OBS_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OBS_CURR[(int)'W'] = &FastProtocolManager::DecodeMarketDataSnapshotFullRefreshOBSCURR;
		this->DecodeMethods_OBS_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OBS_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OBS_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OBS_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_MSR_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_MSR_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_MSR_FOND[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_MSR_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_MSR_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_MSR_FOND[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshMSRFOND;
		this->DecodeMethods_MSR_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_MSR_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_MSR_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_MSR_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_MSR_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_MSR_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_MSR_CURR[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_MSR_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_MSR_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_MSR_CURR[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshMSRCURR;
		this->DecodeMethods_MSR_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_MSR_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_MSR_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_MSR_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OLR_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OLR_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_OLR_FOND[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_OLR_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OLR_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OLR_FOND[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOLRFOND;
		this->DecodeMethods_OLR_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OLR_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OLR_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OLR_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OLR_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OLR_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_OLR_CURR[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_OLR_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OLR_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OLR_CURR[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOLRCURR;
		this->DecodeMethods_OLR_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OLR_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OLR_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OLR_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OBR_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OBR_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_OBR_FOND[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_OBR_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OBR_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OBR_FOND[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOBRFOND;
		this->DecodeMethods_OBR_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OBR_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OBR_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OBR_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_OBR_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_OBR_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_OBR_CURR[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_OBR_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_OBR_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_OBR_CURR[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshOBRCURR;
		this->DecodeMethods_OBR_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_OBR_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_OBR_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_OBR_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_TLR_FOND = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_TLR_FOND, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_TLR_FOND[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_TLR_FOND[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_TLR_FOND[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_TLR_FOND[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshTLRFOND;
		this->DecodeMethods_TLR_FOND[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_TLR_FOND[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_TLR_FOND[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_TLR_FOND[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

		this->DecodeMethods_TLR_CURR = new FastDecodeMethodPointer[ptCount];
		memset(this->DecodeMethods_TLR_CURR, 0, sizeof(FastDecodeMethodPointer) * ptCount);

		for(int i = 0; i < 256; i++)
			this->DecodeMethods_TLR_CURR[i] = &FastProtocolManager::DecodeUnsupportedMessage;

		this->DecodeMethods_TLR_CURR[(int)'A'] = &FastProtocolManager::DecodeLogon;
		this->DecodeMethods_TLR_CURR[(int)'5'] = &FastProtocolManager::DecodeLogout;
		this->DecodeMethods_TLR_CURR[(int)'X'] = &FastProtocolManager::DecodeMarketDataIncrementalRefreshTLRCURR;
		this->DecodeMethods_TLR_CURR[(int)'d'] = &FastProtocolManager::DecodeSecurityDefinition;
		this->DecodeMethods_TLR_CURR[(int)'f'] = &FastProtocolManager::DecodeSecurityStatus;
		this->DecodeMethods_TLR_CURR[(int)'h'] = &FastProtocolManager::DecodeTradingSessionStatus;
		this->DecodeMethods_TLR_CURR[(int)'0'] = &FastProtocolManager::DecodeHeartbeat;

	}

#pragma endregion

#pragma region Get_Free_Item_Methods_GeneratedCode
	inline FastHeaderInfo* GetFreeHeaderInfo() {
		return this->m_header;
	}

	inline FastLogonInfo* GetFreeLogonInfo() {
		return this->m_logon;
	}

	inline FastLogoutInfo* GetFreeLogoutInfo() {
		return this->m_logout;
	}

	inline FastMarketDataSnapshotFullRefreshGenericInfo* GetFreeMarketDataSnapshotFullRefreshGenericInfo() {
		return this->m_marketDataSnapshotFullRefreshGeneric;
	}

	inline FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo() {
		return this->m_marketDataSnapshotFullRefreshGenericGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshGenericInfo* GetFreeMarketDataIncrementalRefreshGenericInfo() {
		return this->m_marketDataIncrementalRefreshGeneric;
	}

	inline FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshGenericGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshOLSFONDInfo* GetFreeMarketDataSnapshotFullRefreshOLSFONDInfo() {
		return this->m_marketDataSnapshotFullRefreshOLSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo() {
		return this->m_marketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshOLSCURRInfo* GetFreeMarketDataSnapshotFullRefreshOLSCURRInfo() {
		return this->m_marketDataSnapshotFullRefreshOLSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo() {
		return this->m_marketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshTLSFONDInfo* GetFreeMarketDataSnapshotFullRefreshTLSFONDInfo() {
		return this->m_marketDataSnapshotFullRefreshTLSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo() {
		return this->m_marketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshTLSCURRInfo* GetFreeMarketDataSnapshotFullRefreshTLSCURRInfo() {
		return this->m_marketDataSnapshotFullRefreshTLSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo() {
		return this->m_marketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshOBSFONDInfo* GetFreeMarketDataSnapshotFullRefreshOBSFONDInfo() {
		return this->m_marketDataSnapshotFullRefreshOBSFOND;
	}

	inline FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo() {
		return this->m_marketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataSnapshotFullRefreshOBSCURRInfo* GetFreeMarketDataSnapshotFullRefreshOBSCURRInfo() {
		return this->m_marketDataSnapshotFullRefreshOBSCURR;
	}

	inline FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo* GetFreeMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo() {
		return this->m_marketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshMSRFONDInfo* GetFreeMarketDataIncrementalRefreshMSRFONDInfo() {
		return this->m_marketDataIncrementalRefreshMSRFOND;
	}

	inline FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshMSRFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshMSRCURRInfo* GetFreeMarketDataIncrementalRefreshMSRCURRInfo() {
		return this->m_marketDataIncrementalRefreshMSRCURR;
	}

	inline FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshMSRCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshOLRFONDInfo* GetFreeMarketDataIncrementalRefreshOLRFONDInfo() {
		return this->m_marketDataIncrementalRefreshOLRFOND;
	}

	inline FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshOLRFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshOLRCURRInfo* GetFreeMarketDataIncrementalRefreshOLRCURRInfo() {
		return this->m_marketDataIncrementalRefreshOLRCURR;
	}

	inline FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshOLRCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshOBRFONDInfo* GetFreeMarketDataIncrementalRefreshOBRFONDInfo() {
		return this->m_marketDataIncrementalRefreshOBRFOND;
	}

	inline FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshOBRFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshOBRCURRInfo* GetFreeMarketDataIncrementalRefreshOBRCURRInfo() {
		return this->m_marketDataIncrementalRefreshOBRCURR;
	}

	inline FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshOBRCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshTLRFONDInfo* GetFreeMarketDataIncrementalRefreshTLRFONDInfo() {
		return this->m_marketDataIncrementalRefreshTLRFOND;
	}

	inline FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshTLRFONDGroupMDEntriesItemsCurrentItem;
	}

	inline FastMarketDataIncrementalRefreshTLRCURRInfo* GetFreeMarketDataIncrementalRefreshTLRCURRInfo() {
		return this->m_marketDataIncrementalRefreshTLRCURR;
	}

	inline FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo* GetFreeMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo() {
		return this->m_marketDataIncrementalRefreshTLRCURRGroupMDEntriesItemsCurrentItem;
	}

	inline FastSecurityDefinitionInfo* GetFreeSecurityDefinitionInfo() {
		return this->m_securityDefinition;
	}

	inline FastSecurityDefinitionGroupInstrAttribItemInfo* GetFreeSecurityDefinitionGroupInstrAttribItemInfo() {
		return this->m_securityDefinitionGroupInstrAttribItemsCurrentItem;
	}

	inline FastSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpItemInfo() {
		return this->m_securityDefinitionMarketSegmentGrpItemsCurrentItem;
	}

	inline FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		return this->m_securityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemsCurrentItem;
	}

	inline FastSecurityStatusInfo* GetFreeSecurityStatusInfo() {
		return this->m_securityStatus;
	}

	inline FastTradingSessionStatusInfo* GetFreeTradingSessionStatusInfo() {
		return this->m_tradingSessionStatus;
	}

	inline FastHeartbeatInfo* GetFreeHeartbeatInfo() {
		return this->m_heartbeat;
	}

#pragma endregion

public:

    inline unsigned int SendMsgSeqNo() { return this->m_sendMsgSeqNo; }
    inline void IncSendMsgSeqNo() { this->m_sendMsgSeqNo++; }

    inline unsigned int RecvMsgSeqNo() { return this->m_recvMsgSeqNo; }
    inline void IncRecvMsgSeqNo() { this->m_recvMsgSeqNo++; }

#pragma region Core_Methods
	inline bool FastCompareString1(char *str1, char *str2) { return *str1 == *str2; }
	inline bool FastCompareString4(char *str1, char *str2) { return *((int*)str1) == *((int*)str2); }
	inline bool FastCompareString8(char *str1, char *str2) { return *((UINT64*)str1) == *((UINT64*)str2); }
	inline void ResetBuffer() { this->currentPos = this->buffer; }
	inline void SetNewBuffer(BYTE *buffer, int length) { 
		this->buffer = buffer;
		this->bufferLength = length;
		this->ResetBuffer();
	} 
	inline void ClearBuffer() { memset(this->buffer, 0, this->bufferLength); }
	
    inline unsigned char GetMsgType() {
        return *(this->m_header->MessageType);
    }
	inline bool CheckBuffer(BYTE *arrayToCompare, int length) {
		int lengthInt = length / 4;
		for (int i = 0; i < lengthInt; i++)
			if (((int*)this->buffer)[i] != ((int*)arrayToCompare)[i])
				return false;
		int length2 = length % 4;
		for (int i = lengthInt * 4; i < length; i++)
			if (this->buffer[i] != arrayToCompare[i])
				return false;
		return true;
	}
	inline bool CheckBufferFromCurrent(BYTE *arrayToCompare, int length) { 
		int lengthInt = length / 4;
		for (int i = 0; i < lengthInt; i++)
			if (((int*)this->currentPos)[i] != ((int*)arrayToCompare)[i])
				return false;
		int length2 = length % 4;
		for (int i = lengthInt * 4; i < length; i++)
			if (this->currentPos[i] != arrayToCompare[i])
				return false;
		return true;
	}
	
	inline void WriteMsgSeqNumber(int msgSeqNumber) {
		*((int*)this->currentPos) = msgSeqNumber;
		this->currentPos += 4;
	}


    inline void WritePresenceMap1(UINT map) {
        *((UINT*)this->currentPos) = map;
        this->currentPos++;
    }

    inline void WritePresenceMap2(UINT map) {
        *((UINT*)this->currentPos) = map;
        this->currentPos+=2;
    }

    inline void WritePresenceMap3(UINT map) {
        *((UINT*)this->currentPos) = map;
        this->currentPos+=3;
    }

    inline void WritePresenceMap4(UINT map) {
        *((UINT*)this->currentPos) = map;
        this->currentPos+=4;
    }

	inline int ReadMsgSeqNumber() {
		int result = *(int*)this->currentPos;
		this->currentPos += 4;
		return result;
	}

	inline bool IsNull() {  return *(this->currentPos) == 0x80; }

    inline void WriteNull() {
        *(this->currentPos) = 0x80;
        this->currentPos++;
    }

	inline bool CheckProcessNullInt32() {
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullUInt32() { 
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcesNullInt64() {
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullUint64() {
		if (*(this->currentPos) == 0x80) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullString() {
		WORD str = *((WORD*)this->currentPos);
		if (str == 0x0000)
			return false;
		if ((str & 0xFF) == 0x00) {
			this->currentPos++;
			return true;
		}
		return false;
	}
	inline bool CheckProcessNullByteVector() {
		return CheckProcessNullUInt32();
	}
	inline bool CheckProcessNullDecimal() {
		return CheckProcessNullInt32();
	}

	inline void WriteInt32_Mandatory(INT32 value) { 
		int encoded = 0;
		if (value >= 0) {

			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				else {
					*((int*)this->currentPos) = encoded;
					this->currentPos++;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				else {
					*((int*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				else {
					*((int*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					*(this->currentPos) = 0x00;
					this->currentPos++;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				else {
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
			}

			if ((value & 0x40) != 0) { 
				*(this->currentPos) = 0x00;
				this->currentPos++;
			}

			*(this->currentPos) = value;
			this->currentPos++;

			*((int*)this->currentPos) = encoded;
			this->currentPos += 4;
		}
		else {
			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0xffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				*((int*)this->currentPos) = encoded;
				this->currentPos++;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				*((int*)this->currentPos) = encoded;
				this->currentPos += 2;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				*((int*)this->currentPos) = encoded;
				this->currentPos += 3;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffff) {
				if ((encoded & 0x40) == 0) {
					*this->currentPos = 0x7f;
					this->currentPos++;
					*((int*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				*((int*)this->currentPos) = encoded;
				this->currentPos += 4;
				return;
			}

			if ((value & 0x40) == 0) { 
				(*this->currentPos) = 0x7f;
				this->currentPos++;
			}
			*(this->currentPos) = (BYTE)(value & 0x7f);
			this->currentPos++;

			*((int*)this->currentPos) = encoded;
			this->currentPos += 4;
		}
	}
	inline void WriteInt32_Optional(INT32 value) {
		if (value > 0)
			value++;
		WriteInt32_Mandatory(value);
	}

	inline void WriteUInt32_Mandatory(UINT32 value) {
		UINT encoded = 0;

		encoded |= ((value & 0x7f) | 0x80);
		value >>= 7;

		if (value == 0) {
			*((int*)this->currentPos) = encoded;
			this->currentPos++;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((int*)this->currentPos) = encoded;
			this->currentPos += 2;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((int*)this->currentPos) = encoded;
			this->currentPos += 3;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((int*)this->currentPos) = encoded;
			this->currentPos += 4;
			return;
		}

		*(this->currentPos) = value;
		this->currentPos++;

		*((int*)this->currentPos) = encoded;
		this->currentPos += 4;
	}
	inline void WriteUInt32_Optional(UINT32 value) {
		value++;
		WriteUInt32_Mandatory(value);
	}

	inline INT32 ReadInt32_Optional() {
		INT32 result = ReadInt32_Mandatory();
		if (result > 0)
			return result - 1;
		return result;
	}
	inline INT32 ReadInt32_Mandatory() {
		INT32 result;
		INT32 memory = *((INT32*)(this->currentPos));

		INT32 valueMasked = memory & 0xff;

		if (valueMasked == 0x00) { // extended positive integer
			result = 0;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}
			this->currentPos += 4;

			result <<= 7;
			memory = *((INT32*)(this->currentPos));
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;

			this->currentPos += 2;
			return result;
		}
		else if (valueMasked == 0x7f) { // extended negative integer
			result = 0;
			memory >>= 8;

			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			this->currentPos += 4;
			memory = *((INT32*)(this->currentPos));
			result |= memory & 0x7f;
			
			this->currentPos ++;
			return result;
		}
		else if ((memory & 0x40) != 0) { // simple negative integer 
			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}
			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}
			this->currentPos += 4;
			result <<= 7;
			memory = *((INT32*)(this->currentPos));
			result |= memory & 0x7f;

			this->currentPos++;
			return result;
		}
		else {  // simple positive integer
			result = 0;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			this->currentPos += 4;

			result <<= 7;
			memory = *((INT32*)(this->currentPos));
			result |= memory & 0x7f;

			this->currentPos++;
			return result;
		}
	}
	
	inline UINT32 ReadUInt32_Mandatory() {
		INT32 result = 0;
		INT32 memory = *((INT32*)(this->currentPos));

		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos++;
			return result;
		}
		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 2;
			return result;
		}
		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 3;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 4;
			return result;
		}

		this->currentPos += 4;

		result <<= 7;
		memory = *((INT32*)(this->currentPos));
		result |= memory & 0x7f;

		this->currentPos++;
		return result;
	}
	inline UINT32 ReadUInt32_Optional() {
		INT32 result = ReadUInt32_Mandatory();
		return result - 1;
	}

	inline void WriteInt64_Optional(INT64 value) {
		if (value > 0)
			value++;
		WriteInt64_Mandatory(value);
	}
	inline void WriteInt64_Mandatory(INT64 value) { 
		INT64 encoded = 0;
		INT32 encoded2;
		if (value >= 0) {
			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos++;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					*((INT64*)this->currentPos) = 0x00;
					this->currentPos++;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 = value & 0x7f;
			value >>= 7;
			if (value == 0) {
				if ((encoded2 & 0x40) != 0) {
					encoded2 <<= 8;
					*((INT32*)(this->currentPos)) = encoded2;
					this->currentPos += 2;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT32*)(this->currentPos)) = encoded2;
					this->currentPos++;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 <<= 8;
			encoded2 |= value & 0x7f;

			*((INT32*)(this->currentPos)) = encoded2;
			this->currentPos += 2;

			*((INT64*)this->currentPos) = encoded;
			this->currentPos += 8;
		}
		else {
			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos++;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 2;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 3;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 4;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 5;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 6;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 7;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					(*this->currentPos) = 0x7f;
					this->currentPos++;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 8;
				return;
			}

			encoded2 = value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded2 & 0x40) == 0) {
					encoded2 <<= 8;
					encoded2 |= 0x7f;

					*((INT64*)this->currentPos) = encoded2;
					this->currentPos += 2;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded2;
					this->currentPos++;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 <<= 8;
			encoded2 |= value & 0x7f;

			*((INT64*)this->currentPos) = encoded2;
			this->currentPos += 2;

			*((INT64*)this->currentPos) = encoded;
			this->currentPos += 8;
			return;
		}
	}
	
	inline void WriteUInt64_Optional(UINT64 value) {
		value++;
		WriteUInt64_Mandatory(value);
	}
	inline void WriteUInt64_Mandatory(UINT64 value) {
		UINT64 encoded = 0;
		UINT encoded2;

		encoded |= ((value & 0x7f) | 0x80);
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos++;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 2;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 3;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 4;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 5;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 6;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 7;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 8;
			return;
		}

		encoded2 = value & 0x7f;
		value >>= 7;
		if (value == 0) { 
			*((UINT*)this->currentPos) = encoded2;
			this->currentPos ++;
			*((UINT64*)this->currentPos) = encoded;
			return;
		}
	
		encoded2 <<= 8;
		encoded2 |= value;

		*((UINT*)this->currentPos) = encoded2;
		this->currentPos +=2;
		*((UINT64*)this->currentPos) = encoded;
		return;
	}

	inline INT64 ReadInt64_Mandatory() {
		INT64 result;
		INT64 memory = *((INT64*)(this->currentPos));

		INT64 valueMasked = memory & 0xff;

		if (valueMasked == 0x00) { // extended positive integer
			result = 0;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 5;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 6;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 7;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 8;
				return result;
			}
			
			this->currentPos += 8;

			result <<= 7;
			memory = *((INT64*)(this->currentPos));
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;

			this->currentPos += 3;
			return result;
		}
		else if (valueMasked == 0x7f) { // extended negative integer
			result = 0;
			memory >>= 8;

			result = 0xffffffffffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 5;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 6;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 7;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 8;
				return result;
			}
			
			this->currentPos += 8;
			result <<= 7;
			memory = *((INT64*)(this->currentPos));
			result |= memory & 0x7f;

			if ((memory & 0x80) != 0) {
				this->currentPos ++;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;

			this->currentPos += 3;
			return result;
		}
		else if ((memory & 0x40) != 0) { // simple negative integer 
			result = 0xffffffffffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}
			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 5;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 6;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 7;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 8;
				return result;
			}

			this->currentPos += 8;
			result <<= 7;
			memory = *((INT64*)(this->currentPos));
			result |= memory & 0x7f;

			if ((memory & 0x80) != 0) {
				this->currentPos ++;
				return result;
			}

			result <<= 7;
			memory >>= 8;

			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;

			this->currentPos += 3;
			return result;
		}
		else {  // simple positive integer
			result = 0;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos++;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 5;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 6;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 7;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 8;
				return result;
			}

			this->currentPos += 8;

			result <<= 7;
			memory = *((INT64*)(this->currentPos));
			result |= memory & 0x7f;

			if ((memory & 0x80) != 0) {
				this->currentPos ++;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
				this->currentPos += 2;
				return result;
			}

			this->currentPos += 3;
			return result;
		}
	}
	inline INT64 ReadInt64_Optional() {
		INT64 value = ReadInt64_Mandatory();
		if (value > 0)
			return value - 1;
		return value;
	}

	inline UINT64 ReadUInt64_Mandatory() {
		UINT64 result;
		UINT64 memory = *(UINT64*)this->currentPos;

		result = memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos++;
			return result;
		}
		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 2;
			return result;
		}
		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 3;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 4;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 5;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 6;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 7;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;
		if ((memory & 0x80) != 0) {
			this->currentPos += 8;
			return result;
		}

		this->currentPos += 8;

		result <<= 7;
		memory = *((INT64*)(this->currentPos));
		result |= memory & 0x7f;

		if ((memory & 0x80) != 0) {
			this->currentPos ++;
			return result;
		}

		result <<= 7;
		memory >>= 8;
		result |= memory & 0x7f;

		this->currentPos +=2;
		return result;
	}
	inline UINT64 ReadUInt64_Optional() {
		return ReadUInt64_Mandatory() - 1;
	}

	inline void CopyToBuffer(BYTE *value, int length) { 
		memcpy(this->buffer, value, length);
	}

	inline void ReadDecimal_Optional(Decimal *value) { 
		value->Mantissa = ReadInt32_Mandatory();
		value->Exponent = ReadInt32_Optional();
	}

	inline void ReadDecimal_Mandatory(Decimal *value) { 
		value->Mantissa = ReadInt32_Mandatory();
		value->Exponent = ReadInt32_Mandatory();
	}

	inline void WriteDecimal_Optional(Decimal *value) { 
		WriteInt32_Optional(value->Exponent);
		WriteInt32_Mandatory(value->Mantissa);
		return;
	}

	inline void WriteDecimal_Mandatory(Decimal *value) {
		WriteInt32_Mandatory(value->Exponent);
		WriteInt32_Mandatory(value->Mantissa);
		return;
	}

	inline void WriteString_Optional(char *str, int length) { 
		if (str == NULL) { 
			*(this->currentPos) = 0x80;
			this->currentPos++;
		}
		else if (length == 0) { 
			*((int*)this->currentPos) = 0x8000;
			this->currentPos += 2;
			return;
		}
		memcpy(this->currentPos, str, length);
		this->currentPos[length - 1] |= 0x80;
		this->currentPos += length;
	}

	inline void WriteString_Mandatory(char *str, int length) {
		if (length == 0) {
			*((int*)this->currentPos) = 0x80;
			this->currentPos ++;
			return;
		}
		memcpy(this->currentPos, str, length);
		this->currentPos[length - 1] |= 0x80;
		this->currentPos += length;
	}

    inline void WriteString_Optional(const char *str, int length) {
        if (str == NULL) {
            *(this->currentPos) = 0x80;
            this->currentPos++;
        }
        else if (length == 0) {
            *((int*)this->currentPos) = 0x8000;
            this->currentPos += 2;
            return;
        }
        memcpy(this->currentPos, str, length);
        this->currentPos[length - 1] |= 0x80;
        this->currentPos += length;
    }

    inline void WriteString_Mandatory(const char *str, int length) {
        if (length == 0) {
            *((int*)this->currentPos) = 0x80;
            this->currentPos ++;
            return;
        }
        memcpy(this->currentPos, str, length);
        this->currentPos[length - 1] |= 0x80;
        this->currentPos += length;
    }

	inline void ReadString_Optional(char **strPtrAddress, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);
		int length = 0;
		if ((memory & 0xffff) == 0x8000) { 
			*strPtrAddress = (char*)this->currentPos;
			lengthAddress = 0;
			this->currentPos += 2;
			return;
		}
		*strPtrAddress = (char*)this->currentPos;
		while (true) {
			if ((memory & 0x8080808080808080) != 0) { 
				if ((memory & 0x0000000080808080) != 0) { 
					if ((memory & 0x8080) != 0) {
						if ((memory & 0x80) != 0) { 
							this->currentPos[0] &= 0x7f;
							length++;
							this->currentPos++;
							break;
						}
						else { 
							this->currentPos[1] &= 0x7f;
							length += 2;
							this->currentPos += 2;
							break;
						}
					}
					else { 
						if ((memory & 0x800000) != 0) { 
							this->currentPos[2] &= 0x7f;
							length += 3;
							this->currentPos += 3;
							break;
						}
						else {
							this->currentPos[3] &= 0x7f;
							length += 4;
							this->currentPos += 4;
							break;
						}
					}
				}
				else { 
					if ((memory & 0x0000808000000000) != 0) { 
						if ((memory & 0x0000008000000000) != 0) { 
							this->currentPos[4] &= 0x7f;
							length += 5;
							this->currentPos += 5;
							break;
						}
						else { 
							this->currentPos[5] &= 0x7f;
							length += 6;
							this->currentPos += 6;
							break;
						}
					}
					else { 
						if ((memory & 0x0080000000000000) != 0) {
							this->currentPos[6] &= 0x7f;
							length += 7;
							this->currentPos += 7;
							break;
						}
						else { 
							this->currentPos[7] &= 0x7f;
							length += 8;
							this->currentPos += 8;
							break;
						}
					}
				}
			}
			length += 8;
			this->currentPos += 8;
			memory = *((UINT64*)this->currentPos);
		}
		*lengthAddress = length;
	}
	inline void ReadString_Mandatory(char **strPtrAddress, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);
		int length = 0;
		if ((memory & 0xff) == 0x80) {
			*(this->currentPos) = 0;
			*strPtrAddress = (char*)this->currentPos;
			lengthAddress = 0;
			this->currentPos ++;
			return;
		}
		*strPtrAddress = (char*)this->currentPos;
		while (true) {
			if ((memory & 0x8080808080808080) != 0) {
				if ((memory & 0x0000000080808080) != 0) {
					if ((memory & 0x8080) != 0) {
						if ((memory & 0x80) != 0) {
							this->currentPos[0] &= 0x7f;
							length++;
							this->currentPos++;
							break;
						}
						else {
							this->currentPos[1] &= 0x7f;
							length += 2;
							this->currentPos += 2;
							break;
						}
					}
					else {
						if ((memory & 0x800000) != 0) {
							this->currentPos[2] &= 0x7f;
							length += 3;
							this->currentPos += 3;
							break;
						}
						else {
							this->currentPos[3] &= 0x7f;
							length += 4;
							this->currentPos += 4;
							break;
						}
					}
				}
				else {
					if ((memory & 0x0000808000000000) != 0) {
						if ((memory & 0x0000008000000000) != 0) {
							this->currentPos[4] &= 0x7f;
							length += 5;
							this->currentPos += 5;
							break;
						}
						else {
							this->currentPos[5] &= 0x7f;
							length += 6;
							this->currentPos += 6;
							break;
						}
					}
					else {
						if ((memory & 0x0080000000000000) != 0) {
							this->currentPos[6] &= 0x7f;
							length += 7;
							this->currentPos += 7;
							break;
						}
						else {
							this->currentPos[7] &= 0x7f;
							length += 8;
							this->currentPos += 8;
							break;
						}
					}
				}
			}
			length += 8;
			this->currentPos += 8;
			memory = *((UINT64*)this->currentPos);
		}
		*lengthAddress = length;
	}

	inline void ReadByteVector_Optional(BYTE **vecPtrAddress, int *lengthAddress) { 
		int length = ReadInt32_Optional();
		*vecPtrAddress = this->currentPos;
		this->currentPos += length;
		*lengthAddress = length;
	}
	inline void ReadByteVector_Mandatory(BYTE **vecPtrAddress, int *lengthAddress) { 
		int length = ReadInt32_Mandatory();
		*vecPtrAddress = this->currentPos;
		this->currentPos += length;
		*lengthAddress = length;
	}

	inline void WriteByteVector_Optional(BYTE *vecPtr, int length) { 
		if (vecPtr == NULL) { 
			*(this->currentPos) = 0x80;
			this->currentPos++;
			return;
		}
		WriteInt32_Optional(length);
		memcpy(this->currentPos, vecPtr, length);
		this->currentPos += length;
	}
	inline void WriteByteVector_Mandatory(BYTE *vecPtr, int length) {
		WriteInt32_Mandatory(length);
		memcpy(this->currentPos, vecPtr, length);
		this->currentPos += length;
	}

	inline void ParsePresenceMap(UINT *map) {
		UINT value = *((UINT*)this->currentPos);
		if((value & FAST_STOPBIT_FIRST_BYTE) != 0) {
			*map = value;
			this->currentPos++;
			return;
		}
		if((value & FAST_STOPBIT_SECOND_BYTE) != 0) {
			*map = value;
			this->currentPos += 2;
			return;
		}
		if((value & FAST_STOPBIT_THIRD_BYTE) != 0) {
			*map = value;
			this->currentPos += 3;
			return;
		}
		*map = value;
		this->currentPos += 4;
		return;
	}

	FastProtocolManager();
	~FastProtocolManager();

	inline BYTE* Buffer() { return this->buffer; }
	inline BYTE* CurrentPos() { return this->currentPos; }
	inline int BufferLength() { return this->bufferLength; }
	inline int MessageLength() { return this->currentPos - this->buffer; }
	inline void SetBufferLength(int value) { this->bufferLength = value; }
#pragma endregion

#pragma region Encode_Methods_Definition_GeneratedCode
	inline void EncodeLogonInfo(FastLogonInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("A", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
		WriteString_Mandatory(info->TargetCompID, info->TargetCompIDLength);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		WriteInt32_Mandatory(info->HeartBtInt);
		if(!info->AllowUsername)
			this->WriteNull();
		else
			WriteString_Optional(info->Username, info->UsernameLength);
		if(!info->AllowPassword)
			this->WriteNull();
		else
			WriteString_Optional(info->Password, info->PasswordLength);
		WriteString_Mandatory(info->DefaultApplVerID, info->DefaultApplVerIDLength);
	}
	inline void EncodeLogoutInfo(FastLogoutInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("5", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
		WriteString_Mandatory(info->TargetCompID, info->TargetCompIDLength);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		if(!info->AllowText)
			this->WriteNull();
		else
			WriteString_Optional(info->Text, info->TextLength);
	}
	inline void EncodeSecurityDefinitionInfo(FastSecurityDefinitionInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WritePresenceMap1(info->PresenceMap);
		WriteString_Mandatory("d", 1);
		WriteString_Mandatory("9", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
		if(CheckMandatoryFieldPresence(info->PresenceMap, info->MsgSeqNumPresenceIndex))
			WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		if(CheckMandatoryFieldPresence(info->PresenceMap, info->MessageEncodingPresenceIndex))
			WriteString_Mandatory(info->MessageEncoding, info->MessageEncodingLength);
		if(!info->AllowTotNumReports)
			this->WriteNull();
		else
			WriteInt32_Optional(info->TotNumReports);
		if(!info->AllowSymbol)
			this->WriteNull();
		else
			WriteString_Optional(info->Symbol, info->SymbolLength);
		if(!info->AllowSecurityID)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->SecurityID, info->SecurityIDLength);
		if(!info->AllowSecurityIDSource)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->SecurityIDSource, info->SecurityIDSourceLength);
		if(!info->AllowProduct)
			this->WriteNull();
		else
			WriteInt32_Optional(info->Product);
		if(!info->AllowCFICode)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->CFICode, info->CFICodeLength);
		if(!info->AllowSecurityType)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->SecurityType, info->SecurityTypeLength);
		if(!info->AllowMaturityDate)
			this->WriteNull();
		else
			WriteUInt32_Optional(info->MaturityDate);
		if(!info->AllowSettlDate)
			this->WriteNull();
		else
			WriteUInt32_Optional(info->SettlDate);
		if(!info->AllowSettleType)
			this->WriteNull();
		else
			WriteString_Optional(info->SettleType, info->SettleTypeLength);
		if(!info->AllowOrigIssueAmt)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->OrigIssueAmt));
		if(!info->AllowCouponPaymentDate)
			this->WriteNull();
		else
			WriteUInt32_Optional(info->CouponPaymentDate);
		if(!info->AllowCouponRate)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->CouponRate));
		if(!info->AllowSettlFixingDate)
			this->WriteNull();
		else
			WriteUInt32_Optional(info->SettlFixingDate);
		if(!info->AllowDividendNetPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->DividendNetPx));
		if(!info->AllowSecurityDesc)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->SecurityDesc, info->SecurityDescLength);
		if(!info->AllowEncodedSecurityDesc)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->EncodedSecurityDesc, info->EncodedSecurityDescLength);
		if(!info->AllowQuoteText)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->QuoteText, info->QuoteTextLength);
		if(!info->AllowGroupInstrAttrib)
			this->WriteNull();
		else {
			WriteUInt32_Mandatory(info->GroupInstrAttribCount);
			FastSecurityDefinitionGroupInstrAttribItemInfo **giaItemInfo = info->GroupInstrAttrib;
			for(int i = 0; i < info->GroupInstrAttribCount; i++) {
				WriteInt32_Mandatory((*giaItemInfo)->InstrAttribType);
				if(!(*giaItemInfo)->AllowInstrAttribValue)
					this->WriteNull();
				else
					WriteByteVector_Optional((*giaItemInfo)->InstrAttribValue, (*giaItemInfo)->InstrAttribValueLength);
				giaItemInfo++;
			}
		}
		if(!info->AllowCurrency)
			this->WriteNull();
		else
			WriteString_Optional(info->Currency, info->CurrencyLength);
		if(!info->AllowMarketSegmentGrp)
			this->WriteNull();
		else {
			WriteUInt32_Mandatory(info->MarketSegmentGrpCount);
			FastSecurityDefinitionMarketSegmentGrpItemInfo **msgItemInfo = info->MarketSegmentGrp;
			for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
				if(!(*msgItemInfo)->AllowRoundLot)
					this->WriteNull();
				else
					WriteDecimal_Optional(&((*msgItemInfo)->RoundLot));
				if(!(*msgItemInfo)->AllowTradingSessionRulesGrp)
					this->WriteNull();
				else {
					WriteUInt32_Mandatory((*msgItemInfo)->TradingSessionRulesGrpCount);
					FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo **tsrgItemInfo = (*msgItemInfo)->TradingSessionRulesGrp;
					for(int i = 0; i < (*msgItemInfo)->TradingSessionRulesGrpCount; i++) {
						WriteString_Mandatory((*tsrgItemInfo)->TradingSessionID, (*tsrgItemInfo)->TradingSessionIDLength);
						if(!(*tsrgItemInfo)->AllowTradingSessionSubID)
							this->WriteNull();
						else
							WriteString_Optional((*tsrgItemInfo)->TradingSessionSubID, (*tsrgItemInfo)->TradingSessionSubIDLength);
						if(!(*tsrgItemInfo)->AllowSecurityTradingStatus)
							this->WriteNull();
						else
							WriteInt32_Optional((*tsrgItemInfo)->SecurityTradingStatus);
						if(!(*tsrgItemInfo)->AllowOrderNote)
							this->WriteNull();
						else
							WriteInt32_Optional((*tsrgItemInfo)->OrderNote);
						tsrgItemInfo++;
					}
				}
				msgItemInfo++;
			}
		}
		if(!info->AllowSettlCurrency)
			this->WriteNull();
		else
			WriteString_Optional(info->SettlCurrency, info->SettlCurrencyLength);
		if(!info->AllowPriceType)
			this->WriteNull();
		else
			WriteInt32_Optional(info->PriceType);
		if(!info->AllowStateSecurityID)
			this->WriteNull();
		else
			WriteString_Optional(info->StateSecurityID, info->StateSecurityIDLength);
		if(!info->AllowEncodedShortSecurityDesc)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->EncodedShortSecurityDesc, info->EncodedShortSecurityDescLength);
		if(!info->AllowMarketCode)
			this->WriteNull();
		else
			WriteByteVector_Optional(info->MarketCode, info->MarketCodeLength);
		if(!info->AllowMinPriceIncrement)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->MinPriceIncrement));
		if(!info->AllowMktShareLimit)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->MktShareLimit));
		if(!info->AllowMktShareThreshold)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->MktShareThreshold));
		if(!info->AllowMaxOrdersVolume)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->MaxOrdersVolume));
		if(!info->AllowPriceMvmLimit)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->PriceMvmLimit));
		if(!info->AllowFaceValue)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->FaceValue));
		if(!info->AllowBaseSwapPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->BaseSwapPx));
		if(!info->AllowRepoToPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->RepoToPx));
		if(!info->AllowBuyBackPx)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->BuyBackPx));
		if(!info->AllowBuyBackDate)
			this->WriteNull();
		else
			WriteUInt32_Optional(info->BuyBackDate);
		if(!info->AllowNoSharesIssued)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->NoSharesIssued));
		if(!info->AllowHighLimit)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->HighLimit));
		if(!info->AllowLowLimit)
			this->WriteNull();
		else
			WriteDecimal_Optional(&(info->LowLimit));
		if(!info->AllowNumOfDaysToMaturity)
			this->WriteNull();
		else
			WriteInt32_Optional(info->NumOfDaysToMaturity);
	}
	inline void EncodeSecurityStatusInfo(FastSecurityStatusInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("f", 1);
		WriteString_Mandatory("9", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		WriteString_Mandatory(info->Symbol, info->SymbolLength);
		if(!info->AllowTradingSessionID)
			this->WriteNull();
		else
			WriteString_Optional(info->TradingSessionID, info->TradingSessionIDLength);
		if(!info->AllowTradingSessionSubID)
			this->WriteNull();
		else
			WriteString_Optional(info->TradingSessionSubID, info->TradingSessionSubIDLength);
		if(!info->AllowSecurityTradingStatus)
			this->WriteNull();
		else
			WriteInt32_Optional(info->SecurityTradingStatus);
		if(!info->AllowAuctionIndicator)
			this->WriteNull();
		else
			WriteUInt32_Optional(info->AuctionIndicator);
	}
	inline void EncodeTradingSessionStatusInfo(FastTradingSessionStatusInfo* info) {
		ResetBuffer();
		WriteMsgSeqNumber(this->m_sendMsgSeqNo);
		WriteString_Mandatory("h", 1);
		WriteString_Mandatory("9", 1);
		WriteString_Mandatory("FIXT.1.1", 8);
		WriteString_Mandatory("MOEX", 4);
		WriteUInt32_Mandatory(info->MsgSeqNum);
		WriteUInt64_Mandatory(info->SendingTime);
		WriteInt32_Mandatory(info->TradSesStatus);
		if(!info->AllowText)
			this->WriteNull();
		else
			WriteString_Optional(info->Text, info->TextLength);
		WriteString_Mandatory(info->TradingSessionID, info->TradingSessionIDLength);
	}
#pragma endregion

    void* DecodeUnsupportedMessage() {
        return NULL;
    }

#pragma region Decode_Methods_Definition_GeneratedCode
	inline FastHeaderInfo* DecodeHeader() {

		FastHeaderInfo *info = GetFreeHeaderInfo();
		
		this->ParsePresenceMap(&(info->PresenceMap));

		ReadString_Mandatory(&(info->MessageType), &(info->MessageTypeLength));
		return info;
	}

	void* DecodeLogon() {
		FastLogonInfo* info = GetFreeLogonInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		ReadString_Mandatory(&(info->TargetCompID), &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->HeartBtInt = ReadInt32_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Username), &(info->UsernameLength));
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Password), &(info->PasswordLength));
		ReadString_Mandatory(&(info->DefaultApplVerID), &(info->DefaultApplVerIDLength));
		return info;
	}
	void* DecodeLogout() {
		FastLogoutInfo* info = GetFreeLogoutInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		ReadString_Mandatory(&(info->TargetCompID), &(info->TargetCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Text), &(info->TextLength));
		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshGeneric() {
		FastMarketDataSnapshotFullRefreshGenericInfo* info = GetFreeMarketDataSnapshotFullRefreshGenericInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->NetChgPrevDay));

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshGenericGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
				else {
					gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
					gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshGeneric() {
		FastMarketDataIncrementalRefreshGenericInfo* info = GetFreeMarketDataIncrementalRefreshGenericInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshGenericGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->SumQtyOfBest = ReadInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
				else {
					gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
					gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOLSFOND() {
		FastMarketDataSnapshotFullRefreshOLSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshOLSFONDInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOLSFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOLSCURR() {
		FastMarketDataSnapshotFullRefreshOLSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshOLSCURRInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOLSCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshTLSFOND() {
		FastMarketDataSnapshotFullRefreshTLSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshTLSFONDInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshTLSFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshTLSCURR() {
		FastMarketDataSnapshotFullRefreshTLSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshTLSCURRInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshTLSCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOBSFOND() {
		FastMarketDataSnapshotFullRefreshOBSFONDInfo* info = GetFreeMarketDataSnapshotFullRefreshOBSFONDInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOBSFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataSnapshotFullRefreshOBSCURR() {
		FastMarketDataSnapshotFullRefreshOBSCURRInfo* info = GetFreeMarketDataSnapshotFullRefreshOBSCURRInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		if(!CheckProcessNullUInt32())
			info->LastMsgSeqNumProcessed = ReadUInt32_Optional();
		info->RptSeq = ReadInt32_Mandatory();
		if(!CheckProcessNullInt32())
			info->TradSesStatus = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullUInt32())
			info->LastFragment = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->RouteFirst = ReadUInt32_Optional();
		if(!CheckProcessNullInt32())
			info->MDSecurityTradingStatus = ReadInt32_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataSnapshotFullRefreshOBSCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshMSRFOND() {
		FastMarketDataIncrementalRefreshMSRFONDInfo* info = GetFreeMarketDataIncrementalRefreshMSRFONDInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshMSRFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->StartTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MinCurrPxChgTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->VolumeIndicator = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
				else {
					gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
					gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshMSRCURR() {
		FastMarketDataIncrementalRefreshMSRCURRInfo* info = GetFreeMarketDataIncrementalRefreshMSRCURRInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshMSRCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->QuoteCondition), &(gmdeItemInfo->QuoteConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradeCondition), &(gmdeItemInfo->TradeConditionLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OpenCloseSettlFlag), &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->TotalNumOfTrades = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->OfferNbOr = ReadInt32_Optional();
			if(!CheckProcessNullInt32())
				gmdeItemInfo->BidNbOr = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->CXFlag), &(gmdeItemInfo->CXFlagLength));
				else {
					gmdeItemInfo->CXFlag = gmdeItemInfo->PrevCXFlag;
					gmdeItemInfo->CXFlagLength = gmdeItemInfo->PrevCXFlagLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOLRFOND() {
		FastMarketDataIncrementalRefreshOLRFONDInfo* info = GetFreeMarketDataIncrementalRefreshOLRFONDInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOLRFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrdType), &(gmdeItemInfo->OrdTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOLRCURR() {
		FastMarketDataIncrementalRefreshOLRCURRInfo* info = GetFreeMarketDataIncrementalRefreshOLRCURRInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOLRCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!CheckProcessNullString())
					ReadString_Optional(&(gmdeItemInfo->DealNumber), &(gmdeItemInfo->DealNumberLength));
				else {
					gmdeItemInfo->DealNumber = gmdeItemInfo->PrevDealNumber;
					gmdeItemInfo->DealNumberLength = gmdeItemInfo->PrevDealNumberLength;
				}
			}
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderStatus), &(gmdeItemInfo->OrderStatusLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOBRFOND() {
		FastMarketDataIncrementalRefreshOBRFONDInfo* info = GetFreeMarketDataIncrementalRefreshOBRFONDInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOBRFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->EffectiveTime = ReadUInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshOBRCURR() {
		FastMarketDataIncrementalRefreshOBRCURRInfo* info = GetFreeMarketDataIncrementalRefreshOBRCURRInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshOBRCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshTLRFOND() {
		FastMarketDataIncrementalRefreshTLRFONDInfo* info = GetFreeMarketDataIncrementalRefreshTLRFONDInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshTLRFONDGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeMarketDataIncrementalRefreshTLRCURR() {
		FastMarketDataIncrementalRefreshTLRCURRInfo* info = GetFreeMarketDataIncrementalRefreshTLRCURRInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory();
		FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo* gmdeItemInfo = NULL;
		FastMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo** gmdeItemInfoList = info->GroupMDEntries;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeMarketDataIncrementalRefreshTLRCURRGroupMDEntriesItemInfo();
			(*gmdeItemInfoList) = gmdeItemInfo;
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDUpdateAction = ReadUInt32_Optional();
			ReadString_Mandatory(&(gmdeItemInfo->MDEntryType), &(gmdeItemInfo->MDEntryTypeLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->MDEntryID), &(gmdeItemInfo->MDEntryIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->Symbol), &(gmdeItemInfo->SymbolLength));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->RptSeq = ReadInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryDate = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->MDEntryTime = ReadUInt32_Optional();
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->OrigTime = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->OrderSide), &(gmdeItemInfo->OrderSideLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->SettlDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->SettleType), &(gmdeItemInfo->SettleTypeLength));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!CheckProcessNullInt32())
				gmdeItemInfo->PriceType = ReadInt32_Optional();
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!CheckProcessNullUInt32())
				gmdeItemInfo->BuyBackDate = ReadUInt32_Optional();
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionID), &(gmdeItemInfo->TradingSessionIDLength));
			if(!CheckProcessNullString())
				ReadString_Optional(&(gmdeItemInfo->TradingSessionSubID), &(gmdeItemInfo->TradingSessionSubIDLength));
			gmdeItemInfoList++;
		}

		return info;
	}
	void* DecodeSecurityDefinition() {
		FastSecurityDefinitionInfo* info = GetFreeSecurityDefinitionInfo();

		info->PresenceMap = this->m_header->PresenceMap;

		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		if(CheckMandatoryFieldPresence(info->PresenceMap, PRESENCE_MAP_INDEX0)) {
			info->MsgSeqNum = ReadUInt32_Mandatory();
		}
		else {
			info->MsgSeqNum++;
		}
		info->SendingTime = ReadUInt64_Mandatory();
		if(CheckMandatoryFieldPresence(info->PresenceMap, PRESENCE_MAP_INDEX1)) {
			ReadString_Mandatory(&(info->MessageEncoding), &(info->MessageEncodingLength));
		}
		else {
			info->MessageEncoding = this->MessageEncodingConstString;
			info->MessageEncodingLength = 5;
		}
		if(!CheckProcessNullInt32())
			info->TotNumReports = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityID), &(info->SecurityIDLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityIDSource), &(info->SecurityIDSourceLength));
		if(!CheckProcessNullInt32())
			info->Product = ReadInt32_Optional();
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->CFICode), &(info->CFICodeLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityType), &(info->SecurityTypeLength));
		if(!CheckProcessNullUInt32())
			info->MaturityDate = ReadUInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->SettlDate = ReadUInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->SettleType), &(info->SettleTypeLength));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->OrigIssueAmt));
		if(!CheckProcessNullUInt32())
			info->CouponPaymentDate = ReadUInt32_Optional();
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->CouponRate));
		if(!CheckProcessNullUInt32())
			info->SettlFixingDate = ReadUInt32_Optional();
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->DividendNetPx));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->SecurityDesc), &(info->SecurityDescLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->EncodedSecurityDesc), &(info->EncodedSecurityDescLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->QuoteText), &(info->QuoteTextLength));

		info->GroupInstrAttribCount = ReadUInt32_Mandatory();
		FastSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;
		FastSecurityDefinitionGroupInstrAttribItemInfo** giaItemInfoList = info->GroupInstrAttrib;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = GetFreeSecurityDefinitionGroupInstrAttribItemInfo();
			(*giaItemInfoList) = giaItemInfo;
			giaItemInfo->InstrAttribType = ReadInt32_Mandatory();
			if(!CheckProcessNullByteVector())
				ReadByteVector_Optional(&(giaItemInfo->InstrAttribValue), &(giaItemInfo->InstrAttribValueLength));
			giaItemInfoList++;
		}

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Currency), &(info->CurrencyLength));

		info->MarketSegmentGrpCount = ReadUInt32_Mandatory();
		FastSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;
		FastSecurityDefinitionMarketSegmentGrpItemInfo** msgItemInfoList = info->MarketSegmentGrp;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = GetFreeSecurityDefinitionMarketSegmentGrpItemInfo();
			(*msgItemInfoList) = msgItemInfo;
			if(!CheckProcessNullDecimal())
				ReadDecimal_Optional(&(msgItemInfo->RoundLot));

			msgItemInfo->TradingSessionRulesGrpCount = ReadUInt32_Mandatory();
			FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;
			FastSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo** tsrgItemInfoList = msgItemInfo->TradingSessionRulesGrp;

			for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
				tsrgItemInfo = GetFreeSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
				(*tsrgItemInfoList) = tsrgItemInfo;
				ReadString_Mandatory(&(tsrgItemInfo->TradingSessionID), &(tsrgItemInfo->TradingSessionIDLength));
				if(!CheckProcessNullString())
					ReadString_Optional(&(tsrgItemInfo->TradingSessionSubID), &(tsrgItemInfo->TradingSessionSubIDLength));
				if(!CheckProcessNullInt32())
					tsrgItemInfo->SecurityTradingStatus = ReadInt32_Optional();
				if(!CheckProcessNullInt32())
					tsrgItemInfo->OrderNote = ReadInt32_Optional();
				tsrgItemInfoList++;
			}

			msgItemInfoList++;
		}

		if(!CheckProcessNullString())
			ReadString_Optional(&(info->SettlCurrency), &(info->SettlCurrencyLength));
		if(!CheckProcessNullInt32())
			info->PriceType = ReadInt32_Optional();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->StateSecurityID), &(info->StateSecurityIDLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->EncodedShortSecurityDesc), &(info->EncodedShortSecurityDescLength));
		if(!CheckProcessNullByteVector())
			ReadByteVector_Optional(&(info->MarketCode), &(info->MarketCodeLength));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MinPriceIncrement));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MktShareLimit));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MktShareThreshold));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->MaxOrdersVolume));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->PriceMvmLimit));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->FaceValue));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->BaseSwapPx));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->RepoToPx));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->BuyBackPx));
		if(!CheckProcessNullUInt32())
			info->BuyBackDate = ReadUInt32_Optional();
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->NoSharesIssued));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->HighLimit));
		if(!CheckProcessNullDecimal())
			ReadDecimal_Optional(&(info->LowLimit));
		if(!CheckProcessNullInt32())
			info->NumOfDaysToMaturity = ReadInt32_Optional();
		return info;
	}
	void* DecodeSecurityStatus() {
		FastSecurityStatusInfo* info = GetFreeSecurityStatusInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		ReadString_Mandatory(&(info->Symbol), &(info->SymbolLength));
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->TradingSessionSubID), &(info->TradingSessionSubIDLength));
		if(!CheckProcessNullInt32())
			info->SecurityTradingStatus = ReadInt32_Optional();
		if(!CheckProcessNullUInt32())
			info->AuctionIndicator = ReadUInt32_Optional();
		return info;
	}
	void* DecodeTradingSessionStatus() {
		FastTradingSessionStatusInfo* info = GetFreeTradingSessionStatusInfo();


		ReadString_Mandatory(&(info->ApplVerID), &(info->ApplVerIDLength));
		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		info->TradSesStatus = ReadInt32_Mandatory();
		if(!CheckProcessNullString())
			ReadString_Optional(&(info->Text), &(info->TextLength));
		ReadString_Mandatory(&(info->TradingSessionID), &(info->TradingSessionIDLength));
		return info;
	}
	void* DecodeHeartbeat() {
		FastHeartbeatInfo* info = GetFreeHeartbeatInfo();


		ReadString_Mandatory(&(info->BeginString), &(info->BeginStringLength));
		ReadString_Mandatory(&(info->SenderCompID), &(info->SenderCompIDLength));
		info->MsgSeqNum = ReadUInt32_Mandatory();
		info->SendingTime = ReadUInt64_Mandatory();
		return info;
	}
	inline void Decode_Generic() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_Generic[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OLS_FOND() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OLS_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OLS_CURR() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OLS_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_TLS_FOND() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_TLS_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_TLS_CURR() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_TLS_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OBS_FOND() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OBS_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OBS_CURR() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OBS_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_MSR_FOND() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_MSR_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_MSR_CURR() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_MSR_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OLR_FOND() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OLR_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OLR_CURR() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OLR_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OBR_FOND() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OBR_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_OBR_CURR() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_OBR_CURR[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_TLR_FOND() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_TLR_FOND[msgType];
		(this->*funcPtr)();
	}
	inline void Decode_TLR_CURR() {
		this->DecodeHeader();
		unsigned char msgType = this->GetMsgType();
		FastDecodeMethodPointer funcPtr = this->DecodeMethods_TLR_CURR[msgType];
		(this->*funcPtr)();
	}
#pragma endregion
};

