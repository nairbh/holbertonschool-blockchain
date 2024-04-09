#include "blockchain.h"

/**
 * block_mine - Mines a Block in order to insert it in the Blockchain
 * @block: pointer to the Block to be mined
 */
void block_mine(block_t *block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	uint64_t nonce;

	nonce = block->info.nonce;

	while (1)
	{
		block->info.nonce = nonce;

		block_hash(block, hash_buf);
		if (hash_matches_difficulty(hash_buf, block->info.difficulty))
		{
			memcpy(block->hash, hash_buf, SHA256_DIGEST_LENGTH);
			return;
		}
		nonce++;
	}
}
