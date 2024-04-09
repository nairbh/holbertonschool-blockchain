#include "hblk_crypto.h"

/**
 * ec_create - creates a new EC key pair.
 * Return: a pointer to an EC_KEY structure, or NULL upon failure
 */
EC_KEY *ec_create(void)
{
	EC_KEY *key;

	key = EC_KEY_new_by_curve_name(NID_secp256k1);
	if (!key)
	{
		fprintf(stderr, "Failed to create EC key\n");
		return (NULL);
	}

	if (!EC_KEY_generate_key(key))
	{
		fprintf(stderr, "Failed to generate EC key pair\n");
		EC_KEY_free(key);
		return (NULL);
	}

	return (key);
}
