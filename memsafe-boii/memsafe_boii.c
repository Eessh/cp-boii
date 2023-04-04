#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memsafe_boii.h"

/**
 * This is the allocation record, which will be stored
 * in a linked list of allocation records.
 */
typedef struct memsafe__boii__allocation
{
  void* mem_address;
  size_t mem_size;
  char* func_call_file;
  size_t func_call_line;
  char* func_name;

  struct memsafe__boii__allocation* next;
} memsafe__boii__allocation;

/**
 * This is the linked list for the allocation records.
 */
typedef struct memsafe__boii__allocation_list
{
  memsafe__boii__allocation* head;
  memsafe__boii__allocation* tail;
} memsafe__boii__allocation_list;

/**
 * Creates/allocates memory for a new allocation record.
 *
 * Returns `NULL` if unable to create record.
 */
static memsafe__boii__allocation*
memsafe__boii__allocation_new(void* mem_address,
                              size_t mem_size,
                              const char* func_call_file,
                              size_t func_call_line,
                              const char* func_name);

/**
 * Frees/deallocates memory for the allocation record.
 */
static void memsafe__boii__allocation_free(memsafe__boii__allocation* record);

/**
 * Creates/allocates memory for a new allocation record list.
 *
 * Returns `NULL` if unable to create new allocation record list.
 */
static memsafe__boii__allocation_list* memsafe__boii__allocation_list_new();

/**
 * Adds the new allocation record to the record list.
 */
static void
memsafe__boii__allocation_list_add_record(memsafe__boii__allocation_list* list,
                                          memsafe__boii__allocation* record);

/**
 * Removes the allocation record for the address pointed by the entity.
 */
static void memsafe__boii__allocation_list_remove_record(
  memsafe__boii__allocation_list* list, void* entity);

/**
 * Frees/deallocates memory for allocation record list.
 */
static void
memsafe__boii__allocation_list_free(memsafe__boii__allocation_list* list);

/**
 * Actual variable which holds the records.
 */
static memsafe__boii__allocation_list memory_allocations_record_list =
  (memsafe__boii__allocation_list){.head = NULL, .tail = NULL};

static memsafe__boii__allocation*
memsafe__boii__allocation_new(void* mem_address,
                              size_t mem_size,
                              const char* func_call_file,
                              size_t func_call_line,
                              const char* func_name)
{
  if(!mem_address)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Tyring to allocate new reacord with NULL memory "
           "address!\n");
#endif
    return NULL;
  }

  if(mem_size < 0)
  {
    // some idiot is allocating negative memory
    return NULL;
  }

  memsafe__boii__allocation* record =
    (memsafe__boii__allocation*)calloc(1, sizeof(memsafe__boii__allocation));
  if(!record)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Unable to allocate memory for record!\n");
#endif
    return NULL;
  }

  record->mem_address = mem_address;
  record->mem_size = mem_size;
  record->func_call_file =
    (char*)calloc(strlen(func_call_file) + 1, sizeof(char));
  strcpy(record->func_call_file, func_call_file);
  record->func_call_line = func_call_line;
  record->func_name = (char*)calloc(strlen(func_name) + 1, sizeof(char));
  strcpy(record->func_name, func_name);

  return record;
}

static void memsafe__boii__allocation_free(memsafe__boii__allocation* record)
{
  if(!record)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Trying to free record pointing to NULL!\n");
#endif
    return;
  }

  // freeing function name, filename strings before
  // as these strings are dynamically allocated.
  free(record->func_call_file);
  free(record->func_name);
  free(record);
}

static memsafe__boii__allocation_list* memsafe__boii__allocation_list_new()
{
  memsafe__boii__allocation_list* list =
    (memsafe__boii__allocation_list*)calloc(
      1, sizeof(memsafe__boii__allocation_list));
  if(!list)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Unable to allocate memory for new allocations "
           "record list!\n");
#endif
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;

  return list;
}

static void
memsafe__boii__allocation_list_add_record(memsafe__boii__allocation_list* list,
                                          memsafe__boii__allocation* record)
{
  if(!list)
  {
#ifdef DEBUG
    printf(
      "MemsafeBoii__Log: Trying to add record to a NULL pointing allocations "
      "record list!\n");
#endif
    return;
  }
  if(!record)
  {
#ifdef DEBUG
    printf(
      "MemsafeBoii__Log: Trying to add a NULL pointing record to allocations "
      "record list!\n");
#endif
    return;
  }

  if(list->head == NULL)
  {
    list->head = record;
    list->tail = record;
    return;
  }

  list->tail->next = record;
  list->tail = record;
}

