#include "disassemble.h"

const int VERSION = '1.0';

int main(const int args, const char *argv[]){

	
	const char *file_name = nullptr;

	if(args < 1){
		file_name = argv[1];
		return 0;
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

	int answer = disasm(commands, num);
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

	free(commands);
	return 0;
}


bool check_compatibility(Elem_t * commands){

	return commands[0] == 'GBUM' && commands[1] == VERSION;
}


int disasm(Elem_t * commands, int size){

	unsigned long long int pc = START_BIAS;

	for(;pc < size;){

		#define DEF_FUNC(name, num, len, code, param_code) \
			else if(commands[pc] == num){\
				printf("%15s ", #name);\
				for(int i = 1; i < len; i++){\
					printf("%d ", commands[pc + i]);\
				}\
				printf("\n");\
				pc += len;\
			}
		
		BEGIN
		#include "commands.h"
		else{
			fprintf(stderr, "Command %d unresolved" PRINT_LOCATION "\n", commands[pc], __LOCATION__);
			return UNRESOLVED_COMMAND;
		}
		#undef DEF_FUNC
	}

	return 0;
}
