/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey, edited by Elizabeth Duncan
Homework 19 ------ Homework 19 ------- Homework 19

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// VALUE: represents a value in a key-value pair
typedef struct {
    enum Type {INT, STRING} type;
    union {
	int i;
	char *s;
    };
} Value;


/* Makes a Value object that contains an int. */
Value *make_int_value(int i) 
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = INT;
    value->i = i;
    return value;
}


/* Makes a Value object that contains a string. */
Value *make_string_value(char *s) 
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = STRING;
    value->s = s;
    return value;
}


/* Prints a value object. */
void print_value (Value *value) 
{
    if (value == NULL) {
	printf ("%p", value);
	return;
    }
    switch (value->type) {
    case INT:
	printf ("%d", value->i);
	break;
    case STRING:
	printf ("%s", value->s);
	break;
    }
}

// HASHABLE: Represents a key in a key-value pair.

/* Here's another way to make a polymorphic object.

The key can be any pointer type.  It's stored as a (void *), so
when you extract it, you have to cast it back to whatever it is.

hash is a pointer to a function that knows how to hash the key.
equal is a pointer to a function that knows how to compare keys.

 */

typedef struct {
    void *key;
    int (*hash) (void *);
    int (*equal) (void *, void *);
} Hashable;


/* Makes a Hashable object. */
Hashable *make_hashable(void *key, 
			int (*hash) (void *),
			int (*equal) (void *, void *)
			)
{
    Hashable *hashable = (Hashable *) malloc (sizeof (Hashable));
    hashable->key = key;
    hashable->hash = hash;
    hashable->equal = equal;
    return hashable;
}


/* Prints a Hashable object. */
void print_hashable(Hashable *hashable)
{
	printf ("key %p\n", hashable->key);
    printf ("hash %p\n", hashable->hash);
}


/* Hashes an integer. */
int hash_int(void *p)
{
    return *(int *)p;
}


/* Hashes a string. */
int hash_string(void *p)
{
    char *s = (char *) p;
    int total = 0;
    int i = 0;

    while (s[i] != 0) {
	total += s[i];
	i++;
    }
    return total;
}


/* Hashes any Hashable. */
int hash_hashable(Hashable *hashable)
{
    return hashable->hash (hashable->key);
}


/* Compares integers. Edited by Allison Duncan*/
int equal_int (void *ip, void *jp)
{
    if(ip == jp){
		return 1;
	}else{
		return 0;
	}
}


/* Compares strings. Edited by Allison Duncan*/
int equal_string (void *s1, void *s2)
{
    if(strcmp(s1, s2)){
		return 1;	
	}else{
    return 0;
	}
}


/* Compares Hashables. Edited by Allison Duncan*/
int equal_hashable(Hashable *h1, Hashable *h2)
{
    return h1->equal(h1,h2);
}


/* Makes a Hashable int. 

Allocates space and copies the int.
*/
Hashable *make_hashable_int (int x)
{
    int *p = (int *) malloc (sizeof (int));
    *p = x;
    return make_hashable((void *) p, hash_int, equal_int);
}


/* Makes a Hashable string. 

Stores a reference to the string (not a copy).
*/
Hashable *make_hashable_string (char *s)
{
    return make_hashable((void *) s, hash_string, equal_string);
}



// NODE: a node in a list of key-value pairs

typedef struct node {
    Hashable *key;
    Value *value;
    struct node *next;
} Node;


