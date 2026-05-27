# double pendulum

A simple double pendulum simulation built using **C++** and **raylib**. The simulation calculates the chaotic movement of a double pendulum system by solving the equations of motion derived from Lagrangian mechanics.

## Lagrangian Physics Overview

A double pendulum consists of two pendulums, one attached to the other. To find how it moves over time, we use generalized coordinates $\theta_1$ and $\theta_2$ (the angles of the arms relative to the vertical).

### 1. Positions and Velocities
The Cartesian coordinates for the first bob $(x_1, y_1)$ and second bob $(x_2, y_2)$ are:
* $x_1 = L_1 \sin\theta_1$
* $y_1 = L_1 \cos\theta_1$
* $x_2 = L_1 \sin\theta_1 + L_2 \sin\theta_2$
* $y_2 = L_1 \cos\theta_1 + L_2 \cos\theta_2$

Taking the time derivatives gives the velocities $(\dot{x}_1, \dot{y}_1)$ and $(\dot{x}_2, \dot{y}_2)$.

### 2. Kinetic & Potential Energy
The total Kinetic Energy ($T$) of the system is:
$$T = \frac{1}{2} m_1 (\dot{x}_1^2 + \dot{y}_1^2) + \frac{1}{2} m_2 (\dot{x}_2^2 + \dot{y}_2^2)$$
$$T = \frac{1}{2} m_1 L_1^2 \dot{\theta}_1^2 + \frac{1}{2} m_2 \left[ L_1^2 \dot{\theta}_1^2 + L_2^2 \dot{\theta}_2^2 + 2 L_1 L_2 \dot{\theta}_1 \dot{\theta}_2 \cos(\theta_1 - \theta_2) \right]$$

The total Potential Energy ($V$) of the system (taking the pivot as $y=0$, downward as positive $y$) is:
$$V = -(m_1 + m_2) g L_1 \cos\theta_1 - m_2 g L_2 \cos\theta_2$$

### 3. The Lagrangian & Euler-Lagrange Equations
The Lagrangian ($\mathcal{L}$) is the difference between kinetic and potential energy:
$$\mathcal{L} = T - V$$

To find the equations of motion, we solve the Euler-Lagrange equation for both coordinates ($i = 1, 2$):
$$\frac{d}{dt}\left(\frac{\partial \mathcal{L}}{\partial \dot{\theta}_i}\right) - \frac{\partial \mathcal{L}}{\partial \theta_i} = 0$$

### 4. Explicit Equations for Acceleration
Solving the system of simultaneous differential equations gives explicit formulas for the angular accelerations $\ddot{\theta}_1$ and $\ddot{\theta}_2$. These exact mathematical formulas are implemented directly within the project's `update()` loop:

$$\ddot{\theta}_1 = \frac{-g(2m_1 + m_2)\sin\theta_1 - m_2 g \sin(\theta_1 - 2\theta_2) - 2\sin(\theta_1 - \theta_2)m_2(\dot{\theta}_2^2 L_2 + \dot{\theta}_1^2 L_1 \cos(\theta_1 - \theta_2))}{L_1(2m_1 + m_2 - m_2\cos(2\theta_1 - 2\theta_2))}$$

$$\ddot{\theta}_2 = \frac{2\sin(\theta_1 - \theta_2)\left( \dot{\theta}_1^2 L_1(m_1 + m_2) + g(m_1 + m_2)\cos\theta_1 + \dot{\theta}_2^2 L_2 m_2 \cos(\theta_1 - \theta_2) \right)}{L_2(2m_1 + m_2 - m_2\cos(2\theta_1 - 2\theta_2))}$$

---

## Code Implementation

The simulation maps these equations into code using a basic **Euler Integration** method to step through time:

```cpp