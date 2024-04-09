#include "transaction.h"

/**
 * tx_out_create - initializes a transaction output struct
 * @amount :the amount of the transaction
 * @pub: the public key of the transaction receiver
 *
 * Return: a pointer to the created transaction output upon success,
 *         or NULL upon failure
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *tx_out = NULL;

	tx_out = malloc(sizeof(tx_out_t));
	if (!tx_out)
		return (NULL);
	tx_out->amount = amount;
	memcpy(tx_out->pub, pub, EC_PUB_LEN);
	if (!sha256((int8_t const *)tx_out, sizeof(uint32_t) + EC_PUB_LEN,
		    tx_out->hash))
		return (free(tx_out), NULL);
	return (tx_out);
}
