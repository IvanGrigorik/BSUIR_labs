package com.crossplatform.lab1.Controllers;

import com.crossplatform.lab1.Entities.RandomableEntities;
import com.crossplatform.lab1.Logic.RandomService;
import com.crossplatform.lab1.MyLogger;
import com.crossplatform.lab1.Service.Counter;
import lombok.AllArgsConstructor;
import org.apache.logging.log4j.Level;
import org.jetbrains.annotations.NotNull;
<<<<<<< HEAD
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
=======
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.concurrent.Semaphore;
>>>>>>> ff83f32c041bb96b5785f4d5727916d75c056574

import java.util.ArrayList;
import java.util.List;


@Controller
@AllArgsConstructor
public class HomeController {
    RandomService randomService;
    Counter counter;

    private final Object obj;
    // private Semaphore sem;

    @GetMapping("/random")
    public String controllerGet(@RequestParam(value = "num") long number,
                                @RequestParam(value = "md") RandomableEntities.MODES random_mode, @NotNull Model model) {

<<<<<<< HEAD
        // If random_mode == 0 - random less, 1 - random more
        RandomableEntities newEntity = new RandomableEntities(number, random_mode);
        Long result = randomService.generateRandomNumber(newEntity);
=======
        // sem.acquire();
        synchronized (obj) {
>>>>>>> ff83f32c041bb96b5785f4d5727916d75c056574

            RandomableEntities newEntity = new RandomableEntities(number, random_mode);
            Long result = randomService.generateRandomNumber(newEntity);

            model.addAttribute("num", number);
            model.addAttribute("md", random_mode);
            model.addAttribute("rnum", result);

            counter.incrementCount();

            MyLogger.setLog(Level.INFO, "Successful mapping");
        }
        // sem.release();
        return "front";
    }

    @GetMapping("/count")
    public String controllerCount(Model model) {
        model.addAttribute("count", counter.getCount());
        return "count";
    }

    @PostMapping("/random1")
<<<<<<< HEAD
    public ArrayList<Long> controllerPost(@RequestBody ArrayList<RandomableEntities> randomableEntitiesArrayList,
                                          @NotNull Model model) {
        counter.incrementCount();
        MyLogger.setLog(Level.INFO, "Successful controller Post");
        return randomService.generateRandomList(randomableEntitiesArrayList);
=======
    public ResponseEntity<?> controllerPost(@RequestBody List<RandomableEntities> randomableEntitiesArrayList) {
        for (int i = 0; i < randomableEntitiesArrayList.size(); i++) {
            counter.incrementCount();
        }
        MyLogger.setLog(Level.INFO, "Successful controller Post");
        return new ResponseEntity<>(randomService.generateRandomList(randomableEntitiesArrayList), HttpStatus.OK);
>>>>>>> ff83f32c041bb96b5785f4d5727916d75c056574
    }
}
