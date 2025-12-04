/**
@mainpage DataExSys: A Secure Decentralized Data Exchange System

@section intro_sec Introduction

Welcome to the developer documentation for **DataExSys**, a C++ SDK for building secure, decentralized data exchange applications. This project is the reference implementation for the research paper, *Secure Data Exchange System for Ad-hoc Networks Using Blockchain-Enhanced DSR*.

The system is designed for low-mobility Personal Area Networks (PANETs) and provides a robust framework for secure peer-to-peer communication, resistant to common network attacks like Sybil, Blackhole, and Wormhole attacks.

@section core_features_sec Core Features

- **Multi-Layer Blockchain**: A specialized architecture featuring a `PKCertChain` for identity and a `RouteLogChain` for routing audits.
- **Bayesian Trust Management**: A `LocalTrustDiary` on each node to dynamically assess the trustworthiness of peers.
- **Hybrid Consensus**: A lightweight Proof-of-Work combined with a density-aware Quorum mechanism for secure node registration.
- **Modern C++**: Built with C++20/23 for performance, safety, and modern concurrency.

@section quick_links_sec Quick Links

- @subpage architecture
- @subpage threat_model
- @subpage mitigation_model
- @subpage developer_guide
- @subpage open_source_guide
- @subpage product_guide

@section getting_started_sec Getting Started

To get started with the codebase, clone the repository and follow the build instructions in the main README.md file. The API reference can be navigated using the links at the top of this page.

*/