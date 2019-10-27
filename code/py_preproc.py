preproc_file = open('commands.h', 'r')
arr = []
for line in preproc_file:
	if(line[0] == '#'):
		line = '//\n'
	arr.append(line)

preproc_file.close()
preproc_file = open("commands.h", 'w')
preproc_file.write("//This is auto-generted file from commands.h, which is a raw output of g++ preprocessor for command_describe.h")
for x in arr:
	preproc_file.write(x)
