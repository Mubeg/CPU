#define BEGIN if(false){return true;}
#define END

#include "ionegin"
#include "stack.h"
#include "enum.h"


const char default_binary_file_name[] = "assembled.mubeg";
const int ASSEMBLE_ROUNDS = 2;
const int UNRESOLVED_COMMAND = 2;


bool check_compatibility(Elem_t * commands);


int disasm(Elem_t * commands, int size);
