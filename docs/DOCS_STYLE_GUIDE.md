# Team03 DuckOnWheels Documentation Style Guide

This guide defines the official documentation rules using **Doxygen**.

All modules (Control, Perception, Middleware, UI, Cloud) must follow this format to ensure consistency and traceability.

---

## 1. General Rules

- Every source file must include a Doxygen header (`@file`, `@brief`, `@ingroup`).
- All public functions, classes, and structs must have `@param`, `@return`, and `@details`.
- Write all documentation in **English (technical tone)**.
- Comments must describe the **intent**, not the syntax.

---

## 2. File Header Template

```cpp
/**
 * @file motor_control.cpp
 * @brief Implements PWM motor control for the PiRacer prototype.
 * @ingroup Control
 * @author ...
 * @date 2025-10-16
 * @version 1.0
 */
```
## 3. Function and Class Documentation

```
/**
 * @class MotorController
 * @brief Handles DC motor PWM signals using PCA9685.
 *
 * Provides functions for initialization, calibration, and speed control.
 */
 ```

```
/**
 * @brief Set the PWM duty cycle.
 * @param channel Motor output (0–15)
 * @param duty PWM value (0–4095)
 * @return true if successful, false otherwise
 */
```

## 4. Inline Comments

Good:
```
// Apply PID correction to steering angle
angle += pid_output;
```

Bad:
```
// Add 1 to angle
angle++;
```

## 5. Validation Checklist

Before merging:

 Header present with @file, @brief, @ingroup

 All functions documented

 No missing @param or @return

 doxygen Doxyfile runs without warnings

## 6. Best Practices

Use @todo, @warning, @see, @ref appropriately.

Reference requirements with @ref REQ-XXXX.

Avoid redundancy; Doxygen auto-parses structure.

Regenerate documentation every sprint.