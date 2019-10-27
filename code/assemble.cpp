#include "assemble.h"

const int VERSION = '1.0';

int main(const int args, const char *argv[]){


	if(args < 2){
		fprintf(stderr, "Неверный вызов\nИспользуйсте: %s -c [выходной файл] [имя файла для компиляции]\n", argv[0]);
		return 0;
	}
	
	const char *file_name   = nullptr;
	const char *output_file = nullptr;

	for(int n_args = 1; n_args < args; n_args++){

		if(argv[n_args][0] == '-'){

			switch(argv[n_args][1]){

				case 'c':
					output_file = argv[n_args + 1];
					n_args++;
					break;
				default:
					break;
			}
		}
		else{
			file_name = argv[n_args];
		}
	}

	//file_name = "test";

	if(file_name == nullptr){
		fprintf(stderr, "Неверный вызов\nИспользуйсте: %s [имя файла для компиляции]\n", argv[0]);
		return 0;
	}

	int buff_size = 0;
	Buff_elem_t *buff = read_file_to_created_buff(file_name, &buff_size);

	int text_size = 0;
	str_ptr text = make_text_must_free(buff, buff_size, &text_size);

	change_ch1_to_ch2_and_count_in_ch_buff(';', '\0', buff, buff_size);

	int answer = output_file == nullptr ? assemble(text, text_size) : assemble(text, text_size, output_file);
	switch(answer){
		case 0:
			break;
		case NO_RIGHTS:
			fprintf(stderr, "No_rights opening for write \n");
			break;
		default:
			fprintf(stderr, "Assemble answer unexpeted: %d\n", answer);
			break;	
	}	

	free(buff);
	free(text);
	return 0;
}

int assemble(const str_ptr text, const size_t text_size, const char o_file[]/* = default_binary_file_name*/){

	assert(text   != nullptr);
	assert(o_file != nullptr);

	FILE * file = fopen(o_file, "wb");
	
	if(file == nullptr){
		return NO_RIGHTS;
	}


	bool has_errors = false;

	label labels[MAX_LABEL_NUM] = {};
	unsigned int label_counter = 0;

	Stack_t stack = {};

	for(int _ = 0; _ < ASSEMBLE_ROUNDS; _++){
		
	stack = {};	
	STACK_INIT(&stack);
		
	stack_push(&stack, TYPE_OF_FILE);
	stack_push(&stack, VERSION);

	unsigned long long int pc = START_BIAS;
	
		for(size_t i = 0; i < text_size; i++){
			
			int pos = 0;
			char buff[MAX_LINE_LEN] = "";

			if(text[i].size < MAX_LINE_LEN){
				sscanf(text[i].str, "%s%n", buff, &pos);
			}

			if(!assemble_one_line(text + i, buff, pos, &stack, &pc, labels, &label_counter)){
				_ == ASSEMBLE_ROUNDS - 1 ? 
				fprintf(stderr, "Compilation error line %d: %s |" PRINT_LOCATION "\n", i + 1, buff, __LOCATION__) : 0;
				has_errors = true;
			}
		}
		_ != ASSEMBLE_ROUNDS - 1 ? stack_deinit(&stack) : 0;
	}

	/*for(int i = 0; i < label_counter; i++){
		printf("Lable [%d]: %s\n", labels[i].num, labels[i].label);
	}*/

	if(!check_labels(labels, label_counter)){
		fprintf(stderr, "We wouldn't recomend running this programm as label check failed\n");	
	}
	if(!has_errors){
		fwrite(stack.data, sizeof(Elem_t), stack.size, file);
		stack_assemble_listing(&stack, o_file, text, text_size);
	}
	else{
		stack_dump(&stack, __LOCATION__, false);
	}

	stack_deinit(&stack);

	return 0;
}

