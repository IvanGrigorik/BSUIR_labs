package com.crossplatform.lab1.Controllers;

import com.crossplatform.lab1.Entities.RandomableEntities;
import com.crossplatform.lab1.Logic.RandomLogic;

import com.crossplatform.lab1.MyLogger;
import org.apache.logging.log4j.Level;
import org.jetbrains.annotations.NotNull;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

//import java.util.concurrent.atomic.AtomicLong;

@Controller
public class HomeController {
//    private final AtomicLong counter = new AtomicLong();

    @Autowired
    RandomLogic randomLogic;

    @GetMapping("/random")
    public String controllerGet(@RequestParam(value = "num", defaultValue = "50") long number,
                                @RequestParam(value = "md", defaultValue = "3") int random_mode, @NotNull Model model) {

        // If random_mode == 0 - random less, 1 - random more
        RandomableEntities newEntity = new RandomableEntities(number, random_mode);
        Long result = randomLogic.randomNew(newEntity);

        model.addAttribute("num", number);
        model.addAttribute("md", random_mode);
        model.addAttribute("rnum", result);

        MyLogger.setLog(Level.INFO, "Successful get mapping");

        return "front";
    }
    // DTO - Data transfer object
}
