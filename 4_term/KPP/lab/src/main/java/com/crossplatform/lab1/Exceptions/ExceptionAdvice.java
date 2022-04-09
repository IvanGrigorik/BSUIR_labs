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

    @ExceptionHandler(MissingServletRequestParameterException.class)
    public ResponseEntity<Object> handleIllegalArgumentException(@NotNull MissingServletRequestParameterException e) {
        var message = "Status 400: \"" + e.getParameterName() + "\" of type \"" + e.getParameterType() + "\"";
        MyLogger.setLog(Level.WARN, message);
        return new ResponseEntity<>(message, HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(MethodArgumentTypeMismatchException.class)
    public ResponseEntity<Object> handleTypeMismatchException(@NotNull MethodArgumentTypeMismatchException e) {
        var message = "Status 400: \"" + e.getName() + "=" + e.getValue() + "\" but type must be \"" + e.getRequiredType() + "\"";
        MyLogger.setLog(Level.WARN, message);
        return new ResponseEntity<>(message, HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(Exception.class)
    public ResponseEntity<Object> handleServerException() {
        var message = "Status 500: ";
        MyLogger.setLog(Level.ERROR, message);
        return new ResponseEntity<>(message, HttpStatus.INTERNAL_SERVER_ERROR);
    }

}