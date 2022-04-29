package com.crossplatform.lab1.Logic;

import com.crossplatform.lab1.Entities.RandomableEntities;
import com.crossplatform.lab1.MyLogger;

import lombok.extern.java.Log;
import org.apache.logging.log4j.Level;
import org.jetbrains.annotations.NotNull;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;


import java.util.ArrayList;
import java.util.Random;
import java.util.stream.Collectors;

@Service
public class RandomService {
    private final Random rand = new Random();

    @Autowired
    private RandomHash hashMap;

    public long generateRandomNumber(@NotNull RandomableEntities randomRequest) throws IllegalArgumentException {
        MyLogger.setLog(Level.INFO, "Randomize number " + randomRequest.number() + " " + randomRequest.mode());

        long result;


        if (hashMap.isInMap(randomRequest)) {
            result = hashMap.getResult(randomRequest);
            MyLogger.setLog(Level.INFO, randomRequest.number() + " obtained from the hash map");
        } else {
            switch (randomRequest.mode()) {
                case LESS -> result = generateRandomLess(randomRequest.number());
                case MORE -> result = generateRandomMore(randomRequest.number());
                case RANDOM -> result = roll_is_dota2();
                default -> {
                    MyLogger.setLog(Level.WARN, "ERROR IN RANDOM LOGIC: UNKNOWN RANDOM MODE PARAMETER");
                    throw new IllegalArgumentException("Invalid random mode parameters");
                }
            }
            hashMap.addHash(randomRequest, result);
            MyLogger.setLog(Level.INFO, randomRequest.number() + " added to the hash map");
        }
        return result;
    }

    public ArrayList<Long> generateRandomList(ArrayList<RandomableEntities> randomableEntitiesArrayList) {
        return randomableEntitiesArrayList
                .stream()
                .map(this::generateRandomNumber)
                .collect(Collectors.toCollection(ArrayList::new));
    }

    private long generateRandomLess(long number) {
        return rand.nextLong(number - 50, number);
    }

    private long generateRandomMore(long number) {
        return rand.nextLong(number, number + 50);
    }

    private long roll_is_dota2() {
        return rand.nextLong(0, 100);
    }
}