/* Makes a Node. Edited by Allison Duncan. */
Node *make_node(Hashable *key, Value *value, Node *next)
{
	Node *new_node = (Node *) calloc ( 1, sizeof (Node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = next;
	return new_node;
}


/* Prints a Node. */
void print_node(Node *node)
{
    print_hashable(node->key);
    printf ("value %p\n", node->value);
    printf ("next %p\n", node->next);
}


/* Prints all the Nodes in a list. Edited by Allison Duncan*/
void print_list(Node *node)
{
	//fprintf(stderr, "print_list's node: %p\n", node->next);
	while(node){
    	print_node(node);
		node = node->next;
		//fprintf(stderr, "hi");
	}
}


/* Prepends a new key-value pair onto a list.

This is actually a synonym for make_node.
 */
Node *prepend(Hashable *key, Value *value, Node *next)
{
    return make_node(key, value, next);
}


/* Looks up a key and returns the corresponding value, or NULL. Edited by Allison Duncan */
Value *list_lookup(Node *list, Hashable *key)
{
	Node *i = list;
	Node *next = NULL;
	
	for(; i!= NULL; i=next){
		if(i->key == key){
			return i->value;
		}
		next = i->next;
	}
	return NULL;
}


// MAP: a map in a list of key-value pairs
typedef struct map {
    int n;
    Node **lists;
} Map;


/* Makes a Map with n lists. Edited by Allison Duncan*/
Map *make_map(int n)
{
    Map *new_map = (Map *) calloc (1, sizeof (Map));
	new_map->n = n;
    Node *new_nodes = (Node *) calloc ( n, sizeof (Node));
    new_map->lists = new_nodes; 
    return new_map;
}


/* Prints a Map. */
void print_map(Map *map)
{
    int i;

    for (i=0; i<map->n; i++) {
	if (map->lists[i] != NULL) {
	    printf ("%d\n", i);
		//fprintf(stderr,"about to print_list\n");
	    print_list (map->lists[i]);
		//fprintf(stderr, "finished print_list\n");
	}
    }
}


/* Adds a key-value pair to a map. Edited by Allison Duncan*/
void map_add(Map *map, Hashable *key, Value *value)
{	
	int index = hash_hashable(key) % map->n;
	//Node *last_node = map->lists[index-1];
	//last_node->next = lists[index];
	map->lists[index] = prepend(key, value, map->lists[index]);	
}


/* Looks up a key and returns the corresponding value, or NULL. Edited by Allison Duncan */
Value *map_lookup(Map *map, Hashable *key)
{
    int i;
    for (i=0; i<map->n; i++) {
		if (map->lists[i] != NULL) {
			if(map->lists[i]->key == key){
				return map->lists[i]->value;
			}
		}
    }
	return NULL;
}


/* Prints the results of a test lookup. */
void print_lookup(Value *value)
{
    printf ("Lookup returned ");
    print_value (value);
    printf ("\n");
}


int main ()
{
	//these work fine - functions given by Allen
    Hashable *hashable1 = make_hashable_int (1);
    Hashable *hashable2 = make_hashable_string ("Allen");
    Hashable *hashable3 = make_hashable_int (2);

    // make_int_value also given
    Value *value1 = make_int_value (17);
    Node *node1 = make_node(hashable1, value1, NULL);
	fprintf(stdout, "Print node:\n");
    print_node (node1);

    Value *value2 = make_string_value ("Downey");
    Node *list = prepend(hashable2, value2, node1);
	fprintf(stdout, "Print list:\n");
    print_list (list);

    // run some test lookups
    Value *value = list_lookup (list, hashable1);
	fprintf(stdout, "List lookup:\n");
    print_lookup(value);

	fprintf(stdout, "List lookup:\n");
    value = list_lookup (list, hashable2);
    print_lookup(value);

	fprintf(stdout, "List lookup:\n");
    value = list_lookup (list, hashable3);
    print_lookup(value);

    // make a map
    Map *map = make_map(10);
    map_add(map, hashable1, value1);
    map_add(map, hashable2, value2);

    printf ("Map\n");
    print_map(map);

	fprintf(stderr, "map lookup: \n");
    // run some test lookups
    value = map_lookup(map, hashable1);
    print_lookup(value);

    value = map_lookup(map, hashable2);
    print_lookup(value);

    value = map_lookup(map, hashable3);
    print_lookup(value);

    return 0;
}