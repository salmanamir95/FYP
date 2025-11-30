## 🚘 Proposed Model: “Dijkstra-Consensus Route-Log Blockchain (DCRL-Chain)”

### 🔹 **Core Concept**

A **distributed append-only linked-list ledger** per node/cluster that logs verified routes, messages, or events.

Each new route log (block) is appended **only after nodes reach local consensus** using a **multi-metric Dijkstra algorithm** (metrics = trust score, latency, RSSI, reputation, etc.).

Each block is:

* Signed by the **sender**, **receiver**, and **multi-hop forwarders (HPS nodes)**
* Has **SHA-256 hash chaining** for immutability
* Contains **aggregated trust scores**, timestamps, and route metadata

This merges:

* **Blockchain-level integrity**
* **Network-level consensus**
* **Symmetric/asymmetric encryption for payload security**
* **Trust propagation** via gossip or Bayesian inference

---

## 🧱 Architectural Stack (Layered)

| **Layer**                       | **Function**                                                  | **Tech / Idea Borrowed From**                                      | **Relevant Prior Works (Fit)**                                                                                             |
| ------------------------------- | ------------------------------------------------------------- | ------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------- |
| **1. Data Encryption Layer**    | Payload encryption + authentication                           | AES-GCM / ChaCha20 + ECC-based session keys                        | 🔹 ECC + AES hybrid (2023–2025, Springer) <br> 🔹 Luo et al., 2024 (Nature – certificateless signcryption)                 |
| **2. Ledger Security Layer**    | Append-only linked-list of route logs                         | SHA-256 hash chaining + digital signatures (sender, HPS, receiver) | 🔹 Byun et al., 2025 (blockchain trust in SCMS) <br> 🔹 CB-RTM (Rana et al., 2024) – lightweight blockchain                |
| **3. Consensus Layer**          | Multi-metric Dijkstra (trust, hop count, delay, energy, etc.) | Deterministic shortest-path selection = consensus                  | 🔹 Wei et al., 2024 – Bayesian trust adaptation <br> 🔹 Ali et al., 2024 – gossip trust distribution                       |
| **4. Trust Evaluation Layer**   | Local trust computation (Bayesian, Dirichlet, reputation)     | Trust updates → weight edges in Dijkstra graph                     | 🔹 BTLB-PP (Bala et al., 2023) <br> 🔹 DBREMM (2023) – double-layer trust blockchain                                       |
| **5. Verification Layer**       | Multi-signature authentication per route                      | Aggregate signature of sender + multi-hop nodes                    | 🔹 Li et al., 2025 – certificateless aggregate signature <br> 🔹 Xu et al., 2024 – lattice-based certificateless signature |
| **6. Privacy / Key Management** | Lightweight certificateless or ID-based keys                  | Certificateless KEM for ad-hoc keying                              | 🔹 Verma et al., 2024 (quantum-secure certificateless auth) <br> 🔹 Naresh et al., 2024 (ID-based secure VANET)            |

---

## 🧩 How Each Component Contributes

| **Property**              | **Mechanism in Your System**                                 | **Supporting Works**             | **Effect**                              |
| ------------------------- | ------------------------------------------------------------ | -------------------------------- | --------------------------------------- |
| **Trustability**          | Weighted Dijkstra (trust-based edge cost) + Bayesian updates | Wei 2024, Bala 2023              | Consensus favors honest, stable nodes   |
| **Integrity**             | SHA-256 hash chaining, multi-signatures                      | Byun 2025, Li 2025               | Immutable & verifiable route logs       |
| **Confidentiality**       | ECC-derived AES-GCM session keys                             | ECC + AES hybrid (Springer 2023) | End-to-end data protection              |
| **Authentication**        | Multi-hop digital signatures (aggregate)                     | Li 2025, Luo 2024                | Ensures all nodes on route are verified |
| **Performance**           | Local deterministic Dijkstra (no mining)                     | CB-RTM 2024                      | Fast, energy-efficient consensus        |
| **Scalability**           | Linked-list blockchain (not global chain)                    | DistB-VNET 2024                  | Works under partitioned ad-hoc settings |
| **Post-Quantum Security** | Lattice-based certificateless signatures (optional upgrade)  | Xu 2024, Verma 2024              | Future-proof authentication             |

---

## ⚙️ Feasibility in **Pure Ad-Hoc (Infra-less) VANET**

