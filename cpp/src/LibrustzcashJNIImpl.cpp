//
// Created by ruipeng on 6/5/19.
//

#include "org_linda_common_zksnark_Librustzcash_LibrustzcashJNI.h"
#include "librustzcash.h"
#include <iostream>

jboolean bool2jboolean(bool b) {
    if (b) {
        return JNI_TRUE;
    } else {
        return JNI_FALSE;
    }
}

/*
 * Matt
 */

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashInitZksnarkParams
 * Signature: ([BILjava/lang/String;[BILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashInitZksnarkParams
    (JNIEnv * env, jobject, jstring spend_path, jstring spend_hash, jstring output_path, jstring output_hash) {
    const char* sp = env->GetStringUTFChars(spend_path, nullptr);
    const char* sh = env->GetStringUTFChars(spend_hash, nullptr);
    const char* op = env->GetStringUTFChars(output_path, nullptr);
    const char* oh = env->GetStringUTFChars(output_hash, nullptr);
    
    if (sp == NULL || sh == NULL || op == NULL || oh == NULL) {
        if (sp) env->ReleaseStringUTFChars(spend_path, sp);
        if (sh) env->ReleaseStringUTFChars(spend_hash, sh);
        if (op) env->ReleaseStringUTFChars(output_path, op);
        if (oh) env->ReleaseStringUTFChars(output_hash, oh);
        return;
    }
    
    librustzcash_init_zksnark_params(
        (const unsigned char*)sp, (size_t)env->GetStringLength(spend_path), 
        sh, 
        (const unsigned char*)op, (size_t)env->GetStringLength(output_path), 
        oh
    );
    
    env->ReleaseStringUTFChars(spend_path, sp);
    env->ReleaseStringUTFChars(spend_hash, sh);
    env->ReleaseStringUTFChars(output_path, op);
    env->ReleaseStringUTFChars(output_hash, oh);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashZip32XskMaster
 * Signature: ([BI[B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashZip32XskMaster
  (JNIEnv * env, jobject, jbyteArray seed, jint seedlen, jbyteArray xsk_master) {
    const unsigned char * s = (const unsigned char *)env->GetByteArrayElements(seed, nullptr);
    unsigned char * x = (unsigned char *)env->GetByteArrayElements(xsk_master, nullptr);
    
    if (s == NULL || x == NULL) {
        if (s) env->ReleaseByteArrayElements(seed, (jbyte*)s, JNI_ABORT);
        if (x) env->ReleaseByteArrayElements(xsk_master, (jbyte*)x, JNI_ABORT);
        return;
    }
    
    librustzcash_zip32_xsk_master(s, (size_t)seedlen, x);
    env->ReleaseByteArrayElements(seed, (jbyte*)s, JNI_ABORT);
    env->ReleaseByteArrayElements(xsk_master, (jbyte*)x, 0);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashZip32XskDerive
 * Signature: ([BI[B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashZip32XskDerive
  (JNIEnv * env, jobject, jbyteArray xsk_parent, jint i, jbyteArray xsk_i) {
    const unsigned char * xp = (const unsigned char *)env->GetByteArrayElements(xsk_parent, nullptr);
    unsigned char * xi = (unsigned char *)env->GetByteArrayElements(xsk_i, nullptr);
    
    if (xp == NULL || xi == NULL) {
        if (xp) env->ReleaseByteArrayElements(xsk_parent, (jbyte*)xp, JNI_ABORT);
        if (xi) env->ReleaseByteArrayElements(xsk_i, (jbyte*)xi, JNI_ABORT);
        return;
    }
    
    librustzcash_zip32_xsk_derive(xp, (uint32_t)i, xi);
    env->ReleaseByteArrayElements(xsk_parent, (jbyte*)xp, JNI_ABORT);
    env->ReleaseByteArrayElements(xsk_i, (jbyte*)xi, 0);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashZip32XfvkAddress
 * Signature: ([B[B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashZip32XfvkAddress
  (JNIEnv * env, jobject, jbyteArray xfvk, jbyteArray j, jbyteArray j_ret, jbyteArray addr_ret) {
    const unsigned char * x = (const unsigned char *)env->GetByteArrayElements(xfvk, nullptr);
    const unsigned char * jPoint = (const unsigned char *)env->GetByteArrayElements(j, nullptr);
    unsigned char * jr = (unsigned char *)env->GetByteArrayElements(j_ret, nullptr);
    unsigned char * a = (unsigned char *)env->GetByteArrayElements(addr_ret, nullptr);
    
    if (x == NULL || jPoint == NULL || jr == NULL || a == NULL) {
        if (x) env->ReleaseByteArrayElements(xfvk, (jbyte*)x, JNI_ABORT);
        if (jPoint) env->ReleaseByteArrayElements(j, (jbyte*)jPoint, JNI_ABORT);
        if (jr) env->ReleaseByteArrayElements(j_ret, (jbyte*)jr, JNI_ABORT);
        if (a) env->ReleaseByteArrayElements(addr_ret, (jbyte*)a, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_zip32_xfvk_address(x, jPoint, jr, a));
    
    env->ReleaseByteArrayElements(xfvk, (jbyte*)x, JNI_ABORT);
    env->ReleaseByteArrayElements(j, (jbyte*)jPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(j_ret, (jbyte*)jr, 0);
    env->ReleaseByteArrayElements(addr_ret, (jbyte*)a, 0);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashAskToAk
 * Signature: ([B[B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashAskToAk
  (JNIEnv * env, jobject, jbyteArray ask, jbyteArray result) {
    const unsigned char * a = (const unsigned char *)env->GetByteArrayElements(ask, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (a == NULL || r == NULL) {
        if (a) env->ReleaseByteArrayElements(ask, (jbyte*)a, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return;
    }
    
    librustzcash_ask_to_ak(a, r);
    env->ReleaseByteArrayElements(ask, (jbyte*)a, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingComputeNf
 * Signature: ([B[BJ[B[B[BJ[B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingComputeNf
  (JNIEnv * env, jobject, jbyteArray diversifier, jbyteArray pk_d, jlong value, jbyteArray r, jbyteArray ak, jbyteArray nk, jlong position, jbyteArray result) {
    const unsigned char * d = (const unsigned char *)env->GetByteArrayElements(diversifier, nullptr);
    const unsigned char * p = (const unsigned char *)env->GetByteArrayElements(pk_d, nullptr);
    const unsigned char * rPoint = (const unsigned char *)env->GetByteArrayElements(r, nullptr);
    const unsigned char * a = (const unsigned char *)env->GetByteArrayElements(ak, nullptr);
    const unsigned char * n = (const unsigned char *)env->GetByteArrayElements(nk, nullptr);
    unsigned char * rs = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (d == NULL || p == NULL || rPoint == NULL || a == NULL || n == NULL || rs == NULL) {
        if (d) env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
        if (p) env->ReleaseByteArrayElements(pk_d, (jbyte*)p, JNI_ABORT);
        if (rPoint) env->ReleaseByteArrayElements(r, (jbyte*)rPoint, JNI_ABORT);
        if (a) env->ReleaseByteArrayElements(ak, (jbyte*)a, JNI_ABORT);
        if (n) env->ReleaseByteArrayElements(nk, (jbyte*)n, JNI_ABORT);
        if (rs) env->ReleaseByteArrayElements(result, (jbyte*)rs, JNI_ABORT);
        return;
    }
    
    librustzcash_sapling_compute_nf(d, p, (uint64_t)value, rPoint, a, n, (uint64_t)position, rs);
    
    env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
    env->ReleaseByteArrayElements(pk_d, (jbyte*)p, JNI_ABORT);
    env->ReleaseByteArrayElements(r, (jbyte*)rPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(ak, (jbyte*)a, JNI_ABORT);
    env->ReleaseByteArrayElements(nk, (jbyte*)n, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)rs, 0);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashNskToNk
 * Signature: ([B[B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashNskToNk
  (JNIEnv * env, jobject, jbyteArray nsk, jbyteArray result) {
    const unsigned char * n = (const unsigned char *)env->GetByteArrayElements(nsk, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (n == NULL || r == NULL) {
        if (n) env->ReleaseByteArrayElements(nsk, (jbyte*)n, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return;
    }
    
    librustzcash_nsk_to_nk(n, r);
    env->ReleaseByteArrayElements(nsk, (jbyte*)n, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingGenerateR
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingGenerateR
  (JNIEnv * env, jobject, jbyteArray result) {
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (r == NULL) {
        return;
    }
    
    librustzcash_sapling_generate_r(r);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingKaDerivepublic
 * Signature: ([B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingKaDerivepublic
  (JNIEnv * env, jobject, jbyteArray diversifier, jbyteArray esk, jbyteArray result) {
    const unsigned char * d = (const unsigned char *)env->GetByteArrayElements(diversifier, nullptr);
    const unsigned char * e = (const unsigned char *)env->GetByteArrayElements(esk, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (d == NULL || e == NULL || r == NULL) {
        if (d) env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
        if (e) env->ReleaseByteArrayElements(esk, (jbyte*)e, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result_bool = bool2jboolean(librustzcash_sapling_ka_derivepublic(d, e, r));
    
    env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
    env->ReleaseByteArrayElements(esk, (jbyte*)e, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
    
    return result_bool;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashCrhIvk
 * Signature: ([B[B[B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashCrhIvk
  (JNIEnv *env, jobject, jbyteArray ak, jbyteArray nk, jbyteArray result) {
    const unsigned char * a = (const unsigned char *)env->GetByteArrayElements(ak, nullptr);
    const unsigned char * n = (const unsigned char *)env->GetByteArrayElements(nk, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (a == NULL || n == NULL || r == NULL) {
        if (a) env->ReleaseByteArrayElements(ak, (jbyte*)a, JNI_ABORT);
        if (n) env->ReleaseByteArrayElements(nk, (jbyte*)n, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return;
    }
    
    librustzcash_crh_ivk(a, n, r);
    env->ReleaseByteArrayElements(ak, (jbyte*)a, JNI_ABORT);
    env->ReleaseByteArrayElements(nk, (jbyte*)n, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
}

/*
 * Kiven
 */

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingKaAgree
 * Signature: ([B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingKaAgree
  (JNIEnv * env, jobject, jbyteArray p, jbyteArray sk, jbyteArray result) {
    const unsigned char * pPoint = (const unsigned char *)env->GetByteArrayElements(p, nullptr);
    const unsigned char * skPoint = (const unsigned char *)env->GetByteArrayElements(sk, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (pPoint == NULL || skPoint == NULL || r == NULL) {
        if (pPoint) env->ReleaseByteArrayElements(p, (jbyte*)pPoint, JNI_ABORT);
        if (skPoint) env->ReleaseByteArrayElements(sk, (jbyte*)skPoint, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result_bool = bool2jboolean(librustzcash_sapling_ka_agree(pPoint, skPoint, r));
    
    env->ReleaseByteArrayElements(p, (jbyte*)pPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(sk, (jbyte*)skPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
    
    return result_bool;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashCheckDiversifier
 * Signature: ([B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashCheckDiversifier
  (JNIEnv * env, jobject, jbyteArray diversifier) {
    const unsigned char * d = (const unsigned char *)env->GetByteArrayElements(diversifier, nullptr);
    
    if (d == NULL) {
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_check_diversifier(d));
    env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashIvkToPkd
 * Signature: ([B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashIvkToPkd
  (JNIEnv * env, jobject, jbyteArray ivk, jbyteArray diversifier, jbyteArray result) {
    const unsigned char * i = (const unsigned char *)env->GetByteArrayElements(ivk, nullptr);
    const unsigned char * d = (const unsigned char *)env->GetByteArrayElements(diversifier, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (i == NULL || d == NULL || r == NULL) {
        if (i) env->ReleaseByteArrayElements(ivk, (jbyte*)i, JNI_ABORT);
        if (d) env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result_bool = bool2jboolean(librustzcash_ivk_to_pkd(i, d, r));
    
    env->ReleaseByteArrayElements(ivk, (jbyte*)i, JNI_ABORT);
    env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
    
    return result_bool;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingComputeCm
 * Signature: ([B[BJ[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingComputeCm
  (JNIEnv * env, jobject, jbyteArray diversifier, jbyteArray pk_d, jlong value, jbyteArray r, jbyteArray result) {
    const unsigned char * d = (const unsigned char *)env->GetByteArrayElements(diversifier, nullptr);
    const unsigned char * p = (const unsigned char *)env->GetByteArrayElements(pk_d, nullptr);
    const unsigned char * rPoint = (const unsigned char *)env->GetByteArrayElements(r, nullptr);
    unsigned char * rs = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (d == NULL || p == NULL || rPoint == NULL || rs == NULL) {
        if (d) env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
        if (p) env->ReleaseByteArrayElements(pk_d, (jbyte*)p, JNI_ABORT);
        if (rPoint) env->ReleaseByteArrayElements(r, (jbyte*)rPoint, JNI_ABORT);
        if (rs) env->ReleaseByteArrayElements(result, (jbyte*)rs, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result_bool = bool2jboolean(librustzcash_sapling_compute_cm(d, p, (uint64_t)value, rPoint, rs));
    
    env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
    env->ReleaseByteArrayElements(pk_d, (jbyte*)p, JNI_ABORT);
    env->ReleaseByteArrayElements(r, (jbyte*)rPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)rs, 0);
    
    return result_bool;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingProvingCtxInit
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingProvingCtxInit
  (JNIEnv *, jobject) {
    return (jlong)librustzcash_sapling_proving_ctx_init();
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingSpendProof
 * Signature: (J[B[B[B[B[BJ[B[B[B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingSpendProof
  (JNIEnv * env, jobject, jlong ctx, jbyteArray ak, jbyteArray nsk, jbyteArray diversifier, jbyteArray rcm, jbyteArray ar,
  jlong value, jbyteArray anchor, jbyteArray witness, jbyteArray cv, jbyteArray rk, jbyteArray zkproof) {
    const unsigned char * akPoint = (const unsigned char *)env->GetByteArrayElements(ak, nullptr);
    const unsigned char * nskPoint = (const unsigned char *)env->GetByteArrayElements(nsk, nullptr);
    const unsigned char * dPoint = (const unsigned char *)env->GetByteArrayElements(diversifier, nullptr);
    const unsigned char * rcmPoint = (const unsigned char *)env->GetByteArrayElements(rcm, nullptr);
    const unsigned char * arPoint = (const unsigned char *)env->GetByteArrayElements(ar, nullptr);
    const unsigned char * anchorPoint = (const unsigned char *)env->GetByteArrayElements(anchor, nullptr);
    const unsigned char * wPoint = (const unsigned char *)env->GetByteArrayElements(witness, nullptr);
    unsigned char * cvPoint = (unsigned char *)env->GetByteArrayElements(cv, nullptr);
    unsigned char * rkPoint = (unsigned char *)env->GetByteArrayElements(rk, nullptr);
    unsigned char * zPoint = (unsigned char *)env->GetByteArrayElements(zkproof, nullptr);
    
    if (akPoint == NULL || nskPoint == NULL || dPoint == NULL || rcmPoint == NULL || arPoint == NULL || 
        anchorPoint == NULL || wPoint == NULL || cvPoint == NULL || rkPoint == NULL || zPoint == NULL) {
        if (akPoint) env->ReleaseByteArrayElements(ak, (jbyte*)akPoint, JNI_ABORT);
        if (nskPoint) env->ReleaseByteArrayElements(nsk, (jbyte*)nskPoint, JNI_ABORT);
        if (dPoint) env->ReleaseByteArrayElements(diversifier, (jbyte*)dPoint, JNI_ABORT);
        if (rcmPoint) env->ReleaseByteArrayElements(rcm, (jbyte*)rcmPoint, JNI_ABORT);
        if (arPoint) env->ReleaseByteArrayElements(ar, (jbyte*)arPoint, JNI_ABORT);
        if (anchorPoint) env->ReleaseByteArrayElements(anchor, (jbyte*)anchorPoint, JNI_ABORT);
        if (wPoint) env->ReleaseByteArrayElements(witness, (jbyte*)wPoint, JNI_ABORT);
        if (cvPoint) env->ReleaseByteArrayElements(cv, (jbyte*)cvPoint, JNI_ABORT);
        if (rkPoint) env->ReleaseByteArrayElements(rk, (jbyte*)rkPoint, JNI_ABORT);
        if (zPoint) env->ReleaseByteArrayElements(zkproof, (jbyte*)zPoint, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_sapling_spend_proof(
        (void *)ctx, akPoint, nskPoint, dPoint, rcmPoint, arPoint,
        (uint64_t)value, anchorPoint, wPoint, cvPoint, rkPoint, zPoint
    ));
    
    env->ReleaseByteArrayElements(ak, (jbyte*)akPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(nsk, (jbyte*)nskPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(diversifier, (jbyte*)dPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(rcm, (jbyte*)rcmPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(ar, (jbyte*)arPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(anchor, (jbyte*)anchorPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(witness, (jbyte*)wPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(cv, (jbyte*)cvPoint, 0);
    env->ReleaseByteArrayElements(rk, (jbyte*)rkPoint, 0);
    env->ReleaseByteArrayElements(zkproof, (jbyte*)zPoint, 0);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingOutputProof
 * Signature: (J[B[B[B[BJ[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingOutputProof
  (JNIEnv * env, jobject, jlong ctx, jbyteArray esk, jbyteArray diversifier, jbyteArray pk_d, jbyteArray rcm, jlong value, jbyteArray cv, jbyteArray zkproof) {
    const unsigned char * e = (const unsigned char *)env->GetByteArrayElements(esk, nullptr);
    const unsigned char * d = (const unsigned char *)env->GetByteArrayElements(diversifier, nullptr);
    const unsigned char * p = (const unsigned char *)env->GetByteArrayElements(pk_d, nullptr);
    const unsigned char * r = (const unsigned char *)env->GetByteArrayElements(rcm, nullptr);
    unsigned char * c = (unsigned char *)env->GetByteArrayElements(cv, nullptr);
    unsigned char * z = (unsigned char *)env->GetByteArrayElements(zkproof, nullptr);
    
    if (e == NULL || d == NULL || p == NULL || r == NULL || c == NULL || z == NULL) {
        if (e) env->ReleaseByteArrayElements(esk, (jbyte*)e, JNI_ABORT);
        if (d) env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
        if (p) env->ReleaseByteArrayElements(pk_d, (jbyte*)p, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(rcm, (jbyte*)r, JNI_ABORT);
        if (c) env->ReleaseByteArrayElements(cv, (jbyte*)c, JNI_ABORT);
        if (z) env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_sapling_output_proof(
        (void *)ctx, e, d, p, r, (uint64_t)value, c, z
    ));
    
    env->ReleaseByteArrayElements(esk, (jbyte*)e, JNI_ABORT);
    env->ReleaseByteArrayElements(diversifier, (jbyte*)d, JNI_ABORT);
    env->ReleaseByteArrayElements(pk_d, (jbyte*)p, JNI_ABORT);
    env->ReleaseByteArrayElements(rcm, (jbyte*)r, JNI_ABORT);
    env->ReleaseByteArrayElements(cv, (jbyte*)c, 0);
    env->ReleaseByteArrayElements(zkproof, (jbyte*)z, 0);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingSpendSig
 * Signature: ([B[B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingSpendSig
  (JNIEnv * env, jobject, jbyteArray ask, jbyteArray ar, jbyteArray sighash, jbyteArray result) {
    const unsigned char * askPoint = (const unsigned char *)env->GetByteArrayElements(ask, nullptr);
    const unsigned char * arPoint = (const unsigned char *)env->GetByteArrayElements(ar, nullptr);
    const unsigned char * s = (const unsigned char *)env->GetByteArrayElements(sighash, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (askPoint == NULL || arPoint == NULL || s == NULL || r == NULL) {
        if (askPoint) env->ReleaseByteArrayElements(ask, (jbyte*)askPoint, JNI_ABORT);
        if (arPoint) env->ReleaseByteArrayElements(ar, (jbyte*)arPoint, JNI_ABORT);
        if (s) env->ReleaseByteArrayElements(sighash, (jbyte*)s, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result_bool = bool2jboolean(librustzcash_sapling_spend_sig(askPoint, arPoint, s, r));
    
    env->ReleaseByteArrayElements(ask, (jbyte*)askPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(ar, (jbyte*)arPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(sighash, (jbyte*)s, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
    
    return result_bool;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingBindingSig
 * Signature: (JJ[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingBindingSig
  (JNIEnv * env, jobject, jlong ctx, jlong valueBalance, jbyteArray sighash, jbyteArray result) {
    const unsigned char * s = (const unsigned char *)env->GetByteArrayElements(sighash, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (s == NULL || r == NULL) {
        if (s) env->ReleaseByteArrayElements(sighash, (jbyte*)s, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result_bool = bool2jboolean(librustzcash_sapling_binding_sig((void *)ctx, (int64_t)valueBalance, s, r));
    
    env->ReleaseByteArrayElements(sighash, (jbyte*)s, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
    
    return result_bool;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingProvingCtxFree
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingProvingCtxFree
  (JNIEnv *, jobject, jlong ctx) {
    librustzcash_sapling_proving_ctx_free((void *)ctx);
}

/*
 * Olenheim
 */

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingVerificationCtxInit
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingVerificationCtxInit
  (JNIEnv *, jobject) {
    return (jlong)librustzcash_sapling_verification_ctx_init();
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingCheckSpend
 * Signature: (J[B[B[B[B[B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingCheckSpend
  (JNIEnv * env, jobject, jlong ctx, jbyteArray cv, jbyteArray anchor, jbyteArray nullifier, jbyteArray rk, jbyteArray zkproof, jbyteArray spendAuthSig, jbyteArray sighashValue) {
    const unsigned char * c = (const unsigned char *)env->GetByteArrayElements(cv, nullptr);
    const unsigned char * a = (const unsigned char *)env->GetByteArrayElements(anchor, nullptr);
    const unsigned char * n = (const unsigned char *)env->GetByteArrayElements(nullifier, nullptr);
    const unsigned char * r = (const unsigned char *)env->GetByteArrayElements(rk, nullptr);
    const unsigned char * z = (const unsigned char *)env->GetByteArrayElements(zkproof, nullptr);
    const unsigned char * sp = (const unsigned char *)env->GetByteArrayElements(spendAuthSig, nullptr);
    const unsigned char * si = (const unsigned char *)env->GetByteArrayElements(sighashValue, nullptr);
    
    if (c == NULL || a == NULL || n == NULL || r == NULL || z == NULL || sp == NULL || si == NULL) {
        if (c) env->ReleaseByteArrayElements(cv, (jbyte*)c, JNI_ABORT);
        if (a) env->ReleaseByteArrayElements(anchor, (jbyte*)a, JNI_ABORT);
        if (n) env->ReleaseByteArrayElements(nullifier, (jbyte*)n, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(rk, (jbyte*)r, JNI_ABORT);
        if (z) env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
        if (sp) env->ReleaseByteArrayElements(spendAuthSig, (jbyte*)sp, JNI_ABORT);
        if (si) env->ReleaseByteArrayElements(sighashValue, (jbyte*)si, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_sapling_check_spend((void *)ctx, c, a, n, r, z, sp, si));
    
    env->ReleaseByteArrayElements(cv, (jbyte*)c, JNI_ABORT);
    env->ReleaseByteArrayElements(anchor, (jbyte*)a, JNI_ABORT);
    env->ReleaseByteArrayElements(nullifier, (jbyte*)n, JNI_ABORT);
    env->ReleaseByteArrayElements(rk, (jbyte*)r, JNI_ABORT);
    env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
    env->ReleaseByteArrayElements(spendAuthSig, (jbyte*)sp, JNI_ABORT);
    env->ReleaseByteArrayElements(sighashValue, (jbyte*)si, JNI_ABORT);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingCheckOutput
 * Signature: (J[B[B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingCheckOutput
  (JNIEnv *env, jobject, jlong ctx, jbyteArray cv, jbyteArray cm, jbyteArray ephemeralKey, jbyteArray zkproof) {
    const unsigned char * cvPoint = (const unsigned char *)env->GetByteArrayElements(cv, nullptr);
    const unsigned char * cmPoint = (const unsigned char *)env->GetByteArrayElements(cm, nullptr);
    const unsigned char * e = (const unsigned char *)env->GetByteArrayElements(ephemeralKey, nullptr);
    const unsigned char * z = (const unsigned char *)env->GetByteArrayElements(zkproof, nullptr);
    
    if (cvPoint == NULL || cmPoint == NULL || e == NULL || z == NULL) {
        if (cvPoint) env->ReleaseByteArrayElements(cv, (jbyte*)cvPoint, JNI_ABORT);
        if (cmPoint) env->ReleaseByteArrayElements(cm, (jbyte*)cmPoint, JNI_ABORT);
        if (e) env->ReleaseByteArrayElements(ephemeralKey, (jbyte*)e, JNI_ABORT);
        if (z) env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_sapling_check_output((void *)ctx, cvPoint, cmPoint, e, z));
    
    env->ReleaseByteArrayElements(cv, (jbyte*)cvPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(cm, (jbyte*)cmPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(ephemeralKey, (jbyte*)e, JNI_ABORT);
    env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingFinalCheck
 * Signature: (JJ[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingFinalCheck
  (JNIEnv * env, jobject, jlong ctx, jlong valueBalance, jbyteArray bindingSig, jbyteArray sighashValue) {
    const unsigned char * b = (const unsigned char *)env->GetByteArrayElements(bindingSig, nullptr);
    const unsigned char * s = (const unsigned char *)env->GetByteArrayElements(sighashValue, nullptr);
    
    if (b == NULL || s == NULL) {
        if (b) env->ReleaseByteArrayElements(bindingSig, (jbyte*)b, JNI_ABORT);
        if (s) env->ReleaseByteArrayElements(sighashValue, (jbyte*)s, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_sapling_final_check((void *)ctx, (int64_t)valueBalance, b, s));
    
    env->ReleaseByteArrayElements(bindingSig, (jbyte*)b, JNI_ABORT);
    env->ReleaseByteArrayElements(sighashValue, (jbyte*)s, JNI_ABORT);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingCheckSpendNew
 * Signature: ([B[B[B[B[B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingCheckSpendNew
  (JNIEnv * env, jobject, jbyteArray cv, jbyteArray anchor, jbyteArray nullifier, jbyteArray rk, jbyteArray zkproof, jbyteArray spendAuthSig, jbyteArray sighashValue) {
    const unsigned char * c = (const unsigned char *)env->GetByteArrayElements(cv, nullptr);
    const unsigned char * a = (const unsigned char *)env->GetByteArrayElements(anchor, nullptr);
    const unsigned char * n = (const unsigned char *)env->GetByteArrayElements(nullifier, nullptr);
    const unsigned char * r = (const unsigned char *)env->GetByteArrayElements(rk, nullptr);
    const unsigned char * z = (const unsigned char *)env->GetByteArrayElements(zkproof, nullptr);
    const unsigned char * sp = (const unsigned char *)env->GetByteArrayElements(spendAuthSig, nullptr);
    const unsigned char * si = (const unsigned char *)env->GetByteArrayElements(sighashValue, nullptr);
    
    if (c == NULL || a == NULL || n == NULL || r == NULL || z == NULL || sp == NULL || si == NULL) {
        if (c) env->ReleaseByteArrayElements(cv, (jbyte*)c, JNI_ABORT);
        if (a) env->ReleaseByteArrayElements(anchor, (jbyte*)a, JNI_ABORT);
        if (n) env->ReleaseByteArrayElements(nullifier, (jbyte*)n, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(rk, (jbyte*)r, JNI_ABORT);
        if (z) env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
        if (sp) env->ReleaseByteArrayElements(spendAuthSig, (jbyte*)sp, JNI_ABORT);
        if (si) env->ReleaseByteArrayElements(sighashValue, (jbyte*)si, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_sapling_check_spend_new(c, a, n, r, z, sp, si));
    
    env->ReleaseByteArrayElements(cv, (jbyte*)c, JNI_ABORT);
    env->ReleaseByteArrayElements(anchor, (jbyte*)a, JNI_ABORT);
    env->ReleaseByteArrayElements(nullifier, (jbyte*)n, JNI_ABORT);
    env->ReleaseByteArrayElements(rk, (jbyte*)r, JNI_ABORT);
    env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
    env->ReleaseByteArrayElements(spendAuthSig, (jbyte*)sp, JNI_ABORT);
    env->ReleaseByteArrayElements(sighashValue, (jbyte*)si, JNI_ABORT);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingCheckOutputNew
 * Signature: ([B[B[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingCheckOutputNew
  (JNIEnv *env, jobject, jbyteArray cv, jbyteArray cm, jbyteArray ephemeralKey, jbyteArray zkproof) {
    const unsigned char * cvPoint = (const unsigned char *)env->GetByteArrayElements(cv, nullptr);
    const unsigned char * cmPoint = (const unsigned char *)env->GetByteArrayElements(cm, nullptr);
    const unsigned char * e = (const unsigned char *)env->GetByteArrayElements(ephemeralKey, nullptr);
    const unsigned char * z = (const unsigned char *)env->GetByteArrayElements(zkproof, nullptr);
    
    if (cvPoint == NULL || cmPoint == NULL || e == NULL || z == NULL) {
        if (cvPoint) env->ReleaseByteArrayElements(cv, (jbyte*)cvPoint, JNI_ABORT);
        if (cmPoint) env->ReleaseByteArrayElements(cm, (jbyte*)cmPoint, JNI_ABORT);
        if (e) env->ReleaseByteArrayElements(ephemeralKey, (jbyte*)e, JNI_ABORT);
        if (z) env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
        return JNI_FALSE;
    }
    
    jboolean result = bool2jboolean(librustzcash_sapling_check_output_new(cvPoint, cmPoint, e, z));
    
    env->ReleaseByteArrayElements(cv, (jbyte*)cvPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(cm, (jbyte*)cmPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(ephemeralKey, (jbyte*)e, JNI_ABORT);
    env->ReleaseByteArrayElements(zkproof, (jbyte*)z, JNI_ABORT);
    
    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingFinalCheckNew
 * Signature: (J[B[B[BI[BI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingFinalCheckNew
  (JNIEnv * env, jobject, jlong valueBalance, jbyteArray bindingSig, jbyteArray sighashValue, jbyteArray spendCv, jint spendCvLen, jbyteArray outputCv, jint outputCvLen) {
    const unsigned char * b = (const unsigned char *)env->GetByteArrayElements(bindingSig, nullptr);
    const unsigned char * s = (const unsigned char *)env->GetByteArrayElements(sighashValue, nullptr);
    const unsigned char * scv = (const unsigned char *)env->GetByteArrayElements(spendCv, nullptr);
    const unsigned char * ocv = (const unsigned char *)env->GetByteArrayElements(outputCv, nullptr);

    if (b == NULL || s == NULL || scv == NULL || ocv == NULL) {
        if (b) env->ReleaseByteArrayElements(bindingSig, (jbyte*)b, JNI_ABORT);
        if (s) env->ReleaseByteArrayElements(sighashValue, (jbyte*)s, JNI_ABORT);
        if (scv) env->ReleaseByteArrayElements(spendCv, (jbyte*)scv, JNI_ABORT);
        if (ocv) env->ReleaseByteArrayElements(outputCv, (jbyte*)ocv, JNI_ABORT);
        return JNI_FALSE;
    }

    jboolean result = bool2jboolean(librustzcash_sapling_final_check_new(
        (int64_t)valueBalance, b, s, scv, (size_t)spendCvLen, ocv, (size_t)outputCvLen
    ));

    env->ReleaseByteArrayElements(bindingSig, (jbyte*)b, JNI_ABORT);
    env->ReleaseByteArrayElements(sighashValue, (jbyte*)s, JNI_ABORT);
    env->ReleaseByteArrayElements(spendCv, (jbyte*)scv, JNI_ABORT);
    env->ReleaseByteArrayElements(outputCv, (jbyte*)ocv, JNI_ABORT);

    return result;
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashSaplingVerificationCtxFree
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashSaplingVerificationCtxFree
  (JNIEnv *, jobject, jlong ctx) {
    librustzcash_sapling_verification_ctx_free((void *)ctx);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashMerkleHash
 * Signature: (I[B[B[B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashMerkleHash
  (JNIEnv *env, jobject, jint depth, jbyteArray a, jbyteArray b, jbyteArray result) {
    const unsigned char * aPoint = (const unsigned char *)env->GetByteArrayElements(a, nullptr);
    const unsigned char * bPoint = (const unsigned char *)env->GetByteArrayElements(b, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (aPoint == NULL || bPoint == NULL || r == NULL) {
        if (aPoint) env->ReleaseByteArrayElements(a, (jbyte*)aPoint, JNI_ABORT);
        if (bPoint) env->ReleaseByteArrayElements(b, (jbyte*)bPoint, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return;
    }
    
    librustzcash_merkle_hash((size_t)depth, aPoint, bPoint, r);
    env->ReleaseByteArrayElements(a, (jbyte*)aPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(b, (jbyte*)bPoint, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashTreeUncommitted
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashTreeUncommitted
  (JNIEnv *env, jobject, jbyteArray result) {
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (r == NULL) {
        return;
    }
    
    librustzcash_tree_uncommitted(r);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
}

/*
 * Class:     org_linda_common_zksnark_Librustzcash_LibrustzcashJNI
 * Method:    librustzcashToScalar
 * Signature: ([B[B)V
 */
JNIEXPORT void JNICALL Java_org_linda_common_zksnark_Librustzcash_00024LibrustzcashJNI_librustzcashToScalar
  (JNIEnv *env, jobject, jbyteArray input, jbyteArray result) {
    const unsigned char * i = (const unsigned char *)env->GetByteArrayElements(input, nullptr);
    unsigned char * r = (unsigned char *)env->GetByteArrayElements(result, nullptr);
    
    if (i == NULL || r == NULL) {
        if (i) env->ReleaseByteArrayElements(input, (jbyte*)i, JNI_ABORT);
        if (r) env->ReleaseByteArrayElements(result, (jbyte*)r, JNI_ABORT);
        return;
    }
    
    librustzcash_to_scalar(i, r);
    env->ReleaseByteArrayElements(input, (jbyte*)i, JNI_ABORT);
    env->ReleaseByteArrayElements(result, (jbyte*)r, 0);
}