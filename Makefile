chesshack:
	mkdir bin
	cc main.c moves.c -o ./bin/chesshack 

clean:
	rm chesshack
