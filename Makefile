#
#Johnathan Baugh
#jxb141430@utdallas.edu
#CS 3377.501
#

# Set up info for C++ implicit rule
CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -I /scratch/perkins/include
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -l cdk -l curses

# Project name for backup
PROJECTNAME = jxb141430HW6

SRCS = HW6.cc

# We choose the name of the executable to be created
EXEC = myProg

#Extension being used .c, .cc, .cpp

EXT = .cc

#######
OBJS = $(SRCS:$(EXT)=.o)


all: $(EXEC)


clean:
	rm -f $(OBJS) *.d *~ \#* myProg

Makefile: $(SRCS:$(EXT)=.d)



# Pattern for .d files.
%.d:%$(EXT)
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$








#  This is a rule to link the files
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)



# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


# dependency files
-include $(SRCS:$(EXT)=.d)

