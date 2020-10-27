/**
 * Wallet for Jörmungandr blockchain
 *
 * Provide support for recovering funds from both Yoroi and Daedalus wallets.
 *
 * Copyright 2020, Input Output HK Ltd
 * Licensed with: MIT OR Apache-2.0
 */

#ifndef IOHK_CHAIN_WALLET_LIBC_
#define IOHK_CHAIN_WALLET_LIBC_

/* Generated with cbindgen:0.14.4 */

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Payload type for voting
 */
enum PayloadType
{
  PayloadType_Public = 1,
};
typedef uint8_t PayloadType;

typedef struct Error
{

} Error;

typedef Error *ErrorPtr;

typedef struct Wallet
{

} Wallet;

typedef Wallet *WalletPtr;

typedef struct Settings
{

} Settings;

typedef Settings *SettingsPtr;

typedef struct Conversion
{

} Conversion;

typedef Conversion *ConversionPtr;

typedef struct Proposal
{

} Proposal;

typedef Proposal *ProposalPtr;

/**
 * decrypt payload of the wallet transfer protocol
 *
 * Parameters
 *
 * password: byte buffer with the encryption password
 * password_length: length of the password buffer
 * ciphertext: byte buffer with the encryption password
 * ciphertext_length: length of the password buffer
 * plaintext_out: used to return a pointer to a byte buffer with the decrypted text
 * plaintext_out_length: used to return the length of decrypted text
 *
 * The returned buffer is in the heap, so make sure to call the delete_buffer function
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though the function checks if
 * the pointers are null. Mind not to put random values in or you may see
 * unexpected behaviors.
 */
ErrorPtr iohk_jormungandr_symmetric_cipher_decrypt(const uint8_t *password,
                                                   uintptr_t password_length,
                                                   const uint8_t *ciphertext,
                                                   uintptr_t ciphertext_length,
                                                   const uint8_t **plaintext_out,
                                                   uintptr_t *plaintext_out_length);

/**
 * once funds have been retrieved with `iohk_jormungandr_wallet_retrieve_funds`
 * it is possible to convert all existing funds to the new wallet.
 *
 * The returned arrays are transactions to send to the network in order to do the
 * funds conversion.
 *
 * Don't forget to call `iohk_jormungandr_wallet_delete_conversion` to
 * properly free the memory
 *
 * # Errors
 *
 * On error the function returns a `ErrorPtr`. On success `NULL` is returned.
 * The `ErrorPtr` can then be observed to gathered details of the error.
 * Don't forget to call `iohk_jormungandr_wallet_delete_error` to free
 * the `ErrorPtr` from memory and avoid memory leaks.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
ErrorPtr iohk_jormungandr_wallet_convert(WalletPtr wallet,
                                         SettingsPtr settings,
                                         ConversionPtr *conversion_out);

/**
 * get the total value ignored in the conversion
 *
 * value_out: will returns the total value lost into dust inputs
 * ignored_out: will returns the number of dust utxos
 *
 * these returned values are informational only and this show that
 * there are UTxOs entries that are unusable because of the way they
 * are populated with dusts.
 *
 * # Errors
 *
 * On error the function returns a `ErrorPtr`. On success `NULL` is returned.
 * The `ErrorPtr` can then be observed to gathered details of the error.
 * Don't forget to call `iohk_jormungandr_wallet_delete_error` to free
 * the `ErrorPtr` from memory and avoid memory leaks.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
ErrorPtr iohk_jormungandr_wallet_convert_ignored(ConversionPtr conversion,
                                                 uint64_t *value_out,
                                                 uintptr_t *ignored_out);

/**
 * retrieve the index-nth transactions in the conversions starting from 0
 * and finishing at `size-1` where size is retrieved from
 * `iohk_jormungandr_wallet_convert_transactions_size`.
 *
 * the memory allocated returned is not owned and should not be kept
 * for longer than potential call to `iohk_jormungandr_wallet_delete_conversion`
 *
 * # Errors
 *
 * On error the function returns a `ErrorPtr`. On success `NULL` is returned.
 * The `ErrorPtr` can then be observed to gathered details of the error.
 * Don't forget to call `iohk_jormungandr_wallet_delete_error` to free
 * the `ErrorPtr` from memory and avoid memory leaks.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
ErrorPtr iohk_jormungandr_wallet_convert_transactions_get(ConversionPtr conversion,
                                                          uintptr_t index,
                                                          const uint8_t **transaction_out,
                                                          uintptr_t *transaction_size);

/**
 * get the number of transactions built to convert the retrieved wallet
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
uintptr_t iohk_jormungandr_wallet_convert_transactions_size(ConversionPtr conversion);

/**
 * Delete a binary buffer that was returned by this library alongside with its
 * length.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 */
void iohk_jormungandr_wallet_delete_buffer(uint8_t *ptr, uintptr_t length);

