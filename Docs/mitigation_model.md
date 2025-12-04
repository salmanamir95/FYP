/**
@page mitigation_model Attack Mitigation Model

The DataExSys protocol employs a multi-faceted defense strategy where specific architectural components are designed to counter the threats outlined in the @ref threat_model.

### 1. Mitigating Sybil Attacks

*   **Mechanism**: The **`PKCertChain`'s Hybrid Consensus Model**.
*   **How it Works**: To register on the network, a new node must overcome two barriers:
    1.  **Lightweight Proof-of-Work**: The node must expend computational resources to solve a hash challenge. This makes creating a large number of fake identities computationally expensive and impractical.
    2.  **Density-Aware Quorum**: The node must be vouched for by a minimum number of existing, trusted nodes. This social validation layer prevents an unknown entity from joining without community approval.
*   **Result**: Sybil nodes are filtered out at the registration phase.

### 2. Mitigating Blackhole Attacks

*   **Mechanism**: **`LocalTrustDiaries` and the `RouteLogChain`**.
*   **How it Works**: Each node monitors the success of interactions with its neighbors. If a node (the suspected blackhole) consistently fails to forward packets, its neighbors will record negative events (`NAcks`) in their `LocalTrustDiaries`. This causes the node's Bayesian trust score to drop rapidly. During the next route discovery, the `RouteLogChain`'s path selection algorithm will heavily penalize or completely avoid routes that include this low-trust node.
*   **Result**: Blackhole nodes are quickly identified by their behavior and isolated from the network's routing paths.

### 3. Mitigating Wormhole Attacks

*   **Mechanism**: **Rolling Signatures** in the `RouteLogChain`.
*   **How it Works**: When a packet is forwarded, each intermediate node signs the *entire* packet received from the previous node, including the previous signature. This creates a verifiable, chained cryptographic proof of the actual path taken. A wormhole creates a discontinuity in this chain (a hop is hidden), which is immediately detectable by the destination node during verification.
*   **Result**: Packets attempting to traverse a wormhole are identified as invalid and dropped, rendering the attack ineffective.

### 4. Mitigating Replay Attacks

*   **Mechanism**: **Transaction Logging and Timestamps** in the `RouteLogChain`.
*   **How it Works**: Every significant packet transmission is logged as a unique transaction in the `RouteLogChain`, which includes a timestamp. When a node receives a packet, it can check the blockchain to see if an identical transaction has already been processed.
*   **Result**: Replayed packets are identified as duplicates and are discarded, preventing them from disrupting the network.

*/