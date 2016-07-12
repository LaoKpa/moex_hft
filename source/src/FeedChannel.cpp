#include "FeedChannel.h"
#include "LogManager.h"

FeedChannel::FeedChannel(const char *id, const char *name) {
	strcpy(this->id, id);
	strcpy(this->name, name);

	this->orderBookIncremental = NULL;
	this->orderBookSnapshot = NULL;
	this->statisticsIncremental = NULL;
	this->statisticsSnapshot = NULL;
	this->ordersIncremental = NULL;
	this->ordersSnapshot = NULL;
	this->tradesIncremental = NULL;
	this->tradesSnapshot = NULL;
	this->instrumentReplay = NULL;
	this->instrumentStatus = NULL;
	this->historicalReplay = NULL;
}

FeedChannel::~FeedChannel() {
}

void FeedChannel::SetConnection(FeedConnection *conn) { 
	if (strcmp(conn->Id(), "OBR"))
		this->orderBookIncremental = conn;
	if (strcmp(conn->Id(), "OBS"))
		this->orderBookSnapshot = conn;
	if (strcmp(conn->Id(), "MSR"))
		this->statisticsIncremental = conn;
	if (strcmp(conn->Id(), "MSS"))
		this->statisticsSnapshot = conn;
	if (strcmp(conn->Id(), "OLR"))
		this->ordersIncremental = conn;
	if (strcmp(conn->Id(), "OLS"))
		this->ordersSnapshot = conn;
	if (strcmp(conn->Id(), "TLR"))
		this->tradesIncremental = conn;
	if (strcmp(conn->Id(), "TLS"))
		this->tradesSnapshot = conn;
	if (strcmp(conn->Id(), "IDF"))
		this->instrumentReplay = conn;
	if (strcmp(conn->Id(), "ISF"))
		this->instrumentStatus = conn;
	if (strcmp(conn->Id(), "H"))
		this->historicalReplay = conn;
}

bool FeedChannel::Logon(FeedConnection *conn) { 
	if (conn == NULL)
		return true;
	return conn->Logon();
}

bool FeedChannel::Logout(FeedConnection *conn) { 
	if (conn == NULL)
		return true;
	return conn->Logout();
}

bool FeedChannel::Connect(FeedConnection *conn) { 
	if (conn == NULL)
		return true;
	return conn->Connect();
}
bool FeedChannel::Disconnect(FeedConnection *conn) { 
	if (conn == NULL)
		return true;
	return conn->Disconnect();
}

bool FeedChannel::Connect() { 
	DefaultLogManager::Default->StartLog(this->name, "FeedChannel::Connect");
	
	if (!this->Connect(this->orderBookIncremental)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->Connect(this->statisticsIncremental)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->Connect(this->ordersIncremental)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->Connect(this->tradesIncremental)) {
		DefaultLogManager::Default->EndLog(false);
		return false;
	}
	if (!this->Connect(this->instrumentStatus)) { 
		DefaultLogManager::Default->EndLog(false);
		return false;
	}

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool FeedChannel::Disconnect() { 
	
	bool result = true;
	
	result &= this->Disconnect(this->orderBookIncremental);
	result &= this->Disconnect(this->orderBookSnapshot);
	result &= this->Disconnect(this->statisticsIncremental);
	result &= this->Disconnect(this->statisticsSnapshot);
	result &= this->Disconnect(this->ordersIncremental);
	result &= this->Disconnect(this->ordersSnapshot);
	result &= this->Disconnect(this->tradesIncremental);
	result &= this->Disconnect(this->tradesSnapshot);
	result &= this->Disconnect(this->instrumentReplay);
	result &= this->Disconnect(this->instrumentStatus);
	result &= this->Disconnect(this->historicalReplay);

	return result;
}

bool FeedChannel::Logon() { 
	
	bool result = true;

	result &= this->Logon(this->orderBookIncremental);
	result &= this->Logon(this->orderBookSnapshot);
	result &= this->Logon(this->statisticsIncremental);
	result &= this->Logon(this->statisticsSnapshot);
	result &= this->Logon(this->ordersIncremental);
	result &= this->Logon(this->ordersSnapshot);
	result &= this->Logon(this->tradesIncremental);
	result &= this->Logon(this->tradesSnapshot);
	result &= this->Logon(this->instrumentReplay);
	result &= this->Logon(this->instrumentStatus);
	result &= this->Logon(this->historicalReplay);

	return result;
}

bool FeedChannel::Logout() { 
	bool result = true;

	result &= this->Logout(this->orderBookIncremental);
	result &= this->Logout(this->orderBookSnapshot);
	result &= this->Logout(this->statisticsIncremental);
	result &= this->Logout(this->statisticsSnapshot);
	result &= this->Logout(this->ordersIncremental);
	result &= this->Logout(this->ordersSnapshot);
	result &= this->Logout(this->tradesIncremental);
	result &= this->Logout(this->tradesSnapshot);
	result &= this->Logout(this->instrumentReplay);
	result &= this->Logout(this->instrumentStatus);
	result &= this->Logout(this->historicalReplay);

	return result;
}