#include <jni.h>
#include "sodium.h"
#include "org_linda_common_zksnark_Libsodium_LibsodiumJNI.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_org_linda_common_zksnark_Libsodium_LibsodiumJNI_crypto_1generichash_1blake2b_1state_1init
    (JNIEnv *env, jobject obj) {
    crypto_generichash_blake2b_state* state_p = new crypto_generichash_blake2b_state();
    if (!state_p) {
        return 0;
    }
    return (jlong) state_p;
}

JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Libsodium_LibsodiumJNI_crypto_1generichash_1blake2b_1state_1free
    (JNIEnv *env, jobject obj, jlong state) {
    crypto_generichash_blake2b_state* state_p = (crypto_generichash_blake2b_state*) state;
    if (state_p) {
        delete state_p;
    }
}

JNIEXPORT jint JNICALL Java_org_linda_common_zksnark_Libsodium_LibsodiumJNI_crypto_1generichash_1blake2b_1init_1salt_1personal
    (JNIEnv *env, jobject obj, jlong state, jbyteArray key, jint keylen, jint outlen, jbyteArray salt, jbyteArray personal) {
    
    unsigned char* key_p = NULL;
    unsigned char* salt_p = NULL;
    unsigned char* personal_p = NULL;
    jint ret = -1;
    
    if (key != NULL) {
        key_p = (unsigned char *) env->GetByteArrayElements(key, NULL);
        if (key_p == NULL) {
            return -1;
        }
    }
    
    if (salt != NULL) {
        salt_p = (unsigned char *) env->GetByteArrayElements(salt, NULL);
        if (salt_p == NULL) {
            if (key_p != NULL) env->ReleaseByteArrayElements(key, (jbyte *)key_p, JNI_ABORT);
            return -1;
        }
    }
    
    if (personal != NULL) {
        personal_p = (unsigned char *) env->GetByteArrayElements(personal, NULL);
        if (personal_p == NULL) {
            if (key_p != NULL) env->ReleaseByteArrayElements(key, (jbyte *)key_p, JNI_ABORT);
            if (salt_p != NULL) env->ReleaseByteArrayElements(salt, (jbyte *)salt_p, JNI_ABORT);
            return -1;
        }
    }

    ret = crypto_generichash_blake2b_init_salt_personal(
        (crypto_generichash_blake2b_state *) state,
        key_p,
        (size_t) keylen,
        (size_t) outlen,
        salt_p,
        personal_p
    );

    if (key_p != NULL) env->ReleaseByteArrayElements(key, (jbyte *)key_p, JNI_ABORT);
    if (salt_p != NULL) env->ReleaseByteArrayElements(salt, (jbyte *)salt_p, JNI_ABORT);
    if (personal_p != NULL) env->ReleaseByteArrayElements(personal, (jbyte *)personal_p, JNI_ABORT);

    return ret;
}

JNIEXPORT jint JNICALL Java_org_linda_common_zksnark_Libsodium_LibsodiumJNI_crypto_1generichash_1blake2b_1update
    (JNIEnv *env, jobject obj, jlong state, jbyteArray in, jlong inlen) {
    
    unsigned char* in_p = NULL;
    jint ret = -1;
    
    if (in != NULL) {
        in_p = (unsigned char *) env->GetByteArrayElements(in, NULL);
        if (in_p == NULL) {
            return -1;
        }
    }

    ret = crypto_generichash_blake2b_update(
        (crypto_generichash_blake2b_state *) state,
        in_p,
        (unsigned long long) inlen
    );

    if (in_p != NULL) env->ReleaseByteArrayElements(in, (jbyte *)in_p, JNI_ABORT);

    return ret;
}

JNIEXPORT jint JNICALL Java_org_linda_common_zksnark_Libsodium_LibsodiumJNI_crypto_1generichash_1blake2b_1final
    (JNIEnv *env, jobject obj, jlong state, jbyteArray out, jint outlen) {
    
    unsigned char* out_p = NULL;
    jint ret = -1;
    
    if (out != NULL) {
        out_p = (unsigned char *) env->GetByteArrayElements(out, NULL);
        if (out_p == NULL) {
            return -1;
        }
    }

    ret = crypto_generichash_blake2b_final(
        (crypto_generichash_blake2b_state *) state,
        out_p,
        (size_t) outlen
    );

    if (out_p != NULL) {
        env->ReleaseByteArrayElements(out, (jbyte *)out_p, 0);
    }

    return ret;
}

