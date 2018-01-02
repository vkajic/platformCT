#pragma once

// Contains auxiliary cryptotask functions
namespace cryptotask
{

  // Converts a hex string into a char array
  char *decode_hex_to_array(std::string s) {
    char *answer = new char[(s.length() + 1) / 2];
    int len = s.length() / 2;
    for (int i = 0; i < len; i++) {
      std::string byte = s.substr(2*i,2);
      answer[i] = (char)(int)strtoul(byte.c_str(), NULL, 16);
    }
    return answer;
  }

  // Converts a char array to a public_key
  crypto::public_key char_array_to_pubkey(char *a) {
    crypto::public_key pubkey;
    for(unsigned int i=0; i<32; i++) {
      pubkey.data[i] = a[i];
    }
    return pubkey;
  }

  // Converts a hex string to a public_key
  crypto::public_key decode_hex_to_pubkey(std::string s) {
    char *a = decode_hex_to_array(s);
    return char_array_to_pubkey(a);
  }

}