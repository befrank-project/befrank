// Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers, The BeFrank developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstdint>

namespace CryptoNote {
namespace parameters {

const uint64_t CRYPTONOTE_MAX_BLOCK_NUMBER                   = 500000000;
const size_t   CRYPTONOTE_MAX_BLOCK_BLOB_SIZE                = 500000000;
const size_t   CRYPTONOTE_MAX_TX_SIZE                        = 1000000000;
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX       = 86; // addresses start with "F"
const size_t   CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW          = 10;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT            = 60 * 60 * 2;

const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW             = 60;

// MONEY_SUPPLY - total number coins to be generated
const uint64_t MONEY_SUPPLY                                  = UINT64_C(10000000000000);
const uint64_t RESERVE_FUND                                  = UINT64_C(2000000000000);
const size_t CRYPTONOTE_COIN_VERSION                         = 1;
const unsigned EMISSION_SPEED_FACTOR                         = 18;
static_assert(EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");

const size_t   CRYPTONOTE_REWARD_BLOCKS_WINDOW               = 100;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE     = 1000000; //size of block (bytes) after which reward for block calculated using block size
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V2  = 1000000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1  = 100000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE;
const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE        = 600;
const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT              = 2;
const uint64_t MINIMUM_FEE                                   = UINT64_C(1);
const uint64_t DEFAULT_DUST_THRESHOLD                        = UINT64_C(1);

const uint64_t DIFFICULTY_TARGET                             = 120; // seconds
const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY             = 24 * 60 * 60 / DIFFICULTY_TARGET;
const size_t   DIFFICULTY_WINDOW                             = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY; // blocks
const size_t   DIFFICULTY_WINDOW_V2                          = 17; // blocks
const size_t   DIFFICULTY_CUT                                = 60;  // timestamps to cut after sorting
const size_t   DIFFICULTY_LAG                                = 15;  // !!!
static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

const size_t   MAX_BLOCK_SIZE_INITIAL                        = 1000000;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;

const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

const uint64_t CRYPTONOTE_MEMPOOL_TX_LIVETIME                = 60 * 60 * 24;     //seconds, one day
const uint64_t CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = 60 * 60 * 24 * 7; //seconds, one week
const uint64_t CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 7;  // CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL * CRYPTONOTE_MEMPOOL_TX_LIVETIME = time to forget tx

const size_t   FUSION_TX_MAX_SIZE                            = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT * 30 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;

const uint32_t UPGRADE_HEIGHT_V2                             = 1;
const uint32_t UPGRADE_HEIGHT_V3                             = 2;
const unsigned UPGRADE_VOTING_THRESHOLD = 90;               // percent
const uint32_t   UPGRADE_VOTING_WINDOW                       = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
const uint32_t   UPGRADE_WINDOW                              = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
static_assert(0 < UPGRADE_VOTING_THRESHOLD && UPGRADE_VOTING_THRESHOLD <= 100, "Bad UPGRADE_VOTING_THRESHOLD");
static_assert(UPGRADE_VOTING_WINDOW > 1, "Bad UPGRADE_VOTING_WINDOW");

const char     CRYPTONOTE_BLOCKS_FILENAME[]                  = "blocks.dat";
const char     CRYPTONOTE_BLOCKINDEXES_FILENAME[]            = "blockindexes.dat";
const char     CRYPTONOTE_BLOCKSCACHE_FILENAME[]             = "blockscache.dat";
const char     CRYPTONOTE_POOLDATA_FILENAME[]                = "poolstate.bin";
const char     P2P_NET_DATA_FILENAME[]                       = "p2pstate.bin";
const char     CRYPTONOTE_BLOCKCHAIN_INDICES_FILENAME[]      = "blockchainindices.dat";
const char     MINER_CONFIG_FILE_NAME[]                      = "miner_conf.json";
} // parameters

const char     CRYPTONOTE_NAME[]                             = "befrank";
const char     GENESIS_COINBASE_TX_HEX[]                     = "010a01ff000180c0a8ca9a3a029b2e4c0281c0b02e7c53291a94d1d0cbff8883f8024f5142ee494ffbbd0880712101827b04a29be01f599850ee3fa1140a05bc4292504f0b820f27ca814b0656c7ec";

const uint8_t  CURRENT_TRANSACTION_VERSION                   =  1;
const uint8_t  BLOCK_MAJOR_VERSION_1                         =  1;
const uint8_t  BLOCK_MAJOR_VERSION_2                         =  2;
const uint8_t  BLOCK_MAJOR_VERSION_3                         =  3;
const uint8_t  BLOCK_MINOR_VERSION_0                         =  0;
const uint8_t  BLOCK_MINOR_VERSION_1                         =  1;

const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT        =  10000;  //by default, blocks ids count in synchronizing
const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            =  200;    //by default, blocks count in blocks downloading
const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT         =  1000;

const int      P2P_DEFAULT_PORT                              =  18320;
const int      RPC_DEFAULT_PORT                              =  18322;

const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT                =  1000;
const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT                 =  5000;

const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE          = 16 * 1024 * 1024; // 16 MB
const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT                 = 8;
const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT     = 70;
const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL                = 60;            // seconds
const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE                   = 50000000;      // 50000000 bytes maximum packet size
const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE                = 250;
const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT                = 5000;          // 5 seconds
const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT           = 2000;          // 2 seconds
const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT                    = 60 * 2 * 1000; // 2 minutes
const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT          = 5000;          // 5 seconds
const char     P2P_STAT_TRUSTED_PUB_KEY[]                    = "04522aabf22d2c98fabdacdab9803e0def7ecc0908526edc029c6dd62252f431f7d1ea5710d5b9e370a12830eb8c45cc7726eaa9b1c897cb98aef801113c4075b1";

const char* const SEED_NODES[] = { 
  "seed.befrank.site:18320",
  "seed2.befrank.site:18320",
  "seed3.befrank.site:18320",
  "seed4.befrank.site:18320",
  "seed5.befrank.site:18320",
  "seed6.befrank.site:18320",
  "eat-sleep-mine.com:18320"
};

struct CheckpointData {
  uint32_t height;
  const char* blockId;
};

const std::initializer_list<CheckpointData> CHECKPOINTS = { 
	{	       1, "2a9c2d3e4e8f00ed29b8c8ee2c34212bc932547d079ce39924a31ed22726b91c" },
	{	     100, "15bd06a8670c71dbbadfa701794b9a24f49f4c42f533597e98893c3f781603b3" },
	{	     500, "19fdafd1116eb327999db012c7cd1cdbca5385105a3aaeef24467f9dee2c7502" },
	{	    1000, "9930bf2d319a2aff24bb80e9db88f5fd6357e1c0448f34fa7aec20db97e75d13" },
	{       2000, "a6c56b7e1e4fbc4131bf182c6712ebf3caea29386d1306bb1750c6b3a61f282e" },
	{	    5000, "4b9bb365ee89cc5cb9ca7fdd9f2ed70ffcdf3d7998ae6f49dcd007e4257a1685" },
	{       8800, "0e61f5d84e0d1dbe09b58fa2e9e5df0fb415ab0c979965cc3b293f9992943a2e" },
	{       9000, "ee80e46cfcb9d02c4fde597b613beb05516a712b3998bb080a3aa8adc5adef23" },
	{      10000, "97c327e6581ecab11cee3e743a597fa725476b9efeebcda884a174f72f643832" },
	{      12500, "b8d8eb3b64e5aba708d6e81bc10021dc38e41c1d9a090f4471fa62595fd01b02" },
	{      15000, "6c17c197d16df481202f072844d358a06d57b5d462634b419486b6dace8fc6e7" },
	{      17500, "caaa3de7583b995667bdd960bb22902bf527eafa0b77a549baeb0c20ec51d7dd" },
	{      20000, "207f960bbdf19a53bd79d411ccce96b60c515b6802d0a1d03467eacee4bbcfb4" },
	{      22500, "157e2f894a6d0e87233e47d4f733b46f2e14af2686da9f2632ea2c8c93cee07a" },
	{      25000, "3c4a4068dc2a0ddc2e59093408d711e68a0a6c85bec1ddf33ce77af36e56f502" },
	{      27500, "a46967209e8f8cb316687543648747bf929fe22e3ffe4b094b1c6196f0b42f17" },
	{      30000, "a84942d3382d70f311228c4dbaa58b46096497c0fdbe2694c6da947caa270c41" },
	{      31000, "482b6af4a391f6063203ee07c4be538d2b403f6d063e0943b680f6b0bab0806c" },
	{      31489, "f6adb5f2a4322405c3703463a1428859e409ccec28e9011c2eb374b07cdb7a69" }
};

} // CryptoNote

#define ALLOW_DEBUG_COMMANDS



