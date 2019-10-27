#include "processor.h"

const int VERSION = '1.0';

int operative[MEM_KB << 10];

int main(const int args, const char *argv[]){
	
	const char *file_name = nullptr;

	if(args > 1){
		file_name = argv[1];
	}
	else{
		file_name = default_binary_file_name;
	}
	
	//file_name = "assembled.mubeg";

	if(file_name == nullptr){
		fprintf(stderr, "Неверный вызов\nИспользуйсте: %s [имя файла для исполнения]\n", argv[0]);
		return 0;
	}

	FILE * file = fopen(file_name, "rb");
	if(file == nullptr){
		fprintf(stderr, "No_rights opening for read %s" PRINT_LOCATION "\n", file_name, __LOCATION__);
		return 0;
	}

	int size = get_file_length(file);

	Elem_t *commands = (Elem_t *) calloc(sizeof(char), size);
	int num = fread(commands, sizeof(Elem_t), size/sizeof(Elem_t), file);
	if(num != size/sizeof(Elem_t)){

		fprintf(stderr, "fread %s problem " PRINT_LOCATION "\n", file_name, __LOCATION__ );
		return 0;	
	}
	
	if(!check_compatibility(commands)){
		fprintf(stderr, "File %s imcompatible" PRINT_LOCATION "\n", file_name, __LOCATION__);
		return 0;
	}

	Processor_t proc1 = {};
	processor_init(&proc1);

	int answer = run(commands, proc1);
	switch(answer){
		case 0:
			break;
		case UNRESOLVED_COMMAND:
			fprintf(stderr, "Command unresolved" PRINT_LOCATION "\n", __LOCATION__);
			break;
		default:
			fprintf(stderr, "Run answer unexpeted: %d\n", answer);
			break;	
	}

	processor_deinit(&proc1);
	free(commands);
	return 0;
}

bool check_compatibility(Elem_t * commands){

	return commands[0] == 'GBUM' && commands[1] == VERSION;
}

int run(Elem_t * commands, Processor_t processor){

	unsigned long long int pc = START_BIAS;

	while(true){

		#define DEF_FUNC(name, num, len, code, param_code) \
			else if(commands[pc] == num){\
				fflush(stdout);\
				code;\
				pc++;\
			}
				//printf("command[%4d]: %s\n", pc, #name);\
		
		BEGIN
		#include "commands.h"
		else{
			stack_dump(&processor.stack, __LOCATION__, false);
			fprintf(stderr, "Command %d unresolved" PRINT_LOCATION "\n", commands[pc], __LOCATION__);
			return UNRESOLVED_COMMAND;
		}
		//stack_dump(&processor.stack, __LOCATION__, false);
		#undef DEF_FUNC
	}

	return 0;
}

bool processor_init(Processor_t * proc){

	assert(proc != nullptr);

	return STACK_INIT(&proc->stack);
}

bool processor_deinit(Processor_t * proc){

	assert(proc != nullptr);

	return stack_deinit(&proc->stack);
}
