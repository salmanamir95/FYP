/**
@page threat_model Threat Model

The DataExSys security framework is designed to operate in a zero-trust ad-hoc environment where nodes cannot be assumed to be well-behaved. The protocol is built to be resilient against the following specific, common attacks in MANETs and PANETs.

### 1. Sybil Attack

*   **Description**: An attacker subverts the network's reputation system by creating a large number of pseudonymous identities (fake nodes). These fake nodes can be used to out-vote honest nodes in consensus protocols, unfairly boost the reputation of a malicious node, or mount other coordinated attacks.
*   **Impact**: Compromises the integrity of trust and consensus mechanisms, potentially leading to network control by the attacker.

### 2. Blackhole Attack

*   **Description**: A malicious node advertises itself as having the shortest or most optimal path to a destination during the route discovery phase. Once it is included in the route, it proceeds to silently drop all packets that are routed through it, effectively creating a "black hole" in the network.
*   **Impact**: Causes denial of service, data loss, and complete disruption of communication between affected nodes.

### 3. Wormhole Attack

*   **Description**: Two or more malicious nodes collaborate by creating a low-latency, out-of-band tunnel between them. They advertise this tunnel as a very short and efficient route. Honest nodes are tricked into routing their packets through the wormhole, allowing the attackers to intercept, modify, or drop all traffic passing through it.
*   **Impact**: Enables man-in-the-middle attacks, selective packet dropping, and can severely distort the network's perception of its own topology.

### 4. Replay Attack

*   **Description**: An attacker captures legitimate data or control packets (e.g., a route request or a data transmission) and re-transmits them later. This can be done to impersonate a node, disrupt routing tables, or consume network resources.
*   **Impact**: Can lead to network congestion, incorrect routing, and denial of service. Without proper sequencing and freshness checks, replayed packets can be indistinguishable from valid ones.

*/