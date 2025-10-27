# ⚙️ Configuration Guide — Duck On Wheels Repository

## 🧭 Purpose
This document describes the configuration of the GitHub repository for the SEA ME Team 03 — *Duck On Wheels* project.  
It ensures reproducibility, traceability, and compliance with Trustable Software Framework (TSF) practices.

---

## 🧱 Repository Structure
- `.github/ISSUE_TEMPLATE/` → Issue and task templates  
- `.github/PULL_REQUEST_TEMPLATE.md` → Standard PR template  
- `.github/workflows/` → CI/CD and Docs pipelines  
- `docs/` → Internal documentation and TSF evidence

---

## 🔧 Workflows Configured
| Workflow | Description |
|-----------|-------------|
| `ci.yml` | Basic CI placeholder for build/test verification |
| `doxygen-docs.yml` | Automatic documentation generation and GitHub Pages deployment |
| `auto-label.yml` | Automatic labeling of PRs and issues based on file paths |

All workflows are triggered on push and pull requests for `main` and `develop`.

---

## 🔒 Branch Protection (Rulesets)
**Branches:** `main`, `develop`

| Rule | Status |
|------|---------|
| Require pull request | ✅ Enabled |
| Require review (1 approval) | ✅ Enabled |
| Require passing checks (CI + Docs) | ✅ Enabled |
| Require signed commits | ✅ Enabled |
| Restrict who can push | ✅ Maintainers only |
| Linear history | ✅ Enabled |

---

## 🧾 License and Policies
- **License:** MIT  
- **Commit Signing:** Required (GPG/SSH)
- **Review Policy:** Minimum 1 reviewer for merges
- **Documentation:** Generated via Doxygen, deployed to GitHub Pages

---

## 🧠 Future Additions
- CodeQL analysis for static code security
- Dependabot for dependency management
- Automated milestone linking
- TSF compliance tracking

---

> **Maintained by:** SEA ME — Team 03 “Duck On Wheels”  
> _Last updated:_ 2025-10-27
