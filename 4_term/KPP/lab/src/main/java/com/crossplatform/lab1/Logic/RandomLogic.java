package com.crossplatform.lab1.Logic;

import com.crossplatform.lab1.Entities.RandomableEntities;
import com.crossplatform.lab1.MyLogger;

import org.apache.logging.log4j.Level;
import org.jetbrains.annotations.NotNull;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;


import java.util.Random;

@Service
public class RandomLogic {
    private final Random rand = new Random();

    @Autowired
    private RandomHash hashMap;

    public long randomNew(@NotNull RandomableEntities randomRequest) throws IllegalArgumentException {
        MyLogger.setLog(Level.INFO, "Randomize number");

        long result;

        if (hashMap.isInMap(randomRequest)) {
            result = hashMap.getResult(randomRequest);
            MyLogger.setLog(Level.INFO, randomRequest.getNumber() + " obtained from the hash map");
        } else {
            switch (randomRequest.getMode()) {
                case 0 -> result = randomLess(randomRequest.getNumber());
                case 1 -> result = randomMore(randomRequest.getNumber());
                case 2 -> result = random();
                default -> {
                    MyLogger.setLog(Level.WARN, "400 WARN");
                    throw new IllegalArgumentException("Exception in RandomLogic");
                }
            }
            hashMap.addHash(randomRequest, result);
            MyLogger.setLog(Level.INFO, randomRequest.getNumber() + " added to the hash map");
        }
        return result;
    }

    private long randomLess(long number) {
        return rand.nextLong(number - 50, number);
    }

    private long randomMore(long number) {
        return rand.nextLong(number, number + 50);
    }

    private long random() {
        return rand.nextLong(0, 100);
    }


}
