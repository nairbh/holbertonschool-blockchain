#include "hblk_crypto.h"

/**
 * ec_verify - Verifies the signature of a given set of bytes
 *
 * @key: Pointer to the EC_KEY structure containing the public key
 * @msg: Pointer to the message to verify the signature of
 * @msglen: Length of the message
 * @sig: Pointer to the signature to be checked
 *
 * Return: 1 if the signature is valid, 0 otherwise
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t const *sig)
{
	if (key == NULL || msg == NULL || sig == NULL)
		return (0);

	return (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key) == 1);
}
