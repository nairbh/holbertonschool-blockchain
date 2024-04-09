/* Description: Create Block (timestamp set to constant) and hash it */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "blockchain.h"

/**
 * _print_hex_buffer - Prints a buffer in its hexadecimal form
 *
 * @buf: Pointer to the buffer to be printed
 * @len: Number of bytes from @buf to be printed
 */
static void _print_hex_buffer(uint8_t const *buf, size_t len)
{
	size_t i;

	for (i = 0; buf && i < len; i++)
		printf("%02x", buf[i]);

	fflush(NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	blockchain_t *blockchain;
	block_t *block;
	uint8_t hash[SHA256_DIGEST_LENGTH];

	blockchain = blockchain_create();
	block = llist_get_head(blockchain->chain);

	block = block_create(block, (int8_t *)"Holberton", 9);
	block->info.timestamp = 972;
	llist_add_node(blockchain->chain, block, ADD_NODE_REAR);

	block_hash(block, hash);
	printf("Hash: ");
	_print_hex_buffer(hash, SHA256_DIGEST_LENGTH);
	printf("\n");

	blockchain_destroy(blockchain);
	return (EXIT_SUCCESS);
}
