package org.linda.common.zksnark;

class NativeLoader {
    static void loadLibrary(String libraryName) {
        try {
            System.loadLibrary(libraryName);
        } catch (UnsatisfiedLinkError e) {
            try {
                // Try loading from system path
                System.loadLibrary(libraryName);
            } catch (UnsatisfiedLinkError e2) {
                System.err.println("Failed to load native library: " + libraryName);
                e2.printStackTrace();
            }
        }
    }
}