JNIEXPORT jint JNICALL Java_org_linda_common_zksnark_Libsodium_LibsodiumJNI_crypto_1generichash_1blake2b_1salt_1personal
    (JNIEnv *env, jobject obj, jbyteArray out, jint outlen, jbyteArray in, jlong inlen, jbyteArray key, jint keylen, jbyteArray salt, jbyteArray personal) {
    
    unsigned char* out_p = NULL;
    unsigned char* in_p = NULL;
    unsigned char* key_p = NULL;
    unsigned char* salt_p = NULL;
    unsigned char* personal_p = NULL;
    jint ret = -1;
    
    // Get out array
    if (out != NULL) {
        out_p = (unsigned char *) env->GetByteArrayElements(out, NULL);
        if (out_p == NULL) {
            goto cleanup;
        }
    }
    
    // Get in array
    if (in != NULL) {
        in_p = (unsigned char *) env->GetByteArrayElements(in, NULL);
        if (in_p == NULL) {
            goto cleanup;
        }
    }
    
    // Get key array
    if (key != NULL) {
        key_p = (unsigned char *) env->GetByteArrayElements(key, NULL);
        if (key_p == NULL) {
            goto cleanup;
        }
    }
    
    // Get salt array
    if (salt != NULL) {
        salt_p = (unsigned char *) env->GetByteArrayElements(salt, NULL);
        if (salt_p == NULL) {
            goto cleanup;
        }
    }
    
    // Get personal array
    if (personal != NULL) {
        personal_p = (unsigned char *) env->GetByteArrayElements(personal, NULL);
        if (personal_p == NULL) {
            goto cleanup;
        }
    }

    ret = crypto_generichash_blake2b_salt_personal(
        out_p,
        (size_t) outlen,
        in_p,
        (unsigned long long) inlen,
        key_p,
        (size_t) keylen,
        salt_p,
        personal_p
    );

cleanup:
    if (out_p != NULL) env->ReleaseByteArrayElements(out, (jbyte *)out_p, 0);
    if (in_p != NULL) env->ReleaseByteArrayElements(in, (jbyte *)in_p, JNI_ABORT);
    if (key_p != NULL) env->ReleaseByteArrayElements(key, (jbyte *)key_p, JNI_ABORT);
    if (salt_p != NULL) env->ReleaseByteArrayElements(salt, (jbyte *)salt_p, JNI_ABORT);
    if (personal_p != NULL) env->ReleaseByteArrayElements(personal, (jbyte *)personal_p, JNI_ABORT);

    return ret;
}

JNIEXPORT jint JNICALL Java_org_linda_common_zksnark_Libsodium_LibsodiumJNI_crypto_1aead_1chacha20poly1305_1ietf_1decrypt
    (JNIEnv *env, jobject obj, jbyteArray m, jlongArray mlen_p, jbyteArray nsec, jbyteArray c, jlong clen, jbyteArray ad, jlong adlen, jbyteArray npub, jbyteArray k) {
    
    unsigned char* m_p = NULL;
    unsigned long long* mlen_p_p = NULL;
    unsigned char* nsec_p = NULL;
    unsigned char* c_p = NULL;
    unsigned char* ad_p = NULL;
    unsigned char* npub_p = NULL;
    unsigned char* k_p = NULL;
    jint ret = -1;
    
    if (m != NULL) {
        m_p = (unsigned char *) env->GetByteArrayElements(m, NULL);
        if (m_p == NULL) {
            goto cleanup;
        }
    }
    
    if (mlen_p != NULL) {
        mlen_p_p = (unsigned long long*) env->GetLongArrayElements(mlen_p, NULL);
        if (mlen_p_p == NULL) {
            goto cleanup;
        }
    }
    
    if (nsec != NULL) {
        nsec_p = (unsigned char *) env->GetByteArrayElements(nsec, NULL);
        if (nsec_p == NULL) {
            goto cleanup;
        }
    }
    
    if (c != NULL) {
        c_p = (unsigned char *) env->GetByteArrayElements(c, NULL);
        if (c_p == NULL) {
            goto cleanup;
        }
    }
    
    if (ad != NULL) {
        ad_p = (unsigned char *) env->GetByteArrayElements(ad, NULL);
        if (ad_p == NULL) {
            goto cleanup;
        }
    }
    
    if (npub != NULL) {
        npub_p = (unsigned char *) env->GetByteArrayElements(npub, NULL);
        if (npub_p == NULL) {
            goto cleanup;
        }
    }
    
    if (k != NULL) {
        k_p = (unsigned char *) env->GetByteArrayElements(k, NULL);
        if (k_p == NULL) {
            goto cleanup;
        }
    }

    ret = crypto_aead_chacha20poly1305_ietf_decrypt(
        m_p,
        mlen_p_p,
        nsec_p,
        c_p,
        (unsigned long long) clen,
        ad_p,
        (unsigned long long) adlen,
        npub_p,
        k_p
    );

cleanup:
    if (m_p != NULL) env->ReleaseByteArrayElements(m, (jbyte *)m_p, 0);
    if (mlen_p_p != NULL) env->ReleaseLongArrayElements(mlen_p, (jlong *)mlen_p_p, 0);
    if (nsec_p != NULL) env->ReleaseByteArrayElements(nsec, (jbyte *)nsec_p, JNI_ABORT);
    if (c_p != NULL) env->ReleaseByteArrayElements(c, (jbyte *)c_p, JNI_ABORT);
    if (ad_p != NULL) env->ReleaseByteArrayElements(ad, (jbyte *)ad_p, JNI_ABORT);
    if (npub_p != NULL) env->ReleaseByteArrayElements(npub, (jbyte *)npub_p, JNI_ABORT);
    if (k_p != NULL) env->ReleaseByteArrayElements(k, (jbyte *)k_p, JNI_ABORT);

    return ret;
}

