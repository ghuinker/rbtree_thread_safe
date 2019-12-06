#include <pthread.h>

# include "manager.h"
# include "rbtree.h"

typedef struct mod_obj {
	rbtree *t;
	manager *m;
} mod_obj_t;

uint16_t get_index(manager *m, bool is_mod){
  uint16_t index;

  if(is_mod){
    wait_mod_index(m);
    index = mod_obj->m->mod_action_index;
    mod_obj->m->mod_action_index++;
    signal_mod_index(m);
  } else {
    wait_search_index(m);
    index = mod_obj->m->search_action_index;
    mod_obj->m->search_action_index++;
    signal_search_index(m);
  }

  return index;
}

void *mod_thread(mod_obj_t *mod_obj)
{
	uint16_t index;
  action_t action;

  //wait until all threads are initialized
  while(!mod_obj->start_work);

  while((index = get_index(mode_obj->m, true)) < mod_obj->mod_actions_length -1){
    action = mod_obj->mod_actions[index];
    if(action.type == act_insert){
      insert_key(mod_obj->t, action.value);
    }
    if(action.type == act_delete){
      insert_key(mod_obj->t, action.value);
    }
  }
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

}
