PBrain-VM
=========

Virtual machine implementation written in C for the imaginary instruction set "PBrain".


PBrain
-------

"PBrain" is a simplified, imaginary instruction set. It has a total of *thirty-two* opcode instructions. They are all in the format `XX YY ZZ`, where `XX` is the opcode, `YY` is a first parameter, and `ZZ` is a second parameter.


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

	> Corresponding to the instruction `03 XX XX`, used to load the specified value into the accumulator.

- **void load_acc_register(char pointer[2]):**

	> Corresponding to the instruction `04 Pn --`, used to load the data in memory referenced by the given pointer into the accumulator.

- **void load_acc_direct(int location):**

	> Corresponding to the instruction `05 XX --`, used to load the data in memory at the given location into the accumulator.

- **void store_acc_register(char pointer [2]):**

	> Corresponding to the instruction `06 Pn --`, used to store the data from the accumulator into memory at the location stored by the given pointer.

- **void store_acc_direct(int location):**

	> Corresponding to the instruction `07 XX --`, used to store the data from the accumulator into memory at the location specified.

- **void reg_to_mem_register(char register_name[2], char pointer[2]):**

	> Corresponding to the instruction `08 Rn Pn`, used to store the data from the specified register into memory at the location stored by the given pointer.

- **void reg_to_mem_direct(char register_name[2], int location):**

	> Corresponding to the instruction `09 Rn XX`, used to store the data from the specified register into memory at the location specified.

- **void mem_to_reg_register(char register_name[2], char pointer[2]):**

	> Corresponding to the instruction `10 Rn Pn`, used to load data from memory at the location stored by the given pointer into the specified register.

- **void mem_to_reg_direct(char register_name[2], int location):**

	> Corresponding to the instruction `11 Rn XX`, used to load data from memory at the specified location into the specified register.

- **void add_acc_immediate(int value):**

	> Corresponding to the instruction `12 XX XX`, used to add the given value directly to the accumulator.

- **void subtract_acc_immediate(int value):**

	> Corresponding to the instruction `13 XX XX`, used to subtract the given value directly from the accumulator.

- **void add_register_to_acc(char register_name[2]):**

	> Corresponding to the instruction `14 Rn --`, used to add the contents of the given register to the accumulator.

- **void subtract_register_from_acc(char register_name[2]):**

	> Corresponding to the instruction `15 Rn --`, used to subtract the contents of the given register from the accumulator.

- **void add_acc_register(char pointer[2]):**

	> Corresponding to the instruction `16 Pn --`, used to add the value in memory at the location stored by the pointer to the accumulator.

- **void add_acc_direct(int location):**

	 > Corresponding to the instruction `17 XX --`, used to add the value in memory at the specified location to the accumulator.

- **void subtract_acc_register(char pointer[2]):**

	> Corresponding to the instruction `18 Pn --`, used to subtract the value in memory at the location stored by the pointer from the accumulator.

- **void subtract_acc_direct(int location):**

	> Corresponding to the instruction `19 XX --`, used to subtract the value in memory at the specified location from the accumulator.

- **void compare_equal_register(char pointer[2]):**

	> Corresponding to the instruction `20 Pn --`, used to set `PSW[0]` to 'T' if the accumulator is greater than the value stored in memory at the location stored by the pointer. If not, `PSW[0]` is set to 'F'.

- **void compare_lesser_register(char pointer[2]):**

	> Corresponding to the instruction `21 Pn --`, used to set `PSW[0]` to 'T' if the accumulator is less than the value stored in memory at the location stored by the pointer. If not, `PSW[0]` is set to 'F'.

- **void compare_greater_register(char pointer[2]):**

	> Corresponding to the instruction `22 Pn --`, used to set `PSW[0]` to 'T' if the accumulator is equal to the value stored in memory at the location stored by the pointer. If not, `PSW[0]` is set to 'F'.

- **void compare_greater_immediate(int value):**

	> Corresponding to the instruction `23 XX XX`, used to set `PSW[0]` to 'T' if the accumulator is greater than the given value, or 'F' if the accumulator is less than the given value.

- **void compare_equal_immediate(int value):**

	> Corresponding to the instruction `24 XX XX`, used to set `PSW[0]` to 'T' if the accumulator is equal to the given value, or 'F' if they are not equal.

- **void compare_lesser_immediate(int value):**

	> Corresponding to the instruction `25 XX XX`, used to set `PSW[0]` to 'T' if the accumulator is less than the given value, or 'F' if the accumulator is greater than the given value.

- **void branch_if_true(int new_program_line):**

	> Corresponding to the instruction `26 XX --`, used to change the Program Counter (PC) to the given value if `PSW[0]` is 'T'.

- **void branch_if_false(int new_program_line):**

	> Corresponding to the instruction `27 XX --`, used to change the Program Counter (PC) to the given value if `PSW[0]` is 'F'.

- **unconditional_branch(int new_program_line):**

	> Corresponding to the instruction `28 XX --`, used to change the Program Counter (PC) to the given value regardless of `PSW`.

- **void acc_to_register(char register_name[2]):**

	> Corresponding to the instruction `29 Rn --`, used to store the current value of the accumulator in the given register.

- **void register_to_acc(char register_name[2]):**

	> Corresponding to the instruction `30 Rn --`, used to load the value of the given register into the accumulator.

- **void halt():**

	> Corresponding to the instruction `90 XX XX`, used to stop the program and halt any existing operations.