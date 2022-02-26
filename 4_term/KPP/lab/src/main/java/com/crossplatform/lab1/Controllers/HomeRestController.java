package com.crossplatform.lab1.Controllers;

public record HomeRestController(long id, long result) {

    public long getId() {
        return id;
    }

    public long getResult() {
        return result;
    }
}
