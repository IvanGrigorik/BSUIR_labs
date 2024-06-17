#ifndef MATRIX_H
#define MATRIX_H

#include <iomanip>
#include <iostream>
#include <memory>
#include <random>

template <size_t Size>
class Matrix final {
private:
    int (*matrix)[Size];

public:
    constexpr Matrix() { matrix = new int[Size][Size]; }

    constexpr ~Matrix() { delete[] matrix; }

    constexpr void Print() const noexcept
    {
        for (size_t i = 0; i < Size; i++) {
            for (size_t j = 0; j < Size; j++) {
                std::cout << std::setw(5) << matrix[i][j];
            }
            std::cout << '\n';
        }
    }

    void Randomize()
    {
        static std::random_device rd;
        static std::mt19937 rng(rd());
        static std::uniform_int_distribution<> distribution(1, 10);

        for (size_t i = 0; i < Size; i++) {
            for (size_t j = 0; j < Size; j++) {
                matrix[i][j] = distribution(rng);
            }
        }
    }

    [[nodiscard]] constexpr auto PlainArray() noexcept { return matrix; }
    [[nodiscard]] constexpr auto PlainArray() const noexcept { return matrix; }

    constexpr auto operator[](size_t i) const noexcept { return *(matrix + i); }
    constexpr auto operator[](size_t i) noexcept { return *(matrix + i); }

    template <size_t N>
    constexpr friend bool operator==(const Matrix<N>& m1,
        const Matrix<N>& m2) noexcept
    {
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                if (m1[i][j] != m2[i][j])
                    return false;

        return true;
    }
};

#endif // MATRIX_H