JNIEXPORT jint JNICALL Java_org_linda_common_zksnark_Libsodium_LibsodiumJNI_crypto_1aead_1chacha20poly1305_1ietf_1encrypt
    (JNIEnv *env, jobject obj, jbyteArray c, jlongArray clen_p, jbyteArray m, jlong mlen, jbyteArray ad, jlong adlen, jbyteArray nsec, jbyteArray npub, jbyteArray k) {
    
    unsigned char* c_p = NULL;
    unsigned long long* clen_p_p = NULL;
    unsigned char* m_p = NULL;
    unsigned char* ad_p = NULL;
    unsigned char* nsec_p = NULL;
    unsigned char* npub_p = NULL;
    unsigned char* k_p = NULL;
    jint ret = -1;
    
    if (c != NULL) {
        c_p = (unsigned char *) env->GetByteArrayElements(c, NULL);
        if (c_p == NULL) {
            goto cleanup;
        }
    }
    
    if (clen_p != NULL) {
        clen_p_p = (unsigned long long*) env->GetLongArrayElements(clen_p, NULL);
        if (clen_p_p == NULL) {
            goto cleanup;
        }
    }
    
    if (m != NULL) {
        m_p = (unsigned char *) env->GetByteArrayElements(m, NULL);
        if (m_p == NULL) {
            goto cleanup;
        }
    }
    
    if (ad != NULL) {
        ad_p = (unsigned char *) env->GetByteArrayElements(ad, NULL);
        if (ad_p == NULL) {
            goto cleanup;
        }
    }
    
    if (nsec != NULL) {
        nsec_p = (unsigned char *) env->GetByteArrayElements(nsec, NULL);
        if (nsec_p == NULL) {
            goto cleanup;
        }
    }
    
    if (npub != NULL) {
        npub_p = (unsigned char *) env->GetByteArrayElements(npub, NULL);
        if (npub_p == NULL) {
            goto cleanup;
        }
    }
    
    if (k != NULL) {
        k_p = (unsigned char *) env->GetByteArrayElements(k, NULL);
        if (k_p == NULL) {
            goto cleanup;
        }
    }

    ret = crypto_aead_chacha20poly1305_ietf_encrypt(
        c_p,
        clen_p_p,
        m_p,
        (unsigned long long) mlen,
        ad_p,
        (unsigned long long) adlen,
        nsec_p,
        npub_p,
        k_p
    );

cleanup:
    if (c_p != NULL) env->ReleaseByteArrayElements(c, (jbyte *)c_p, 0);
    if (clen_p_p != NULL) env->ReleaseLongArrayElements(clen_p, (jlong *)clen_p_p, 0);
    if (m_p != NULL) env->ReleaseByteArrayElements(m, (jbyte *) m_p, JNI_ABORT);
    if (ad_p != NULL) env->ReleaseByteArrayElements(ad, (jbyte *) ad_p, JNI_ABORT);
    if (nsec_p != NULL) env->ReleaseByteArrayElements(nsec, (jbyte *) nsec_p, JNI_ABORT);
    if (npub_p != NULL) env->ReleaseByteArrayElements(npub, (jbyte *) npub_p, JNI_ABORT);
    if (k_p != NULL) env->ReleaseByteArrayElements(k, (jbyte *) k_p, JNI_ABORT);

    return ret;
}

#ifdef __cplusplus
}
#endif