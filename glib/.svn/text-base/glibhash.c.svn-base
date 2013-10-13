/* 
   Elizabeth Duncan
   Homework 20
   Software Systems 
   Olin College

*/

#include <stdio.h>
#include "/usr/local/Cellar/glib/2.34.1/include/glib-2.0/glib.h"

void iterator(gpointer value, gpointer key, gpointer user_data) {
 printf(user_data, value, *(gint *)key);
}

/* Increments the frequency associated with key. */
void increment_counter(GHashTable* hash, gchar *word)
{
	gint *counter;
	gint *new_counter;
	
    counter = (gint *) g_hash_table_lookup (hash, word);

    if (counter == NULL) {
		new_counter = g_new (gint, 1);
		*new_counter = 1;
		g_hash_table_insert (hash, word, new_counter);
    } else {
		*counter += 1;
    }
}

int main(int argc, char** argv) {
	//declare constants
	GIOChannel *channel;
	gchar **buf;
	FILE *fp;
	int i=0;
	char word[100];
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
	gchar *lala;

	//open file
	fp = fopen("Easier.txt","r");
	if(!fp){
		g_print("Unable to open the file %s\n",argv[1]);
		return 1;
	}
	
	//create channel
	channel = g_io_channel_unix_new(fileno(fp));
	
	//read in stuff and save words to a hash table
	while (1) {
		lala = fgets (word, sizeof(word), fp);
		if (lala == NULL) {
			break;
		}

		buf = g_strsplit(word, " ", 0);
		for (i=0; buf[i] != NULL; i++) {
	    	increment_counter(hash, buf[i]);
		}
    }
	
	fclose(fp);
	
	//Print stuff
	 g_hash_table_foreach(hash, (GHFunc)iterator, "%s: %d\n");

	 g_hash_table_destroy(hash);
	
	return 0;
}