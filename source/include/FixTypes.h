//
// Created by arsen on 11.07.16.
//

#ifndef HFT_ROBOT_FIXTYPES_H
#define HFT_ROBOT_FIXTYPES_H

#include "Types.h"
#include "UTCTimeConverter.h"

#pragma pack(push)
#pragma pack(4)
typedef struct _PartyInfo {
    char	ID[16];
    int		IDLength;
    char	IDSource;
    int		Role;
} FixPartyInfo;

typedef struct _UnderlyingSymbolInfo {
    char	Symbol[16];
    int		SymbolLength;
    char	SymbolSfx[16];
    int		SymbolSfxLength;
    char	SecurityId[16];
    int		SecurityIdLength;
    char	SecurityIdSource[32];
    int		SecurityIdSourceLength;
    int		NoSecurityAltId;
    char	SecurityAltId[16][16];	// max 16
    int		SecurityAltIdLength[16];
    char	SecurityAltIdSource[16][32];
    int		SecurityAltIdSourceLength[16];
    bool	AllowProduct;
    int		Product;
    char	CfiCode[32];
    int		CfiCodeLength;
    char	SecurityType[16];
    int		SecurityTypeLength;
    char	SecuritySubType[32];
    int		SecuritySubTypeLength;
    bool	AllowMonthYear;
    int		Month;
    int		Year;
    char	MonthYearString[8];
    int		MaturityDateMonth;
    int		MaturityDateYear;
    bool	AllowMaturityDate;
    char	MaturityDateString[8];
    int		CouponPaymentDateMonth;
    int		CouponPaymentDateYear;
    bool	AllowCouponPaymentDate;
    char	CouponPaymentDateString[8];
    int		IssueDateMonth;
    int		IssueDateYear;
    bool	AllowIssueDate;
    char	IssueDateString[8];
    bool	AllowRepoCollateralSecurityType;
    int		RepoCollateralSecurityType;
    bool	AllowRepurchaseTerm;
    int		RepurchaseTerm;
    bool	AllowRepurchaseRate;
    float	RepurchaseRate;
    bool	AllowFactor;
    float	Factor;
    char	CreditRating[16];
    int		CreditRatingLength;
    char	InstrRegistry[32];
    int		InstrRegistryLength;
    bool	AllowCountry;
    char	Country[2];
    char	StateOrProvinceOfIssue[128];
    int		StateOrProvinceOfIssueLength;
    char	LocaleOfIssue[32];
    int		LocaleOfIssueLength;
    int		RedemtionDateMonth;
    int		RedemtionDateYear;
    bool	AllowRedemptionDate;
    char	RedemptionDate[8];
    bool	AllowStrikePrice;
    float	StrikePrice;
    bool	AllowStrikeCurrency;
    char	StrikeCurrency[3];
    bool	AllowOptAttribute;
    char	OptAttribute;
    bool	AllowContractMultiplier;
    float	ContractMultiplier;
    bool	AllowCouponRate;
    float	CouponRate;
    char	SecurityExchange[128];
    int		SecurityExchangeLength;
    char	Issuer[64];
    int		IssuerLength;
    int		EncodedIssuerLength;
    char	EncodedIssuer[128];
    int		SecurityDescriptionLength;
    char	SecurityDescription[128];
    int		EncodedSecurityDescriptionLength;
    char	EncodedSecurityDescription[128];
    char	CPProgramm[128];
    int		CPProgrammLength;
    char	CPRegType[64];
    int		CPRegTypeLength;
    bool	AllowCurrency;
    char	Currency[3];
    bool	AllowQty;
    float	Qty;
    bool	AllowPx;
    float	Px;
    bool	AllowDirtyPrice;
    float	DirtyPrice;
    bool	AllowEndPrice;
    float	EndPrice;
    bool	AllowStartValue;
    float	StartValue;
    bool	AllowCurrentValue;
    float	CurrentValue;
    bool	AllowEndValue;
    float	EndValue;
} UnderlyingSymbolInfo;

typedef struct _UnderlyingStipulation {
    char	StipType[32];
    int		StipTypeLength;
    char	StipValue[16];
    int		StipValueLength;
}UnderlyingStipulation;

typedef enum _FixSessionStatus  {
    Active = 0,
    PasswordDoesNotMeetRequirements = 3
}FixSessionStatus;


typedef struct _LogonInfo {
    int MsgStartSequenceNumber;
    int EncryptionType;
    int HearthBtInt;
    bool ShouldResetSeqNum;
    char CompID[32];
    int CompIDLength;
    char Password[12];
    int PassLength;
    char NewPassword[12];
    int NewPassLength;
    bool AllowSessionStatus;
    FixSessionStatus SessionStatus;
    bool CancelOnDisconnect;
    char LanguageId;
}FixLogonInfo;

typedef enum _FixSessionRejectReason {
    IncorrectTag = 0,
    FieldMissing = 1,
    TagIsNotDefinedForMessage = 2,
    UndefinedTag = 3,
    TagMissingValue = 4,
    IncorrectTagValue = 5,
    DataFormatNotCorrectForTagValue = 6,
    DecryptionProblem = 7,
    SigningProblem = 8,
    CompIDProblem = 9,
    SendingTimeNotCorrect = 10,
    IncorrectMsgType = 11,
    XMLValidationProblem = 12,
    TagIsUsedMoreThanOnce = 13,
    InvalidTagOrder = 14,
    InvalidFieldOrder = 15,
    IncorrectNumInGroup = 16,
    FieldNoDataValueContainsSeparator = 17,
    Other = 99,
    NoReason = -1
}FixSessionRejectReason;


