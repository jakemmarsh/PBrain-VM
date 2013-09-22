PBrain-VM
=========

Virtual machine implementation written in C for the imaginary Assembly-like language "PBrain".


PBrain
-------

"PBrain" is a simplified, imaginary version of Assembly language. It has a total of *thirty-two* opcode instructions. They are all in the format `XX YY ZZ`, where `XX` is the opcode, `YY` is a first parameter, and `ZZ` is a second parameter.


API Functions
---------------------
This virtual machine implementation provides an API for all thirty-two of the opcodes, as well as storing data and saving to memory.

- **char * get_named_param(int start_position):**

	> When given a full 6-character long instruction, it is sometimes necessary to extract a named identifier, such as a pointer or register.
	> This function can be used to obtain the name of the pointer or register as a string, providing only the `start_position` of the paremeter name in the current instruction.

- **int get_int_param(int start_position, int length):**

	> Similar to `get_named_param`, this function is used to extract necessary data from instructions. When a value (integer) is given directly in an instruction,
	> it must be used in the form of an int. This function returns an int, providing the `start_position` of the value in the current instruction, as well as the `length` of the value (in characters).

- **void read_to_memory(int program_line, char input_line[7], int i):**
	
	> Each time a new line of source code is interpreted by the virtual machine, it must be read into memory.

- **void load_pointer_immediate(char* pointer, int value):**
	
	> Corresponding to the instruction `00 Pn XX`, used to load the specified value into the pointer given.

- **void add_pointer_immediate(char pointer[2], int value):**
	
	> Corresponding to the instruction `01 Pn XX`, used to add the specified value to the pointer given.

- **void subtract_pointer_immediate(char pointer[2], int value):**
	
	> Corresponding to the instruction `02 Pn XX`, used to subtract the specified value from the pointer given.

- **void load_acc_immediate(int value):**

	> Corresponding to the instruction '03 XX XX', used to load the specified value into the accumulator.

- **void load_acc_register(char pointer[2]):**

	> Corresponding to the instruction '04 Pn --', used to load the data in memory referenced by the given pointer into the accumulator.

- **void load_acc_direct(int location):**

	> Corresponding to the instruction '05 XX --', used to load the data in memory at the given location into the accumulator.