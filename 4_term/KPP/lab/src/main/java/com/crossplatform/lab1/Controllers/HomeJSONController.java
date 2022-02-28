package com.crossplatform.lab1.Controllers;

public record HomeJSONController(long id, long result) {

    public long getId() {
        return id;
    }

    public long getResult() {
        return result;
    }
}
