cc = gcc

src = $(shell ls src/*.c src/*.h)

obj = build/bin/Gomoku

obj : $(src)
	$(cc) -o $(obj) $(src)

clean:
	rm $(obj)
