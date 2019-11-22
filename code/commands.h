//This is auto-generted file from commands.h, which is a raw output of g++ preprocessor for command_describe.h//
//
//
//
//
//
//
//
DEF_FUNC(push, 10, 2, {stack_push(&(processor.stack), (commands[++(processor.pc)]));},

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






      if(false){return false;}
//


else if(strcmp("ax", arg_str.str) == 0){ stack_push(stack, CMD_push_oper_reg); (*pc)++;; stack_push(stack, REG_ax); (*pc)++;; }
else if(strcmp("bx", arg_str.str) == 0){ stack_push(stack, CMD_push_oper_reg); (*pc)++;; stack_push(stack, REG_bx); (*pc)++;; }
else if(strcmp("cx", arg_str.str) == 0){ stack_push(stack, CMD_push_oper_reg); (*pc)++;; stack_push(stack, REG_cx); (*pc)++;; }
else if(strcmp("dx", arg_str.str) == 0){ stack_push(stack, CMD_push_oper_reg); (*pc)++;; stack_push(stack, REG_dx); (*pc)++;; }
//
      else{fprintf(stderr, "No such registor %s\n", arg_str.str); return false;}

    }
    else{
     stack_push(stack, CMD_push_oper); (*pc)++;;
     stack_push(stack, arg); (*pc)++;;
    }


   }
   else{






    if(false){return false;}
//


else if(strcmp("ax", arg_str.str) == 0){ stack_push(stack, CMD_push_reg); (*pc)++;; stack_push(stack, REG_ax); (*pc)++;; }
else if(strcmp("bx", arg_str.str) == 0){ stack_push(stack, CMD_push_reg); (*pc)++;; stack_push(stack, REG_bx); (*pc)++;; }
else if(strcmp("cx", arg_str.str) == 0){ stack_push(stack, CMD_push_reg); (*pc)++;; stack_push(stack, REG_cx); (*pc)++;; }
else if(strcmp("dx", arg_str.str) == 0){ stack_push(stack, CMD_push_reg); (*pc)++;; stack_push(stack, REG_dx); (*pc)++;; }
//
    else return false;

   }
  }
 }
 else{
  stack_push(stack, CMD_push); (*pc)++;;
  stack_push(stack, arg); (*pc)++;;
 }

)

DEF_FUNC(push_reg, 11, 2, {stack_push(&(processor.stack), (processor.registors[commands[++(processor.pc)]]));}, correct = false;)


DEF_FUNC(push_oper, 12, 2, {operative[(commands[++(processor.pc)])] = stack_pop(&processor.stack);}, correct = false;)


DEF_FUNC(push_oper_reg, 13, 2, {operative[(processor.registors[commands[++(processor.pc)]])] = stack_pop(&processor.stack);}, correct = false;)


DEF_FUNC(pop, 20, 1, {stack_pop(&processor.stack);},

 str arg_str = {};

  if(get_arg_str(line, &pos, &arg_str)){

  if(arg_str.str[0] == '['){

   int arg = 0;
   int temp_pos = 0;
   arg_str.str++;

   if(!get_arg_dec(&arg_str, &temp_pos, &arg)){

     arg_str.str[strlen(arg_str.str) - 1] == ']' ? arg_str.str[strlen(arg_str.str) - 1] = '\0' : 0;






     if(false){return false;}
//


else if(strcmp("ax", arg_str.str) == 0){ stack_push(stack, CMD_pop_oper_reg); (*pc)++;; stack_push(stack, REG_ax); (*pc)++;; }
else if(strcmp("bx", arg_str.str) == 0){ stack_push(stack, CMD_pop_oper_reg); (*pc)++;; stack_push(stack, REG_bx); (*pc)++;; }
else if(strcmp("cx", arg_str.str) == 0){ stack_push(stack, CMD_pop_oper_reg); (*pc)++;; stack_push(stack, REG_cx); (*pc)++;; }
else if(strcmp("dx", arg_str.str) == 0){ stack_push(stack, CMD_pop_oper_reg); (*pc)++;; stack_push(stack, REG_dx); (*pc)++;; }
//
     else {fprintf(stderr, "No such registor %s\n", arg_str.str); return false;}

   }
   else{
    stack_push(stack, CMD_pop_oper); (*pc)++;;
    stack_push(stack, arg); (*pc)++;;
   }


  }
  else{






   if(false){return false;}
//


else if(strcmp("ax", arg_str.str) == 0){ stack_push(stack, CMD_pop_reg); (*pc)++;; stack_push(stack, REG_ax); (*pc)++;; }
else if(strcmp("bx", arg_str.str) == 0){ stack_push(stack, CMD_pop_reg); (*pc)++;; stack_push(stack, REG_bx); (*pc)++;; }
else if(strcmp("cx", arg_str.str) == 0){ stack_push(stack, CMD_pop_reg); (*pc)++;; stack_push(stack, REG_cx); (*pc)++;; }
else if(strcmp("dx", arg_str.str) == 0){ stack_push(stack, CMD_pop_reg); (*pc)++;; stack_push(stack, REG_dx); (*pc)++;; }
//
   else return false;

  }
 }
 else{
  stack_push(stack, CMD_pop); (*pc)++;;
 }

)

