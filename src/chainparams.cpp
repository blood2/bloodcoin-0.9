// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>
#include <stdint.h>


using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x6df9a8d5, 0x25974f2d, 0xe226655e, 0x473bf25e, 0xf301a28b, 0xcf0f212d, 0xdd7e21b2, 0xde2cee2e,
};

static CBigNum bnMainProofOfWorkLimit(~uint256(0) >> 21);
static const int64_t nGenesisBlockRewardCoin = 1 * COIN;
static const int64_t nBlockRewardStartCoin = 8192 * COIN;
static const int64_t nBlockRewardMinimumCoin = 1 * COIN;


class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0x35;
        pchMessageStart[3] = 0xc2;
        vAlertPubKey = ParseHex("0438e2caf8302a8a3d2e342a0b04cf6b6956be5bbcf53c2aa1d45d33763faceb20e8821be435694198fc26a3807963e4fd04ede1d5a5966220080a353bab070a5f");
        nDefaultPort = 5011;
        nRPCPort = 5009;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 21);  
        //nSubsidyHalvingInterval = 210000;

        // Genesis block
        const char* pszTimestamp = "The 2015 Bilderberg Conference just took place";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = nGenesisBlockRewardCoin;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("047c2e1ef97661cdbbc9d448dd35415c2d511fcab295eb39fb5fb27ec95442fbb44e2beb1233a5eadb9b1aeac97312f43ef244645ea9efc503e5d233a4a8424932") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 112;
        genesis.nTime    = 1434482533;
        genesis.nBits    = 0x1e07ffff;
        genesis.nNonce   = 12238375;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000031d234b64f9a2c8fc5c5ff49e3bcb6f809e558bddf1a3fb8f4fd48b953e"));
        assert(genesis.hashMerkleRoot == uint256("0xb1b803d7826df7d8b6464f3125c7dce12b050a5dc836693096f61d2cb5b5db45"));

        vSeeds.push_back(CDNSSeedData("ns000.bloodcoin.cc", "nd000.bloodcoin.cc"));
        vSeeds.push_back(CDNSSeedData("ns004.bloodcoin.cc", "nd004.bloodcoin.cc"));
        vSeeds.push_back(CDNSSeedData("ns001.bloodcoin.cc", "nd001.bloodcoin.cc"));



        base58Prefixes[PUBKEY_ADDRESS] = list_of(85);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(9);
        base58Prefixes[SECRET_KEY] =     list_of(213);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000005);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xff;

        vAlertPubKey = ParseHex("04517d8a699cb43d3938d7b24faaff7cda448ca4ea267723ba614784de661949bf632d6304316b244646dea079735b9a6fc4af804efb4752075b9fe2245e14e412");
        nDefaultPort = 19999;
        nRPCPort = 19998;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1390666206;
        genesis.nNonce = 3861367235;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x00000bafbc94add76cb75e2ec92894837288a481e5c005f6563d91623bf8bc2c"));

        vFixedSeeds.clear();
        vSeeds.clear();
        /*vSeeds.push_back(CDNSSeedData("dashpay.io", "testnet-seed.dashpay.io"));
        vSeeds.push_back(CDNSSeedData("dash.qa", "testnet-seed.dash.qa"));
        *///legacy seeders
        //vSeeds.push_back(CDNSSeedData("darkcoin.io",  "testnet-seed.darkcoin.io"));
        //vSeeds.push_back(CDNSSeedData("darkcoin.qa", "testnet-seed.darkcoin.qa"));
        //vSeeds.push_back(CDNSSeedData("masternode.io", "test.dnsseed.masternode.io"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(139);                    // Testnet dash addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 19);                    // Testnet dash script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY]     = list_of(239);                    // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x3a)(0x80)(0x61)(0xa0); // Testnet dash BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x3a)(0x80)(0x58)(0x37); // Testnet dash BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet dash BIP44 coin type is '5' (All coin's testnet default)
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1417713337;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1096447;
        nDefaultPort = 19994;
        strDataDir = "regtest";

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x000008ca1832a4baf228eb1553c03d3a2c8e02399550dd6ea8d65cec3ef23d2e"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
