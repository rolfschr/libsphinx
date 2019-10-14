#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <sodium.h>
#include <string.h>

//#define TRACE 1
//#define NORANDOM 1

#ifdef TRACE
#include <stdio.h>
void dump(const uint8_t *p, const size_t len, const char* msg);
#endif

#ifdef NORANDOM
void a_randombytes(void* const buf, const size_t len);
void a_randomscalar(unsigned char* buf);
#define crypto_core_ristretto255_scalar_random a_randomscalar
#define randombytes a_randombytes
#endif


int sphinx_oprf(const uint8_t *pwd, const size_t pwd_len,
                const uint8_t k[crypto_core_ristretto255_SCALARBYTES],
                uint8_t key[crypto_generichash_BYTES]);
int sphinx_server_3dh(uint8_t mk[crypto_generichash_BYTES],
                      const uint8_t ix[crypto_scalarmult_SCALARBYTES],
                      const uint8_t ex[crypto_scalarmult_SCALARBYTES],
                      const uint8_t Ip[crypto_scalarmult_BYTES],
                      const uint8_t Ep[crypto_scalarmult_BYTES]);
int sphinx_user_3dh(uint8_t mk[crypto_generichash_BYTES],
                    const uint8_t ix[crypto_scalarmult_SCALARBYTES],
                    const uint8_t ex[crypto_scalarmult_SCALARBYTES],
                    const uint8_t Ip[crypto_scalarmult_BYTES],
                    const uint8_t Ep[crypto_scalarmult_BYTES]);

int sphinx_blindPW(const uint8_t *pw, const size_t pwlen, uint8_t *r, uint8_t *alpha);

/*
 * This is a simple utility function that can be used to calculate
 * f_k(c), where c is a constant, this is useful if the peers want to
 * authenticate each other.
 */
void sphinx_f(const uint8_t *k, const size_t k_len, const uint8_t val, uint8_t *res);

#endif //COMMON_H