#include <pthread.h>
#include <semaphore.h>

# include "manager.h"
# include "rbtree.h"

uint16_t get_index(manager *m, bool is_mod){
  uint16_t index;

  if(is_mod){
    sem_wait(m->mod_sem);
    index = m->mod_action_index;
    m->mod_action_index++;
    sem_post(m->mod_sem);
  } else {
    sem_wait(m->search_sem);
    index = m->search_action_index;
    m->search_action_index++;
    sem_post(m->search_sem);
  }

  return index;
}

void *search_thread(search_obj_t *search_obj)
{
	uint16_t index;
  action_t action;

  //wait until all threads are initialized
  while(!search_obj->m->start_work);

  while((index = get_index(search_obj->m, false)) < search_obj->m->search_actions_length -1){
    action = search_obj->m->search_actions[index];
    if(action.type == act_search){
      search_tree(search_obj->t, action.value);
    }
  }
  return 0;
}

void *mod_thread(mod_obj_t *mod_obj)
{
	uint16_t index;
  action_t action;

  //wait until all threads are initialized
  while(!mod_obj->m->start_work);

  while((index = get_index(mod_obj->m, true)) < mod_obj->m->mod_actions_length -1){
    action = mod_obj->m->mod_actions[index];
    if(action.type == act_insert){
      insert_key(mod_obj->t, action.value);
    }
    if(action.type == act_delete){
      delete_key(mod_obj->t, action.value);
    }
  }
  return 0;
}


void execute_work(manager *m, rbtree *t){
	int i;
  pthread_t thread_id;

  for(i=0; i<m->mod_actions_length){

  }
  for(i=0; i<m->search_actions_length){
    pthread_create(&tid, NULL, myThreadFun, NULL);
  }

	pthread_join(thread_id, NULL);

}

//Init queues and set thread numbers and meta data
//Also init thread objects
void init_manager(manager *m, rbtree *t, instruction *i){
  // Init semaphores
  sem_init(&mutex, 0, 1);
  //Remember to destoruy

	for(action_t a:i->actions){
    if(a.type == act_search){
      m->search_actions.push_back(a);
      m->search_actions_length++;
    }
    else{
      m->mod_actions.push_back(a);
      m->mod_actions_length++;
    }
  }
}
