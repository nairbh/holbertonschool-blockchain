/* Description: Print extracted public key */

#include <stdlib.h>
#include <stdio.h>

#include "hblk_crypto.h"

#define PUB "043e0da16c605c46846316fbe9dc465ab966e641aa4b3285e539e7ec87e114ce9ca914b0d77a5abe5a88d7eb757c9b61b2c8006885a23993bcf0a87b5d8b371472"

/* _ec_from_hex.c */
EC_KEY *_ec_from_hex(char const *hex);

/**
 * _print_hex_buffer - Prints a buffer in its hexadecimal form
 *
 * @buf: Pointer to the buffer to be printed
 * @len: Number of bytes from @buf to be printed
 */
static void _print_hex_buffer(unsigned char const *buf, unsigned int len)
{
	unsigned int i;

	for (i = 0; buf && i < len; i++)
		printf("%02x", buf[i]);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	EC_KEY *key;
	uint8_t pub[EC_PUB_LEN];
	uint8_t *test_ptr;

	/* Prerequisites */
	key = _ec_from_hex(PUB); /* Here, @key doesn't contain a private key */
	if (!key)
	{
		printf("_ec_from_hex() failed\n");
		return (EXIT_FAILURE);
	}
	if (!EC_KEY_check_key(key))
	{
		printf("Key verification failed\n");
		return (EXIT_FAILURE);
	}
	if (EC_GROUP_get_curve_name(EC_KEY_get0_group(key)) != NID_secp256k1)
	{
		printf("The curve used is not secp256k1\n");
		return (EXIT_FAILURE);
	}

	/* Test `ec_to_pub()` */
	test_ptr = ec_to_pub(key, pub);
	if (!test_ptr)
	{
		printf("ec_to_pub() failed\n");
		EC_KEY_free(key);
		return (EXIT_FAILURE);
	}
	if (test_ptr != pub)
	{
		printf("Return value and pointer differ\n");
		EC_KEY_free(key);
		return (EXIT_FAILURE);
	}

	_print_hex_buffer(pub, EC_PUB_LEN);
	printf("\n");

	/* Cleanup */
	EC_KEY_free(key);

	return (EXIT_SUCCESS);
}
