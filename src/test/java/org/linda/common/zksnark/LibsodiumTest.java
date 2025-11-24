package org.linda.common.zksnark;

import org.junit.Test;

import java.nio.charset.StandardCharsets;

import static org.junit.Assert.*;

public class LibsodiumTest {
    private Libsodium libsodium = LibsodiumWrapper.getInstance();

    @Test
    public void testCryptoGenerichashBlake2BStateInitFree() {
        long state = libsodium.cryptoGenerichashBlake2BStateInit();
        assertNotEquals(0L, state);
        
        // Should not crash
        libsodium.cryptoGenerichashBlake2BStateFree(state);
    }

    @Test
    public void testCryptoGenerichashBlake2BInitSaltPersonal() {
        long state = libsodium.cryptoGenerichashBlake2BStateInit();
        assertNotEquals(0L, state);
        
        byte[] key = new byte[32];
        byte[] salt = new byte[16];
        byte[] personal = new byte[16];
        
        int result = libsodium.cryptoGenerichashBlake2BInitSaltPersonal(
            state, key, key.length, 32, salt, personal);
        
        assertEquals(0, result);
        
        libsodium.cryptoGenerichashBlake2BStateFree(state);
    }

    @Test
    public void testCryptoGenerichashBlake2BUpdate() {
        long state = libsodium.cryptoGenerichashBlake2BStateInit();
        assertNotEquals(0L, state);
        
        byte[] key = new byte[32];
        byte[] salt = new byte[16];
        byte[] personal = new byte[16];
        
        int result = libsodium.cryptoGenerichashBlake2BInitSaltPersonal(
            state, key, key.length, 32, salt, personal);
        assertEquals(0, result);
        
        byte[] input = "test input".getBytes(StandardCharsets.UTF_8);
        result = libsodium.cryptoGenerichashBlake2BUpdate(state, input, input.length);
        assertEquals(0, result);
        
        libsodium.cryptoGenerichashBlake2BStateFree(state);
    }

    @Test
    public void testCryptoGenerichashBlake2BFinal() {
        long state = libsodium.cryptoGenerichashBlake2BStateInit();
        assertNotEquals(0L, state);
        
        byte[] key = new byte[32];
        byte[] salt = new byte[16];
        byte[] personal = new byte[16];
        
        int result = libsodium.cryptoGenerichashBlake2BInitSaltPersonal(
            state, key, key.length, 32, salt, personal);
        assertEquals(0, result);
        
        byte[] input = "test input".getBytes(StandardCharsets.UTF_8);
        result = libsodium.cryptoGenerichashBlake2BUpdate(state, input, input.length);
        assertEquals(0, result);
        
        byte[] output = new byte[32];
        result = libsodium.cryptoGenerichashBlake2BFinal(state, output, output.length);
        assertEquals(0, result);
        
        libsodium.cryptoGenerichashBlake2BStateFree(state);
    }

    @Test
    public void testCryptoGenerichashBlake2BSaltPersonal() {
        byte[] out = new byte[32];
        byte[] in = "test input".getBytes(StandardCharsets.UTF_8);
        byte[] key = new byte[32];
        byte[] salt = new byte[16];
        byte[] personal = new byte[16];
        
        int result = libsodium.cryptoGenerichashBlake2BSaltPersonal(
            out, out.length,
            in, in.length, 
            key, key.length, 
            salt, personal);
        
        assertEquals(0, result);
        
        // Check that output was modified (not all zeros)
        boolean allZeros = true;
        for (byte b : out) {
            if (b != 0) {
                allZeros = false;
                break;
            }
        }
        assertFalse(allZeros);
    }

    @Test
    public void testCryptoAeadChacha20Poly1305IetfEncryptDecrypt() {
        // Test data
        byte[] message = "Hello, World!".getBytes(StandardCharsets.UTF_8);
        byte[] key = new byte[32]; // crypto_aead_chacha20poly1305_ietf_KEYBYTES
        byte[] nonce = new byte[12]; // crypto_aead_chacha20poly1305_ietf_NPUBBYTES
        byte[] additionalData = "metadata".getBytes(StandardCharsets.UTF_8);
        
        // Initialize with some values
        for (int i = 0; i < key.length; i++) key[i] = (byte) i;
        for (int i = 0; i < nonce.length; i++) nonce[i] = (byte) (i + 10);
        
        // Encrypt
        byte[] ciphertext = new byte[message.length + 16]; // message + tag
        long[] ciphertextLen = new long[1];
        
        int result = libsodium.cryptoAeadChacha20Poly1305IetfEncrypt(
            ciphertext, ciphertextLen,
            message, message.length,
            additionalData, additionalData.length,
            null, nonce, key);
        
        assertEquals(0, result);
        
        // Decrypt
        byte[] decrypted = new byte[message.length];
        long[] decryptedLen = new long[1];
        
        result = libsodium.cryptoAeadChacha20Poly1305IetfDecrypt(
            decrypted, decryptedLen,
            null,
            ciphertext, ciphertextLen[0],
            additionalData, additionalData.length,
            nonce, key);
        
        assertEquals(0, result);
        assertEquals(message.length, decryptedLen[0]);
        
        // Verify decrypted message matches original
        for (int i = 0; i < message.length; i++) {
            assertEquals(message[i], decrypted[i]);
        }
    }
}