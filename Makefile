include Makefile.rules

all:
	cd src && make all

dbg:
	cd src && make ${OUT}-dbg

tst:
	./recalage-dbg tests/first.pgm tests/nuage.txt

check:
	cd tests && ./moulinette.sh

clean:
	cd src && make clean
	rm -f *.o *~

distclean:
	cd src && make distclean
	rm -f *.o *~
dist:
	make distclean
	cd .. && tar -cjf 'moular_t-recalage.tar.bz2' 'moular_t-recalage'

debug:
	cd src && make debug