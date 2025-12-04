/**
@page developer_guide Developer Guide & SDK Notes

This guide provides practical instructions and notes for developers working with the cryptographic primitives in the DataExSys project. It covers the command-line workflow for key generation and the critical distinction between CLI tools and library-based implementation.

@section workflow_sec Core Cryptographic Workflow

The fundamental workflow for a node joining the network and communicating involves key generation, certificate creation, and message signing.

### 1. Key Generation (Ed25519)

Each node must first generate its own Ed25519 key pair (private and public key). This is the foundation of its identity.

@code{.sh}
# Generate a new Ed25519 private key
openssl genpkey -algorithm Ed25519 -out node_private.pem

# Extract the public key from the private key
openssl pkey -in node_private.pem -pubout -out node_public.pem
@endcode

- The **private key** (`node_private.pem`) must be kept secret. It is used to sign messages and prove identity.
- The **public key** (`node_public.pem`) is shared openly. It is used by other nodes to verify signatures.

### 2. Certificate Creation

To register on the `PKCertChain`, the node must create a self-signed X.509 certificate. This certificate binds its public key to its identity.

@code{.sh}
openssl req -new -x509 -key node_private.pem -out node_cert.pem -days 365
@endcode

This certificate is then broadcast to the network for validation and inclusion in the `PKCertChain`.

@section signing_verification_sec Message Signing and Verification

@subsection signing_imp_sec Important Limitation of OpenSSL CLI

The `openssl` command-line tool **cannot be used to sign or verify arbitrary data** (e.g., a message string) with an Ed25519 key. The CLI is only suitable for key/certificate management.

All signing and verification operations **must be done programmatically** using a cryptographic library. Since this project links against OpenSSL's `libcrypto`, you will use its C++ API to perform these actions.

@subsection signing_logic_sec Programmatic Logic

1.  **To Sign a Message**:
    - Load the private key (`EVP_PKEY`) from `node_private.pem`.
    - Create a signing context (`EVP_MD_CTX`).
    - Use `EVP_DigestSign(...)` with the message data to produce a 64-byte binary signature.

2.  **To Verify a Signature**:
    - Load the public key (`EVP_PKEY`) from `node_public.pem`.
    - Create a verification context (`EVP_MD_CTX`).
    - Use `EVP_DigestVerify(...)` with the original message, the signature, and the public key. The function will return `1` for success or `0` for failure.

@note Raw Ed25519 signatures are 64-byte binary data. If they need to be stored or transmitted in a text-based format (like in a log file or JSON), they should be encoded using Base64 or Hex. Remember to decode them back to binary before performing verification.

*/