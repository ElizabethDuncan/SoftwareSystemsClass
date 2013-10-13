/* Homework09 for Software Systems

Based originally on Allen Downey's code
Edited by Allie Duncan

*/

#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_PAGE_FRAMES 35
#define PAGE_SIZE 1024
#define PHYSICAL_MEMORY_SIZE (NUMBER_OF_PAGE_FRAMES * PAGE_SIZE)
#define OFFSET_MASK 0x03ff

unsigned int page_table[NUMBER_OF_PAGE_FRAMES];
char *physical_memory = NULL;


/* fetch_va: fetches a value from physical memory 
   by looking up the page fram in the page table.
 */
char fetch_va(char *va)
{
  /* Move page to the right by 10 to select the 6 first bits that define the page */
  unsigned long page = address >> 10;
  /* Look up the page in the page table */
  unsigned long pagelookup = page_table[page];
  /* Move the pagelookup 10 to the left to make room 
     for 10 more bits (for a 16 bit address) 
  */
  pagelookup = pagelookup << 10;
  /* Clear those 10 new bits using given code */
  unsigned long offset = pagelookup & OFFSET_MASK;
  /* Save to physical address */
  unsigned long pa = offset | pagelookup;
  /* Given */
  int value = physical_memory[pa];
  return value;
}

void populate_page_table()
{
  int i;
  for (i=0; i<NUMBER_OF_PAGE_FRAMES; i++) {
    page_table[i] = i;
  }
}

void print_page_table()
{
  int i;
  for (i=0; i<NUMBER_OF_PAGE_FRAMES; i++) {
    printf("%d\t%d\n", i, page_table[i]);
  }
}

int main()
{
  physical_memory = (char *) malloc(sizeof(char) * PHYSICAL_MEMORY_SIZE);

  populate_page_table();
  // print_page_table();

  char *va = (char *) 0x0fff;
  char value = fetch_va(va);

  printf("value %d\n", value);

  return 0;
}