static void memsafe__boii__allocation_list_remove_record(
  memsafe__boii__allocation_list* list, void* entity)
{
  if(list == NULL)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Trying to remove record from a NULL pointing "
           "allocations record "
           "list!\n");
#endif
    return;
  }
  if(entity == NULL)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Trying to remove a record of NULL pointing "
           "entity!\n");
#endif
    return;
  }

  if((*list).head == NULL)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Trying to remove a record of an entity from an "
           "empty allocations "
           "record list!\n");
#endif
    return;
  }

  // finding the entity's allocation record in the list
  memsafe__boii__allocation* entity_record_allocation_node = (*list).head;
  while(entity_record_allocation_node != NULL)
  {
    if(entity_record_allocation_node->mem_address == entity)
    {
      break;
    }
    entity_record_allocation_node = entity_record_allocation_node->next;
  }

  // freeing the entity memory
  free(entity);

  if((*list).head == (*list).tail)
  {
    // only one record in the list
    memsafe__boii__allocation_free((*list).head);
    (*list).head = NULL;
    (*list).tail = NULL;
    return;
  }

  // removing entity's allocation record from list.
  // deleting node in a linked list, using a pointer to the node
  if(entity_record_allocation_node == (*list).tail)
  {
    // we need to traverse the list from head to delete the tail node
    memsafe__boii__allocation* temp = (*list).head;
    while(temp->next != entity_record_allocation_node)
    {
      temp = temp->next;
    }
    temp->next = NULL;
    free(entity_record_allocation_node);
  }
  else
  {
    // we could just copy values of next node into current node
    // then free memory of next node
    memsafe__boii__allocation* next_record =
      entity_record_allocation_node->next;
    entity_record_allocation_node->mem_address = next_record->mem_address;
    entity_record_allocation_node->mem_size = next_record->mem_size;
    entity_record_allocation_node->func_call_line = next_record->func_call_line;
    entity_record_allocation_node->next = next_record->next;

    // we need to free function name, filename strings in entity's record
    // as they are dynamically allocated, if we just replace the pointer with
    // next record's pointer, we would leave the memory un-freed
    free(entity_record_allocation_node->func_name);
    free(entity_record_allocation_node->func_call_file);
    entity_record_allocation_node->func_name = next_record->func_name;
    entity_record_allocation_node->func_call_file = next_record->func_call_file;

    // freeing memory of next record
    free(next_record);
  }
}

static void
memsafe__boii__allocation_list_free(memsafe__boii__allocation_list* list)
{
  if(list == NULL)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Trying to free a NULL pointing record list!\n");
#endif
    return;
  }

  if((*list).head == NULL)
  {
    // no records in the list
    // free(list);
    return;
  }

  if((*list).head == (*list).tail)
  {
    // only one record in the list
    memsafe__boii__allocation_free((*list).head);
    (*list).head = NULL;
    (*list).tail = NULL;
    // free(list);
    return;
  }

  // freeing each record by traversing the list
  memsafe__boii__allocation* current_record = (*list).head->next;
  memsafe__boii__allocation* past_record = (*list).head;
  while(current_record != NULL)
  {
    memsafe__boii__allocation_free(past_record);
    past_record = current_record;
    current_record = current_record->next;
  }
  memsafe__boii__allocation_free(past_record);

  // finally freeing list, after all records are freed
  // No need to free the list, as it is not dynamically allocated
  // it is a static variable defined in memsafe_boii.h
  // free(list);
}

void* memsafe__boii__allocate(size_t mem_size,
                              const char* func_call_file,
                              size_t func_call_line,
                              const char* func_name)
{
  void* mem_ptr = calloc(1, mem_size);
  if(!mem_ptr)
  {
// out of memory
#ifdef DEBUG
    printf("MemsafeBoii__Log: Unable to allocate memory of size: %zu\n",
           mem_size);
#endif
    return NULL;
  }

  if(mem_size < 0)
  {
    // some idiot is allocating negative memory
    return NULL;
  }

#ifdef DEBUG
  printf("MemsafeBoii__Log: Allocation:\n  memory_size: %zu\n  function_name: "
         "%s\n  line_number: "
         "%zu\n  file: %s\n",
         mem_size,
         func_name,
         func_call_line,
         func_call_file);
#endif

  // Record allocation
  memsafe__boii__allocation* record = memsafe__boii__allocation_new(
    mem_ptr, mem_size, func_call_file, func_call_line, func_name);
  if(!record)
  {
    // unable to allocate memory for record.
    free(mem_ptr);
    return NULL;
  }
  memsafe__boii__allocation_list_add_record(&memory_allocations_record_list,
                                            record);

  return mem_ptr;
}

