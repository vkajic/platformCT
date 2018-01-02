#pragma once

#include "crypto/crypto.h"
#include "cryptonote_basic/cryptonote_basic_impl.h"
#include "cryptotask/cryptotask_utils.h"


/**
  * Implementation steps:
  *   1. Add cryptotask_txs field to the block. Have it include hardcoded receiver and amount
  *      Issues fixed:
  *        - cryptotask_txs were not being copied when copying block or constructing it
  *        - output indexes of received block didn't contain the cryptocontract_txs
  *        - size of output txs now also contains cryptotask_txs, checked failed on process_new_blockchain_entry
  *   2. Produce only cryptotask_txs if there are any txs for a hardcoded contract address
  *   3. Produce the txs to the senders of the hardcoded contract address
  *   4. Add cryptotask_txs validation
  */
namespace cryptotask
{
    class CryptoTask {

      private:
        // Hardcoded receiver of the only cryptotask_tx of every block created
        cryptonote::account_public_address receiver;
        uint64_t amount;

      public:
        //Mock contractor that sets the receiver of every cryptotask_tx created to a hardcoded address
        CryptoTask() {
          //Mnemonic used to obtain funds:
          //    "does cube aspire peeled wiggle hawk unquoted august opposite lesson framed gauze vastness getting speedy degrees academy jigsaw luxury light kidneys kisses using wobbly opposite"
          std::string const RECEIVER_SPEND_PUBLIC_KEY = "450c916014367c5d5220da983b9a725e51883e37a970d2dbcbceaf2bdfaf690b";
          std::string const RECEIVER_VIEW_PUBLIC_KEY = "7680b90d0b63b97dc81379e6ca78c5e9f0184720528af5658d11a376bf8ac5d9";

          //Hardcoded values for tests
          receiver.m_spend_public_key = decode_hex_to_pubkey(RECEIVER_SPEND_PUBLIC_KEY);
          receiver.m_view_public_key = decode_hex_to_pubkey(RECEIVER_VIEW_PUBLIC_KEY);

          amount = 1000 * 1000000000000;
        }

        // Validates the cryptotask_txs field of a block, so that no tx generated was invalid
        // FIXME: Currently always returns true
        bool validate_cryptotask_txs(cryptonote::block &b) {
          return true;
        }

        // Scans the block txs, and returns the receivers (an amounts) of generated money with cryptotask_txs
        // FIXME: Currently returns only one hardcoded receiver and amount
        void cryptotask_txs(cryptonote::block &b, std::vector<cryptonote::account_public_address> &receivers, std::vector<uint64_t> &amounts) {
          receivers.push_back(receiver);
          amounts.push_back(amount);
        }

    };
}
