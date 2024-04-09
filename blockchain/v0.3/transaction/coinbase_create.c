#include "transaction.h"

/**
 * coinbase_create - Write a function that creates a coinbase transaction
 * @receiver: it contains the public key of the miner, who will receive
 *            the coinbase coins
 * @block_index: the index of the Block the coinbase transaction will belong to
 *
 * Return: a pointer to the created transaction upon success, or NULL
 *         upon failure
 */
transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
	transaction_t *tx = NULL;
	tx_in_t *tx_in;
	tx_out_t *tx_out;
	uint8_t pub[EC_PUB_LEN];

	if (!receiver || !ec_to_pub(receiver, pub))
		return (NULL);
	tx = calloc(1, sizeof(transaction_t));
	if (!tx)
		return (NULL);
	tx->inputs = llist_create(MT_SUPPORT_FALSE);
	tx->outputs = llist_create(MT_SUPPORT_FALSE);
	if (!tx->inputs || !tx->outputs)
		return (NULL);
	tx_in = calloc(1, sizeof(tx_in_t));
	if (!tx_in)
		return (NULL);
	memcpy(tx_in->tx_out_hash, &block_index, 4);

	if (llist_add_node(tx->inputs, tx_in, ADD_NODE_FRONT) == -1)
		return (NULL);

	tx_out = tx_out_create(COINBASE_AMOUNT, pub);
	if (!tx_out)
		return (NULL);

	if (llist_add_node(tx->outputs, tx_out, ADD_NODE_FRONT) == -1)
		return (NULL);

	if (!transaction_hash(tx, tx->id))
		return (NULL);
	return (tx);
}
