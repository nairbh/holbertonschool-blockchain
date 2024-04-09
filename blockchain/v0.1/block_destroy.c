#include "blockchain.h"

/**
 * block_destroy - deletes an existing Block
 * @block: block to delete
 */
void block_destroy(block_t *block)
{
	free(block);
}
