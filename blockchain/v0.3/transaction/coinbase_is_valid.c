#include "transaction.h"

/**
 * coinbase_is_valid - Write a function that checks whether a coinbase
 *                     transaction is valid
 * @coinbase: pointer to the coinbase transaction to verify
 * @block_index: the index of the Block the coinbase transaction will belong to
 * Return: 1 if the coinbase transaction is valid, and 0 otherwise
 */
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	uint8_t hash[SHA256_DIGEST_LENGTH];
	uint8_t buff[SIG_MAX_LEN] = {0};
	tx_in_t *input = NULL;
	tx_out_t *output = NULL;

	if (!coinbase)
		return (0);
	if (!transaction_hash(coinbase, hash) ||
	    memcmp(hash, coinbase->id, SHA256_DIGEST_LENGTH))
		return (0);
	if (llist_size(coinbase->inputs) != 1)
		return (0);
	if (llist_size(coinbase->outputs) != 1)
		return (0);
	input = llist_get_node_at(coinbase->inputs, 0);
	if (memcmp(input->tx_out_hash,
		   &block_index, sizeof(uint32_t)) ||
	    memcmp(&input->tx_out_hash[sizeof(uint32_t)], buff,
		   SHA256_DIGEST_LENGTH - sizeof(uint32_t)) ||
	    memcmp(input->block_hash, buff, SHA256_DIGEST_LENGTH) ||
	    memcmp(&input->sig, buff, SIG_MAX_LEN) || input->sig.len)
		return (0);
	output = llist_get_node_at(coinbase->outputs, 0);
	if (output->amount != COINBASE_AMOUNT)
		return (0);
	return (1);
}
