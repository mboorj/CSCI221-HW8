#include "bitio.hh"

// Construct with an input stream
BitInput::BitInput(std::istream& is){ // borrowing structure from Tour of C++
  bits_vector_t bits_;
  for (int i; is>>bits_;){
    bits_.push_back(input_bit(i)) // or if i is bool, push_back(i)
  }
}

// Read a single bit (or trailing zero)
// Allowed to crash or throw an exception if called past end-of-file.
bool BitInput::input_bit(){
  if (this.eof()){
    std::cerr << "Past end of file." << '\n';
  }
  if (this == 0){
    return false;
  } else if (this == 1){
    return true;
  }
}

// Construct with an input stream
BitOutput::BitOutput(std::ostream& os){ // why ostream? if building from input wouldn't we want istream?

}

// Output a single bit (buffered)
void BitOutput::output_bit(bool bit){
  if (bit){
    std::cout << '1'; // should it be os_ << instead?
  } else {
    std::cout << '0';
  }
}
