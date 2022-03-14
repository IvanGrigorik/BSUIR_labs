package com.crossplatform.lab1.Exceptions;

import com.crossplatform.lab1.MyLogger;
import org.apache.logging.log4j.Level;
import org.jetbrains.annotations.NotNull;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.MissingServletRequestParameterException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import org.springframework.web.method.annotation.MethodArgumentTypeMismatchException;

@RestControllerAdvice
public class ExceptionAdvice {

    @ExceptionHandler(value = {MissingServletRequestParameterException.class, MethodArgumentTypeMismatchException.class})
    public ResponseEntity<String> handleArgumentException() {
        String message = "400: Invalid params";
        MyLogger.setLog(Level.ERROR, "WARN in argument");
        return new ResponseEntity<>(message, HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(Exception.class)
    public ResponseEntity<String> handleException(@NotNull Exception e) {
        MyLogger.setLog(Level.ERROR, "WARN in number format");
        return new ResponseEntity<>("Invalid input: " + e.getMessage(), HttpStatus.INTERNAL_SERVER_ERROR);
    }
}