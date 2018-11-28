typedef struct {
    char* key;
    char* value;    
} ht_item;

typedef struct {
    int size;
    int count;
    ht_item** items;
    int base_size;
} ht_hash_table;


static ht_item* ht_new_item(const char* key, const char* value);
ht_hash_table* ht_new();
static void ht_del_item(ht_item* i);
void ht_del_hash_table(ht_hash_table* ht);
static int ht_hash(const char* s, const int a, const int m);
static int ht_get_hash(const char* s,const int n_buckets,const int attempt);
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char * ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);
static ht_hash_table* ht_new_sized(const int base_size);
static void ht_resize(ht_hash_table* ht, const int base_size);
static void ht_resize_up(ht_hash_table* ht);
static void ht_resize_down(ht_hash_table* ht);

  
