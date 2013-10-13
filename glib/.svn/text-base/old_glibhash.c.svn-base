#include <stdio.h>
#include "/usr/local/Cellar/glib/2.34.1/include/glib-2.0/glib.h"

void iterator(gpointer value, gpointer key, gpointer user_data) {
 printf(user_data, value, key);
}

int main(int argc, char** argv) {
	//declare constants
	GIOChannel *channel;
	gchar buf[100];
	gsize bytes_read;
	FILE *fp;
	int space_count = 0;
	int i=0;
	char word[100];
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
	
	int counter;
	
	//open file
	fp = fopen("Easier.txt","r");
	if(!fp){
		g_print("Unable to open the file %s\n",argv[1]);
		return 1;
	}
	
	//create channel
	channel = g_io_channel_unix_new(fileno(fp));
	
	//read in stuff and save words to a hash table
	do{
			g_io_channel_read_chars(channel,buf,1,&bytes_read,NULL);
			if(*buf != ' '){
				word[i] = *buf;
				i++;
			}else{
				word[i] = '\0';
				if(g_hash_table_lookup(hash, word)){
					printf("increment counter!");
					counter = GPOINTER_TO_INT(g_hash_table_lookup(hash, word));
					counter++;
					g_hash_table_remove(hash, word);
					g_hash_table_insert(hash, word, GINT_TO_POINTER(counter));
				}else{
					g_hash_table_insert(hash, word, GINT_TO_POINTER(1));
					printf("create word: %s \n", word);
				}
				space_count++;
				i = 0;
			}
		}
	
	//if everything is read, close the channel	
	while(bytes_read > 0);
		g_io_channel_shutdown(channel,TRUE,NULL);
	
	//Add last word (not covered in do statement)
	word[i-1] = '\0';
	if(g_hash_table_lookup(hash, word)){
		counter = GPOINTER_TO_INT(g_hash_table_lookup(hash, word));
		counter++;
		g_hash_table_remove(hash, word);
		g_hash_table_insert(hash, word, GINT_TO_POINTER(counter));
		printf("increment counter!");
	}else{
		g_hash_table_insert(hash, word, GINT_TO_POINTER(1));
		printf("create word: %s \n", word);
	}

	fclose(fp);
	
	//Print stuff
	//g_print("This: %d \n", GPOINTER_TO_INT(g_hash_table_lookup(hash, "This")));
	 g_hash_table_foreach(hash, (GHFunc)iterator, "%s: %d\n");
	

	g_print("\n");
	g_print("space count: %d \n", space_count);

	 g_hash_table_destroy(hash);
	
	return 0;
}