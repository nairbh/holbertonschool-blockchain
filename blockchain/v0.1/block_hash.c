#include "blockchain.h"


/**
 * block_hash - computes the hash of a Block
 * @block: pointer to the Block to be hashed
 * @hash_buf: The resulting hash must be stored
 * Return: pointer to hash_buf on success, otherwise NULL
 */
uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t length = (sizeof(block->info) + block->data.len);
	uint8_t *temp_buf = NULL;

	if (length > SHA256_DIGEST_LENGTH)
	{
		temp_buf = (uint8_t *)malloc(length);
		if (temp_buf == NULL)
			return (NULL);

		memcpy(temp_buf, (uint8_t *)&block->info, sizeof(block->info));
		memcpy(temp_buf + sizeof(block->info), block->data.buffer,
				block->data.len);
		sha256((int8_t const *)temp_buf, length, hash_buf);
	}
	else
	{
		memcpy(hash_buf, (uint8_t *)&block->info, sizeof(block->info));
		memcpy(hash_buf + sizeof(block->info), block->data.buffer,
				block->data.len);
		sha256((int8_t const *)block, length, hash_buf);
	}

	return (hash_buf);
}
