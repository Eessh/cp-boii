#ifndef MEMSAFE__BOII
#define MEMSAFE__BOII

#pragma once

#include <stddef.h>

#define memsafe_boii_api__allocate(mem_size)                                   \
  memsafe__boii__allocate(mem_size, __FILE__, __LINE__, __FUNCTION__)
#define memsafe_boii_api__reallocate(entity, new_mem_size)                     \
  memsafe__boii__reallocate(                                                   \
    entity, new_mem_size, __FILE__, __LINE__, __FUNCTION__)
#define memsafe_boii_api__deallocate(entity)                                   \
  memsafe__boii__deallocate(entity, __FILE__, __LINE__, __FUNCTION__)
#define memsafe_boii_api__clean()                                              \
  memsafe__boii__clean(__FILE__, __LINE__, __FUNCTION__)

/**
 * Allocates memory of given size and
 * logs the function in debug mode (`#define DEBUG`) which called allocate.
 *
 * Returns `NULL` if unable to allocate memory.
 *
 * Stores a record of this allocation, for
 * detecting memory leaks if not deallocated.
 *
 * It is advised to call `memsafe__boii__clean()`
 * at the end of your program, it clears up all
 * of the un-freed memory, preventing memory leaks.
 */
void* memsafe__boii__allocate(size_t mem_size,
                              const char* func_call_file,
                              size_t func_call_line,
                              const char* func_name);

/**
  * Reallocates memory with new size for the given memory pointer.
  *
  * Returns `NULL` if unable to reallocate memory with new size.
  *
  * Updates record for this reallocation.
  */
void* memsafe__boii__reallocate(void* entity,
                                size_t new_mem_size,
                                const char* func_call_file,
                                size_t func_call_line,
                                const char* func_name);

/**
 * Deallocates memory of the given pointer
 * and logs the function in debug mode (`#define DEBUG`) which called allocate.
 *
 * Removes the record for allocation.
 */
void memsafe__boii__deallocate(void* entity,
                               const char* func_call_file,
                               size_t func_call_line,
                               const char* func_name);

/**
 * Cleans up all of the un-freed memory.
 *
 * It is advised to call `memsafe__boii__clean()`
 * at the end of your program, preventing memory leaks.
 */
void memsafe__boii__clean(const char* func_call_file,
                          size_t func_call_line,
                          const char* func_name);

#endif
