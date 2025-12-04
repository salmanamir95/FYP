/**
@page architecture System Architecture

The DataExSys protocol is built on a modular, multi-layer architecture designed to separate concerns and optimize for security and performance in a decentralized environment.

## System Decomposition

The system is composed of three primary logical components:

1.  **The Security Framework**: The core of the system, comprising the multi-layer blockchain and the trust management model.
2.  **The Routing Engine**: An enhanced DSR protocol that leverages the security framework to make trust-aware routing decisions.
3.  **The Application Layer**: The user-facing application that performs data exchange.

## The Multi-Layer Blockchain

Instead of a single, monolithic blockchain, DataExSys uses a specialized, multi-layer design to handle different tasks efficiently.

### 1. PKCertChain (Public Key Certificate Chain)

This layer is the foundation of trust and identity in the network.

*   **Purpose**: To manage node identity, registration, and certificate lifecycle in a decentralized manner. It serves as a distributed Public Key Infrastructure (PKI).
*   **Consensus**: New nodes are admitted via a hybrid consensus mechanism:
    1.  **Lightweight Proof-of-Work**: The new node must solve a simple hash challenge to prevent low-effort Sybil attacks.
    2.  **Density-Aware Quorum**: Existing trusted nodes "vouch" for the new node. The number of vouches required (`MinThreshold`) adapts based on network density, making the system resilient and scalable.
*   **Function**: Stores immutable records of `(NodeID, PublicKey, Certificate, Status)`.

### 2. RouteLogChain (Route Log Chain)

This layer provides an auditable and tamper-proof record of network activity.

*   **Purpose**: To log significant routing events, such as path discoveries and data packet transmissions.
*   **Consensus**: Path selection is based on a multi-metric score calculated by the destination node, considering trust, latency, and hops.
*   **Function**: Stores records of routing decisions and packet metadata. This log is crucial for detecting Blackhole and Replay attacks. The use of **Rolling Signatures**, where each intermediate node signs over the previous node's signature, makes the path immutable and prevents Wormhole attacks.

### 3. Meta-Blockchain (Dispatcher)

This is a logical dispatcher that directs incoming transactions to the appropriate chain (`PKCertChain` or `RouteLogChain`), ensuring a clean separation of concerns.

## Local Trust Diaries

Each node maintains a `LocalTrustDiary` for its neighbors.

*   **Purpose**: To maintain a dynamic, probabilistic trust score for every other node it interacts with.
*   **Mechanism**: It uses a **Bayesian (Beta-Bernoulli) model**. The trust score is updated based on positive (`Acks`) and negative (`NAcks`) interactions. This allows trust to be built over time and enables rapid identification of malicious nodes (e.g., Blackhole nodes that consistently drop packets).
*   **Integration**: The trust scores from the diary are used as a key metric in the `RouteLogChain`'s path selection algorithm, ensuring that the system prefers routes through more trustworthy nodes.

*/