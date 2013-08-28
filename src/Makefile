include ../Makefile.rules

OBJS= initialisation.o masse.o matrice.o projection.o main.o \
	transfo.o val_propres.o vector.o matrice_op.o quaternion.o \
	matrice_op2.o

all: ${OUT}

${OUT}: ${OBJS}
	${CC} ${OBJS} -o $@ ${LDFLAGS} && mv $@ ..

${OUT}-dbg: ${OBJS}
	${CC} ${OBJS} -o $@ ${LDFLAGS} -L/usr/pkg/lib -lefence && mv $@ ..

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	-rm -f *~ *.o

distclean:
	-rm -f *~ *.o ${OUT}

depends:
	${CC} -M *.c > .depends

include .depends
