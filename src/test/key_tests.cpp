// Copyright (c) 2012-2013 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "key.h"

#include "base58.h"
#include "script.h"
#include "uint256.h"
#include "util.h"

#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

using namespace std;

static const string strSecret1     ("7qqrxbWBT6v8LTABNae6j9Je9wGagQy6qjjRU3ApBqUQ78HULDy");
static const string strSecret2     ("7r41KxLVNTZA3bYj5FjiAC58GkTENKM6XV9MAxnzSmywcsswtjv");
static const string strSecret1C    ("XCafWPHo8D7VNrTWnFUkH1erzSXmexncn7cEzLaKGpwvyuTpyo6r");
static const string strSecret2C    ("XDWGSfF2DiCvvTV2hn3WfZsD6Wnn15yhPZDr2yFzYmYL5EC78XhR");
static const CBitcoinAddress addr1 ("Xjn3e3Xy1TXnthGp4iAUh8no3wLPVcxZyk");
static const CBitcoinAddress addr2 ("XcSKA3pffkLSZN5HjKF2bcpq4UXRkqXmi1");
static const CBitcoinAddress addr1C("Xmgi9Tn6PyZKwPHWhGmMwAEam61T4wMDWz");
static const CBitcoinAddress addr2C("Xta1praZQjyELweyMByXyiREw1ZRsjXzVp");


static const string strAddressBad("Xta1praZQjyELweyMByXyiREw1ZRsjXzVP");

