/* list.c */

#include "list.h"

/**/
/* malloc a new list header and initialize it */

list_t *list_init(
void)
{
list_t *list = malloc(sizeof(list_t));

list->first = 0;
list->current = 0;
list->last = 0;

return list;

}

/* Set current point to first pointer */

void list_reset(
list_t *list)
{
list->current = list->first;
}

/* return 1 if current pointer is pointing at a valid link */
/* return 0 if current pointer is NULL                     */
int list_not_end(
list_t *list)
{
if(list->current == 0)
return 0;

else 
return 1;

}


/* advance current point to next link */

void list_next_link(
list_t *list)
{
assert(list->current != 0);
list->current = list->current->next;
   

}

/* return address of entity pointied to by current link */

void *list_get_entity(
list_t *list)
{

   assert(list->current != 0);
return (list->current->entity);
}


/**/
/* Add an element to the end of a list */

void list_add(
list_t *list,
void   *entity)
{
link_t *link = malloc(sizeof(link_t));

link -> next = 0; 
link -> entity = entity;
if(list -> first == 0){
	list->first = link;
	list->current = link;
	list->last = link;
}
else {
	list->last->next = link;
	list->last = link;
	list->current = link;
}
}

/* free() all entities, links, and the list header */

void list_del(
list_t *list)
{
while(list -> first != 0){
link_t *ptr = list->first;
list->first = list->first->next;
free(ptr);
}


}
