package com.crossplatform.lab1.Exceptions;

import com.crossplatform.lab1.Logic.RandomLogic;
import com.crossplatform.lab1.MyLogger;
import org.apache.logging.log4j.Level;
import org.jetbrains.annotations.NotNull;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

@RestControllerAdvice
public class ExceptionAdvice {
    @ExceptionHandler(IllegalArgumentException.class)
    public ResponseEntity<String> handleException(@NotNull IllegalArgumentException e) {
        MyLogger.setLog(Level.WARN, "WARN in argument");
        return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(NumberFormatException.class)
    public ResponseEntity<String> handleException(@NotNull NumberFormatException e) {
        MyLogger.setLog(Level.WARN, "WARN in number format");
        return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(Exception.class)
    public ResponseEntity<String> handleException(@NotNull Exception e) {
        MyLogger.setLog(Level.WARN, "WARN in ExceptionAdvice");
        return new ResponseEntity<>(e.getMessage(), HttpStatus.INTERNAL_SERVER_ERROR);
    }
}