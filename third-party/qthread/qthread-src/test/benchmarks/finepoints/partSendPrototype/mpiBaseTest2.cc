#include <qthread/qthread.h>
#include <qthread/barrier.h>
#include <qthread/qloop.h>
#include <mpi.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpiPart.h"

extern int idx;

typedef struct args {
	int rank;
	int numIterations;
	char* sendBuf;
	char* recvBuf;
	int numThreads;
	size_t threadPart;
  int other;
  MPI_Request sendReq;
  MPI_Request recvReq;
} arg_t;

static qt_barrier_t *wait_on_me;
static double start;

static void worker(unsigned long tid, unsigned long, void *arg) {
  arg_t *a = (arg_t*)arg;
  int rc;
  int iteration;
  //int rank = a->rank;
  int numIterations = a->numIterations;
  char* sendBuf = a->sendBuf;
  //char* recvBuf = a->recvBuf;
  //int numThreads = a->numThreads;
  size_t threadPart = a->threadPart;
  MPI_Request sendReq = a->sendReq;
  MPI_Request recvReq = a->recvReq;
  idx = tid;
  for ( iteration = 0; iteration < numIterations; iteration++ ) {
    if (tid == 0) {
      rc = MPI_Start_part(&sendReq);
      assert( rc == MPI_SUCCESS );
    }
    qt_barrier_enter(wait_on_me);

    rc = MPI_Partitioned_Add_to_buffer( &sendReq, sendBuf + (threadPart * tid), threadPart, MPI_CHAR );
    assert( rc  == MPI_SUCCESS );
    qt_barrier_enter(wait_on_me);

    if( tid == 0 ) {
      rc = MPI_Wait_part(&recvReq, MPI_STATUS_IGNORE );
      assert( rc == MPI_SUCCESS );
    }
  }
}

double doTest2( int rank, int numIterations, char* sendBuf, char* recvBuf, int numThreads, size_t threadPart )
{
  arg_t arg;
  int other = (rank + 1) % 2;
  int TAG = 0xdead;
  MPI_Request sendReq,recvReq;
  int rc;

  arg.rank = rank;
  arg.numIterations = numIterations;
  arg.sendBuf = sendBuf;
  arg.recvBuf = recvBuf;
  arg.numThreads = numThreads;
  arg.threadPart = threadPart;
  
  if ( rank == 0 ) {
    rc = MPI_Partitioned_Send_create( sendBuf, threadPart * numThreads, MPI_CHAR, numThreads, other, TAG,
                                      MPI_COMM_WORLD, &sendReq );
    assert( rc == MPI_SUCCESS );

    rc = MPI_Partitioned_Recv_create( recvBuf, threadPart * numThreads, MPI_CHAR, other, TAG,
                                      MPI_COMM_WORLD, &recvReq );
    assert( rc == MPI_SUCCESS );
  } else {
    rc = MPI_Partitioned_Recv_create( recvBuf, threadPart * numThreads, MPI_CHAR, other, TAG,
                                      MPI_COMM_WORLD, &recvReq );
    assert( rc == MPI_SUCCESS );

    rc = MPI_Partitioned_Send_create( sendBuf, threadPart * numThreads, MPI_CHAR, numThreads, other, TAG,
                                      MPI_COMM_WORLD, &sendReq );
    assert( rc == MPI_SUCCESS );
  }
  arg.sendReq = sendReq;
  arg.recvReq = recvReq;

  start = MPI_Wtime();
  qt_loop(0, numThreads, worker, &arg);

  return MPI_Wtime() - start;
}
