/* date = May 23rd 2026 7:59 pm */

#ifndef CORE_MEMORY_H
#define CORE_MEMORY_H

typedef enum MemoryTag MemoryTag;
enum MemoryTag
{
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_PLATFORM,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,
    
    
    MEMORY_TAG_MAX_TAGS
};

shared_function void initialize_memory();
shared_function void shutdown_memory();

shared_function void* sallocate(U64 size, MemoryTag tag);
shared_function void  sfree(void* block, U64 size, MemoryTag tag);
shared_function void* szero_memory(void* block, U64 size);
shared_function void* scopy_memory(void* dst, const void* source, U64 size);
shared_function void* s_set_memory(void* dst, S32 value, U64 size);

shared_function char* get_memory_usage_str();

#endif //CORE_MEMORY_H
