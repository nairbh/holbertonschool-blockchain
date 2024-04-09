#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

/**
 * blockchain_create - Creates a new Blockchain structure and initializes it
 *
 * Return: Pointer to the created Blockchain structure, or NULL on failure
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain = NULL;
	block_t *genesis = NULL;
	llist_t *chain = NULL;
	char *hash = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97"
		     "\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f"
		     "\x04\x51\x58\x03";

	blockchain = calloc(1, sizeof(blockchain_t));

	if (!blockchain)
		return (NULL);
	chain = llist_create(MT_SUPPORT_TRUE);
	if (!chain)
		return (free(blockchain), NULL);
	blockchain->chain = chain;
	genesis = calloc(1, sizeof(block_t));
	if (!genesis)
		return (free(chain), free(blockchain), NULL);
	genesis->info.index = 0;
	genesis->info.difficulty = 0;
	genesis->info.timestamp = 1537578000;
	genesis->info.nonce = 0;
	memset(genesis->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(genesis->data.buffer, "Holberton School", 16);
	genesis->data.len = 16;
	memcpy(genesis->hash, hash, SHA256_DIGEST_LENGTH);

	if (llist_add_node(chain, genesis, ADD_NODE_FRONT) == -1)
		return (free(genesis), free(chain), free(blockchain), NULL);

	return (blockchain);
}
