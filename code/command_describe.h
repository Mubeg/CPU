//DEF_FUNC(name, num, len, code, param_code)

#define PUSH(arg) stack_push(&processor.stack, (arg))
#define ARG commands[++pc]
#define REG(num) processor.registors[num]
#define POP stack_pop(&processor.stack)
#define DROP(arg) arg
#define PUT(cmd)  stack_push(stack, cmd); *pc += 1;
#define OPER(arg) operative[(sleep_for_while(), arg)]

#define JMP_do_param(cmd) \
	{\
\
	str arg = {};\
	if(!get_arg_str(line, &pos, &arg)){\
			correct = false;\
	}\
	else{\
		label label = {};\
		strcpy(label.label, arg.str);\
		label.num = -1;\
\
		int pos = find_label(labels, &label);\
\
		if(pos != -1){\
\
			PUT(cmd);\
			PUT(labels[pos].num);\
\
		}\
		else if(*label_counter == MAX_LABEL_NUM - 1){\
\
			fprintf(stderr, "Label overflow from label: %s\n", label.label);\
			correct = false;\
\
		}\
		else{\
			labels[(*label_counter)++] = label;\
			\
			PUT(cmd);\
			PUT(-1);\
		}\
	}\
\
}
 
DEF_FUNC(push, 10, 2, {PUSH(ARG);}, 

	int arg = 0;
	if(!get_arg_dec(line, &pos, &arg)){
		str arg_str = {};
		if(!get_arg_str(line, &pos, &arg_str)){
			correct = false;
		}
		else{

			if(arg_str.str[0] == '['){


				int temp_pos = 0;
				arg_str.str++;

				if(!get_arg_dec(&arg_str, &temp_pos, &arg)){

						arg_str.str[strlen(arg_str.str) - 1] == ']' ? arg_str.str[strlen(arg_str.str) - 1] = '\0' : 0;

						#define DEF_REG(name, num) else if(strcmp(#name, arg_str.str) == 0){\
										PUT(CMD_push_oper_reg);\
										PUT(REG_##name);\
										}

						if(false){return false;}
						#include"registors.h"
						else{fprintf(stderr, "No such registor %s\n", arg_str.str); return false;}
						#undef DEF_REG
				}
				else{	
					PUT(CMD_push_oper);
					PUT(arg);
				}
				

			}
			else{
			
				#define DEF_REG(name, num) else if(strcmp(#name, arg_str.str) == 0){\
								PUT(CMD_push_reg);\
								PUT(REG_##name);\
								}

				if(false){return false;}
				#include"registors.h"
				else return false;
				#undef DEF_REG
			}
		}
	}
	else{
		PUT(CMD_push);
		PUT(arg);
	}

)

DEF_FUNC(push_reg, 11, 2, {PUSH(REG(ARG));}, correct = false;)


DEF_FUNC(push_oper, 12, 2, {OPER(ARG) = POP;}, correct = false;)


DEF_FUNC(push_oper_reg, 13, 2, {OPER(REG(ARG)) = POP;}, correct = false;)


DEF_FUNC(pop, 20, 1, {POP;}, 

	str arg_str = {};
	
 	if(get_arg_str(line, &pos, &arg_str)){
		
		if(arg_str.str[0] == '['){
			
			int arg = 0;
			int temp_pos = 0;
			arg_str.str++;		
	
			if(!get_arg_dec(&arg_str, &temp_pos, &arg)){

					arg_str.str[strlen(arg_str.str) - 1] == ']' ? arg_str.str[strlen(arg_str.str) - 1] = '\0' : 0;

					#define DEF_REG(name, num) else if(strcmp(#name, arg_str.str) == 0){\
									PUT(CMD_pop_oper_reg);\
									PUT(REG_##name);\
									}

					if(false){return false;}
					#include"registors.h"
					else {fprintf(stderr, "No such registor %s\n", arg_str.str); return false;}
					#undef DEF_REG
			}
			else{	
				PUT(CMD_pop_oper);
				PUT(arg);
			}


		}
		else{
		
			#define DEF_REG(name, num) else if(strcmp(#name, arg_str.str) == 0){\
							PUT(CMD_pop_reg);\
							PUT(REG_##name);\
							}

			if(false){return false;}
			#include"registors.h"
			else return false;
			#undef DEF_REG
		}
	}
	else{
		PUT(CMD_pop);	
	}

)

