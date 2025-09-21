# 최소제곱법을 이용한 원 피팅 이론

## 개요

최소제곱법(Least Squares Method)을 사용한 원 피팅은 주어진 점들의 집합으로부터 가장 적합한 원을 찾는 알고리즘입니다. 이 문서는 대수적 원 피팅(Algebraic Circle Fitting) 방법의 수학적 이론과 구현을 설명합니다.

## 1. 원의 방정식과 변환

### 기본 원의 방정식
원의 일반적인 방정식은 다음과 같습니다:

$$(x - c_x)^2 + (y - c_y)^2 = r^2$$

여기서:
- $(c_x, c_y)$: 원의 중심점
- $r$: 원의 반지름

### 대수적 형태로 변환
원의 방정식을 전개하면:

$$x^2 - 2c_x \cdot x + c_x^2 + y^2 - 2c_y \cdot y + c_y^2 = r^2$$

정리하면:

$$x^2 + y^2 = 2c_x \cdot x + 2c_y \cdot y + (r^2 - c_x^2 - c_y^2)$$

이를 다음과 같이 표현할 수 있습니다:

$$x^2 + y^2 = 2c_x \cdot x + 2c_y \cdot y + f$$

여기서 $f = r^2 - c_x^2 - c_y^2$입니다.

## 2. 선형 시스템 구성

### 행렬 형태로 변환
$n$개의 점 $(x_i, y_i)$에 대해 위의 방정식을 적용하면:

$$x_i^2 + y_i^2 = 2c_x \cdot x_i + 2c_y \cdot y_i + f$$

이를 행렬 형태로 표현하면:

$$\mathbf{A} \mathbf{p} = \mathbf{b}$$

여기서:

$$\mathbf{A} = \begin{bmatrix}
2x_1 & 2y_1 & 1 \\
2x_2 & 2y_2 & 1 \\
\vdots & \vdots & \vdots \\
2x_n & 2y_n & 1
\end{bmatrix}, \quad \mathbf{p} = \begin{bmatrix}
c_x \\
c_y \\
f
\end{bmatrix}, \quad \mathbf{b} = \begin{bmatrix}
x_1^2 + y_1^2 \\
x_2^2 + y_2^2 \\
\vdots \\
x_n^2 + y_n^2
\end{bmatrix}$$

## 3. 최소제곱법 해

### 정규방정식 (Normal Equation)
최소제곱법의 해는 다음 정규방정식을 통해 구할 수 있습니다:

$$\mathbf{p} = (\mathbf{A}^T \mathbf{A})^{-1} \mathbf{A}^T \mathbf{b}$$

### 정규방정식의 계수 계산

#### $\mathbf{A}^T \mathbf{A}$ 행렬의 요소들:

$$(\mathbf{A}^T \mathbf{A})_{11} = \sum_{i=1}^{n} (2x_i)^2 = 4\sum_{i=1}^{n} x_i^2$$

$$(\mathbf{A}^T \mathbf{A})_{12} = (\mathbf{A}^T \mathbf{A})_{21} = \sum_{i=1}^{n} (2x_i)(2y_i) = 4\sum_{i=1}^{n} x_i y_i$$

$$(\mathbf{A}^T \mathbf{A})_{22} = \sum_{i=1}^{n} (2y_i)^2 = 4\sum_{i=1}^{n} y_i^2$$

$$(\mathbf{A}^T \mathbf{A})_{13} = (\mathbf{A}^T \mathbf{A})_{31} = \sum_{i=1}^{n} (2x_i) \cdot 1 = 2\sum_{i=1}^{n} x_i$$

$$(\mathbf{A}^T \mathbf{A})_{23} = (\mathbf{A}^T \mathbf{A})_{32} = \sum_{i=1}^{n} (2y_i) \cdot 1 = 2\sum_{i=1}^{n} y_i$$

$$(\mathbf{A}^T \mathbf{A})_{33} = \sum_{i=1}^{n} 1^2 = n$$

따라서:

