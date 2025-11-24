/**
 * Java wrapper for libsodium cryptographic functions.
 * Provides access to blake2b hashing and chacha20-poly1305 encryption.
 * 
 * @author LindaProtocol
 * @version 1.0.0
 */
package org.linda.common.zksnark;

public class Libsodium {
  private static final LibsodiumJNI INSTANCE = new LibsodiumJNI();

  static {
      loadNativeLibrary();
  }

  private static void loadNativeLibrary() {
      try {
          // Try to load the library directly from the known path
          String libraryPath = System.getProperty("java.library.path");
          System.out.println("Library path: " + libraryPath);
          
          // Try different library names
          try {
              System.loadLibrary("zksnarkjni");
          } catch (UnsatisfiedLinkError e1) {
              try {
                  System.loadLibrary("sodiumjni");
              } catch (UnsatisfiedLinkError e2) {
                  // If both fail, try loading from absolute path
                  String absolutePath = "/home/ubuntu/zksnark-java-sdk/cpp/build/libzksnarkjni.so";
                  System.load(absolutePath);
              }
          }
      } catch (UnsatisfiedLinkError e) {
          System.err.println("Failed to load native library: " + e.getMessage());
          e.printStackTrace();
      }
  }

  public long cryptoGenerichashBlake2BStateInit() {
    /**
     * Initializes a new blake2b hash state.
     *
     * @return native pointer to the hash state
     */
    return INSTANCE.crypto_generichash_blake2b_state_init();
  }
    /**
     * Frees a blake2b hash state.
     *
     * @param state the native pointer to the hash state
     */
  public void cryptoGenerichashBlake2BStateFree(long state) {
    INSTANCE.crypto_generichash_blake2b_state_free(state);
  }

  public int cryptoGenerichashBlake2BInitSaltPersonal(
      long state, byte[] key, int keylen, int outlen, byte[] salt, byte[] personal) {
    return INSTANCE.crypto_generichash_blake2b_init_salt_personal(
        state, key, keylen, outlen, salt, personal);
  }

  public int cryptoGenerichashBlake2BUpdate(
      long state, byte[] in, long inlen) {
    return INSTANCE.crypto_generichash_blake2b_update(state, in, inlen);
  }

  public int cryptoGenerichashBlake2BFinal(
      long state, byte[] out, int outlen) {
    return INSTANCE.crypto_generichash_blake2b_final(state, out, outlen);
  }

  public int cryptoGenerichashBlake2BSaltPersonal(
      byte[] out, int outlen, byte[] in, long inlen, byte[] key, int keylen, byte[] salt, byte[] personal) {
    return INSTANCE.crypto_generichash_blake2b_salt_personal(out, outlen, in, inlen, key, keylen, salt, personal);
  }

  public int cryptoAeadChacha20Poly1305IetfDecrypt(
      byte[] m, long[] mlen_p, byte[] nsec, byte[] c, long clen, byte[] ad, long adlen, byte[] npub, byte[] k) {
    return INSTANCE.crypto_aead_chacha20poly1305_ietf_decrypt(m, mlen_p, nsec, c, clen, ad, adlen, npub, k);
  }

  public int cryptoAeadChacha20Poly1305IetfEncrypt(
      byte[] c, long[] clen_p, byte[] m, long mlen, byte[] ad, long adlen, byte[] nsec, byte[] npub, byte[] k) {
    return INSTANCE.crypto_aead_chacha20poly1305_ietf_encrypt(c, clen_p, m, mlen, ad, adlen, nsec, npub, k);
  }

  static class LibsodiumJNI {
    private native long crypto_generichash_blake2b_state_init();

    private native void crypto_generichash_blake2b_state_free(long state);

    private native int crypto_generichash_blake2b_init_salt_personal(
        long state, byte[] key, int keylen, int outlen, byte[] salt, byte[] personal);

    private native int crypto_generichash_blake2b_update(
        long state, byte[] in, long inlen);

    private native int crypto_generichash_blake2b_final(
        long state, byte[] out, int outlen);

    private native int crypto_generichash_blake2b_salt_personal(
        byte[] out, int outlen, byte[] in, long inlen, byte[] key, int keylen, byte[] salt, byte[] personal);

    private native int crypto_aead_chacha20poly1305_ietf_decrypt(
        byte[] m, long[] mlen_p, byte[] nsec, byte[] c, long clen, byte[] ad, long adlen, byte[] npub, byte[] k);

    private native int crypto_aead_chacha20poly1305_ietf_encrypt(
        byte[] c, long[] clen_p, byte[] m, long mlen, byte[] ad, long adlen, byte[] nsec, byte[] npub, byte[] k);
  }
}