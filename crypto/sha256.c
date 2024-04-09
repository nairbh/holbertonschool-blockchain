#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hblk_crypto.h"

/**
 * sha256 - computes the hash of a sequence of bytes
 * @s: the sequence of bytes to be hashed
 * @len: is the number of bytes to hash in s
 * @digest: resulting hash must be stored in
 * Return: a pointer to digest, if digest happens to be NULL, return NULL
 */
uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	SHA256_CTX sha256;

	if (s == NULL || digest == NULL)
		return (NULL);

	if (!SHA256_Init(&sha256))
		return (NULL);

	if (!SHA256_Update(&sha256, (const unsigned char *)s, len))
		return (NULL);

	if (!SHA256_Final(digest, &sha256))
		return (NULL);

	return (digest);
}
