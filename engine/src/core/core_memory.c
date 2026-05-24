////////////////////////////////////////////////////////////////
//~ Sebas: Internal Memory Types

struct memory_stats
{
    U64 total_allocated;
    U64 tagged_allocation[MEMORY_TAG_MAX_TAGS];
};

global struct memory_stats stats = {};

global const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = 
{
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "PLATFORM   ",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      ",
};

////////////////////////////////////////////////////////////////
//~ Sebas: Memory System Functions

void 
initialize_memory()
{
    MemoryZero(&stats, sizeof(stats));
}

void 
shutdown_memory()
{
}

void* 
sallocate(U64 size, MemoryTag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN)
    {
        SWARN("sallocate called using MEMORY_TAG_UNKWNOWN. Re-class this allocation."); 
    }
    
    stats.total_allocated += size;
    stats.tagged_allocation[tag] += size;
    
    void* block  = platform_memory_reserve(size);
    MemoryZero(block, size);
    return block;
}

void  
sfree(void* block, U64 size, MemoryTag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN)
    {
        SWARN("sfree called using MEMORY_TAG_UNKWNOWN. Re-class this allocation."); 
    }
    
    stats.total_allocated -= size;
    stats.tagged_allocation[tag] -= size;
    platform_free(block);
}

//void* 
//szero_memory(void* block, U64 size)
//{
//
//}
//
//void* 
//scopy_memory(void* dst, const void* source, U64 size)
//{
//
//}
//
//void* 
//s_set_memory(void* dst, S32 value, U64 size)
//{
//
//}

char* 
get_memory_usage_str()
{
    char buffer[8000] = "System memory use (tagged):\n";
    U64 offset = strlen(buffer);
    for (U32 tag = 0;
         tag < MEMORY_TAG_MAX_TAGS;
         ++tag)
    {
        char unit[4] = "XiB";
        F32 amount = 1.0f;
        U64 alloc_amount = stats.tagged_allocation[tag];
        if (alloc_amount >= Gigabytes(1))
        {
            unit[0] = 'G';
            amount = alloc_amount / (F32)Gigabytes(1);
        }
        else if (alloc_amount >= Megabytes(1))
        {
            unit[0] = 'M';
            amount = alloc_amount / (F32)Megabytes(1);
        }
        else if (alloc_amount >= Kilobytes(1))
        {
            unit[0] = 'K';
            amount = alloc_amount / (F32)Kilobytes(1);
        }
        else
        {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (F32)alloc_amount;
        }
        
        S32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memory_tag_strings[tag], amount, unit);
        offset += length;
    }
    
    char* out_string = _strdup(buffer);
    return out_string;
}