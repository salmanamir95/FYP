## **Layer 1 – Physical (PHY Layer)**

**Module:** **RF Anomaly & Jamming Detector**

- **Purpose:** Detect physical-layer attacks such as jamming or unauthorized signal injections.
- **How:** Monitor signal strength, channel usage, and sudden interference patterns in kernel. Raise alerts to Layer 2/3.
- **Outcome:** Early detection of physical-layer threats before packets even reach the MAC layer.

---

## **Layer 2 – Data Link (MAC Layer)**

**Module:** **Secure Neighbor Authentication**

- **Purpose:** Ensure that all directly reachable nodes are legitimate.
- **How:** Add MAC-layer signatures to frames verified by the kernel crypto module (Layer 6).
- **Outcome:** Protects against Sybil and spoofed neighbor attacks, prevents malicious node participation at the link level.

---

## **Layer 3 – Network (Routing Layer)**

**Module:** **Blockchain-Verified Routing Guard**

- **Purpose:** Secure route discovery and maintenance in DSR.
- **How:** Integrate **RouteLog Chain** verification in kernel; only allow packet forwarding along authenticated, trust-weighted routes.
- **Outcome:** Prevents Blackhole/Wormhole attacks and tampering with routing tables.

---

## **Layer 4 – Transport Layer**

**Module:** **Trust-Aware Transport Enforcer**

- **Purpose:** Ensure that only trusted nodes participate in reliable end-to-end delivery.
- **How:** Kernel module monitors transport flows and applies Bayesian trust scores to accept/reject connections or retransmissions.
- **Outcome:** Mitigates attacks where malicious nodes inject or drop transport packets.

---

## **Layer 5 – Session Layer**

**Module:** **Secure Session Binder**

- **Purpose:** Bind sessions to verified node identities and prevent hijacking.
- **How:** Use PKCertChain IDs in kernel to tag each session; reject session setup if identity is unverified.
- **Outcome:** Protects against session spoofing and replay attacks.

---

## **Layer 6 – Presentation Layer (Crypto Layer)**

**Module:** **Kernel Crypto Guard**

- **Purpose:** Ensure payload confidentiality, integrity, and authenticity.
- **How:** Encrypt/decrypt packets and blockchain entries; sign packets and verify signatures using kernel crypto API.
- **Outcome:** Prevents eavesdropping, tampering, and replay attacks at the payload level.

---

## **Layer 7 – Application Layer (Blockchain / Trust Layer)**

**Module:** **PKCertChain & Bayesian Trust Diary**

- **Purpose:** Authenticate nodes and maintain trust scores in kernel.
- **How:** Blockchain stores immutable node certificates; Bayesian trust diary updates per packet/route.
- **Outcome:** Provides secure, verifiable node identity, route accountability, and trust-based decision-making.

---

### **Cross-Layer Security**

- **Meta-module:** **Kernel Security Orchestrator**

  - Coordinates security modules across layers
  - Monitors boolean activation, anomaly events, and trust metrics
  - Ensures all packets are validated end-to-end from PHY → Application

---

✅ **Security-First Stack Summary**

| OSI Layer      | Security Module                    | Primary Protection                    |
| -------------- | ---------------------------------- | ------------------------------------- |
| 1 Physical     | RF Anomaly & Jamming Detector      | Jamming & signal interference         |
| 2 Data Link    | Secure Neighbor Authentication     | Sybil & spoofed MAC attacks           |
| 3 Network      | Blockchain-Verified Routing Guard  | Blackhole/Wormhole, routing tampering |
| 4 Transport    | Trust-Aware Transport Enforcer     | Malicious packet injection/drop       |
| 5 Session      | Secure Session Binder              | Session hijacking, replay attacks     |
| 6 Presentation | Kernel Crypto Guard                | Eavesdropping, tampering, replay      |
| 7 Application  | PKCertChain & Bayesian Trust Diary | Node authentication, trust evaluation |

---
