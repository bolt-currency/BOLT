/*
 * Copyright (c) 2009-2010 Satoshi Nakamoto
 * Copyright (c) 2010-2014 The Bitcoin Developers
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

#ifndef BITCOIN_HASH_H
#define BITCOIN_HASH_H

#include "serialize.h"
#include "uint256.h"
#include "version.h"

#include "algorithm/sph_blake.h"

#include <vector>

#include <openssl/ripemd.h>
#include <openssl/sha.h>

/* ----------- BOLT Hash ------------------------------------------------ */

template<typename T1>
inline uint256 HashBlake(const T1 pbegin, const T1 pend)
{
    sph_blake256_context     ctx_blake;
    static unsigned char pblank[1];
    uint256 hash1;
    sph_blake256_init(&ctx_blake);
    sph_blake256 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake256_close(&ctx_blake, static_cast<void*>(&hash1));
    return hash1;
}


template<typename T1, typename T2>
inline uint256 HashBlake(const T1 p1begin, const T1 p1end,
                    const T2 p2begin, const T2 p2end)
{
    sph_blake256_context     ctx_blake;
    static unsigned char pblank[1];
    uint256 hash1;
    sph_blake256_init(&ctx_blake);
    sph_blake256 (&ctx_blake, (p1begin == p1end ? pblank : static_cast<const void*>(&p1begin[0])), (p1end - p1begin) * sizeof(p1begin[0]));
    sph_blake256 (&ctx_blake, (p2begin == p2end ? pblank : static_cast<const void*>(&p2begin[0])), (p2end - p2begin) * sizeof(p2begin[0]));
    sph_blake256_close(&ctx_blake, static_cast<void*>(&hash1));
    uint256 hash2;
    sph_blake256 (&ctx_blake, (unsigned char*)&hash1, sizeof(hash1));
    sph_blake256_close(&ctx_blake, static_cast<void*>(&hash2));
    return hash2;
}

template<typename T1, typename T2, typename T3>
inline uint256 HashBlake(const T1 p1begin, const T1 p1end,
                    const T2 p2begin, const T2 p2end,
                    const T3 p3begin, const T3 p3end)
{
    sph_blake256_context     ctx_blake;
    static unsigned char pblank[1];
    uint256 hash1;
    sph_blake256_init(&ctx_blake);
    sph_blake256 (&ctx_blake, (p1begin == p1end ? pblank : static_cast<const void*>(&p1begin[0])), (p1end - p1begin) * sizeof(p1begin[0]));
    sph_blake256 (&ctx_blake, (p2begin == p2end ? pblank : static_cast<const void*>(&p2begin[0])), (p2end - p2begin) * sizeof(p2begin[0]));
    sph_blake256 (&ctx_blake, (p3begin == p3end ? pblank : static_cast<const void*>(&p3begin[0])), (p3end - p3begin) * sizeof(p3begin[0]));
    sph_blake256_close(&ctx_blake, static_cast<void*>(&hash1));
    uint256 hash2;
    sph_blake256 (&ctx_blake, (unsigned char*)&hash1, sizeof(hash1));
    sph_blake256_close(&ctx_blake, static_cast<void*>(&hash2));
    return hash2;
}

/* ----------- Bitcoin Hash ------------------------------------------------- */
template<typename T1>
inline uint256 Hash(const T1 pbegin, const T1 pend)
{
    static unsigned char pblank[1];
    uint256 hash1;
    SHA256((pbegin == pend ? pblank : (unsigned char*)&pbegin[0]), (pend - pbegin) * sizeof(pbegin[0]), (unsigned char*)&hash1);
    uint256 hash2;
    SHA256((unsigned char*)&hash1, sizeof(hash1), (unsigned char*)&hash2);
    return hash2;
}

class CHashWriter
{
private:
    sph_blake256_context     ctx_blake;

public:
    int nType;
    int nVersion;

    void Init() {
        //SHA256_Init(&ctx);
        sph_blake256_init(&ctx_blake);
    }

