#include "bitio.hh"

// Construct with an input stream
BitInput::BitInput(std::istream& is)
  :is_(is), poss_in_(0), count_(8)
  {} // need to get is from address to actual stream, then we can default copy constructor

// Read a single bit (or trailing zero)
// Allowed to crash or throw an exception if called past end-of-file.
bool BitInput::input_bit(){
  if (is_.eof()){ // if next thing in istream is end
    std::cerr << "Past end of file." << '\n';
    throw ; // does an error
  }

  if (count_ == 8){ // have to do things in a byte (8 bits). if we've made it to 8, we can output a thing
    count_ = 0;
    poss_in_ = is_.get(); // output the 8 bits we've assembled
  }
  auto ret = poss_in_ & 1; // logical and with 1, gives us the last bit
  poss_in_ = poss_in_ >> 1; // shift right 1, gives us a new last bit
  count_++;

  return ret;
}


// Construct with an output stream
BitOutput::BitOutput(std::ostream& os) // start with LEAST SIGNIFICANT
  :os_(os), poss_out_(0), count_(0)
  {}

BitOutput::~BitOutput(){

  //if count isn't finished, output whatever you've got
  if (count_ != 0){
    os_.put(poss_out_);
  }
 }

// Output a single bit (buffered)
void BitOutput::output_bit(bool bit){

  poss_out_ = poss_out_ << 1; // shift one to the left, make room for new bit
  poss_out_ = poss_out_ | bit; // logical or with new bit to add to end


  if (count_ == 7){ // we'll have a full byte of things waiting to go out
    count_ = 0;
    os_.put(poss_out_); // output our byte
    poss_out_ = 0; // empty output for next set of 8 bits
  }
  count_++;
 }
