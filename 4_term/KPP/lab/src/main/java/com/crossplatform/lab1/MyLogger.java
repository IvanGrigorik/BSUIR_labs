package com.crossplatform.lab1;

import com.crossplatform.lab1.Logic.RandomLogic;
import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.Level;
import org.apache.logging.log4j.LogManager;

public class MyLogger {
    private static final Logger logger = LogManager.getLogger(RandomLogic.class);

    public static void setLog(Level lvl, Object message) {
        logger.log(lvl, message);
    }
}
