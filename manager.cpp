#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
using namespace std;

# include "manager.h"
# include "rbtree.h"

typedef struct thread_object {
	rbtree *t;
	manager *m;
	bool is_mod;
	uint16_t id;
} thread_object_t;

action_t *get_action(manager *m, bool is_mod){
	//Mod Thread Update
	action_t *action;
	if(is_mod) {
		if(!m->mod_actions->empty()) {
			sem_wait(m->mod_sem);
			//Check empty after sempahore is locked
			if(!m->mod_actions->empty()) {
				action = m->mod_actions->front();
				m->mod_actions->pop();
				sem_post(m->mod_sem);
				return action;
			}
			else{
				sem_post(m->mod_sem);
				return NULL;
			}
		}
		//If empty on initial check
		else{
			return NULL;
		}
	}
	//Search Thread Update
	else{
		if(!m->search_actions->empty()) {
			sem_wait(m->search_sem);
			//Check empty after sempahore is locked
			if(!m->search_actions->empty()) {
				action = m->search_actions->front();
				m->search_actions->pop();
				sem_post(m->search_sem);
				return action;
			}
			else{
				sem_post(m->search_sem);
				return NULL;
			}
		}
		//If empty on initial check
		else{
			return NULL;
		}
	}
}


void *thread_function(void *args){
	thread_object_t *thread_obj;
	action_t *action;
	manager *m;
	rbtree *t;

	thread_obj = (thread_object_t *) args;
	m=thread_obj->m;
	t=thread_obj->t;

	while((action = get_action(m, thread_obj->is_mod)) != NULL) {
		if(action->type == act_search) {
			cout << thread_obj->id << "-SEARCH: " << action->value << endl;
			search_tree(t, action->value);
		}

		else if(action->type == act_insert) {
			cout << thread_obj->id << "-INSERT: " << action->value << endl;
			insert_key(t, action->value);
		}

		else if(action->type == act_delete) {
			cout << thread_obj->id << "-DELETE: " << action->value << endl;
			delete_key(t, action->value);
		}
	}
	return 0;
}


void execute_work(manager *m, rbtree *t, instruction *inst){
	uint16_t i, mod_count, search_count;
	pthread_t thread_id[inst->num_mod_threads + inst->num_search_threads];
	thread_object_t *thread_args;

	i = mod_count = search_count = 0;

	while((mod_count + search_count) < (inst->num_mod_threads + inst->num_search_threads)){
		if(mod_count < inst->num_mod_threads){
			thread_args = new thread_object_t{t, m, true, i};
			pthread_create(&thread_id[i++], NULL, thread_function, thread_args);
			mod_count++;
		}
		if(search_count < inst->num_search_threads){
			thread_args = new thread_object_t{t, m, false, i};
			pthread_create(&thread_id[i++], NULL, thread_function, thread_args);
			search_count++;
		}
	}



	m->start_work = true;

	for(i=0; i<(inst->num_mod_threads + inst->num_search_threads); i++) {
		pthread_join(thread_id[i], NULL);
	}

}

//Init queues and set thread numbers and meta data
//Also init thread objects
void init_manager(manager *m, rbtree *t, instruction *i){
	// Init semaphores
	m->mod_sem = new sem_t;
	m->search_sem = new sem_t;
	sem_init(m->mod_sem, 0, 1);
	sem_init(m->search_sem, 0, 1);
	//Remember to destoruy

	/*
	   Left off:
	   Init sempahores in this and rbtree
	   then add mod_objects and search objects to manager
	   then in execute do for each mod_object in whatever
	   then for now print result of everything for testing

	   then add result node and id to object

	 */

	 m->search_actions = new queue<action_t *>;
	 m->mod_actions = new queue<action_t *>;

	for(action_t* a:i->actions) {
		if(a->type == act_search) {
			m->search_actions->push(a);
		}
		else{
			m->mod_actions->push(a);
		}
	}
}
