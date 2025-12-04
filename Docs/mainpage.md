/**
@mainpage DataExSys SDK Documentation

@section intro_sec Introduction

Welcome to the developer documentation for the **DataExSys SDK**. This SDK provides the necessary tools to build applications that can securely participate in the DataExSys decentralized network.

The core of the system is built around a decentralized identity ledger (`PKCertChain`) and modern, efficient cryptography (`Ed25519`) to ensure data integrity and authenticity.

@section getting_started_sec Getting Started

To begin using the SDK, you should familiarize yourself with the core concepts:

- **Node Identity**: How nodes generate keys and certificates.
- **Signing & Verification**: The process of signing data with a private key and verifying it with a public key.
- **Blockchain Interaction**: How to register a node's identity on the blockchain.

@section modules_sec Core Modules

The SDK is organized into several key modules:
- **Security**: Provides cryptographic primitives for signing, verification, and key management.
- **Blockchain**: Manages the `PKCertChain` and node identities.
- **Consensus**: The underlying algorithm for network agreement.

*/