// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x71;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0x00;
        vAlertPubKey = ParseHex("044237af191e295d9f47806b00143372f671f0c67b6cc164403770184353e3c9005d8d9778085b4b74cc285f1d9213a3b793af051790fd080349512c90914d7114");
        nDefaultPort = 9333;
        nRPCPort = 19333;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "today I create olegcoin lets goooooooo!!! 13 Feb 2020";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1581617132, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1581617132;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1495627;
        //mining genesis block
        //hashGenesisBlock = uint256("0x01");
        //if(true && genesis.GetHash() != hashGenesisBlock)
        //              {
        //                printf("Searching for genesis block...\n");
        //                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        //                uint256 thash;
        //
        //                while (true)
        //                {
        //                  thash = genesis.GetHash();
        //                  if (thash <= hashTarget)
        //                     break;
        //                  if((genesis.nNonce & 0xFFF) == 0)
        //                  {
        //                    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        //                  }
        //                  ++genesis.nNonce;
        //                  if (genesis.nNonce == 0)
        //                  {
        //                    printf("NONCE WRAPPED, incrementing time\n");
        //                    ++ genesis.nTime;
        //                  }
        //                }
        //  printf("genesis.nTime = %u \n", genesis.nTime);
        //  printf("genesis.nNonce = %u \n", genesis.nNonce);
        //  printf("genesis.nVersion = %u \n", genesis.nVersion);
        //  printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //  printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str());
        //              }
        //mining genesis block
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000040d04e75284e7c2d0ee762e40feddb53269ebfe5a6951ecdfb2d48557ff"));
        assert(genesis.hashMerkleRoot == uint256("0x34a86bfa80850659f79469ad6c6b09d852d543b9ad443a07089f24e9763c1692"));

        vSeeds.push_back(CDNSSeedData("vasin.nl", "dnsseed.vasin.nl"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 115); // o
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 5000;
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
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xdf;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04c5230a773a6af8cbd85f32a2cb4b78862ffaa9c808bbd8fb49ec6b46e91c13dd8d40f106016333e21521d8e25d864dd1f7cd445a69ed7c0f402014caeef708df");
        nDefaultPort = 8333;
        nRPCPort = 18333;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1538512;
        hashGenesisBlock = uint256("0x01");
        //mining genesis block
        //hashGenesisBlock = uint256("0x01");
        //if(true && genesis.GetHash() != hashGenesisBlock)
        //              {
        //                printf("Searching for genesis block...\n");
        //                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        //                uint256 thash;
        //
        //                while (true)
        //                {
        //                  thash = genesis.GetHash();
        //                  if (thash <= hashTarget)
        //                     break;
        //                  if((genesis.nNonce & 0xFFF) == 0)
        //                  {
        //                    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        //                  }
        //                  ++genesis.nNonce;
        //                  if (genesis.nNonce == 0)
        //                  {
        //                    printf("NONCE WRAPPED, incrementing time\n");
        //                    ++ genesis.nTime;
        //                  }
        //                }
        //  printf("genesis.nTime = %u \n", genesis.nTime);
        //  printf("genesis.nNonce = %u \n", genesis.nNonce);
        //  printf("genesis.nVersion = %u \n", genesis.nVersion);
        //  printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //  printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str());
        //              }
        //mining genesis block

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000041f4a49ebce06d6421129c9ced8cee76ad700f4aadd4753cb106fd9ecdc6"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 116); // o or p
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
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
        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xbe;
        pchMessageStart[2] = 0xbf;
        pchMessageStart[3] = 0xd0;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1581617132;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1495627;
        
        //mining genesis block
        //hashGenesisBlock = uint256("0x01");
        //if(true && genesis.GetHash() != hashGenesisBlock)
        //              {
        //                printf("Searching for genesis block...\n");
        //                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        //                uint256 thash;
        //
        //                while (true)
        //                {
        //                  thash = genesis.GetHash();
        //                  if (thash <= hashTarget)
        //                     break;
        //                  if((genesis.nNonce & 0xFFF) == 0)
        //                  {
        //                    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        //                  }
        //                  ++genesis.nNonce;
        //                  if (genesis.nNonce == 0)
        //                  {
        //                    printf("NONCE WRAPPED, incrementing time\n");
        //                    ++ genesis.nTime;
        //                  }
        //                }
        //  printf("genesis.nTime = %u \n", genesis.nTime);
        //  printf("genesis.nNonce = %u \n", genesis.nNonce);
        //  printf("genesis.nVersion = %u \n", genesis.nVersion);
        //  printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //  printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str());
        //              }
        //mining genesis block

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 10100;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x408cc8fb5b296c4e0257862dd4943f78935a254b596e9211f0eb60c11c5dc1b0"));

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
