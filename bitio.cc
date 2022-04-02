#include "bitio.hh"

// Construct with an input stream
BitInput::BitInput(std::istream& is){ // borrowing structure from Tour of C++
  bits_vector_t bits_;
  for (int i; is>>bits_;){
    bits_.push_back(input_bit(i))
  }
}

// Read a single bit (or trailing zero)
// Allowed to crash or throw an exception if called past end-of-file.
bool BitInput::input_bit(){
  if (this.eof()){
    std::cerr << "Past end of file." << '\n';
    return; // something???
  }
  if (this == 0){
    return false;
  } else if (this == 1){
    return true;
  }
}

// Construct with an output stream
BitOutput::BitOutput(std::ostream& os){
  std::ostream& os_ = os;
}

// Output a single bit (buffered)
void BitOutput::output_bit(bool bit){
  if (bit){
    os_ << 1; // should it be os_ << instead?
  } else {
    os_ << 0;
  }
  if (bit) {
    poss_out_.push_back(1);
  } else {
    poss_out_.push_back(0);
  }
  if (poss_out_.size() == 8){
    uint_8t num = vec8_to_bin(poss_out_);
    poss_out_.erase(poss_out_.begin(),poss_out_.begin()+7);
    os_ << num;
  }
  //if vector of things is smaller than 8, just append
  //if vector of things has size 8, turn it into an int, output, empty the vector
}

uint_8t vec8_to_bin(std::vector v){
  uint_8t i = 128*v[0]+64*v[1]+32*v[2]+16*v[3]+8*v[4]+4*v[5]+2*v[6]+v[7];
  return i;
}

BitOutput::~BitOutput(){

}