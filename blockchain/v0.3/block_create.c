#include "blockchain.h"

/**
 * block_create - Creates a Block
 * @prev: pointer to the previous Block of the Blockchain.
 * @data: pointer to a memory area to duplicate.
 * @data_len: Stores the number of bytes to duplicate in data.
 *            If data_len is bigger than BLOCKCHAIN_DATA_MAX, then only
 *            BLOCKCHAIN_DATA_MAX bytes must be duplicated.
 *
 * Return: pointer to the allocated Block
 */
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len)
{
	block_t *block;
	uint32_t len;

	if (data_len > BLOCKCHAIN_DATA_MAX)
		len = BLOCKCHAIN_DATA_MAX;
	else
		len = data_len;

	if (!data || !prev)
		return (NULL);
	block = calloc(1, sizeof(block_t));
	if (!block)
		return (NULL);
	(block->info).index = (prev->info).index + 1;
	(block->info).timestamp = time(NULL);
	memcpy(&((block->data).buffer), data, len);
	memcpy(&((block->info).prev_hash), prev->hash, SHA256_DIGEST_LENGTH);
	(block->data).len = len;
	block->transactions = llist_create(MT_SUPPORT_FALSE);
	if (!block->transactions)
		return (free(block), NULL);
	return (block);
}