/**
 * delete the pointer
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
void iohk_jormungandr_wallet_delete_conversion(ConversionPtr conversion);

/**
 * delete the pointer and free the allocated memory
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
void iohk_jormungandr_wallet_delete_error(ErrorPtr error);

/**
 * delete the pointer
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
void iohk_jormungandr_wallet_delete_proposal(ProposalPtr proposal);

/**
 * delete the pointer and free the allocated memory
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
void iohk_jormungandr_wallet_delete_settings(SettingsPtr settings);

/**
 * Delete a null terminated string that was allocated by this library
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
void iohk_jormungandr_wallet_delete_string(char *ptr);

/**
 * delete the pointer, zero all the keys and free the allocated memory
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
void iohk_jormungandr_wallet_delete_wallet(WalletPtr wallet);

/**
 * Get a string describing the error, this will return an allocated
 * null terminated string providing extra details regarding the source
 * of the error.
 *
 * If the given error is a `NULL` pointer, the string is and always
 * is `"success"`. If no details are available the function will return
 * `"no more details"`. This string still need to be deleted with the
 * `iohk_jormungandr_wallet_delete_string` function.
 *
 * This function returns an allocated null terminated pointer. Don't
 * forget to free the memory with: `iohk_jormungandr_wallet_delete_string`.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
char *iohk_jormungandr_wallet_error_details(ErrorPtr error);

/**
 * Get a string describing the error, this will return an allocated
 * null terminated string describing the error.
 *
 * If the given error is a `NULL` pointer, the string is and always
 * is `"success"`. This string still need to be deleted with the
 * `iohk_jormungandr_wallet_delete_string` function.
 *
 * This function returns an allocated null terminated pointer. Don't
 * forget to free the memory with: `iohk_jormungandr_wallet_delete_string`.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
char *iohk_jormungandr_wallet_error_to_string(ErrorPtr error);

/**
 * get the wallet id
 *
 * This ID is the identifier to use against the blockchain/explorer to retrieve
 * the state of the wallet (counter, total value etc...)
 *
 * # Parameters
 *
 * * wallet: the recovered wallet (see recover function);
 * * id_out: a ready allocated pointer to an array of 32bytes. If this array is not
 *   32bytes this may result in a buffer overflow.
 *
 * # Safety
 *
 * This function dereference raw pointers (wallet, block0 and settings_out). Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 * the `id_out` needs to be ready allocated 32bytes memory. If not this will result
 * in an undefined behavior, in the best scenario it will be a buffer overflow.
 *
 * # Errors
 *
 * On error the function returns a `ErrorPtr`. On success `NULL` is returned.
 * The `ErrorPtr` can then be observed to gathered details of the error.
 * Don't forget to call `iohk_jormungandr_wallet_delete_error` to free
 * the `ErrorPtr` from memory and avoid memory leaks.
 *
 * * this function may fail if the wallet pointer is null;
 *
 */
ErrorPtr iohk_jormungandr_wallet_id(WalletPtr wallet,
                                    uint8_t *id_out);

/**
 * recover a wallet from an account and a list of utxo keys
 *
 * You can also use this function to recover a wallet even after you have
 * transferred all the funds to the new format (see the _convert_ function)
 *
 * The recovered wallet will be returned in `wallet_out`.
 *
 * # parameters
 *
 * * account_key: the Ed25519 extended key used wallet's account address private key
 *     in the form of a 64 bytes array.
 * * utxo_keys: an array of Ed25519 extended keys in the form of 64 bytes, used as utxo
 *     keys for the wallet
 * * utxo_keys_len: the number of keys in the utxo_keys array (not the number of bytes)
 * * wallet_out: the recovered wallet
 *
 * # Safety
 *
 * This function dereference raw pointers (password and wallet_out). Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 * # errors
 *
 * The function may fail if:
 *
 * * the `wallet_out` is null pointer
 *
 */
ErrorPtr iohk_jormungandr_wallet_import_keys(const uint8_t *account_key,
                                             const uint8_t *utxo_keys,
                                             uintptr_t utxo_keys_len,
                                             WalletPtr *wallet_out);

