// Copyright (c) 2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_WALLET_SPEND_H
#define BITCOIN_WALLET_SPEND_H

#include <wallet/coinselection.h>
#include <wallet/transaction.h>
#include <wallet/wallet.h>

class COutput
{
public:
    const CWalletTx *tx;

    /** Index in tx->vout. */
    int i;

    /**
     * Depth in block chain.
     * If > 0: the tx is on chain and has this many confirmations.
     * If = 0: the tx is waiting confirmation.
     * If < 0: a conflicting tx is on chain and has this many confirmations. */
    int nDepth;

    /** Pre-computed estimated size of this output as a fully-signed input in a transaction. Can be -1 if it could not be calculated */
    int nInputBytes;

    /** Whether we have the private keys to spend this output */
    bool fSpendable;

    /** Whether we know how to spend this output, ignoring the lack of keys */
    bool fSolvable;

    /**
     * Whether this output is considered safe to spend. Unconfirmed transactions
     * from outside keys and unconfirmed replacement transactions are considered
     * unsafe and will not be used to fund new spending transactions.
     */
    bool fSafe;

    /** Whether to use the maximum sized, 72 byte signature when calculating the size of the input spend. This should only be set when watch-only outputs are allowed */
    bool use_max_sig;

    bool fMature;
    bool fNeedHardwareKey = false;

    COutput(const CWalletTx *txIn, int iIn, int nDepthIn, bool fSpendableIn, bool fSolvableIn, bool fSafeIn, bool use_max_sig_in = false, bool fMatureIn=true, bool fNeedHardwareKeyIn=false, bool fGetSpendSize=true)
        : tx(txIn), i(iIn), nDepth(nDepthIn), fSpendable(fSpendableIn), fSolvable(fSolvableIn), fSafe(fSafeIn), use_max_sig(use_max_sig_in), fMature(fMatureIn), fNeedHardwareKey(fNeedHardwareKeyIn)
    {
        // fGetSpendSize, avoid running DummySignInput when staking
        tx = txIn; i = iIn; nDepth = nDepthIn; fSpendable = fSpendableIn; fSolvable = fSolvableIn; fSafe = fSafeIn; nInputBytes = -1;

        // If known and signable by the given wallet, compute nInputBytes
        // Failure will keep this value -1
        if (fGetSpendSize && fSpendable && tx) {
            nInputBytes = tx->GetSpendSize(i);
        }
    }

    std::string ToString() const;

    inline CInputCoin GetInputCoin() const
    {
        return CInputCoin(tx->tx, i, nInputBytes);
    }
};

#endif // BITCOIN_WALLET_SPEND_H
