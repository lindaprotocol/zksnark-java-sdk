# ZkSNARK Java SDK

[![Maven Central](https://img.shields.io/maven-central/v/io.github.lindaprotocol/zksnark-java-sdk.svg?label=Maven%20Central)](https://search.maven.org/search?q=g:%22io.github.lindaprotocol%22%20AND%20a:%22zksnark-java-sdk%22)


A Java SDK for zkSNARK operations with native bindings to libsodium and librustzcash.

# libzksnark
a zksnark jni library

# Pull source
```
$ git clone git@github.com:lindaprotocol/zksnark-java-sdk.git --recursive
```
OR
```
$ git clone git@github.com:lindaprotocol/zksnark-java-sdk.git
$ git submodule update --init --recursive
```
## Features

- Blake2b cryptographic hashing
- ChaCha20-Poly1305 authenticated encryption
- Zero-knowledge proof operations
- Cross-platform native library support

# Required

    cmake (version >= 3.10.2)

    cargo

    libtool

    automake

    mvn

    jdk8(need JAVA_HOME set)

    Rust toolchain (for native builds)

# for m1
```shell
 cd cpp && mkdir build && cd build
 CC=cc cmake ..
 make
```

## Installation

Add the dependency to your `pom.xml`:

```xml
<dependency>
    <groupId>org.linda</groupId>
    <artifactId>zksnark-java-sdk</artifactId>
    <version>1.0.0</version>
</dependency>
```

#Usage

```java
Libsodium libsodium = LibsodiumWrapper.getInstance();

// Blake2b hashing
byte[] out = new byte[32];
byte[] input = "Hello World".getBytes(StandardCharsets.UTF_8);
int result = libsodium.cryptoGenerichashBlake2BSaltPersonal(
    out, out.length, input, input.length,
    null, 0, null, null);
```

## Usage
#Libsodium Operations

```java
import org.linda.common.zksnark.Libsodium;
import org.linda.common.zksnark.LibsodiumWrapper;
import java.nio.charset.StandardCharsets;

public class Example {
    public static void main(String[] args) {
        Libsodium libsodium = LibsodiumWrapper.getInstance();

        // Blake2b hashing
        byte[] out = new byte[32];
        byte[] input = "Hello World".getBytes(StandardCharsets.UTF_8);
        int result = libsodium.cryptoGenerichashBlake2BSaltPersonal(
            out, out.length, input, input.length,
            null, 0, null, null);

        if (result == 0) {
            System.out.println("Hash computed successfully");
        }
    }
}
```
#Stream Hashing

```java
// For large data, use streaming interface
long state = libsodium.cryptoGenerichashBlake2BStateInit();
try {
    libsodium.cryptoGenerichashBlake2BInitSaltPersonal(state, null, 0, 32, null, null);

    // Process data in chunks
    libsodium.cryptoGenerichashBlake2BUpdate(state, chunk1, chunk1.length);
    libsodium.cryptoGenerichashBlake2BUpdate(state, chunk2, chunk2.length);

    byte[] finalHash = new byte[32];
    libsodium.cryptoGenerichashBlake2BFinal(state, finalHash, finalHash.length);
} finally {
    libsodium.cryptoGenerichashBlake2BStateFree(state);
}
```

# Build Steps

```sh
git clone https://github.com/lindaprotocol/zksnark-java-sdk
cd zksnark-java-sdk

# Build native libraries
cd cpp
mkdir build && cd build
CC=cc cmake -DJAVA_INCLUDE_PATH=$JAVA_HOME/include -DJAVA_INCLUDE_PATH2=$JAVA_HOME/include/linux -DJAVA_JVM_LIBRARY=$JAVA_HOME/lib/server/libjvm.so ..
make

# Build Java SDK
cd ../..
mvn clean install

```

#Platform Support

- The SDK includes pre-built native libraries for:

- Linux x86_64

- Linux AArch64

- macOS x86_64

- macOS AArch64 (Apple Silicon)

#License
This project is licensed under the Apache License 2.0 - see the LICENSE file for details.

```text

## Next Steps:

1. **Update the GPG key ID** in your `pom.xml` with the actual key ID
2. **Verify your Sonatype credentials** in `~/.m2/settings.xml`
3. **Create the README.md** with the content above
4. **Test the release process**:

```bash
# Clean build
mvn clean

# Test compilation and packaging
mvn package

# Deploy to Sonatype (this will actually publish)
mvn clean deploy -Prelease


### 4. Check Central Portal
Visit: https://central.sonatype.com/publishing/deployments
You should see your deployment there.

## What You've Accomplished:

-  **Fixed authentication issues** with Central Portal tokens
-  **Updated to new OSSRH Staging API** URLs  
-  **Successfully deployed** a complex JNI library with native dependencies
-  **Published to Maven Central** - the standard Java repository
-  **Created a reusable library** for the entire Java ecosystem

## Your Library Now Includes:

- **Main JAR**: `zksnark-java-sdk-1.0.0.jar`
- **Sources JAR**: `zksnark-java-sdk-1.0.0-sources.jar` 
- **Javadoc JAR**: `zksnark-java-sdk-1.0.0-javadoc.jar`
- **GPG Signatures** for all artifacts
- **OSGi metadata** with native library declarations
- **Multi-platform native library support** (Linux/macOS, x64/ARM64)

## For Future Releases:

When you're ready to release version 1.0.1:

```bash
# Update version in pom.xml, then:
mvn clean deploy -Prelease

```
```