$$\mathbf{A}^T \mathbf{A} = \begin{bmatrix}
4\sum x_i^2 & 4\sum x_i y_i & 2\sum x_i \\
4\sum x_i y_i & 4\sum y_i^2 & 2\sum y_i \\
2\sum x_i & 2\sum y_i & n
\end{bmatrix}$$

#### $\mathbf{A}^T \mathbf{b}$ 벡터의 요소들:

$$(\mathbf{A}^T \mathbf{b})_1 = \sum_{i=1}^{n} (2x_i)(x_i^2 + y_i^2) = 2\sum_{i=1}^{n} x_i(x_i^2 + y_i^2)$$

$$(\mathbf{A}^T \mathbf{b})_2 = \sum_{i=1}^{n} (2y_i)(x_i^2 + y_i^2) = 2\sum_{i=1}^{n} y_i(x_i^2 + y_i^2)$$

$$(\mathbf{A}^T \mathbf{b})_3 = \sum_{i=1}^{n} 1 \cdot (x_i^2 + y_i^2) = \sum_{i=1}^{n} (x_i^2 + y_i^2)$$

## 4. 구현에서의 단순화

### 계수 정의
구현에서는 다음과 같이 정의합니다:

$$A = n \sum x_i^2 - (\sum x_i)^2$$

$$B = n \sum x_i y_i - \sum x_i \sum y_i$$

$$C = n \sum y_i^2 - (\sum y_i)^2$$

$$D = n \sum (x_i^2 + y_i^2) x_i - \sum (x_i^2 + y_i^2) \sum x_i$$

$$E = n \sum (x_i^2 + y_i^2) y_i - \sum (x_i^2 + y_i^2) \sum y_i$$

### 해 계산
행렬식:

$$\det = AC - B^2$$

중심점:

$$c_x = \frac{DC - EB}{\det}$$

$$c_y = \frac{AE - BD}{\det}$$

### 반지름 계산
반지름은 다음 공식으로 계산됩니다:

$$r^2 = \frac{\sum (x_i^2 + y_i^2) + 2c_x \sum x_i + 2c_y \sum y_i - n(c_x^2 + c_y^2)}{n}$$

$$r = \sqrt{\max(0, r^2)}$$

## 5. 알고리즘의 특성

### 장점
1. **계산 효율성**: 선형 시스템으로 변환되어 빠른 계산 가능
2. **수치적 안정성**: 정규방정식을 사용하여 안정적인 해 제공
3. **구현 단순성**: 복잡한 비선형 최적화 없이 구현 가능

### 단점
1. **기하학적 정확도**: 대수적 오차를 최소화하므로 기하학적 거리 오차와 다름
2. **가중치 부재**: 모든 점에 동일한 가중치 적용
3. **이상치 민감성**: 노이즈가 많은 데이터에서 부정확한 결과

## 6. 수치적 고려사항

### 행렬식 검사
행렬식이 매우 작으면 ($|\det| < 10^{-10}$) 해가 불안정하거나 존재하지 않습니다.

### 반지름 검증
계산된 $r^2$이 음수인 경우, 데이터가 원을 형성하지 않음을 의미합니다.

## 7. 대안 방법들

### 기하학적 거리 기반 방법
각 점에서 원의 경계까지의 수직 거리를 최소화:

$$\min \sum_{i=1}^{n} \left| \sqrt{(x_i - c_x)^2 + (y_i - c_y)^2} - r \right|^2$$

### RANSAC 방법
노이즈가 많은 데이터에서 강건한 원을 찾는 확률적 방법

### Pratt 방법
기하학적 거리를 직접 최소화하는 대수적 방법

## 8. 결론

최소제곱법을 이용한 원 피팅은 계산 효율성과 구현 단순성의 장점이 있지만, 기하학적 정확도 측면에서는 한계가 있습니다. 실제 응용에서는 데이터의 특성과 요구사항에 따라 적절한 방법을 선택해야 합니다.

구멍 분석과 같은 실제 응용에서는 노이즈가 많을 수 있으므로, RANSAC이나 기하학적 거리 기반 방법이 더 적합할 수 있습니다.
