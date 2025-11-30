# ✅ **CURATED SYSTEM CHECKLIST (Your Project Roadmap)**

## **1. Concurrency Architecture**

- [ ] Create a **Thread Pool** dedicated to crypto operations
- [ ] Implement a **Non-blocking Event Loop** (epoll/kqueue/IOCP or libevent/libuv)
- [ ] Add a **Sign Event Queue** (lock-free ring buffer preferred)
- [ ] Use **futures/promises** or **completion callbacks** for async crypto results
- [ ] Create per-thread **crypto worker contexts** (avoid cross-thread state)
- [ ] Implement **thread-local key caching** (public keys, private keys)

---

# **2. Cryptography Safety Layers**

- [ ] Zero all sensitive buffers with `OPENSSL_cleanse()`
- [ ] Use `OPENSSL_secure_malloc()` for ephemeral and private key material
- [ ] Strict bounds checking on all I/O and vector sizes
- [ ] Enforce maximum allowed input size (prevents buffer bombs)
- [ ] Reject malformed PEM, empty data, short signature sizes
- [ ] Maintain a **crypto error stack logger** (`ERR_get_error()`)

---

# **3. File-System & OS-Level Security**

- [ ] Store private keys in dedicated folder with chmod **600**
- [ ] Lock key files using **flock()** while loading
- [ ] Validate paths (prevent directory traversal attacks)
- [ ] Use **atomic file writes** for key logs
- [ ] Use **fsync()** after key generation
- [ ] Memory-map public key files read-only (optional optimization)

---

# **4. Event-Driven Signature System ("Sign Queue")**

### Your crypto subsystem needs these components:

- [ ] An **Event Dispatcher** that receives:

  - NEW_BLOCK_EVENT
  - REQUEST_SIGNATURE_EVENT
  - VERIFY_SIGNATURE_EVENT
  - KEY_ROTATION_EVENT
  - EPHEMERAL_ECDH_EVENT

- [ ] A **Sign Worker Queue**:

  - lock-free
  - multiple producers
  - multiple consumers
  - preserves order for each ID if needed

- [ ] Events should be represented as POD structs:

  ```cpp
  struct SignEvent {
      uint32_t nodeID;
      std::vector<unsigned char> data;
      std::function<void(SignResult&)> callback;
  };
  ```

- [ ] The queue should feed worker threads that:

  - load private key (thread-local)
  - sign
  - return signature via callback
  - never block

---

# **5. Real-Time Ephemeral Key Exchange (MANET-grade)**

- [ ] Use X25519 ephemeral keys per message
- [ ] Maintain ephemeral key pool (pre-generated keys)
- [ ] Store ephemeral public key in message header
- [ ] Add timestamp + nonce to defend replay attacks
- [ ] Verify signature **before** attempting AES-GCM decrypt

---

# **6. Message Serialization / Wire Protocol**

Design a strict binary message format:

```
[Version]
[MessageType]
[SenderID]
[ReceiverID]
[Timestamp]
[EphemeralPublicKeyLen][EphemeralPublicKey]
[CiphertextLen][Ciphertext]
[AuthTag]
[SignatureLen][Signature]
```

- [ ] Must validate _every length field_
- [ ] Must enforce maximum acceptable message size
- [ ] Must refuse malformed messages

---

# **7. Buffer Overflow Defense**

**At code level:**

- [ ] Replace raw pointers with `std::vector` everywhere
- [ ] Never trust external vector size
- [ ] Use safe copy functions only (`memcpy_s`, `std::copy`)
- [ ] Add static analysis: clang-tidy, Coverity, CodeQL

**At OS level:**

- [ ] Enable ASLR
- [ ] Stack smashing protection (`-fstack-protector-strong`)
- [ ] PIE-enabled binaries
- [ ] Hardened malloc (optionally)

---

# **8. Crypto Subsystem Reliability**

- [ ] Add retry logic for corrupted or delayed key loading
- [ ] Add timeouts for signing events
- [ ] Add backpressure (slow senders don’t overload sign queue)
- [ ] Implement metrics:

  - signatures/sec
  - avg verify time
  - queue backlog
  - thread utilization

---

# **9. Key Lifecycle Management**

- [ ] Periodic Ed25519 key rotation
- [ ] Log all public keys into on-chain PKI
- [ ] Keep old pubkeys until all old blocks are validated
- [ ] Protect key logs from rewriting
- [ ] Detect key reuse & duplicates

---

# **10. Testing & Validation**

### **Crypto Tests**

- [ ] Verify(Sign(Data)) → true
- [ ] Verify(Sign(Data), TamperedData) → false
- [ ] Verify(Sign(Data), WrongKey) → false

### **Concurrency Tests**

- [ ] 10k parallel Sign operations
- [ ] 10k parallel Verify operations
- [ ] Thread starvation prevention
- [ ] Deadlock detection

### **Attack Simulation**

- [ ] Replay attack
- [ ] Corrupted ephemeral key
- [ ] Oversized message (buffer bomb)
- [ ] Injected null bytes
- [ ] Timing attacks (measure & randomize)

---

# **11. Build & Deployment Hardening**

- [ ] Use the hardened build flags:

```
-O2 -Wall -Wextra -Werror
-fstack-protector-strong
-D_FORTIFY_SOURCE=2
-fPIE -pie
```

- [ ] Strip symbols (`-Wl,--strip-all`)
- [ ] Prohibit debug logs in release builds

---

# 🚀 **12. Production-Level Modules You Must Implement**

Here’s a concise module list for your system:

### **Core Crypto Module**

- [ ] KeygenManager (thread-safe)
- [ ] Signer (thread-pool based)
- [ ] Verifier (stateless, multi-threaded)
- [ ] EphemeralKeyManager (X25519 pool)
- [ ] AESGCMEngine (AEAD encryption/decryption)

### **Event Modules**

- [ ] EventLoop
- [ ] SignEventQueue (lock-free)
- [ ] DispatchRouter
- [ ] CallbackScheduler

### **Security Modules**

- [ ] KeyStore (secure key storage)
- [ ] MessageValidator (boundary checks)
- [ ] AntiReplayCache (timestamps + nonces)
- [ ] PublicKeyCache

---
