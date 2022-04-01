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


void Huffman::create_huff(){
  auto temp_forest = std::make_shared<HForest>();
  for (int i: freq_table_){
    temp_forest.add_tree(std::make_shared<HTree>(i, freq_table_[i]))
  }

  while (temp_forest.size() > 1){
    auto tree1 = temp_forest.pop_tree();
    auto tree2 = temp_forest.pop_tree();
    auto new_tree = std::make_shared<HTree>(-1, tree1.get_value()+tree2.get_value(), tree1, tree2);
    temp_forest.add_tree(new_tree);
  }
  huff_tree_ = temp_forest.pop_tree(); // janky as heck
}
