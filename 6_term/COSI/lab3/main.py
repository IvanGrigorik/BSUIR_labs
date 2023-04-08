import numpy as np
import sympy
import matplotlib.pyplot as plt


def signal(x):
    return np.sin(x) + np.cos(4 * x)


def discretize(func, n):
    return [func(i * 2 * np.pi / n) for i in range(n)]


def fwht(sample):
    n = len(sample)
    r = n // 2

    result = [0] * n

    for i in range(r):
        result[i] = sample[i] + sample[i + r]
        result[i + r] = -sample[i + r] + sample[i]

    sample = result
    if n > 2:
        sample[:r] = fwht(result[:r])
        sample[r:] = fwht(result[r:])

    return result


def draw_samples(samples):
    plt.stem(samples)
    plt.grid()
    plt.show()


def main():
    n = 16
    sample = discretize(signal, n)
    transformation_result = fwht(sample)
    print(transformation_result)

    transform = sympy.fwht(sample)
    print(transform)


if __name__ == "__main__":
    main()
