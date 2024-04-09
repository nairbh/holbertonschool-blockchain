#include "transaction.h"

/**
 * tx_in_sign - signs a transaction input, given the transaction id it is from
 * @in: pointer to the transaction input structure to sign
 * @tx_id: it contains the ID (hash) of the transaction the transaction input
 *         to sign is stored in
 * @sender: it contains the private key of the receiver of the coins
 *          contained in the transaction output reference    d by the
 *          transaction input
 * @all_unspent: the list of all unspent transaction outputs to date
 * Return: a pointer to the resulting signature structure upon success,
 *         or NULL upon failure
 */
sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
		EC_KEY const *sender, llist_t *all_unspent)
{
	uint8_t pub[EC_PUB_LEN];
	ssize_t i;
	unspent_tx_out_t *utxo;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		utxo = llist_get_node_at(all_unspent, i);
		if (!memcmp(in->tx_out_hash, utxo->out.hash, SHA256_DIGEST_LENGTH))
			break;
		utxo = NULL;
	}

	if (!utxo || !ec_to_pub(sender, pub) ||
			memcmp(pub, utxo->out.pub, EC_PUB_LEN))
		return (NULL);
	if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig))
		return (NULL);

	return (&in->sig);
}