void* memsafe__boii__reallocate(void* entity,
                                size_t new_mem_size,
                                const char* func_call_file,
                                size_t func_call_line,
                                const char* func_name)
{
  if(!entity)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Attempt to reallocate memory for a NULL pointed "
           "memory\n");
#endif
    return NULL;
  }

  if(memory_allocations_record_list.head == NULL)
  {
    // no records
    return NULL;
  }

  if(new_mem_size < 0)
  {
    // some idiot is allocating negative memory
    //
    // Cleanup of the old memory is left
    // to be done by cleanup function
    // as it would be costly to iterate the
    // record list every time some idiot does this
    //
    // Cleanup function iterate record list only once
    return NULL;
  }

  // searching for the allocation record
  memsafe__boii__allocation* record = memory_allocations_record_list.head;
  while(record)
  {
    if(record->mem_address == entity)
    {
      break;
    }
    record = record->next;
  }

  if(!record)
  {
    // allocation record not founc
    return NULL;
  }

  entity = realloc(entity, new_mem_size);
  if(!entity)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Unable to reallocate memory with size: %zu\n",
           new_mem_size);
#endif
    return NULL;
  }

#ifdef DEBUG
  printf(
    "MemsafeBoii__Log: Re-allocation:\n  memory_size: %zu\n  function_name: "
    "%s\n  line_number: "
    "%zu\n  file: %s\n",
    new_mem_size,
    func_name,
    func_call_line,
    func_call_file);
#endif

  // Update allocation record
  record->mem_address = entity;
  record->mem_size = new_mem_size;
  record->func_name =
    (char*)realloc(record->func_name, sizeof(char) * (strlen(func_name) + 1));
  strcpy(record->func_name, func_name);
  record->func_call_line = func_call_line;
  record->func_call_file = (char*)realloc(
    record->func_call_file, sizeof(char) * (strlen(func_call_file) + 1));
  strcpy(record->func_call_file, func_call_file);

  return entity;
}

void memsafe__boii__deallocate(void* entity,
                               const char* func_call_file,
                               size_t func_call_line,
                               const char* func_name)
{
  if(entity == NULL)
  {
#ifdef DEBUG
    printf("MemsafeBoii__Log: Trying to free NULL pointed memory:\n  address: "
           "%p\n "
           "function_name: %s\n line_number: %zu\n  file: %s\n",
           entity,
           func_name,
           func_call_line,
           func_call_file);
#endif
    return;
  }

#ifdef DEBUG
  printf(
    "MemsafeBoii__Log: Deallocation:\n  address: %p\n  function_name: %s\n  "
    "line_number: "
    "%zu\n  file: %s\n",
    entity,
    func_name,
    func_call_line,
    func_call_file);
#endif

  // Remove allocation
  memsafe__boii__allocation_list_remove_record(&memory_allocations_record_list,
                                               entity);
}

void memsafe__boii__clean(const char* func_call_file,
                          size_t func_call_line,
                          const char* func_name)
{
  memsafe__boii__allocation* temp = memory_allocations_record_list.head;
  size_t cleanup_count = 0;
  while(temp != NULL)
  {
    cleanup_count++;
#ifdef DEBUG
    printf(
      "MemsafeBoii__Log: Cleanup (deallocating un-freed memory):\n  address: "
      "%p\n  memory_size: %zu\n  function_name: %s\n  line_number: "
      "%zu\n  file: %s\n",
      temp->mem_address,
      temp->mem_size,
      func_name,
      func_call_line,
      func_call_file);
#endif
    free(temp->mem_address);
    temp->mem_address = NULL;
    temp = temp->next;
  }
  memsafe__boii__allocation_list_free(&memory_allocations_record_list);
  printf("\n * MemsafeBoii * Total cleanups done: %zu\n", cleanup_count);
}
