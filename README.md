PBrain-VM
=========

Virtual machine implementation written in C for the imaginary Assembly-like language "PBrain".


PBrain
-------

"PBrain" is a simplified, imaginary version of Assembly language. It has a total of *thirty-two* opcode instructions. They are all in the format `XXYYZZ`, where `XX` is the opcode, `YY` is a first parameter, and `ZZ` is a second parameter.


API Opcode Functions
---------------------
This virtual machine implementation provides an API for all thirty-two of the opcodes, as well as storing data and saving to memory.

- **void read_to_memory(char memory[100][6], int program_line, char input_line[7], int i):**
	Each time a new line of source code is interpreted by the virtual machine, it must be read into memory.
