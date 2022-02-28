package com.crossplatform.lab1.Controllers;

import org.springframework.web.bind.annotation.*;

import java.util.Random;
import java.util.concurrent.atomic.AtomicLong;

@RestController
public class HomeController {
    private final AtomicLong counter = new AtomicLong();

    @GetMapping("/random")
    public HomeJSONController controllerGet(@RequestParam(value = "num", defaultValue = "50") long number,
                                            @RequestParam(value = "md", defaultValue = "3") int random_mode) {


        // If random_mode == 0 - random less, 1 - random more
        Random rand = new Random();
        long new_number = 0;

        if (random_mode == 0) {
            new_number = rand.nextLong(number - 50, number);
        }
        if (random_mode == 1) {
            new_number = rand.nextLong(number, number + 50);
        }
        if (random_mode == 3) {
            new_number = rand.nextLong(0, 100);
        }

        return new HomeJSONController(counter.incrementAndGet(), new_number);
    }

  /*
    @PostMapping( "/random")
    public ResponseEntity<?> controllerPost(@RequestBody List<Integer> bodyList){


        Random rand = new Random();
        long new_number = 0;


        return new ResponseEntity<>(new_number);
    }
*/

}
