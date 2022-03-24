#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define MAP_CAP_BITS 5

typedef struct entry {
    char *key;
    int value;
    struct entry *next;
} Entry;

typedef struct {
    Entry *buckets;
    size_t capacity; // 桶子數 (i.e., 表格列數)
    size_t size; // 已插入的條目數 (初始為 0)
} HashMap;

int map_init(HashMap *map, unsigned int cap_bits);
int map_entries(HashMap *map, Entry ***entries);

int entry_cmp(const void *a, const void *b){
    Entry *v1 = *(Entry **)a;
    Entry *v2 = *(Entry **)b;
    int cmp = v2->value - v1->value;
    if (cmp)
        return cmp;
    return strcmp(v1->key, v2->key);
}


size_t my_hash_function(const char *key){
    size_t hval = 5381;
    int c;
    while((c = *key++))
        hval = ((hval << 5u)+c);
    return hval;
}


size_t map_idx(HashMap *map,const char *key){
    return my_hash_function(key) & (map->capacity-1);
}

int map_put(HashMap *map, const char *key ,int value) {
    const size_t index = map_idx(map, key);
    Entry *entry = map->buckets + index;

    if (!entry->key) {
        entry->key = strdup(key);
        entry->value = value;
        entry->next = NULL;
        map->size++;
        return 0;
    }
    while (1) {
 
        if (entry->next) {
            entry = entry->next;
            continue;
        }
 
        /* invariant: entry->next == NULL */
 
        Entry *inserted = malloc(sizeof(Entry));
        entry->next = inserted;
        inserted->key = strdup(key);
        inserted->value = value;
        inserted->next = NULL;
        map->size++;
        break;
    }
    return 0;
}

   

int *map_get(HashMap *map, const char *key){
   const size_t index = map_idx(map,key);
   Entry *bucket = map->buckets + index;

   while(bucket && bucket->key){
        if(strcmp(bucket->key, key)==0)
            return &bucket->value;
        else
            bucket = bucket->next;
   }
   return NULL;
}
//接在桶子後方的鏈結串列之節點 每個條目的 key 整張雜湊表

void map_destroy(HashMap *map){
    Entry *entry = map->buckets;
    const size_t capacity = map->capacity;
    size_t size = map->size;

    for (size_t i = 0;size&&i < capacity;i++){
            Entry *e = entry+i;
        if (e->key == NULL)
            continue;

        free(e->key);
        size--;

        e = e->next;

        while (e){
            Entry *next = e->next;
            free(e->key);
            free(e);
            size--;

            e = next;
        }
    }
    free(entry);
}
int main() {

    HashMap map;
    if (map_init(&map, MAP_CAP_BITS) < 0)
        fprintf(stderr, "map_init error\n");


    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, stdin)) {

        buf[strcspn(buf, "\r\n")] = '\0';
        const _Bool decrease = (*buf == '-');

        char *term;
        int increment; // 增量值

        if (decrease) {
            term = buf + 1;
            increment = -1;
        } else {
            term = buf;
            increment = 1;
        }


        int *value = map_get(&map, term);

        if (value)
            (*value) += increment;
        else if (!decrease)
            map_put(&map, term, 1);
    }


    {
        const size_t size = map.size;
        Entry **entries;
        if (map_entries(&map, &entries) < 0) // 取得所有條目
            fprintf(stderr, "map_entries error\n");

        /* 根據 entry_cmp 排序*/
        qsort(entries, size, sizeof(Entry *), entry_cmp);

        /* 按照排序結果依序輸出*/
        for (size_t i = 0; i < size; i++) {
            Entry *e = entries[i];
            const char *term = e->key;
            const int count = e->value;
            printf("%d %s\n", count, term);
        }

        /* 釋放條目指標空間 */
        free(entries);
    }

    /* =================== TERMINATE ==================== */
    map_destroy(&map);
}

int map_init(HashMap *map, unsigned int cap_bits) {
    const size_t capacity = 1u << cap_bits; // 計算 2 的 cap_bts 次方
    map->buckets = calloc(capacity, sizeof(Entry)); // 分配「全為 0」的空間
    map->capacity = capacity;
    map->size = 0;

    return -(map->buckets == NULL);
}

int map_entries(HashMap *map, Entry ***entries) {
    Entry *table = map->buckets;
    const size_t capacity = map->capacity;
    size_t size = map->size;

    /* 若目前雜湊表無任何元素，則回傳 0 */
    if (!size) {
        *entries = NULL;
        return 0;
    }

    /* 否則，根據目前元素數量分配空間 */
    Entry **ret = malloc(size * sizeof(Entry *));
    if (!ret)
        return -1; // 分配失敗則傳回 -1

    size_t j = 0;
    for (size_t i = 0; size && i < capacity; i++) {
        Entry *e = table + i;
        if (!e->key)
            continue; // 若目前 bucket 為空，則查找下一個 bucket

        while (e) {
            ret[j++] = e; // 添加目前的 entry
            size--;
            e = e->next; // 查找鏈結串列節點之 entry
        }
    }

    *entries = ret;
    return 0;
}
