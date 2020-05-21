# chain-wallet-libs

[![MIT licensed][mit-badge]][mit-url]
[![C.I. Integration][ci-integration-badge]][ci-integration-url]
[![C.I. Checks][ci-check-badge]][ci-check-url]
[![Release][release-badge]][release-url]

[mit-badge]: https://img.shields.io/badge/license-MIT%2FApache--2.0-blue
[mit-url]: LICENSE
[ci-integration-badge]: https://github.com/input-output-hk/chain-wallet-libs/workflows/C.I.%20Integration/badge.svg
[ci-integration-url]: https://github.com/input-output-hk/chain-wallet-libs/actions?query=workflow%3A%22C.I.+Integration%22
[ci-check-badge]: https://github.com/input-output-hk/chain-wallet-libs/workflows/C.I.%20Checks/badge.svg
[ci-check-url]: https://github.com/input-output-hk/chain-wallet-libs/actions?query=workflow%3A%22C.I.+Checks%22
[release-badge]: https://github.com/input-output-hk/chain-wallet-libs/workflows/Release/badge.svg
[release-url]: https://github.com/input-output-hk/chain-wallet-libs/actions?query=workflow%3ARelease

Chain Wallet libs is a set of library, written in [rust-lang], to use to build application for [Jörmungandr].

## released binaries

Currently we provide support for many platforms of the high level wallet library.

**Releases can be found there: [link][release-latest]**

### Android

| Target                    | released binaries |
| ------------------------- | :---------------: |
| `aarch64-linux-android`   |         ✓         |
| `arm-linux-androideabi`   |         ✓         |
| `armv7-linux-androideabi` |         ✓         |
| `i686-linux-android`      |         ✓         |
| `x86_64-linux-android`    |         ✓         |

This includes bindings for Android Kotlin already packaged in a AAR package.

### Cordova plugin

_under construction_

### iOS

| Target              | released binaries |
| ------------------- | :---------------: |
| `aarch64-apple-ios` |         ✓         |
| `x86_64-apple-ios`  |         ✓         |

_Swift package in development..._

### Linux

| Target                             | released binaries |
| ---------------------------------- | :---------------: |
| `aarch64-unknown-linux-gnu`        |         ✓         |
| `arm-unknown-linux-gnueabi`        |         ✓         |
| `armv7-unknown-linux-gnueabihf`    |         ✓         |
| `mips64el-unknown-linux-gnueabi64` |         ✓         |
| `powerpc64el-unknown-linux-gnu`    |         ✓         |
| `x86_64-unknown-linux-gnu`         |         ✓         |
| `x86_64-unknown-linux-musl`        |         ✓         |

### MacOS

| Target                | released binaries |
| --------------------- | :---------------: |
| `x86_64-apple-darwin` |         ✓         |

### Wasm (and JavaScript)

| Target                   | released binaries |
| ------------------------ | :---------------: |
| `wasm32-unknown-unknown` |         ✓         |

This include Javascript generated binaries (with typescript annotations)
for webjs and nodejs.

### Windows

| Target                   | released binaries |
| ------------------------ | :---------------: |
| `x86_64-pc-windows-gnu`  |         ✓         |
| `x86_64-pc-windows-msvc` |         ✓         |

# Development

You can find the main rust libraries at the top level of this repository. These
are the core elements and offer prime support for all the different `bindings`
implemented in the `bindings` directory.

## Code formatting

In order to avoid long lasting discussions and arguments about how code should
be formatted for better readability all must be formatted with `rustfmt`.

## Clippy

Cargo clippy is ran on this repository at every PRs. This will come in handy to
prevent some readability issues but also potential mistakes in the C bindings
when manipulating raw pointers.

## Documentation

- [Getting Started](doc/getting_started.md)
- [Wallet Cryptography and Encoding](doc/CRYPTO.md)
- [Enhanced Mnemonic Encoding (EME)](doc/EME.md)

[rust-lang]: https://www.rust-lang.org/
[Jörmungandr]: https://input-output-hk.github.io/jormungandr
[release-latest]: https://github.com/input-output-hk/chain-wallet-libs/releases/latest
