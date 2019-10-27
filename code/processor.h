#define BEGIN if(false){return true;}
#define END

#include "ionegin"
#include "stack.h"
#include "enum.h"

const int UNRESOLVED_COMMAND = 2;
const char default_binary_file_name[] = "assembled.mubeg";
const int ASSEMBLE_ROUNDS = 2;

struct Processor_t {

	hash_t hash;

	Stack_t stack;
	
	int registors[REGISTOR_NUM];

};


int sleep_for_while(void){
	for(int _ = 0; _ < 100000000; _++);
	return 0;
}


bool check_compatibility(Elem_t * commands);


int run(Elem_t * commands, Processor_t processor);


bool processor_init(Processor_t * proc);


bool processor_deinit(Processor_t * proc);
