cc = gcc

OBJDIR = ./obj

src = $(shell ls src/*.c)

obj = Gomoku 

obj : $(src)
	mkdir $(OBJDIR)
	$(cc) -c $(src)
	mv *.o $(OBJDIR)
	$(cc) -o $(obj) $(src)

clean:
	rm $(obj)
	rm -r $(OBJDIR)

