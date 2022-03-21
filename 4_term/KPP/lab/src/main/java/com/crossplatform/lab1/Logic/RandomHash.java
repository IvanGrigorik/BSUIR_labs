package com.crossplatform.lab1.Logic;

import com.crossplatform.lab1.Entities.RandomableEntities;
import org.springframework.stereotype.Component;

import java.util.HashMap;

@Component
public class RandomHash {
    private final HashMap<RandomableEntities, Long> hashMap = new HashMap<>();

    public boolean isInMap(RandomableEntities key) {
        return hashMap.containsKey(key);
    }

    public void addHash(RandomableEntities key, Long randomizedNumber) {
        hashMap.put(key, randomizedNumber);
    }

    public Long getResult(RandomableEntities key) {
        return hashMap.get(key);
    }
}
