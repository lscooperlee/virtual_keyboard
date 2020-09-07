CROSS=

CC=$(CROSS)gcc
CPP=$(CROSS)g++

MKDIR       := mkdir -p
RM          := rm -f
DIRNAME     := dirname


APP=virtual_keyboard

LDFLAGS = 
CFLAGS = -Wall -I. -DDEBUG -g -O2

OUTDIR=./.out
BINDIR=$(OUTDIR)/bin

PATHDIR=$(shell find -type d) 

SRCS= $(foreach dir,$(PATHDIR),$(wildcard $(dir)/*.cpp)) 
PATHOBJS=$(subst ./,,$(SRCS:.cpp=.o))
OBJS=$(patsubst %,$(OUTDIR)/%,$(PATHOBJS))

$(APP):$(OBJS)
	@$(MKDIR) $(BINDIR)
	@$(CPP) $(OBJS) -o $(BINDIR)/$@ $(LDFLAGS) 

$(OBJS):$(OUTDIR)/%.o:%.cpp
	@$(MKDIR) `$(DIRNAME) $@`
	@echo COMPILING $(notdir $@)
	@$(CPP) $(CFLAGS) -c -o $@ $<

format:
	clang-format -style=LLVM -i src/*

clean:
	$(RM) -rf $(OUTDIR)
