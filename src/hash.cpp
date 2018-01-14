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
 
#include "hash.h"

inline uint32_t ROTL32 ( uint32_t x, int8_t r )
{
    return (x << r) | (x >> (32 - r));
}

unsigned int MurmurHash3(unsigned int nHashSeed, const std::vector<unsigned char>& vDataToHash)
{
    // The following is MurmurHash3 (x86_32), see http://code.google.com/p/smhasher/source/browse/trunk/MurmurHash3.cpp
    uint32_t h1 = nHashSeed;
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    const int nblocks = vDataToHash.size() / 4;

    //----------
    // body
    const uint32_t * blocks = (const uint32_t *)(&vDataToHash[0] + nblocks*4);

    for(int i = -nblocks; i; i++)
    {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = ROTL32(k1,15);
        k1 *= c2;

        h1 ^= k1;
        h1 = ROTL32(h1,13); 
        h1 = h1*5+0xe6546b64;
    }

    //----------
    // tail
    const uint8_t * tail = (const uint8_t*)(&vDataToHash[0] + nblocks*4);

    uint32_t k1 = 0;

    switch(vDataToHash.size() & 3)
    {
    case 3: k1 ^= tail[2] << 16;
    case 2: k1 ^= tail[1] << 8;
    case 1: k1 ^= tail[0];
            k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
    };

    //----------
    // finalization
    h1 ^= vDataToHash.size();
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    return h1;
}
