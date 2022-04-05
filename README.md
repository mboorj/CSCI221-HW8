# CSCI221-HW8

This project is a collaboration between Elijah Whitlam-Sandler and Mollie Boor. It was constructed using Eitan's versions of HTree and HForest throughout. 

### BitInput
- **constructor:** initalizes data member ```is_``` as a reference to an istream, initalizes an empty byte of possible input, sets a counter variable to 8. The destructor is left as its default.
- **input_bit:** throws an error if the input stream has reached end of file. Otherwise, checks if the counter has reached 8. If that is the case, the function has either just been called for the first time, or finished outputting a full byte of data. Either way, it should grab a new byte of data from the istream and reset the counter to 0. Regardless of how many bits into the current byte the function is, it will increment the counter, then use bitwise operations to return the correct bit.
### BitOutput
- **constructor:** initalizes data member ```os_``` as a reference to an ostream, initalizes an empty byte of possible output, sets a counter variable to 0.
- **destructor:** since a BitOuptut object can go out of scope with bits still left to be output, we can't default the destructor. Instead, the destructor checks how many bits are in the possible output, appends zeros until the possible output reaches a byte, and puts the output into the ostream. Then, the data members of BitOutput can be default destructed safely.
- **output_bit:** uses bitwise operations to append its parameter bit to the current possible output, then incerements the counter variable. If the output buffer has reached a ful byte the count is reset and the buffer is put into the ostream before being emptied.
### Huffman
- **constructor:** initalizes a frequency table as a vector of integers and a pointer to a currently empty Huffman tree. The frequency table uses an entry's index as its character and the value at the entry as the character's frequency. After initalization, the frequency table has zeros added for each alphabet character and a final end-of-file entry added with frequency 1. The destructor is left as its default.
- **encode:** takes an integer input, the ASCII value of a character, and uses HTree's ```path_to``` to find the directions to the correct node in the Huffman tree. Then, it translates the path into a vector of booleans, updates the frequency table, recalculates the tree, and returns the vector of booleans.
- **decode:** takes a single bit of input and checks if the left or right child of the current node contains a symbol. If the function hasn't found a symbol the key of the node will be -1. In that case, it sets the root of the Huffman tree to the child indicated by the input bit and prepares to be called on the next bit. If it has found a symbol, it updates the frequency table and creates a new Huffman tree. Regardless of whether it found a symbol or not, the function will return the key of the current node. 
- **create_huff:** initalizes a temporary forest and adds one tree per frequency table element. Then, it follows the algorithm described in the assignment instructions and class slideshow to create a single tree.
- **update_freq:** adds 1 to the frequency table entry for the given index.
