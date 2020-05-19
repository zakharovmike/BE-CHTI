# makefile pour MinGW

CCOPT = -Wall -O2
C_SRC = wav_head.c appli.c
CPP_SRC =
EXE = wav2asm.exe

OBJS = $(C_SRC:.c=.o) $(CPP_SRC:.cpp=.o)

# linkage
$(EXE) : $(OBJS)
	g++ -o $(EXE) $(OBJS)

# compilage
.c.o :
	gcc $(CCOPT) -c $<

.cpp.o :
	g++ $(CCOPT) -c $<
# other

clean :
	del *.o; del *.exe

# dependances : 
wav_head.o : wav_head.h
appli.o : wav_head.h