/**
 * retrieve a wallet from the given mnemonics, password and protocol magic
 *
 * this function will work for all yoroi, daedalus and other wallets
 * as it will try every kind of wallet anyway
 *
 * You can also use this function to recover a wallet even after you have
 * transferred all the funds to the new format (see the _convert_ function)
 *
 * The recovered wallet will be returned in `wallet_out`.
 *
 * # parameters
 *
 * * mnemonics: a null terminated utf8 string (already normalized NFKD) in english;
 * * password: pointer to the password (in bytes, can be UTF8 string or a bytes of anything);
 *   this value is optional and passing a null pointer will result in no password;
 * * password_length: the length of the password;
 * * wallet_out: a pointer to a pointer. The recovered wallet will be allocated on this pointer;
 *
 * # errors
 *
 * The function may fail if:
 *
 * * the mnemonics are not valid (invalid length or checksum);
 * * the `wallet_out` is null pointer
 *
 * On error the function returns a `ErrorPtr`. On success `NULL` is returned.
 * The `ErrorPtr` can then be observed to gathered details of the error.
 * Don't forget to call `iohk_jormungandr_wallet_delete_error` to free
 * the `ErrorPtr` from memory and avoid memory leaks.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
ErrorPtr iohk_jormungandr_wallet_recover(const char *mnemonics,
                                         const uint8_t *password,
                                         uintptr_t password_length,
                                         WalletPtr *wallet_out);

/**
 * retrieve funds from daedalus or yoroi wallet in the given block0 (or
 * any other blocks).
 *
 * Execute this function then you can check who much funds you have
 * retrieved from the given block.
 *
 * this function may take sometimes so it is better to only call this
 * function if needed.
 *
 * # Parameters
 *
 * * wallet: the recovered wallet (see recover function);
 * * block0: the pointer to the bytes of the block0;
 * * block0_length: the length of the block0 byte string;
 * * settings_out: the settings that will be parsed from the given
 *   block0;
 *
 * # Errors
 *
 * * this function may fail if the wallet pointer is null;
 * * the block is not valid (cannot be decoded)
 *
 * On error the function returns a `ErrorPtr`. On success `NULL` is returned.
 * The `ErrorPtr` can then be observed to gathered details of the error.
 * Don't forget to call `iohk_jormungandr_wallet_delete_error` to free
 * the `ErrorPtr` from memory and avoid memory leaks.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
ErrorPtr iohk_jormungandr_wallet_retrieve_funds(WalletPtr wallet,
                                                const uint8_t *block0,
                                                uintptr_t block0_length,
                                                SettingsPtr *settings_out);

/**
 * update the wallet account state
 *
 * this is the value retrieved from any jormungandr endpoint that allows to query
 * for the account state. It gives the value associated to the account as well as
 * the counter.
 *
 * It is important to be sure to have an updated wallet state before doing any
 * transactions otherwise future transactions may fail to be accepted by any
 * nodes of the blockchain because of invalid signature state.
 *
 * # Errors
 *
 * * this function may fail if the wallet pointer is null;
 *
 * On error the function returns a `ErrorPtr`. On success `NULL` is returned.
 * The `ErrorPtr` can then be observed to gathered details of the error.
 * Don't forget to call `iohk_jormungandr_wallet_delete_error` to free
 * the `ErrorPtr` from memory and avoid memory leaks.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
ErrorPtr iohk_jormungandr_wallet_set_state(WalletPtr wallet,
                                           uint64_t value,
                                           uint32_t counter);

/**
 * get the total value in the wallet
 *
 * make sure to call `retrieve_funds` prior to calling this function
 * otherwise you will always have `0`
 *
 * After calling this function the results is returned in the `total_out`.
 *
 * # Errors
 *
 * * this function may fail if the wallet pointer is null;
 *
 * On error the function returns a `ErrorPtr`. On success `NULL` is returned.
 * The `ErrorPtr` can then be observed to gathered details of the error.
 * Don't forget to call `iohk_jormungandr_wallet_delete_error` to free
 * the `ErrorPtr` from memory and avoid memory leaks.
 *
 * If the `total_out` pointer is null, this function does nothing
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though
 * the function checks if the pointers are null. Mind not to put random values
 * in or you may see unexpected behaviors
 *
 */
ErrorPtr iohk_jormungandr_wallet_total_value(WalletPtr wallet,
                                             uint64_t *total_out);

/**
 * build the vote cast transaction
 *
 * # Errors
 *
 * This function may fail upon receiving a null pointer or a `choice` value
 * that does not fall within the range specified in `proposal`.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though the function checks if
 * the pointers are null. Mind not to put random values in or you may see
 * unexpected behaviors.
 *
 * Don't forget to remove `transaction_out` with
 * `iohk_jormungandr_waller_delete_buffer`.
 */
ErrorPtr iohk_jormungandr_wallet_vote_cast(WalletPtr wallet,
                                           SettingsPtr settings,
                                           ProposalPtr proposal,
                                           uint8_t choice,
                                           const uint8_t **transaction_out,
                                           uintptr_t *len_out);

/**
 * build the proposal object
 *
 * # Errors
 *
 * This function may fail if:
 *
 * * `proposal_out` is null.
 * * `num_choices` is out of the allowed range.
 *
 * # Safety
 *
 * This function dereference raw pointers. Even though the function checks if
 * the pointers are null. Mind not to put random values in or you may see
 * unexpected behaviors.
 */
ErrorPtr iohk_jormungandr_wallet_vote_proposal(const uint8_t *vote_plan_id,
                                               PayloadType payload_type,
                                               uint8_t index,
                                               uint8_t num_choices,
                                               ProposalPtr *proposal_out);

#endif /* IOHK_CHAIN_WALLET_LIBC_ */
