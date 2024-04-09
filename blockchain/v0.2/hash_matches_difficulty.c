#include "blockchain.h"

/**
 * hash_matches_difficulty - checks whether a given
 *                           hash matches a given difficulty
 * @hash: hash to check
 * @difficulty: the minimum difficulty the hash should match
 * Return: 1 if the difficulty is respected, or 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
	uint32_t difficulty)
{
	uint8_t *ptr = (uint8_t *)hash;
	uint32_t diff = 0;
	int i;

	if (!hash)
		return (0);
	for (; ptr < hash + SHA256_DIGEST_LENGTH; ptr++)
	{
		for (i = 7; i >= 0; i--)
		{
			if ((*ptr >> i) & 1)
				break;
			diff++;
		}
	}
	if (diff > difficulty)
		return (diff);
	else
		return (difficulty);
}
