#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

# include "manager.h"
# include "rbtree.h"

typedef struct thread_object {
	rbtree *t;
	manager *m;
} thread_object_t;

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

void *search_thread(void *search_arg)
{
  thread_object_t *search_obj;
	uint16_t index;
  action_t action;
  node_t *node;

  search_obj = (thread_object_t *) search_arg;

  cout << "SEARCH" << endl;

  //wait until all threads are initialized
  while(!search_obj->m->start_work);

  while((index = get_index(search_obj->m, false)) < search_obj->m->search_actions_length -1){
    action = search_obj->m->search_actions[index];
    if(action.type == act_search){
      node = search_tree(search_obj->t, action.value);
    }
  }
  if(node != NULL){
    cout << node->key << endl;
  }
  return 0;
}

void *mod_thread(void *mod_arg)
{
  thread_object_t *mod_obj;
	uint16_t index;
  action_t action;

  mod_obj = (thread_object_t *) mod_arg;

  cout << "MOD" << endl;

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
  thread_object_t *thread_object;

  thread_object = new thread_object_t;

  thread_object->m = m;
  thread_object->t = t;

  for(i=0; i<m->mod_actions_length; i++){
    pthread_create(&thread_id, NULL, search_thread, thread_object);
  }
  for(i=0; i<m->search_actions_length; i++){
    pthread_create(&thread_id, NULL, search_thread, thread_object);
  }
  m->start_work = true;
	pthread_join(thread_id, NULL);

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