DEF_FUNC(pop_reg, 21, 2, {processor.registors[commands[++(processor.pc)]] = stack_pop(&processor.stack);}, {correct = false;})


DEF_FUNC(pop_oper, 22, 2, {stack_push(&(processor.stack), (operative[(commands[++(processor.pc)])]));}, {correct = false;})


DEF_FUNC(pop_oper_reg, 23, 2, {stack_push(&(processor.stack), (operative[(processor.registors[commands[++(processor.pc)]])]));}, {correct = false;})


DEF_FUNC(add, 30, 1, {stack_push(&(processor.stack), (stack_pop(&processor.stack) + stack_pop(&processor.stack)));}, stack_push(stack, CMD_add); (*pc)++;)


DEF_FUNC(jmp, 40, 2, { (processor.pc) = commands[++(processor.pc)]; (processor.pc) --;}, { str arg = {}; if(!get_arg_str(line, &pos, &arg)){ correct = false; } else{ label label = {}; strcpy(label.label, arg.str); label.num = -1; int pos = find_label(labels, &label); if(pos != -1){ stack_push(stack, CMD_jmp); (*pc)++;; stack_push(stack, labels[pos].num); (*pc)++;; } else if(*label_counter == MAX_LABEL_NUM - 1){ fprintf(stderr, "Label overflow from label: %s\n", label.label); correct = false; } else{ labels[(*label_counter)++] = label; stack_push(stack, CMD_jmp); (*pc)++;; stack_push(stack, -1); (*pc)++;; } }})


DEF_FUNC(out, 50, 1, printf("%" "d", stack_pop(&processor.stack));;, stack_push(stack, CMD_out); (*pc)++;;)


DEF_FUNC(cout, 51, 1, printf("%" "c", stack_pop(&processor.stack));;, stack_push(stack, CMD_cout); (*pc)++;;)


DEF_FUNC(fout, 52, 1, printf("%." ACCURACY_PRINT "f", ((float) stack_pop(&processor.stack)) / ACCURACY);, stack_push(stack, CMD_fout); (*pc)++;;)


DEF_FUNC(end, 0, 1, break;, stack_push(stack, CMD_end); (*pc)++;;)


DEF_FUNC(mul, 60, 1, stack_push(&(processor.stack), (stack_pop(&processor.stack) * stack_pop(&processor.stack)));, stack_push(stack, CMD_mul); (*pc)++;;)


DEF_FUNC(fmul, 61, 1, stack_push(&(processor.stack), ((int) (((float) stack_pop(&processor.stack))/ACCURACY) * (((float) stack_pop(&processor.stack))/ACCURACY) * ACCURACY));, stack_push(stack, CMD_fmul); (*pc)++;;)


