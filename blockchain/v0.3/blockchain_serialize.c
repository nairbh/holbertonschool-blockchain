#include "blockchain.h"

/**
 * blockchain_serialize - serializes a Blockchain into a file
 * @blockchain: Blockchain to be serialized
 * @path: path to a file to serialize the Blockchain into
 * Return: 0 upon success, or -1 upon failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	block_t *block = NULL;
	int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	int i, size;
	char *hblk_magic = "\x48\x42\x4c\x4b";
	char *hblk_version = "\x30\x2E\x31";
	uint8_t endianness = _get_endianness();

	if (!blockchain || !blockchain->chain || !path || !fd)
		return (-1);
	size = llist_size(blockchain->chain);
	if ((size_t)write(fd, hblk_magic, strlen(hblk_magic)) != strlen(hblk_magic))
		return (close(fd), -1);
	if ((size_t)write(fd, hblk_version, strlen(hblk_version))
		!= strlen(hblk_version))
		return (close(fd), -1);
	if (write(fd, &endianness, 1) != 1)
		return (close(fd), -1);
	if (write(fd, &size, 4) != 4)
		return (close(fd), -1);
	for (i = 0; i < size; i++)
	{
		block = llist_get_node_at(blockchain->chain, i);

		if (!block)
			return (close(fd), -1);
		if (write(fd, &(block->info), sizeof(block->info))
			!= sizeof(block->info))
			return (close(fd), -1);
		if (write(fd, &(block->data.len), 4) != 4)
			return (close(fd), -1);
		if (write(fd, block->data.buffer,
			block->data.len) != block->data.len)
			return (close(fd), -1);
		if (write(fd, block->hash, SHA256_DIGEST_LENGTH) !=
			SHA256_DIGEST_LENGTH)
			return (close(fd), -1);
	}
	return (close(fd), 0);
}
