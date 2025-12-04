# DataExSys: Decentralized Data Exchange System

[![Language](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-CMake-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](LICENSE)

**DataExSys** is a secure, decentralized data exchange system built in modern C++20. It uses a lightweight blockchain for identity management and efficient cryptography to enable secure communication between nodes, making it suitable for environments like IoT networks and Mobile Ad-hoc Networks (MANETs).

This project serves as the reference implementation for the paper: *Secure Data Exchange System for Ad-hoc Networks Using Blockchain-Enhanced DSR*.

## Core Architectural Features

*   **Decentralized Identity:** Node identities are managed on a distributed, tamper-resistant blockchain of public key certificates (`PKCertChain`).
*   **Multi-Layer Blockchain:** The system uses a specialized, multi-layer blockchain architecture to separate concerns and improve performance:
    *   `PKCertChain`: Manages node identity, registration, and certificate lifecycle.
    *   `RouteLogChain`: Securely logs routing paths and packet transmissions, enabling auditability and attack detection.
*   **Advanced Attack Mitigation:** The architecture is explicitly designed to detect and mitigate common ad-hoc network attacks:
    *   **Sybil Attacks:** Prevented by the robust consensus mechanism on the `PKCertChain`.
    *   **Blackhole Attacks:** Mitigated by the `LocalTrustDiary` reputation system.
    *   **Wormhole Attacks:** Detected and prevented using `Rolling Signatures` on data packets.
    *   **Replay Attacks:** Thwarted by checking for duplicate transactions in the `RouteLogChain`.
*   **Modern C++ & Tooling:** Written entirely in C++20/23, leveraging modern features for concurrency, safety, and performance.
*   **Cross-Platform Build:** Uses CMake for a consistent build experience across different platforms.

---

## Getting Started

Follow these instructions to get a copy of the project up and running on your local machine for development and testing.

### 1. Prerequisites

Before you begin, ensure you have the necessary development tools installed. You can use the provided shell script to check your environment:
 
```bash
chmod +x ./checktools.sh
./checktools.sh
```

This will verify that `g++`, `cmake`, `git`, `openssl`, and other essential tools are available on your system.

### 2. Clone the Repository

```bash
git clone <your-repository-url>
cd FYP
```

### 3. Build the Project

This project uses a standard out-of-source CMake build process.

```bash
# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Compile the source code
cmake --build .
```

This will create an executable named `DataExSys` inside the `build` directory.

---

## Usage

After a successful build, you can run the application from the `build` directory:

```bash
./DataExSys
```

## Project Structure

The codebase is organized into the following directories:

*   `Blockchain/`: Contains the implementation for the `PKCertChain` and `RouteLogChain`.
*   `Consensus/`: Houses the consensus algorithms (PoW, Quorum).
*   `Security/`: Contains cryptographic helpers (wrapping OpenSSL for Ed25519, etc.).
*   `Helper/`: General-purpose utilities and data structures.
*   `Docs/`: Contains all project documentation, including the API reference, architecture, and guides.
*   `F25_079/`: Contains the LaTeX source for the academic research paper.

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**. Please see `CONTRIBUTING.md` for details on our code of conduct and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.