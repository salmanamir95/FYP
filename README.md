# DataExSys: Decentralized Data Exchange System

[![Language](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-CMake-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](LICENSE)

**DataExSys** is a secure, decentralized data exchange system built in modern C++20. It uses a lightweight blockchain for identity management and efficient cryptography to enable secure communication between nodes, making it suitable for environments like IoT networks and Mobile Ad-hoc Networks (MANETs).

## Key Features

*   **Decentralized Identity:** Node identities are managed on a distributed, tamper-resistant blockchain of public key certificates (`PKCertChain`).
*   **Modern & Secure Cryptography:** Utilizes `Ed25519` for fast and secure digital signatures, implemented via OpenSSL's `libcrypto`.
*   **Modern C++:** Written entirely in C++20, leveraging modern features for concurrency (`std::jthread`), safety, and performance.
*   **Modular Architecture:** A clean separation between the blockchain logic, consensus mechanism, and security primitives.
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

The codebase is organized into the following main directories:

*   `Blockchain/`: Contains the logic for the Public Key Certificate chain.
*   `Consensus/`: Houses the consensus algorithm for agreeing on the state of the blockchain.
*   `Security/`: Contains cryptographic helper functions (wrapping OpenSSL).
*   `Helper/`: General-purpose utility code and data structures.

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**. Please see `CONTRIBUTING.md` for details on our code of conduct and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.