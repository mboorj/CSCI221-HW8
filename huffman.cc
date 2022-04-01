#include "huffman.hh"

Huffman::Huffman(){
  table_t freq_table_;
  for (char i = 0; i <= ALPHABET_SIZE-1; i++){
    freq_table_.insert(0); // index == key (129-> EOF), value == frequency
  }
  freq_table_.insert(1); // EOF
}

void Huffman::update_freq(char index){
  freq_table_[index] += 1;
}

Huffman::bits_t Huffman::encode(int symbol){
  auto dir_bits = huff_tree_->path_to(symbol);
  bits_t bool_bits;
  for (i: dir_bits){
    if (i == HTree::Direction(0)){
      bool_bits.push_back(false);
    } else {
      bool_bits.push_back(true);
    }
  }
  update_freq(symbol);
  create_huff();
  return bool_bits;
}

int Huffman::decode(bool bit){
  if (bit) {
    auto poss = huff_tree_->get_child(Direction(1)); // go right if true
  } else {
    auto poss = huff_tree_->get_child(Direction(0)); // go left if false
  }
  if (poss->get_value() > 0) { // reached an actual symbol
    return poss->get_value();
  } else {
    huff_tree_ = poss; // throw away the part of tree we won't use, bookmark poss for next check
    return poss->get_value(); // will be -1
  }
}

void Huffman::create_huff(){
  auto temp_forest = std::make_shared<HForest>(); // put 1 tree per character into a forest
  for (int i: freq_table_){
    temp_forest.add_tree(std::make_shared<HTree>(i, freq_table_[i]))
  }

  while (temp_forest.size() > 1){ // until everything is in one tree...
    auto tree1 = temp_forest->pop_tree(); // remove and save lowest, second lowest
    auto tree2 = temp_forest->pop_tree();
    auto new_tree = std::make_shared<HTree>(-1, tree1->get_value()+tree2->get_value(), tree1, tree2); // merge as L,R in tree
    temp_forest->add_tree(new_tree); // put new tree into forest, forest.size() -= 1
  }
  huff_tree_ = temp_forest->pop_tree(); // get tree out of the forest, that's your huffman tree
}