DEF_FUNC(ja, 41, 2, if(stack_pop(&processor.stack) > stack_pop(&processor.stack)) {(processor.pc) = commands[++(processor.pc)]; (processor.pc)--;}else{commands[++(processor.pc)];}, { str arg = {}; if(!get_arg_str(line, &pos, &arg)){ correct = false; } else{ label label = {}; strcpy(label.label, arg.str); label.num = -1; int pos = find_label(labels, &label); if(pos != -1){ stack_push(stack, CMD_ja); (*pc)++;; stack_push(stack, labels[pos].num); (*pc)++;; } else if(*label_counter == MAX_LABEL_NUM - 1){ fprintf(stderr, "Label overflow from label: %s\n", label.label); correct = false; } else{ labels[(*label_counter)++] = label; stack_push(stack, CMD_ja); (*pc)++;; stack_push(stack, -1); (*pc)++;; } }})


DEF_FUNC(jae, 42, 2, if(stack_pop(&processor.stack) >= stack_pop(&processor.stack)){(processor.pc) = commands[++(processor.pc)]; (processor.pc)--;}else{commands[++(processor.pc)];}, { str arg = {}; if(!get_arg_str(line, &pos, &arg)){ correct = false; } else{ label label = {}; strcpy(label.label, arg.str); label.num = -1; int pos = find_label(labels, &label); if(pos != -1){ stack_push(stack, CMD_jae); (*pc)++;; stack_push(stack, labels[pos].num); (*pc)++;; } else if(*label_counter == MAX_LABEL_NUM - 1){ fprintf(stderr, "Label overflow from label: %s\n", label.label); correct = false; } else{ labels[(*label_counter)++] = label; stack_push(stack, CMD_jae); (*pc)++;; stack_push(stack, -1); (*pc)++;; } }})


DEF_FUNC(jb, 43, 2, if(stack_pop(&processor.stack) < stack_pop(&processor.stack)) {(processor.pc) = commands[++(processor.pc)]; (processor.pc)--;}else{commands[++(processor.pc)];}, { str arg = {}; if(!get_arg_str(line, &pos, &arg)){ correct = false; } else{ label label = {}; strcpy(label.label, arg.str); label.num = -1; int pos = find_label(labels, &label); if(pos != -1){ stack_push(stack, CMD_jb); (*pc)++;; stack_push(stack, labels[pos].num); (*pc)++;; } else if(*label_counter == MAX_LABEL_NUM - 1){ fprintf(stderr, "Label overflow from label: %s\n", label.label); correct = false; } else{ labels[(*label_counter)++] = label; stack_push(stack, CMD_jb); (*pc)++;; stack_push(stack, -1); (*pc)++;; } }})


DEF_FUNC(jbe, 44, 2, if(stack_pop(&processor.stack) <= stack_pop(&processor.stack)){(processor.pc) = commands[++(processor.pc)]; (processor.pc)--;}else{commands[++(processor.pc)];}, { str arg = {}; if(!get_arg_str(line, &pos, &arg)){ correct = false; } else{ label label = {}; strcpy(label.label, arg.str); label.num = -1; int pos = find_label(labels, &label); if(pos != -1){ stack_push(stack, CMD_jbe); (*pc)++;; stack_push(stack, labels[pos].num); (*pc)++;; } else if(*label_counter == MAX_LABEL_NUM - 1){ fprintf(stderr, "Label overflow from label: %s\n", label.label); correct = false; } else{ labels[(*label_counter)++] = label; stack_push(stack, CMD_jbe); (*pc)++;; stack_push(stack, -1); (*pc)++;; } }})


DEF_FUNC(je, 45, 2, if(stack_pop(&processor.stack) == stack_pop(&processor.stack)){(processor.pc) = commands[++(processor.pc)]; (processor.pc)--;}else{commands[++(processor.pc)];}, { str arg = {}; if(!get_arg_str(line, &pos, &arg)){ correct = false; } else{ label label = {}; strcpy(label.label, arg.str); label.num = -1; int pos = find_label(labels, &label); if(pos != -1){ stack_push(stack, CMD_je); (*pc)++;; stack_push(stack, labels[pos].num); (*pc)++;; } else if(*label_counter == MAX_LABEL_NUM - 1){ fprintf(stderr, "Label overflow from label: %s\n", label.label); correct = false; } else{ labels[(*label_counter)++] = label; stack_push(stack, CMD_je); (*pc)++;; stack_push(stack, -1); (*pc)++;; } }})


