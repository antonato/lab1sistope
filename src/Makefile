coordinator_out = sucesion
comparator_process = comparator


coordinator_headers = fileManage.h utility.h memory.h
coordinator_source  = $(coordinator_headers:.h=.c) coordinator.c 
coordinator_objects = $(coordinator_source:.c=.o)

comparator_headers = fileManage.h memory.h
comparator_process_source = $(comparator_headers:.h=.c) comparator.c
comparator_process_objects = $(comparator_process_source:.c=.o)

CC     = gcc
CFLAGS = -Wall

depends = .depends

build : $(coordinator_out) 
build : $(comparator_process)

$(coordinator_out) : $(coordinator_objects)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(comparator_process) : $(comparator_process_objects)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(objects) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends) : $(coordinator_source) $(coordinator_headers)
	@$(CC) -MM $(coordinator_source) > $@


clean :
	$(RM) $(coordinator_out) $(coordinator_objects) $(zipfile) $(depends)
	$(RM) $(comparator_process) $(comparator_process_objects) $(zipfile) $(depends)

.PHONY : build zip clean

sinclude $(depends)
