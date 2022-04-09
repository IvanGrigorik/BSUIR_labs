package com.crossplatform.lab1.Controllers;

import com.crossplatform.lab1.MyLogger;
import lombok.AllArgsConstructor;
import org.apache.logging.log4j.Level;

@AllArgsConstructor
public class Counter {

    private long count;

    public void incrementCount() {
        ++count;
        MyLogger.setLog(Level.INFO, count);
    }
}