| Factor                     | Assessment                                                                                                                                    |
| -------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| **Connectivity**           | ✅ Fully local consensus (no RSU needed) — each cluster maintains its own route ledger.                                                        |
| **Latency**                | ✅ Consensus in milliseconds — only route computation & signatures.                                                                            |
| **Storage**                | ✅ Minimal (linked list entries, not heavy blockchain). Can be pruned or compressed via Merkle summaries.                                      |
| **Security**               | ✅ SHA-256 chaining + digital signatures = tamper-proof.                                                                                       |
| **Energy**                 | ✅ Low — no mining; symmetric ciphers for payload; ECC for small asymmetric ops.                                                               |
| **Privacy**                | ✅ Certificateless signcryption maintains anonymity while ensuring traceability.                                                               |
| **Post-Quantum Readiness** | ⚙️ Optional upgrade with lattice-based certificateless signatures.                                                                            |
| **Attack Resistance**      | ⚙️ Resistant to route manipulation (since trust metrics & signatures verified). Needs metric validation protocols to resist falsified inputs. |

---

## 🧠 **SWOT Summary of Your Architecture**

| **Strengths**                                                                                                                                                                                                                                  | **Weaknesses**                                                                                                                                                                               |
| ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| - Fully ad-hoc, RSU-free consensus (multi-metric Dijkstra). <br> - Strong cryptographic auditability (hash + multi-signature). <br> - High performance (no global synchronization). <br> - Modular: can plug in any trust or crypto primitive. | - Needs secure metric measurement (else false Dijkstra inputs). <br> - Ledger storage per node can grow over time (must compress). <br> - Multi-signature aggregation requires coordination. |
| **Opportunities**                                                                                                                                                                                                                              | **Threats**                                                                                                                                                                                  |
| - Can become *standard infra-less blockchain variant* for VANETs. <br> - Integrate gossip learning to auto-tune trust weights. <br> - Expand into platoon-level route auditing and intrusion detection.                                        | - Colluding nodes may bias trust metrics. <br> - Metric falsification if beacons not signed. <br> - Requires secure clock sync for route timestamp verification.                             |

---

## 🏁 **Most Compatible Prior Works (Strongly Feasible for Integration)**

| **Category**                    | **Highly Compatible Papers (2023–2025)**                                                      | **Why**                                                 |
| ------------------------------- | --------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
| **Encryption**                  | *ECC (ephemeral) + AES-GCM hybrid* (Springer 2023)                                            | Lightweight & works ad-hoc.                             |
| **Signatures / Authentication** | *Li et al., 2025 – certificateless aggregate signature*                                       | Multi-signature aggregation fits route logs perfectly.  |
| **Certificateless Security**    | *Luo et al., 2024 – certificateless signcryption*                                             | Ensures confidentiality + authentication with low cost. |
| **Trust / Blockchain Base**     | *Byun et al., 2025 – blockchain trust SCMS* <br> *CB-RTM 2024 – lightweight blockchain trust* | Immutability + localized blockchain idea.               |
| **Trust Metric Integration**    | *Wei et al., 2024 – Bayesian anti-attack trust*                                               | For adaptive trust weighting in Dijkstra metrics.       |
| **Gossip / Learning Support**   | *Ali et al., 2024 – gossip learning for trust propagation*                                    | For distributed trust synchronization.                  |

---

## 🔒 Final Insight

Your **“DCRL-Chain”** architecture combines:

* **Security of blockchain (hash + sigs)**
* **Efficiency of Dijkstra consensus**
* **Flexibility of certificateless cryptography**
* **Adaptiveness of Bayesian/gossip trust**

✅ **Feasibility:** Very high for pure V2V / infra-less VANETs.
✅ **Novelty:** Consensus mechanism driven by *multi-metric trust-weighted shortest path* is unique and practical.
✅ **Scalability:** Cluster-level route ledgers can interlink to form a *meta-chain* if infrastructure later appears (hybrid compatibility).

---

Would you like me to **sketch this architecture diagrammatically** (showing Dijkstra-based consensus → route-log blockchain formation → trust/gossip updates → encryption flow)?
It would make an excellent figure for your paper or thesis section on the proposed model.


Vangujar 2024 (ID-CAKE)	ECC key exchange	✅ Excellent	Secure cluster / route session keys
Luo 2024 (Signcryption)	ECC signcryption	✅ Excellent	Per-hop payload confidentiality
Li 2025 (Aggregate Sig)	ECC aggregate sig	✅ Good	Route validation log
Zhan 2024 (Privacy Auth)	ECC pseudonyms	✅ Good	Privacy layer
DBREMM 2023 (Blockchain)	SHA256 + ECC	✅ Excellent	Append-only route-log ledger
Naresh 2024 (ID-based)	Pairing-based	⚠️ Moderate	Use for initial identity bootstrap (Oppo side)

Threshold Ring Sig 2023
ECC ring
⚠️ Moderate
Optional for trust validation