    CHashWriter(int nTypeIn, int nVersionIn) : nType(nTypeIn), nVersion(nVersionIn) {
        Init();
    }

    CHashWriter& write(const char *pch, size_t size) {
        sph_blake256 (&ctx_blake, pch, size);
        return (*this);
    }

    // invalidates the object
    uint256 GetHash() {
        uint256 hash1;
        //SHA256_Final((unsigned char*)&hash1, &ctx);
        sph_blake256_close(&ctx_blake, static_cast<void*>(&hash1));
        uint256 hash2;
        //SHA256((unsigned char*)&hash1, sizeof(hash1), (unsigned char*)&hash2);
        sph_blake256 (&ctx_blake, (unsigned char*)&hash1, sizeof(hash1));
        sph_blake256_close(&ctx_blake, static_cast<void*>(&hash2));
        return hash2;
    }

    template<typename T>
    CHashWriter& operator<<(const T& obj) {
        // Serialize to this stream
        ::Serialize(*this, obj, nType, nVersion);
        return (*this);
    }
};


template<typename T1, typename T2>
inline uint256 Hash(const T1 p1begin, const T1 p1end,
                    const T2 p2begin, const T2 p2end)
{
    static unsigned char pblank[1];
    uint256 hash1;
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, (p1begin == p1end ? pblank : (unsigned char*)&p1begin[0]), (p1end - p1begin) * sizeof(p1begin[0]));
    SHA256_Update(&ctx, (p2begin == p2end ? pblank : (unsigned char*)&p2begin[0]), (p2end - p2begin) * sizeof(p2begin[0]));
    SHA256_Final((unsigned char*)&hash1, &ctx);
    uint256 hash2;
    SHA256((unsigned char*)&hash1, sizeof(hash1), (unsigned char*)&hash2);
    return hash2;
}

template<typename T1, typename T2, typename T3>
inline uint256 Hash(const T1 p1begin, const T1 p1end,
                    const T2 p2begin, const T2 p2end,
                    const T3 p3begin, const T3 p3end)
{
    static unsigned char pblank[1];
    uint256 hash1;
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, (p1begin == p1end ? pblank : (unsigned char*)&p1begin[0]), (p1end - p1begin) * sizeof(p1begin[0]));
    SHA256_Update(&ctx, (p2begin == p2end ? pblank : (unsigned char*)&p2begin[0]), (p2end - p2begin) * sizeof(p2begin[0]));
    SHA256_Update(&ctx, (p3begin == p3end ? pblank : (unsigned char*)&p3begin[0]), (p3end - p3begin) * sizeof(p3begin[0]));
    SHA256_Final((unsigned char*)&hash1, &ctx);
    uint256 hash2;
    SHA256((unsigned char*)&hash1, sizeof(hash1), (unsigned char*)&hash2);
    return hash2;
}

template<typename T>
uint256 SerializeHash(const T& obj, int nType=SER_GETHASH, int nVersion=PROTOCOL_VERSION)
{
    CHashWriter ss(nType, nVersion);
    ss << obj;
    return ss.GetHash();
}

template<typename T1>
inline uint160 Hash160(const T1 pbegin, const T1 pend)
{
    static unsigned char pblank[1];
    uint256 hash1;

    sph_blake256_context     ctx_blake;
    sph_blake256_init(&ctx_blake);
    sph_blake256 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake256_close(&ctx_blake, static_cast<void*>(&hash1));




    //SHA256((pbegin == pend ? pblank : (unsigned char*)&pbegin[0]), (pend - pbegin) * sizeof(pbegin[0]), (unsigned char*)&hash1);
    uint160 hash2;
    RIPEMD160((unsigned char*)&hash1, sizeof(hash1), (unsigned char*)&hash2);
    return hash2;
}

inline uint160 Hash160(const std::vector<unsigned char>& vch)
{
    return Hash160(vch.begin(), vch.end());
}

unsigned int MurmurHash3(unsigned int nHashSeed, const std::vector<unsigned char>& vDataToHash);


#endif
