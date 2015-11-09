CC=gcc
MPICC=mpicc
CFLAGS=-std=c99 -DCLS=`getconf LEVEL1_DCACHE_LINESIZE` -g

mono: mono.c common.c
	$(CC) $(CFLAGS) -o $@ $^
multi: cache_aware.c common.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^
check: cache_aware.c common.c
	$(CC) $(CFLAGS) -o $@ $^ -DCHECK
mpi: dist.c common.c
	$(MPICC) $(CFLAGS) -o $@ $^
ring: ring.c common.c
	$(MPICC) $(CFLAGS) -o $@ $^
all: mono multi check mpi	
run:
	valgrind --tool=cachegrind ./multi
clean:
	rm -f check mono multi cachegrind*
