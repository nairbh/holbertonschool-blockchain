#include "blockchain.h"

/**
 * blockchain_difficulty - computes the difficulty to assign
 *                         to a potential next Block in the Blockchain
 * @blockchain: pointer to the Blockchain to analyze
 * Return: the difficulty to be assigned to a potential next Block
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *last, *adjusted;
	uint64_t time, expected_time;

	if (!blockchain)
		return (0);
	last = llist_get_tail(blockchain->chain);
	if (!last)
		return (0);
	if (last->info.index == 0 ||
		last->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL)
		return (last->info.difficulty);
	adjusted = llist_get_node_at(blockchain->chain,
		last->info.index + 1 - DIFFICULTY_ADJUSTMENT_INTERVAL);
	expected_time = DIFFICULTY_ADJUSTMENT_INTERVAL * BLOCK_GENERATION_INTERVAL;
	time = last->info.timestamp - adjusted->info.timestamp;
	if (time * 2 < expected_time)
		return (last->info.difficulty + 1);
	else if (time > 2 * expected_time)
	{
		if (last->info.difficulty > 0)
			return (last->info.difficulty - 1);
		else
			return (0);
	}
	return (last->info.difficulty);
}
