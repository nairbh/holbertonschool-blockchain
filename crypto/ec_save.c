#include "hblk_crypto.h"

/**
 * ec_save - Save an EC key pair on the disk
 * @key: Pointer to the EC key pair to be saved
 * @folder: Path to the folder in which to save the keys
 *
 * Return: 1 on success, 0 on failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	FILE *fp;
	char path[256];

	if (!key || !folder)
		return (0);
	mkdir(folder, 0777);
	sprintf(path, "%s/" PRI_FILENAME, folder);
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL);
	fclose(fp);

	sprintf(path, "%s/" PUB_FILENAME, folder);
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	if (!PEM_write_EC_PUBKEY(fp, key))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);

	return (1);

}
