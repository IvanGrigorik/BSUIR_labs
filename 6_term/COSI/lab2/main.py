import numpy as np
import matplotlib.pyplot as plt


def func_y(x):
    return np.sin(2 * x)


def func_z(x):
    return np.cos(7 * x)


def discretize(func, n):
    return [func(i * 2 * np.pi / n) for i in range(n)]


def draw_inner_function(func):
    x = np.arange(0, 2 * np.pi, 0.01)
    y = func(x)
    plt.plot(x, y)
    plt.grid()
    plt.show()


def draw_samples(samples):
    plt.stem(samples)
    plt.grid()
    plt.show()


def convolve(sample_x, sample_y):
    n = len(sample_x)
    sample_z = [0.] * n

    for i in range(n):
        for j in range(n):
            sample_z[i] += sample_x[j] * sample_y[i - j]

    return sample_z



def convolve_fft(sample_x, sample_y):
    x_fft = np.fft.fft(sample_x)
    y_fft = np.fft.fft(sample_y)
    z_fft = x_fft * y_fft
    z = np.fft.ifft(z_fft)
    return np.real(z)


def correlate(sample_x, sample_y):
    n = len(sample_x)
    sample_z = [0.] * n

    for i in range(n):
        for j in range(n):
            sample_z[i] += sample_x[j] * sample_y[(i + j) % n]

    return sample_z


def correlate_fft(sample_x, sample_y):
    x_fft = np.fft.fft(sample_x).conj()
    y_fft = np.fft.fft(sample_y)
    z_fft = x_fft * y_fft
    z = np.fft.ifft(z_fft)
    return np.real(z)


def main():
    n = 16
    sampled_y = discretize(func_y, n)
    sampled_z = discretize(func_z, n)

    draw_inner_function(func_y)
    draw_inner_function(func_z)

    # O(N ^ 2)
    convolved = convolve(sampled_z, sampled_y)
    draw_samples(convolved)

    # O(N log(N) )
    convolved_fft = convolve_fft(sampled_z, sampled_y)
    draw_samples(convolved_fft)

    # O(N ^ 2)
    correlation = correlate(sampled_y, sampled_z)
    draw_samples(correlation)

    # O(N log(N) )
    correlation_fft = correlate_fft(sampled_y, sampled_z)
    draw_samples(correlation_fft)


if __name__ == '__main__':
    main()
