/*
 * Copyright (c) 2009 Satoshi Nakamoto
 * Copyright (c) 2009-2014 The Bitcoin Developers
 * Copyright (c) 2017-2018 The Bolt Developers
 *
 * This file is part of Bolt.
 *
 * Bolt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0xd2;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0x03;
        vAlertPubKey = ParseHex("9541788ca1e268a7474763fa965210b6fa6105a45f52d21056c62fb19a2de991aa15aa1d1c516f34d2a0016f51a87959c89f51a148db30c839f71bc525dde8c480");

        nDefaultPort = 11990;
        nRPCPort = 11991;

        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 700800; // 2 years

        // Genesis block
        const char* pszTimestamp = "January 24, 2017: A new cryptocurrency was released in cryptomarket";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 16 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0124cedf6ebadd4596964d890f677f8d2e74fdcc313c6416434384a66d6d8758d1c92de272dc6713e4a81d98841dfdfdc95e204ba915447d2fe9313435c78af3e8") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1513776186;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 4727186;

        hashGenesisBlock = genesis.GetHash();
	
        assert(hashGenesisBlock == uint256("000001850318cbda4fbf1f2cdb72bf3458740f2ec77271391e4aed04e23a0255"));
        assert(genesis.hashMerkleRoot == uint256("3094fb6d1615873184a995ff0563b3fbdc334ea650b14e87c2f717a1da121633"));

        vSeeds.push_back(CDNSSeedData("Mainnet", "104.131.51.223"));
        vSeeds.push_back(CDNSSeedData("Secondnet", "104.131.5.203"));        

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,26);                     // BOLT addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,4);                    // BOLT script addresses start with '7'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 28 + 128);               // BOLT private keys start with '7' or 'X'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x02)(0xFE)(0x52)(0xF8).convert_to_container<std::vector<unsigned char> >(); // BOLT BIP32 pubkeys start with 'drkv'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x02)(0xFE)(0x52)(0xCC).convert_to_container<std::vector<unsigned char> >(); // BOLT BIP32 prvkeys start with 'drkp'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000005).convert_to_container<std::vector<unsigned char> >();             // BOLT BIP44 coin type is '5'
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,55);                    // BOLT private address start with 'P'

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
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0x02;
		
        vAlertPubKey = ParseHex("8895090a194381599d0f53f89ec60b9ec77f0e7b61978ef445142c8a4f1e154ca3441a5e46e12910540352edbd8af43fc1ee1da9a935c1c252fe7426c323d3d32");
		
        nDefaultPort = 21990;
        nRPCPort = 21991;

        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1513776186;
        genesis.nNonce   = 4727186;

        hashGenesisBlock = genesis.GetHash();
        
        assert(hashGenesisBlock == uint256("000001850318cbda4fbf1f2cdb72bf3458740f2ec77271391e4aed04e23a0255"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 80);                    // Testnet bolt addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 44);                    // Testnet bolt script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 88 + 128);               // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >(); // Testnet bolt BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >(); // Testnet bolt BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001).convert_to_container<std::vector<unsigned char> >();             // Testnet bolt BIP44 coin type is '5' (All coin's testnet default)
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,117);                    // BOLT private address start with 'p'
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
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x56;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1513776186;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 767305;
        nDefaultPort = 18445;
        strDataDir = "regtest";

        hashGenesisBlock = genesis.GetHash();
        // assert(hashGenesisBlock == uint256("0x000008ca1832a4baf228eb1553c03d3a2c8e02399550dd6ea8d65cec3ef23d2e"));

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
