#include <stdlib.h>
#include <malloc.h>

#include "label_queue.h"


label_queue_t pc_addr_map;
label_queue_t label_map;

void init_label_queues( )
{
    pc_addr_map.head  = NULL;
    pc_addr_map.end   = NULL;
    pc_addr_map.count = 0;


    label_map.head  = NULL;
    label_map.end   = NULL;
    label_map.count = 0;

}// end of init_label_queues( )


void delete_label_queues( )
{
    Plabel_queue_entry_t entry = pc_addr_map.head;
    while(entry != NULL)
    {
	pc_addr_map.head = entry->next;
	free(entry);

	entry = pc_addr_map.head;
    }// end of while{ }
    pc_addr_map.count = 0;


    entry = label_map.head;
    while(entry != NULL)
    {
	label_map.head = entry->next;
	free(entry);

	entry = label_map.head;
    }// end of while{ }
    label_map.count = 0;

}// end of delete_label_queues( )


void label_queue_add_entry( int       type,
			    uint32_t  content, // stmt's name 
			    int	      stmt_id  // stmt's index in the vector
		  	  )
{
    Plabel_queue_t queue = NULL;

    switch(type)
    {
	case 0:
	{
	    queue = &pc_addr_map;
	    break;
	}
	case 1:
	{
	    queue = &label_map;
	    break;
	}
    }// end of switch{ }


    Plabel_queue_entry_t entry = (Plabel_queue_entry_t)malloc(sizeof(label_queue_entry_t));
    entry->content = content;
    entry->next	   = NULL;
    entry->stmt_id = stmt_id;

    if(queue->head == NULL)
    {
	queue->head = entry;
	queue->end  = entry;
    }
    else
    {
	(queue->end)->next = entry;
	queue->end  	   = entry;
    }// end of if( ) 

    queue->count = queue->count + 1;

}// end of label_queue_add_entry( )



int fetch_stmtid_by_content( int      type,
			     uint32_t content
			   )
{
   Plabel_queue_t queue = NULL;

    switch(type)
    {
	case 0:
	{
	    queue = &pc_addr_map;
	    break;
	}
	case 1:
	{
	    queue = &label_map;
	    break;
	}
    }// end of switch{ }

    Plabel_queue_entry_t entry = queue->head;
    while(entry != NULL)
    {
	if(entry->content == content)
        {
	    return entry->stmt_id;
	}// end of if( )

	entry = entry->next;
    }// end of while{ }
    
    return -1;

}// end of fetch_stmtid_by_content( )

































