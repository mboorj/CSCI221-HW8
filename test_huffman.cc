/*
 * test_huffman: test the Huffman class
 */

#include "huffman.hh"
#include <iostream>
#include <cassert>
#include <climits>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Ensure the encoder actually modifies the coding' length as expected
void test_encode()
{
  Huffman huff;

  auto bits = huff.encode('a');
  assert(bits.size() > CHAR_BIT);

  bits = huff.encode('b');
  assert(bits.size() > CHAR_BIT);

  bits = huff.encode('a');
  assert(bits.size() < CHAR_BIT);

  bits = huff.encode('b');
  assert(bits.size() < CHAR_BIT);

  bits = huff.encode('b');
  assert(bits.size() == huff.encode('a').size());

  bits = huff.encode('b');
  bits = huff.encode('b');
  bits = huff.encode('b');
  assert(bits.size() < huff.encode('a').size());
}

//////////////////////////////////////////////////////////////////////////////
// A utility function that takes a collection of bits and a Huffman tree, and
// figures out which symbol these bits encode.
int decode_symbol(Huffman& huff, const Huffman::bits_t& bits)
{
  int symbol = -1;

  for (auto b : bits) {
    symbol = huff.decode(b);
  }
  assert(symbol > 0);
  return symbol;
}

std::string string_encoder(Huffman& huff, std::string& input){
  std::string out_string;
  for (auto character : input){ // if there's still stuff in the istream
      auto v = huff.encode(character); // get and encode the next char
      for (auto bit : v){
        out_string += (bit == true)? '1' : '0';
      }
    }
  return out_string;
}

std::string string_decoder(Huffman& huff, std::string& input){
  std::string out_string;
  for (auto character : input){ // if there's stuff in the file
      auto bit = (character == '1')? true : false;
      auto sym = huff.decode(bit); // input_bit will automatically move to the next bit after grabbing
      if (sym >= 0){ // if we've decoded a symbol, put it in the file
        out_string += sym;
      }
    }
  return out_string;
}

//////////////////////////////////////////////////////////////////////////////
// Ensure decoding returns the same symbol that was encoded, in different
// scenarios.
void test_decode()
{
  Huffman encoder, decoder;
  Huffman string_e, string_d;
  std::string test_string = "this string is meant for testing purposes.";
  std::string test_string_2 = "                                        ";

  auto bits = encoder.encode('a');
  auto new_sym = decode_symbol(decoder,bits);
  assert(new_sym == 'a');
  bits = encoder.encode('a');
  assert(decode_symbol(decoder, bits) == 'a');
  bits = encoder.encode('b');
  assert(decode_symbol(decoder, bits) == 'b');
  bits = encoder.encode('a');
  assert(decode_symbol(decoder, bits) == 'a');
  bits = encoder.encode(' ');
  assert(decode_symbol(decoder, bits) == ' ');
  bits = encoder.encode('\n');
  assert(decode_symbol(decoder, bits) == '\n');
  bits = encoder.encode(Huffman::HEOF);
  assert(decode_symbol(decoder, bits) == Huffman::HEOF);
  std::string encode_string = string_encoder(string_e, test_string);
  std::string decode_string = string_decoder(string_d, encode_string);
  assert(decode_string == test_string);
  encode_string = string_encoder(string_e, test_string_2);
  decode_string = string_decoder(string_d, encode_string);
  assert(decode_string == test_string_2);
}

//////////////////////////////////////////////////////////////////////////////
int main()
{
  test_encode();
  test_decode();
  return 0;
}
