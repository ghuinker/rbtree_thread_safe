#include <pthread.h>

# include "manager.h"
# include "rbtree.h"


int g = 0;

// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    static int s = 0;

    ++s; ++g;

    printf("New Thread");
    return 0;
}


void execute_work(manager *m, rbtree *t){
	int i;
	pthread_t tid;

	for (i = 0; i < 3; i++)
		pthread_create(&tid, NULL, myThreadFun, NULL);

	pthread_join(tid, NULL);

}

void init_manager(manager *m, rbtree *t, instruction *i){
	m->actions_length = i->actions_length;
	m->actions = &i->actions;

}
