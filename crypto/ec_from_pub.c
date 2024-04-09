#include <stdlib.h>
#include <stdio.h>
#include "hblk_crypto.h"

/**
 * ec_from_pub - Create an EC_KEY structure given a public key
 * @pub: Pointer to the public key
 *
 * Return: Pointer to the created EC_KEY structure upon success,
 *         or NULL upon failure
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;
	EC_GROUP *group;
	EC_POINT *point;

	if (!pub)
		return (NULL);
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	group = EC_GROUP_new_by_curve_name(EC_CURVE);
	if (!group)
	{
		EC_KEY_free(key);
		return (NULL);
	}
	point = EC_POINT_new(group);
	if (!point)
	{
		EC_KEY_free(key);
		EC_GROUP_free(group);
		return (NULL);
	}
	if (EC_POINT_oct2point(group, point, pub, EC_PUB_LEN, NULL) != 1)
	{
		EC_KEY_free(key);
		EC_GROUP_free(group);
		EC_POINT_free(point);
		return (NULL);
	}
	if (EC_KEY_set_public_key(key, point) != 1)
	{
		EC_KEY_free(key);
		EC_GROUP_free(group);
		EC_POINT_free(point);
		return (NULL);
	}
	EC_GROUP_free(group);
	EC_POINT_free(point);
	return (key);
}
