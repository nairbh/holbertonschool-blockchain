#include "blockchain.h"

/**
 * block_destroy - deletes an existing Block
 * @block: block to delete
 */
void block_destroy(block_t *block)
{

	llist_destroy(block->transactions, 1,
			(node_dtor_t)transaction_destroy);
	free(block);
}
