# 2D Elastic Collision Calculation

## Overview

This project implements a 2D elastic collision calculation between two objects (balls) with mass. Collisions are calculated by decomposing the velocity into two components: **normal** (collision direction) and **tangential** (perpendicular).

## Collision Calculation Flow

```mermaid
flowchart TD
    A["Input: Ball A and Ball B"] --> B["Step 1: Calculate distance and normal vector"]
    B --> C["Step 2: Calculate velocity projection<br/>on the normal"]
    C --> D["Step 3: Create normal<br/>velocity vectors"]
    D --> E["Step 4: Apply 1D collision<br/>formula"]
    E --> F["Step 5: Replace normal component<br/>with new velocity"]
    F --> G["Result: Updated Velocities"]
```

## Steps Detail

### Step 1: Normal Vector
Calculation of the normal vector between the centers of the two balls.

```mermaid
graph TD
    A["distance = √[(Bx-Ax)² + (By-Ay)²]"] --> B["normal = (Bx-Ax)/distance, (By-Ay)/distance"]
    B --> C["The normal points from A to B"]
```

**Formula:**
$$\vec{n} = \frac{\vec{AB}}{|\vec{AB}|}$$

---

### Step 1 bis: Separate Overlapping Balls

If the sum of radii is greater than the distance between centers, the balls are overlapping. We need to separate them to prevent penetration.

**Condition:**
$$r_a + r_b > \text{distance}$$

**Separation Process:**

1. Calculate the overlap distance:
$$\text{overlap} = (r_a + r_b) - \text{distance}$$

2. Calculate separation distance (half the overlap plus small padding):
$$\text{separation} = \frac{\text{overlap}}{2} + \epsilon$$

where $\epsilon$ is a small padding value (e.g., 0.5 pixels)

3. Move each ball away from the other along the normal direction:
$$A_{\text{new}} = A - \text{separation} \cdot \vec{n}$$
$$B_{\text{new}} = B + \text{separation} \cdot \vec{n}$$

Each ball moves by half the separation distance in opposite directions, restoring the proper spacing.

---

### Step 2: Scalar Projection
Projection of each velocity onto the normal vector (dot product).

```mermaid
graph LR
    A["e_a = v_a · normal"] --> B["e_a = v_a.x × n.x + v_a.y × n.y"]
    C["e_b = v_b · normal"] --> D["e_b = v_b.x × n.x + v_b.y × n.y"]
```

**Formula:**
$$e_a = \vec{v_a} \cdot \vec{n}$$
$$e_b = \vec{v_b} \cdot \vec{n}$$

---

### Step 3: Normal Velocity Vectors
Reconstruction of velocity vectors along the normal direction.

```mermaid
graph TD
    A["v_a = e_a × normal"] --> B["v_a.x = e_a × n.x<br/>v_a.y = e_a × n.y"]
    C["v_b = e_b × normal"] --> D["v_b.x = e_b × n.x<br/>v_b.y = e_b × n.y"]
```

**Important:** Only the normal component is kept. The tangential component remains unchanged.

---

### Step 4: 1D Collision
Calculation of new velocities in 1D using elastic collision formulas.

```mermaid
graph TD
    A["a2 = calcVelocityA<br/>mass_a, mass_b, e_a, e_b"] --> B["a2 = ((m_a - m_b)/(m_a + m_b)) × e_a<br/>+ ((2 × m_b)/(m_a + m_b)) × e_b"]
    C["b2 = calcVelocityB<br/>mass_a, mass_b, e_a, e_b"] --> D["b2 = ((2 × m_a)/(m_a + m_b)) × e_a<br/>+ ((m_b - m_a)/(m_a + m_b)) × e_b"]
```

**Formulas:**
$$a2 = \frac{(m_a - m_b)e_a + 2m_b e_b}{m_a + m_b}$$
$$b2 = \frac{2m_a e_a + (m_b - m_a)e_b}{m_a + m_b}$$

---

### Step 5: Velocity Update
Replacement of the normal component with the newly calculated velocity.

```mermaid
graph TD
    A["v_a_new = v_a - v_a_old + a2 × normal"] --> B["v_a.x = v_a.x - v_a_old.x + a2 × n.x<br/>v_a.y = v_a.y - v_a_old.y + a2 × n.y"]
    C["Same for v_b with b2"]
    B --> D["Preserves tangential component"]
    C --> D
```

---

## Visual Decomposition Diagram

```mermaid
graph TB
    A["Total Velocity<br/>v = v_normal + v_tangent"] --> B["v_normal = projection on normal<br/>(affected by collision)"]
    A --> C["v_tangent = perpendicular to normal<br/>(unchanged)"]
    B --> D["Replaced by a2 or b2<br/>after collision calculation"]
    C --> D["Kept as is"]
```

---

## Numerical Example

Consider two balls with equal mass (1 kg):
- **Ball A:** position (0, 0), velocity (1, 0)
- **Ball B:** position (2, 0), velocity (-1, 0)

1. **Normal:** (1, 0) → collision along X-axis
2. **e_a = 1 × 1 + 0 × 0 = 1**
3. **e_b = -1 × 1 + 0 × 0 = -1**
4. **a2 = (1 - 1)/(1 + 1) × 1 + (2 × 1)/(1 + 1) × (-1) = -1**
5. **b2 = (2 × 1)/(1 + 1) × 1 + (1 - 1)/(1 + 1) × (-1) = 1**

Result: The balls exchange their velocities!