static const char	**FixSecurityType = new const char*[5] {
        "FXSPOT",
        "FXSWAP",
        "FXFWD",
        "FXBKT",
        "REPO"
};

static int		*FixSecurityTypeLength = new int[5] {
        6,
        6,
        5,
        5,
        4
};

#define FixCFICodeLength 6

typedef struct _FixInstrumentInfo {
    char	Symbol[12];
    int		SymbolLength;
    bool	AllowProduct;
    int		Product;
    bool	AllowCFICode;
    char	CFICode[6];
    bool	AllowSecurityType;
    char	*SecurityType;
    int		SecurityTypeLength;
}FixInstrumentInfo;

typedef struct _FixPartyListInfo {
    int				Count;
    FixPartyInfo	Parties[16];
}FixPartyListInfo;

typedef struct _FixCommisionData {
    float			Commision;
    char			Type[16];
    int				TypeLength;
}FixCommisionData;

typedef struct _FixOrderQtyData {
    float			Qty;
    float			CashQty;
}FixOrderQtyData;

const char FixSideBuy	= '1';
const char FixSideSell	= '2';

const char FixOrdTypeMarket = '1';
const char FixOrdTypeLimit = '2';
const char FixOrdTypeAveragePrice = 'W';

const int	PercentageNominal = 1;
const int	PerItem = 2;
const int	Debit = 9;

const char FixTradeThruTimeFullDay = '0';
const char FixTradeThruTimeGetAvailable = '3';
const char FixTradeThruTimeFullOrDecline = '4';

typedef struct _FixNewOrderInfo {
    char				ClOrdID[12];
    int					ClOrdIDLength;
    FixPartyListInfo	Parties;
    char				Account[12];
    int					AccountLength;
    bool				AllowMaxFloor;
    float				MaxFloor;
    char				SecClOrdID[12];
    int					SecClOrdIDLength;
    char*				TradingSessionID;
    int					TradingSessionIDLength;
    FixInstrumentInfo	Instrument;
    char				Side;
    SYSTEMTIME			TransactTime;
    char				TransactTimeString[UTCTimeStampLength];
    FixOrderQtyData		OrderQtyData;
    char				OrderType;
    bool				AllowPriceType;
    int					PriceType;
    bool				AllowPrice;
    float				Price;
    bool				AllowTradeThruTime;
    char				TradeThruTime;
    bool				AllowTimeInForce;
    char				TimeInForce;
    bool				AllowEffectiveTime;
    SYSTEMTIME			EffectiveTime;
    char				EffectiveTimeString[UTCTimeStampLength];
    bool				AllowOrderCapacity;
    char				OrderCapacity;
    bool				AllowOrderRestrictions;
    char				OrderRestrictions[128];
    int					OrderRestrictionsLength;
    bool				AllowMaxPiceLevels;
    int					MaxPriceLevels;
    bool				AllowCancelOrigOnReject;
    bool				CancelOrigOnReject;
}FixNewOrderInfo;

typedef struct _FixOrderCancelRequestInfo {
    char				OrigClOrdID[12];
    int					OrigClOrdIDLength;
    char				OrdID[12];
    int					OrdIDLength;
    char				ClOrdID[12];
    int					ClOrdIDLength;
    char				Side;
    SYSTEMTIME			TransactTime;
    char				TransactTimeString[UTCTimeStampLength];
}FixOrderCancelRequestInfo;

const char MassCancelRequestTypeByInstrument = '1';
const char MassCancelRequestTypeByQuery = '7';

typedef struct _FixOrderMassCancelRequest {
    char				ClOrdID[12];
    int					ClOrdIDLength;
    char				SecClOrdID[12];
    int					SecClOrdIDLength;
    char				MassCancelRequestType;
    char*				TradingSessionID;
    int					TradingSessionIDLength;
    FixInstrumentInfo	Instrument;
    bool				AllowSide;
    char				Side;
    SYSTEMTIME			TransactTime;
    char				TransactTimeString[UTCTimeStampLength];
    char				Account[12];
    int					AccountLength;
    bool				AllowParties;
    FixPartyListInfo	Parties;
}FixOrderMassCancelRequestInfo;


// Processing Diagnostic Codes
typedef enum _FixDiagnosticCodes {
    FixDcSuccess,
    FixDcFailed,
    FixDcCheckFixVersion,
    FixDcProcessCheckHeader,
    FixDcProcessMessageBodyLen,
}FixDiagnosticCodes;

typedef enum _FixSecurityRequestType {
    FixSecurityRequestType_RequestSecurityIdentityAndSpecifications = 0,
    FixSecurityRequestType_RequestSecurityIdentityAndSpecificationsProvided = 1,
    FixSecurityRequestType_RequestListSequrityTypes = 2,
    FixSecurityRequestType_RequestListSecurities = 3
}FixSecurityRequestType;

typedef enum _FixSecurityListRequestType {
    FixSecurityListRequestType_Symbol = 0,
    FixSecurityListRequestType_SecurityType_CFICode = 1,
    FixSecurityListRequestType_Product = 2,
    FixSecurityListRequestType_TradingSessionID = 3,
    FixSecurityListRequestType_All = 4
}FixSecurityListRequestType;

typedef struct _FixTagValueInfo {
    char		*StartingAddress;
    int			Tag;
    char		*ValueString;
    int			ValueStringLength;
    float		FloatValue;
    int			IntValue;
    char		CharValue;
    int			Length;
}FixTagValueInfo;

typedef struct _Decimal {
    INT32		Mantissa;
    INT32		Exponent;
}Decimal;
#pragma pack(pop)

#endif //HFT_ROBOT_FIXTYPES_H