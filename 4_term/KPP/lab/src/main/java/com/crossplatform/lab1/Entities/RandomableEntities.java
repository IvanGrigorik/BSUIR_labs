package com.crossplatform.lab1.Entities;

import java.util.Objects;

public class RandomableEntities {
    public enum MODES{LESS, MORE, RANDOM}

    private final long number;
    private final MODES mode;

    public RandomableEntities(long number, MODES mode) {
        this.number = number;
        this.mode = mode;
    }

    public long getNumber() {
        return number;
    }

    public MODES getMode() {
        return mode;
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
}