bool assemble_one_line(const str_ptr line, const char * command, int pos, Stack_t * stack,
		       unsigned long long int * pc, label_ptr labels, unsigned int * label_counter){

	assert(line    != nullptr);
	assert(command != nullptr);
	assert(labels  != nullptr);
	assert(label_counter < MAX_LABEL_NUM);

	if(command[0] == '\0'){
		return true;
	}

	#define DEF_FUNC(name, num, len, code, param_code) \
				else if(strcmp(command, #name) == 0){\
					\
					bool correct = true;\
					param_code;\
					if(!correct){\
						return false;\
					}\
				}

	BEGIN 
	#include"commands.h"
	else if(command[pos - 1] == ':'){

		label temp = {};
		temp.num = *pc;
		(strcpy(temp.label, command), temp.label[pos - 1] = '\0');

		int ans = -1;
		if((ans = find_label(labels, &temp)) != -1){
			if(labels[ans].num != -1 && labels[ans].num != temp.num){
				fprintf(stderr, "Label already assigned %s\n", temp.label);
				return false;
			}
		}

		if(ans != -1){
		
			labels[ans] = temp;

		}
		else if(*label_counter == MAX_LABEL_NUM - 1){

			fprintf(stderr, "Label overflow from label: %s\n", temp.label);
			return false;

		}
		else{
			labels[(*label_counter)++] = temp;
		}

	}
	else
		return false;
	END

	#undef DEF_FUNC

	return true;
}


bool check_labels(label_ptr labels, const int label_counter){

	assert(labels != nullptr);
	assert(label_counter < MAX_LABEL_NUM);
	
	bool correct = true;

	for(int i = 0; i < label_counter; i++){
		if(labels[i].num == -1 || strcmp(labels[i].label, "") == 0){
			
			fprintf(stderr, "Label \"%s\" #%d is corrupted\n", labels[i].label, i);
			correct = false;
		}
	}	

	return correct;
}


bool get_arg_dec(const str_ptr line, int *pos, int * arg){

	assert(line != nullptr);
	assert(arg  != nullptr);
	assert(pos  != nullptr);
	assert(*pos > 0);

	int temp_pos = 0;

	if(sscanf(line->str+*pos, "%d%n", arg, &temp_pos) != 1){
		return false;
	}
	*pos += temp_pos;

	//printf("%s\n%d\n%d\n\n",line->str, *arg, *pos);

	return true;	
}

bool get_arg_float(const str_ptr line, int *pos, int * arg){

	assert(line != nullptr);
	assert(arg  != nullptr);
	assert(pos  != nullptr);
	assert(*pos > 0);

	int temp_pos = 0;
	float temp = 0;

	if(sscanf(line->str+*pos, "%f%n", &temp, &temp_pos) != 1){
		return false;
	}
	
	*pos += temp_pos;
	*arg = (int) (temp*1000);

	//printf("%s\n%d\n%d\n\n",line->str, *arg, *pos);

	return true;	
}

int find_label(label_ptr labels, label_ptr label){

	assert(labels != nullptr);
	assert(label  != nullptr);
	
	for(unsigned int i = 0; i < MAX_LABEL_NUM; i++){
		if(strcmp(labels[i].label, label->label) == 0 || labels[i].num == label->num){
			return i;
		}
	}

	return -1;
}

bool get_arg_str(const str_ptr line, int *pos, str_ptr arg){

	assert(line != nullptr);
	assert(arg  != nullptr);
	assert(pos  != nullptr);
	assert(*pos > 0);
	
	int start = 0, temp_pos = 0;

	if(sscanf(line->str + *pos, " %n%*s%n", &start, &temp_pos) != 0){
		return false;
	}
	*pos += temp_pos;
	
	arg->size = temp_pos - start;
	arg->str = line->str + *pos - arg->size;
	arg->str[arg->size] = '\0';

	//printf("%s\n%s\n%d\n%d\n%d\n\n",line->str, arg->str, arg->size, start, *pos);

	return true;
}

void stack_assemble_listing(Stack_t * const stk, const char output_file[], const str_ptr text, size_t text_size){

	if(stk == nullptr) return;

	FILE *listing_file = fopen(LISTING_FILE, "a");
	if(listing_file == nullptr){
		fprintf(stderr, "Not able to open %s in %s line %d in %s\n", LISTING_FILE, __LOCATION__);
	}


	time_t cur_time = -1;
	time(&cur_time);

	fprintf(listing_file, "\nTime and date: %s"
			      "Assemble listing for %s\n\n",
		ctime(&cur_time),
		output_file);
	fflush(listing_file);
	
	if(stk->data != nullptr){
		for(int cur_line = 0, i = START_BIAS, cur_byte = i*sizeof(Elem_t); i < stk->size; cur_line++){
	
			if(cur_line >= text_size){
					break;			
			}
			while(true){
				if(cur_line >= text_size){
					break;			
				}
				int pos = 0;
				sscanf(text[cur_line].str, "%*s%n", &pos);
				
				if(text[cur_line].str[pos - 1] != ':' && !is_spaced(text[cur_line].str)){
					break;
				}
				cur_line++;
			}

			#define DEF_FUNC(name, num, len, code, param_code) \
					else if(stk->data[i] == num){\
						\
						\
						fprintf(listing_file, "[%04X]:", cur_byte);\
						for(int j = 0; j < MAX_COMMAND_LEN*sizeof(Elem_t); j++){\
							unsigned char temp = (j < len*sizeof(Elem_t) ? *(((unsigned char *)(stk->data + i)) + j) : ' ');\
							fprintf(listing_file, j < len*sizeof(Elem_t) ? " %0" MAX_COMMAND_LEN_PRINT "x" :\
									      " %" MAX_COMMAND_LEN_PRINT "c", temp);\
						}\
						\
						fprintf(listing_file, " <-- %s\n", text[cur_line].str);\
						fflush(listing_file);\
						fflush(stdout);\
						i += len;\
						cur_byte+=len*sizeof(Elem_t);\
					}
			if(false) return;
			#include "commands.h"
			#undef DEF_FUNC
			}
	}
	fflush(listing_file);
	
	fclose(listing_file);

}

bool is_spaced(const char str[]){
	
	int i = 0;
	for(char c = str[0]; c != '\0'; c = str[i++]){
		if(!isspace(c)){
			return false;
		}
	}
	return true;
}


