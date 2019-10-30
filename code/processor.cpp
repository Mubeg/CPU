#include "processor.h"

const int VERSION = '1.0';

int operative[MEM_KB << 10] = {};
const int video_mem = length * width * pixel_size;

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

	while(true){
		processor_dump(&processor, __LOCATION__, true);

		#define DEF_FUNC(name, num, len, code, param_code) \
			else if(commands[processor.pc] == num){\
				code;\
				(processor.pc)++;\
			}
		
		BEGIN
		#include "commands.h"
		else{
			processor_dump(&processor, __LOCATION__, false);
			fprintf(stderr, "Command %d unresolved" PRINT_LOCATION "\n", commands[processor.pc], __LOCATION__);
			return UNRESOLVED_COMMAND;
		}
		#undef DEF_FUNC
	}
	

	return 0;
}

void processor_dump(Processor_t * proc, const char called_from_file[], int line, const char func[], bool ok){

	FILE *log_file = fopen(LOG_FILE, "a");
	if(log_file == nullptr){
		fprintf(stderr, "Not able to open %s in %s line %d in %s\n", LOG_FILE, __LOCATION__);
		return;
	}
	
	fprintf(log_file, "Dump of processor [%s]\n", !ok ? "ERROR!!!" : "ok");

	for(int i = 0; i < REGISTOR_NUM; i++){

		#define DEF_REG(name, num) \
			else if(num == i)\
				fprintf(log_file, "\tRegistor[%s] = %d\n", #name, proc->registors[num]);

		if(false == true){return;}
		#include"registors.h"
		END
		#undef DEF_REG

	}
	fflush(log_file);
	
	fprintf(log_file, "Operative Memory:\n");
	/*for(int i = 0; i < MEM_KB<<10; i++){	
		fprintf(log_file, "[%04d] ", operative[i]);
	}*/
	fprintf(log_file, "\n");
	fclose(log_file);

	stack_dump(&proc->stack, called_from_file, line, func, ok);
}

bool processor_init(Processor_t * proc){

	assert(proc != nullptr);
	
	proc->pc = START_BIAS;

	return STACK_INIT(&proc->stack);
}

bool processor_deinit(Processor_t * proc){

	assert(proc != nullptr);

	return stack_deinit(&proc->stack);
}