DEF_FUNC(pop_reg, 21, 2, {REG(ARG) = POP;}, {correct = false;})


DEF_FUNC(pop_oper, 22, 2, {PUSH(OPER(ARG));}, {correct = false;})


DEF_FUNC(pop_oper_reg, 23, 2, {PUSH(OPER(REG(ARG)));}, {correct = false;})


DEF_FUNC(add, 30, 1, {PUSH(POP + POP);}, PUT(CMD_add))


DEF_FUNC(jmp, 40, 2, { pc = ARG; pc --;}, JMP_do_param(CMD_jmp))


DEF_FUNC(out, 50, 1, printf("%d", POP);, PUT(CMD_out);)


DEF_FUNC(cout, 51, 1, printf("%c", POP);, PUT(CMD_cout);)


DEF_FUNC(fout, 52, 1, printf("%." ACCURACY_PRINT "f", ((float) POP) / ACCURACY);, PUT(CMD_fout);)


DEF_FUNC(end, 0, 1, break;, PUT(CMD_end);)


DEF_FUNC(mul, 60, 1, PUSH(POP * POP);, PUT(CMD_mul);)


DEF_FUNC(fmul, 61, 1, PUSH((int) (((float) POP)/ACCURACY) * (((float) POP)/ACCURACY) * ACCURACY );, PUT(CMD_fmul);)


DEF_FUNC(ja,  41, 2, if(POP > POP) {pc = ARG; pc--;}else{DROP(ARG);}, JMP_do_param(CMD_ja ))


DEF_FUNC(jae, 42, 2, if(POP >= POP){pc = ARG; pc--;}else{DROP(ARG);}, JMP_do_param(CMD_jae))


DEF_FUNC(jb,  43, 2, if(POP < POP) {pc = ARG; pc--;}else{DROP(ARG);}, JMP_do_param(CMD_jb ))


DEF_FUNC(jbe, 44, 2, if(POP <= POP){pc = ARG; pc--;}else{DROP(ARG);}, JMP_do_param(CMD_jbe))


DEF_FUNC(je,  45, 2, if(POP == POP){pc = ARG; pc--;}else{DROP(ARG);}, JMP_do_param(CMD_je ))


DEF_FUNC(jne, 46, 2, if(POP != POP){pc = ARG; pc--;}else{DROP(ARG);}, JMP_do_param(CMD_jne))


DEF_FUNC(call, 70, 2, PUSH(pc + 2); pc = ARG; pc--;, JMP_do_param(CMD_call))


DEF_FUNC(return, 100, 1, pc = POP; pc--;, PUT(CMD_return))


DEF_FUNC(sub, 80, 1, {PUSH(POP - POP);}, PUT(CMD_sub))


DEF_FUNC(in, 90, 1, {int temp = 0; scanf("%d", &temp); PUSH(temp);}, PUT(CMD_in))


DEF_FUNC(fin, 91, 1, {float temp = 0; scanf("%f", &temp); PUSH((int) (temp*ACCURACY) );}, PUT(CMD_fin))


DEF_FUNC(div , 110, 1, PUSH((int) ((float) POP) / ((float) POP) );, PUT(CMD_div);)


DEF_FUNC(fdiv, 111, 1, PUSH((int) ((((float) POP)/ACCURACY) / (((float) POP)/ACCURACY) * ACCURACY) );, PUT(CMD_fdiv);)


DEF_FUNC(sqrt, 120, 1, PUSH((int) (sqrt( ((float) POP)/ACCURACY) * ACCURACY) );, PUT(CMD_sqrt);)



