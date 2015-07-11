
// Copyright (c) 2009-2012 The Dash developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SPORK_H
#define SPORK_H

#include "bignum.h"
#include "sync.h"
#include "net.h"
#include "key.h"
#include "core.h"
#include "util.h"
#include "script.h"
#include "base58.h"
#include "main.h"

using namespace std;
using namespace boost;

// Don't ever reuse these IDs for other sporks
#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT               10000
#define SPORK_2_INSTANTX                                      10001
#define SPORK_3_INSTANTX_BLOCK_FILTERING                      10002
#define SPORK_4_NOTUSED                                       10003
#define SPORK_5_MAX_VALUE                                     10004
#define SPORK_6_NOTUSED                                       10005
#define SPORK_7_MASTERNODE_SCANNING                           10006

#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT_DEFAULT       1436724000 // 2015-07-12 21:00:00
#define SPORK_2_INSTANTX_DEFAULT                              978307200   //2001-1-1
#define SPORK_3_INSTANTX_BLOCK_FILTERING_DEFAULT              1436724000 // 2015-07-12 21:00:00
#define SPORK_5_MAX_VALUE_DEFAULT                             100000      //100000 BOD
#define SPORK_7_MASTERNODE_SCANNING_DEFAULT                   978307200   //2001-1-1

class CSporkMessage;
class CSporkManager;

#include "bignum.h"
#include "net.h"
#include "key.h"
#include "util.h"
#include "protocol.h"
#include "darksend.h"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

extern std::map<uint256, CSporkMessage> mapSporks;
extern std::map<int, CSporkMessage> mapSporksActive;
extern CSporkManager sporkManager;

void ProcessSpork(CNode* pfrom, std::string& strCommand, CDataStream& vRecv);
int GetSporkValue(int nSporkID);
bool IsSporkActive(int nSporkID);
void ExecuteSpork(int nSporkID, int nValue);

//
// Spork Class
// Keeps track of all of the network spork settings
//

class CSporkMessage
{
public:
    std::vector<unsigned char> vchSig;
    int nSporkID;
    int64_t nValue;
    int64_t nTimeSigned;

    uint256 GetHash(){
        uint256 n = Hash9(BEGIN(nSporkID), END(nTimeSigned));
        return n;
    }

    IMPLEMENT_SERIALIZE(
        READWRITE(nSporkID);
        READWRITE(nValue);
        READWRITE(nTimeSigned);
        READWRITE(vchSig);
    )
};


class CSporkManager
{
private:
    std::vector<unsigned char> vchSig;

    std::string strMasterPrivKey;
    std::string strTestPubKey;
    std::string strMainPubKey;

public:

    CSporkManager() {
        strMainPubKey = "040947e40e55bef884938fb5367590b52b14256f75ccf05110b02c9bf89261a5cf3b58d1748996b92622b40ffc46c244c39c0508f8011520272c2b6c94094fdd53";
        strTestPubKey = "0438e2caf8302a8a3d2e342a0b04cf6b6956be5bbcf53c2aa1d45d33763faceb20e8821be435694198fc26a3807963e4fd04ede1d5a5966220080a353bab070a5f";
    }

    std::string GetSporkNameByID(int id);
    int GetSporkIDByName(std::string strName);
    bool UpdateSpork(int nSporkID, int64_t nValue);
    bool SetPrivKey(std::string strPrivKey);
    bool CheckSignature(CSporkMessage& spork);
    bool Sign(CSporkMessage& spork);
    void Relay(CSporkMessage& msg);

};

#endif
