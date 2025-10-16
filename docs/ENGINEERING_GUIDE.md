# Team 03 DuckOnWheels Engineering Guide

This document defines the internal engineering rules for the SDV–PiRacer team.  
It provides standards for coding, documentation, version control, testing, and sprint management to ensure technical traceability and team consistency.

---

## 1. Purpose

The goal of this guide is to:
- Establish a uniform workflow for all team members.
- Support SDV and TSF-compliant development processes.
- Maintain traceability between requirements, implementation, and validation.
- Improve team collaboration and code quality.

---

## 2. Repository Structure

── src/
│ ├── control/
│ ├── perception/
│ ├── middleware/
│ ├── ui/
│ └── cloud/
├── docs/
│ ├── architecture/
│ ├── requirements/
│ ├── safety/
│ ├── tests/
│ ├── ENGINEERING_GUIDE.md
│ └── DOCS_STYLE_GUIDE.md
├── tests/
│ ├── unit/
│ ├── integration/
│ └── reports/
├── .github/
│ ├── workflows/
│ └── ISSUE_TEMPLATE/
└── README.md

---

## 3. Branching Strategy

| Branch | Purpose |
|---------|----------|
| `main` | Stable, production-ready branch |
| `develop` | Integration and sprint development |
| `feature/<name>` | New feature or module |
| `bugfix/<name>` | Fix specific issue |
| `docs/<name>` | Documentation updates only |

**Rules:**
- Always branch off from `develop`.  
- Use lowercase and hyphens (e.g. `feature/servo-calibration`).  
- Delete branches after merging.
- Use `rebase` instead of `merge` for small updates.

--- 

## 4. Commit Message Convention

Use the format:


| Type | Description |
|------|--------------|
| feat | New feature or functionality |
| fix | Bug fix |
| refactor | Code structure or cleanup |
| docs | Documentation only |
| test | Unit or integration test |
| chore | CI, build, or config changes |

Example:

```feat(control): implement PID control for steering servo```

---

## 5. Pull Requests

Before submitting a PR:
- Reference at least one issue (`Closes #xx`)
- Link to an active milestone (sprint)
- Ensure the code builds successfully
- Add or update documentation
- Run local unit tests

**Checklist:**
- [ ] Issue linked  
- [ ] CI passed  
- [ ] Documentation updated  
- [ ] Reviewer assigned  
- [ ] No Doxygen warnings  

---

## 6. Code Review Guidelines

| Check | Description |
|--------|-------------|
| Architecture | Matches design intent |
| Style | Consistent with existing code |
| Safety | Handles errors and exceptions correctly |
| Documentation | Up-to-date Doxygen headers |
| Testing | Covers new functionality |

> At least one peer review is required before merging.

---

## 7. Testing Rules

- Each module must include **unit** and **integration** tests.  
- Use the `tests/` folder to organize by module.  
- Tests must run automatically in CI (`.github/workflows/ci.yml`).  
- Each test case must follow the [TEST_CASE_TEMPLATE.md](../.github/TEST_CASE_TEMPLATE.md).  
- Link tests to requirements (e.g. `REQ-CONTROL-001`).

---

## 8. Documentation Rules

- Follow the [DOCS_STYLE_GUIDE.md](DOCS_STYLE_GUIDE.md).  
- Use **Doxygen** for all code documentation.  
- Keep inline comments short and focused.  
- The documentation workflow (`doxygen-docs.yml`) must pass before merging.  

---

## 9. Tools Used

| Tool | Purpose |
|------|----------|
| GitHub Projects | Sprint and issue management |
| GitHub Actions | CI/CD and automation |
| Doxygen | Documentation generation |
| Slack | Team communication |
| C++ | Middleware and simulation |
| PiRacer | Hardware testing platform |

---

## 10. Quality & Compliance

- All CI checks must pass before merge.  
- Use CodeQL for static analysis (security).  
- Critical code must undergo double review (Safety + Lead).  
- Every feature must trace back to a requirement ID.

---

## 11. Team Principles

1. Clarity before speed — document everything.  
2. Safety first — test all control logic.  
3. Traceability everywhere — code ↔ requirements ↔ docs.  
4. Continuous improvement — iterate after every sprint.

---

> This guide is mandatory for all contributors.
