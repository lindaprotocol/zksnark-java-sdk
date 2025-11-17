# ZkSNARK Java SDK

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