// single block
int block_pack_size(Block &block) {
  int res = 0;
  
  return res;
}
void block_pack(Block &block) {
  
}
void block_unpack(Block &block) {
  
}

// 1024 block pack 



// mem state
t_pub_key genesis_pub_key;
t_prv_key genesis_priv_key_FUCK_WE_CANT_SEND_FILE_IN_OUT_SOLUTION_TO_GENESIS_NODE_FUUUUUUUUUUUUUUUUUUU;

void gms_init() {
  unsigned char seed[32] = {0xFC};
  ed25519_create_keypair(genesis_pub_key.b, genesis_priv_key_FUCK_WE_CANT_SEND_FILE_IN_OUT_SOLUTION_TO_GENESIS_NODE_FUUUUUUUUUUUUUUUUUUU.b, seed);
  
  gms.a2pk.push_back(genesis_pub_key);
  gms.balance.push_back(1e6);
}