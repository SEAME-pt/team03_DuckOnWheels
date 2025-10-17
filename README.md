# team03# 🦆 Duck On Wheels — SEA ME / PiRacer  
*A Software Defined Vehicle proof-of-concept with early ADAS capabilities, developed under the SEA ME initiative.*

[![Build Status](https://github.com/SEAME-pt/team03_DuckOnWheels/actions/workflows/ci.yml/badge.svg)](https://github.com/SEAME-pt/team03_DuckOnWheels/actions/workflows/ci.yml)
[![Docs](https://github.com/SEAME-pt/team03_DuckOnWheels/actions/workflows/doxygen-docs.yml/badge.svg)](https://SEAME-pt.github.io/team03_DuckOnWheels/)
[![Last Commit](https://img.shields.io/github/last-commit/SEAME-pt/team03_DuckOnWheels)](https://github.com/SEAME-pt/team03_DuckOnWheels/commits/main)
[![License](https://img.shields.io/github/license/SEAME-pt/team03_DuckOnWheels)](LICENSE)
[![Open Issues](https://img.shields.io/github/issues/SEAME-pt/team03_DuckOnWheels)](https://github.com/SEAME-pt/team03_DuckOnWheels/issues)

---

## Overview

**Duck On Wheels** is part of the **SEA ME program**, which explores Software Defined Vehicle (SDV) and Advanced Driver Assistance Systems (ADAS) concepts using accessible, open-hardware platforms.

This proof-of-concept project runs on a PiRacer with Raspberry Pi 5, serving as a small-scale experimental SDV.
It aims to build a modular stack for:

This project uses a **PiRacer** powered by **Raspberry Pi 5** to explore:
- Real-time motor and steering control  
- Perception through onboard sensors and camera
- Basic ADAS functions such as lane assist and alerting  
- A transparent and traceable engineering workflow aligned with Trustable Software Framework (TSF) principles

---

## Objectives

| Layer | Description |
|--------|--------------|
| **Control** | PWM motor and steering control with PID stabilization |
| **Perception** | Camera-based lane detection and basic sensor fusion |
| **Middleware** | ROS2/MQTT message exchange between modules |
| **UI** | On-device Qt dashboard for visualization |
| **ADAS** | Concept-level lane keeping, alerts, assistive braking |
| **Cloud (Soon)** | Remote telemetry and training feedback |

---

## Internal References

| Document | Description |
|-----------|-------------|
| [ENGINEERING_GUIDE.md](docs/ENGINEERING_GUIDE.md) | Internal engineering workflow, branching, and CI/CD rules |
| [DOCS_STYLE_GUIDE.md](docs/DOCS_STYLE_GUIDE.md) | Doxygen documentation and comment style conventions |

---

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.