DEF_FUNC(jne, 46, 2, if(stack_pop(&processor.stack) != stack_pop(&processor.stack)){(processor.pc) = commands[++(processor.pc)]; (processor.pc)--;}else{commands[++(processor.pc)];}, { str arg = {}; if(!get_arg_str(line, &pos, &arg)){ correct = false; } else{ label label = {}; strcpy(label.label, arg.str); label.num = -1; int pos = find_label(labels, &label); if(pos != -1){ stack_push(stack, CMD_jne); (*pc)++;; stack_push(stack, labels[pos].num); (*pc)++;; } else if(*label_counter == MAX_LABEL_NUM - 1){ fprintf(stderr, "Label overflow from label: %s\n", label.label); correct = false; } else{ labels[(*label_counter)++] = label; stack_push(stack, CMD_jne); (*pc)++;; stack_push(stack, -1); (*pc)++;; } }})


DEF_FUNC(call, 70, 2, stack_push(&(processor.stack), ((processor.pc) + 2)); (processor.pc) = commands[++(processor.pc)]; (processor.pc)--;, { str arg = {}; if(!get_arg_str(line, &pos, &arg)){ correct = false; } else{ label label = {}; strcpy(label.label, arg.str); label.num = -1; int pos = find_label(labels, &label); if(pos != -1){ stack_push(stack, CMD_call); (*pc)++;; stack_push(stack, labels[pos].num); (*pc)++;; } else if(*label_counter == MAX_LABEL_NUM - 1){ fprintf(stderr, "Label overflow from label: %s\n", label.label); correct = false; } else{ labels[(*label_counter)++] = label; stack_push(stack, CMD_call); (*pc)++;; stack_push(stack, -1); (*pc)++;; } }})


DEF_FUNC(return, 100, 1, (processor.pc) = stack_pop(&processor.stack); (processor.pc)--;, stack_push(stack, CMD_return); (*pc)++;)


DEF_FUNC(sub, 80, 1, {stack_push(&(processor.stack), (stack_pop(&processor.stack) - stack_pop(&processor.stack)));}, stack_push(stack, CMD_sub); (*pc)++;)


DEF_FUNC(in, 90, 1, {int temp = 0; scanf("%d", &temp); stack_push(&(processor.stack), (temp));}, stack_push(stack, CMD_in); (*pc)++;)


DEF_FUNC(fin, 91, 1, {float temp = 0; scanf("%f", &temp); stack_push(&(processor.stack), ((int) (temp*ACCURACY)));}, stack_push(stack, CMD_fin); (*pc)++;)


DEF_FUNC(div , 110, 1, stack_push(&(processor.stack), ((int) ((float) stack_pop(&processor.stack)) / ((float) stack_pop(&processor.stack))));, stack_push(stack, CMD_div); (*pc)++;;)


DEF_FUNC(fdiv, 111, 1, stack_push(&(processor.stack), ((int) ((((float) stack_pop(&processor.stack))/ACCURACY) / (((float) stack_pop(&processor.stack))/ACCURACY) * ACCURACY)));, stack_push(stack, CMD_fdiv); (*pc)++;;)


DEF_FUNC(sqrt, 120, 1, stack_push(&(processor.stack), ((int) (sqrt( ((float) stack_pop(&processor.stack))/ACCURACY) * ACCURACY)));, stack_push(stack, CMD_sqrt); (*pc)++;;)


DEF_FUNC(draw, 130, 1, for(int _ = 0; _ < TERMINAL_SHIFT; _++){ printf("%" "c", '\n'); };
         for(int _ = 0; _ < video_mem + 1; _++){ if(_ % width != 0){printf("%" "c", operative[(_)]);;}
               else{printf("%" "c", '\n');;} }, stack_push(stack, CMD_draw); (*pc)++;;)

DEF_FUNC(dump, 140, 1, processor_dump(&processor, __LOCATION__, true), stack_push(stack, CMD_dump); (*pc)++;)
