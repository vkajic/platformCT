#pragma once

#include "crypto/crypto.h"
#include "cryptonote_basic/cryptonote_basic_impl.h"

namespace cryptonote
{
    class CryptoTask {

      private:
        char *decode_hex_to_array(std::string s) {
          char *answer = new char[(s.length() + 1) / 2];
          int len = s.length() / 2;
          for (int i = 0; i < len; i++) {
            std::string byte = s.substr(2*i,2);
            answer[i] = (char)(int)strtoul(byte.c_str(), NULL, 16);
          }
          return answer;
        }

        cryptonote::account_public_address receiver;
        uint64_t amount;

      public:
        CryptoTask() {
          //Mnemonic used to obtain funds:
          //    "does cube aspire peeled wiggle hawk unquoted august opposite lesson framed gauze vastness getting speedy degrees academy jigsaw luxury light kidneys kisses using wobbly opposite"
          std::string const RECEIVER_SPEND_PUBLIC_KEY = "450c916014367c5d5220da983b9a725e51883e37a970d2dbcbceaf2bdfaf690b";
          std::string const RECEIVER_VIEW_PUBLIC_KEY = "7680b90d0b63b97dc81379e6ca78c5e9f0184720528af5658d11a376bf8ac5d9";

          char* spend_public_char = decode_hex_to_array(RECEIVER_SPEND_PUBLIC_KEY.c_str());
          crypto::public_key spend_public_key;
          for(unsigned int i=0; i<32; i++) {
            spend_public_key.data[i] = spend_public_char[i];
          }

          char* view_public_char = decode_hex_to_array(RECEIVER_VIEW_PUBLIC_KEY.c_str());
          crypto::public_key view_public_key;
          for(unsigned int i=0; i<32; i++) {
            view_public_key.data[i] = view_public_char[i];
          }

          //Hardcoded values for tests
          receiver.m_spend_public_key = spend_public_key;
          receiver.m_view_public_key = view_public_key;

          amount = 100;
        }

        bool validate_cryptotask_txs(cryptonote::block &b) {
          return true;
        }

        void cryptotask_txs(cryptonote::block &b, std::vector<cryptonote::account_public_address> &receivers, std::vector<uint64_t> &amounts) {
          receivers.push_back(receiver);
          amounts.push_back(amount);
        }

    };
}