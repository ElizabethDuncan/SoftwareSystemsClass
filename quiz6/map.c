#include <stdlib.h> 

//define Node
typedef struct node {
    Hashable *key;
    Value *value;
    struct node *next;
} Node;

typedef struct {
    void *key;
    int (*hash) (void *);
    int (*equal) (void *, void *);
} Hashable;

typedef struct {
    enum Type {INT, STRING} type;
    union {
	int i;
	char *s;
    };
} Value;

//beginning of code
typedef struct map {
	int n;
	Node **lists;
} Map;
	
Map *make_map(int n){
	int i;
	Map map;
	map.n = n;
	map.lists = (Node **)malloc(sizeof(Node *)*n);
	for(i=0; i<n;i++){
		map.lists[i] = NULL;
	}
	return &map;
}

void map_add(Map *map, Hashable *key, Value *value){
	int hashval = has_hashable(key);
	Node *list = map->lists[hashval];
	prepend(key, value, list);
}

Node *prepend(Hashable *key, Value *value, Node *next){
	Node *node = (Node *)malloc(sizeof(Node));
	node.key = key;
	node.value = value;
	node.next = next;
	return node;
}