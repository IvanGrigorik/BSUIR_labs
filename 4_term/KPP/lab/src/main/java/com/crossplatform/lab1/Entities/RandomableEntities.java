package com.crossplatform.lab1.Entities;

public record RandomableEntities(long number, com.crossplatform.lab1.Entities.RandomableEntities.MODES mode) {
    public enum MODES {LESS, MORE, RANDOM}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RandomableEntities that = (RandomableEntities) o;
        return number == that.number && mode == that.mode;
    }
}
