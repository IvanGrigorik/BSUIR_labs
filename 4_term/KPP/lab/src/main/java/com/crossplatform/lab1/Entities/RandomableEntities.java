package com.crossplatform.lab1.Entities;

import java.util.Objects;

public class RandomableEntities {
    private final long number;
    private final int mode;

    public RandomableEntities(long num, int md) {
            this.number = num;
            this.mode = md;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RandomableEntities that = (RandomableEntities) o;
        return number == that.number && mode == that.mode;
    }

    @Override
    public int hashCode() {
        return Objects.hash(number, mode);
    }

    public long getNumber() {
        return number;
    }

    public int getMode() {
        return mode;
    }
}
