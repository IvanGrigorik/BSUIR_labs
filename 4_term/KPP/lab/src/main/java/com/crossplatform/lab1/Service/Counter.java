package com.crossplatform.lab1.Service;

import com.crossplatform.lab1.MyLogger;
import lombok.AllArgsConstructor;
import org.apache.logging.log4j.Level;
import org.springframework.stereotype.Service;

@Service
public class Counter {
    long count;

    synchronized public void incrementCount() {
        ++count;
        MyLogger.setLog(Level.INFO, "Request count: " + count);
    }

    public long getCount() {
        return count;
    }
}
